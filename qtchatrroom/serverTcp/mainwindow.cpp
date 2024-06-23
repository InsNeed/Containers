#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*配置部分*/
    //setWindowFlags(Qt::WindowStaysOnTopHint);
    // 显示ip
    ui->label_ip->setText(read_ipv4_address());
    // lcd
    timerLcd();

    /*TCP server 部分*/
    // 建立管理对象
    server = new QTcpServer(this);

    // 连接新连接来了的信号槽
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnectSlot()));

    // 开启监听服务
    server->listen(QHostAddress::Any, 8887);

    /*数据库部分*/
    initDBServer(); // 连接到DB库
    createTable();  // 建表，或者打开默认表

    // 点击查询 指定条数的
    connect(ui->pushButtonNum, SIGNAL(clicked()), this, SLOT(selectHistoryNum()));

    // 点击查询 某人 指定条数的
    connect(ui->pushButtonWhoNum, SIGNAL(clicked()), this, SLOT(selectHistoryWho()));

    // 清屏
    connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(pushButtonClearSlot()));
}

MainWindow::~MainWindow()
{
    // 如果还在监听
    if (server->isListening())
        server->close();

    // 从列表删除；不确定是否自动回收，那就手动释放
    for (int i = 0; i < clinetList.size(); i++)
        clinetList.removeAt(i); // 从列表删除

    // lcd timer
    if (timerLcd_1->isActive()) // 如果正在运行，则先关闭
        timerLcd_1->stop();
    delete timerLcd_1; // 销毁

    delete ui;
}

void MainWindow::newConnectSlot()
{
    // 获得服务器端的连接类对象
    socketNewClinet = server->nextPendingConnection();

    // 给新对象发消息
    QTextStream output(socketNewClinet);

    // 如果满员则踢出
    if (clinetList.size() == MAXNUM_CONNECT)
    {
        qDebug() << "聊天室满员";
        output << QString("聊天室已达人数上限，连接失败！");
        socketNewClinet->close();
        return;
    }
    else
    {
        // 加入列表
        clinetList.append(socketNewClinet);
    }

    // 收到 新客户端 消息的信号槽
    connect(socketNewClinet, SIGNAL(readyRead()), this, SLOT(readyReadSlot()));

    //  新客户端 掉线的信号槽
    connect(socketNewClinet, SIGNAL(disconnected()), this, SLOT(disconnetedSlot()));

    // 提示、给客户端打个招呼、
    output << QString("服务器：你好啊！");

    // 获得对面的IP地址和端口号
    QString ip = socketNewClinet->peerAddress().toString();
    quint16 portNum = socketNewClinet->peerPort();
    QString portText = QString::number(portNum);

    // 显示在公屏上
    QString text = "新对象加入聊天室";
    text.append(ip).append(":").append(portText);
    qDebug() << text;
    ui->textBrowser->append(text);
}

void MainWindow::disconnetedSlot()
{
    // 拿到发射者
    socketNewClinet = (QTcpSocket *)sender();

    for (int i = 0; i < clinetList.size(); i++)
    {
        if (socketNewClinet == clinetList.at(i))
        {
            qDebug() << "第" << i << "个客户端掉线了";

            // 获得 掉线客户端的 IP地址和端口号
            QString ip = clinetList.at(i)->peerAddress().toString();
            quint16 portNum = clinetList.at(i)->peerPort();
            QString portText = QString::number(portNum);

            // 提示
            QString text = "连接已断开！";
            text.append(ip).append(":").append(portText);

            qDebug() << text;
            ui->textBrowser->append(text);

            // 从列表删除
            clinetList.removeAt(i);
        }
    }
}

void MainWindow::readyReadSlot()
{
    for (int i = 0; i < clinetList.size(); i++)
    {
        // 只对当下真发消息的，才能检测到
        if (clinetList.at(i)->isReadable() && clinetList.at(i)->bytesAvailable() > 0)
        {

            QTextStream input(clinetList.at(i));
            QString text = input.readAll(); // 一口气都读了
            qDebug() << text;

            /*如果是查询命令，则执行，若不是，则继续*/
            if (judge_sqlcmd(text) == true)
            {
                qDebug() << "客户端进行了查询命令";
                ui->textBrowser->append("客户端进行了查询命令");

                QStringList list = text.split(",");
                QTextStream output(clinetList.at(i));

                // 只是数量
                if (list.size() == 2)
                {
                    QString numText = list[1];
                    qDebug() << "客户端要查询指定" << numText << "条聊天记录";
                    _sqlCmd = "SELECT * FROM [tableName] order by time desc LIMIT [tableNum]";

                    _sqlCmd.replace("[tableName]", _tableNameChat);
                    _sqlCmd.replace("[tableNum]", numText);
                    qDebug() << "查询命令为" << _sqlCmd;

                    QSqlQuery _sqOpt;

                    if (_sqOpt.exec(_sqlCmd))
                    {
                        QString serialNum = "(?)"; // 序号
                        int i = 0;

                        while (_sqOpt.next())
                        {
                            serialNum.replace(1, 1, QString::number(i++)); // 编号
                            QString time = _sqOpt.value(0).toString();     // 时间
                            QString name = _sqOpt.value(1).toString();     // 姓名
                            QString talk = _sqOpt.value(2).toString();     // 对话

                            QString ret = serialNum + " " + time + " " + name + " " + talk;
                            output << ret << endl; // 发回去
                        }
                    }
                }
                // 名字和数量
                else if (list.size() == 3)
                {
                    QString numText = list[1];
                    QString name = list[2];

                    qDebug() << "客户端要查询" << name << "指定" << numText << "条聊天记录";

                    _sqlCmd = "SELECT * FROM [tableName] where name=\"[name]\" order by time desc;";

                    _sqlCmd.replace("[tableName]", _tableNameChat);
                    _sqlCmd.replace("[tableNum]", numText);
                    _sqlCmd.replace("[name]", name);
                    qDebug() << "查询命令为" << _sqlCmd;

                    QSqlQuery _sqOpt;

                    if (_sqOpt.exec(_sqlCmd))
                    {
                        QString serialNum = "(?)"; // 序号
                        int i = 0;

                        while (_sqOpt.next())
                        {
                            serialNum.replace(1, 1, QString::number(i++)); // 编号
                            QString time = _sqOpt.value(0).toString();     // 时间
                            QString name = _sqOpt.value(1).toString();     // 姓名
                            QString talk = _sqOpt.value(2).toString();     // 对话

                            QString ret = serialNum + " " + time + " " + name + " " + talk;
                            output << ret << endl; // 发回去
                        }
                    }
                }

                break;
            }


            qDebug() << "第" << i << "个客户端发的消息";
            ui->textBrowser->append(MainWindow::getCurrentTimeByFormat());
            ui->textBrowser->append(text);

            // 转发给其他客户端，除了发的人
            for (int m = 0; m < clinetList.size(); m++)
            {
                if (m == i)
                    continue;

                QTextStream output(clinetList.at(m));
                output << text; // 消息格式是  姓名+正文
            }

            // 分割，然后插入数据库
            QStringList list = text.split(":");
            insertData(list[0], list[1]);
        }
    }
}

void MainWindow::timeroutLcdSlot()
{
    // 获得当前时间
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
    // 设置显示
    ui->lcdNumber->display(time);
}

QString MainWindow::getCurrentTimeByFormat()
{
    QDateTime dt = QDateTime::currentDateTime();
    QString fdt = dt.toString("yyyy/MM/dd hh时mm分ss秒");
    return fdt;
}

QString MainWindow::read_ipv4_address()
{
    QString ip_address;

    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if ((ipAddressesList.at(i) != QHostAddress::LocalHost) && ipAddressesList.at(i).toIPv4Address())
        {
            ip_address = ipAddressesList.at(i).toString();

            qDebug() << "get  " << ip_address; // debug

            if (ip_address.startsWith("192.168", Qt::CaseSensitive))
            {
                qDebug() << "找到192.168的开头" << ip_address; // debug
                return ip_address;
            }
        }
    }

    // 没有能用的地址，就返回 回环地址
    if (ip_address.isEmpty())
        ip_address = QHostAddress(QHostAddress::LocalHost).toString();

    return ip_address;
}

void MainWindow::timerLcd()
{
    // 刷新时间
    timeroutLcdSlot();

    // 创建定时器对象
    timerLcd_1 = new QTimer(this);

    // 设置定时器参数（时间、一次性）
    timerLcd_1->setInterval(1000);
    timerLcd_1->setSingleShot(false);

    // 连接信号槽
    connect(timerLcd_1, SIGNAL(timeout()), this, SLOT(timeroutLcdSlot()));

    // 启动定时器
    timerLcd_1->start();

    // 刷新
    timeroutLcdSlot();
}

bool MainWindow::initDBServer()
{
    // 创建去连接数据库的对象
    db = QSqlDatabase::addDatabase("QSQLITE");

    // 要 打开 或者 创建 的数据库 名称
    db.setDatabaseName(_dbName);

    // 打开数据库连接
    if (db.open())
    {
        qDebug() << "连接并打开数据库成功";
        return true;
    }
    else
    {
        _infoErr = db.lastError();
        _textErr = _infoErr.text();
        QMessageBox::critical(this, "错误", _textErr);

        return false;
    }
}

void MainWindow::createTable()
{
    // 建表语句
    _sqlCmd = QString("CREATE TABLE %1(time TEXT PRIMARY KEY,name TEXT,talk TEXT);"\
                      ).arg(_dbName);

    QSqlQuery _sqlOpt; // 操作对象

    // 是否成功执行创建表命令
    if (_sqlOpt.exec(_sqlCmd))
    {
        qDebug() << "第一回建表成功";
    }
    else
    {
        _infoErr = _sqlOpt.lastError();
        _textErr = _infoErr.text();
        qDebug() << "建表失败，可能已经存在。具体信息为>" << _textErr;
    }
}

void MainWindow::insertData(const QString &name, const QString &talk)
{
    // 预处理的SQL语句
    _sqlCmd = "INSERT INTO chatHistory VALUES(?,?,?)";

    // 操作对象
    QSqlQuery _sqOpt;

    // 预处理，会与exec绑定为默认执行的语句
    _sqOpt.prepare(_sqlCmd);

    // 绑定参数 （ODBC风格）
    // 按照顺序，不然失败
    _sqOpt.addBindValue(MainWindow::getCurrentTimeByFormat());
    _sqOpt.addBindValue(name);
    _sqOpt.addBindValue(talk);

    // 执行绑定后的SQL语句
    if (_sqOpt.exec()) // 成功
    {
        qDebug() << "数据插入成功" << name << talk;
    }
    else // 失败
    {
        _infoErr = _sqOpt.lastError();
        _textErr = _infoErr.text();

        _textErr.prepend("数据插入命令执行失败!");

        QMessageBox::warning(this, "通知", _textErr);
    }
}

bool MainWindow::judge_sqlcmd(QString &text)
{
    bool flag_return = false;

    QString cmd_selectNum = "selectNum";
    QString cmd_selectNumName = "selectNumWho";

    // 数量
    if (text.contains(cmd_selectNum))
        flag_return = true;

    // 数量 和 名字
    if (text.contains(cmd_selectNumName))
        flag_return = true;

    return flag_return;
}

void MainWindow::selectHistoryNum()
{
    int index = ui->spinBoxNum->value();
    qDebug() <<"index："<< index;
    qDebug() << "要查询指定" << index << "条聊天记录";
    _sqlCmd = QString("SELECT * FROM %1 order by time desc LIMIT %2")\
            .arg(_tableNameChat,QString::number(index));

//    _sqlCmd.replace("[tableName]", _tableNameChat);
//    _sqlCmd.replace("[tableNum]", QString::number(index));
    qDebug() << "查询命令为" << _sqlCmd;

    QSqlQuery _curQueryResult;

    if (_curQueryResult.exec(_sqlCmd))
    {
        int i = 0;

        while (_curQueryResult.next())
        {
            QString serialNum = QString("(%1)").arg(QString(++i));
            QString time = _curQueryResult.value(0).toString();     // 时间
            QString name = _curQueryResult.value(1).toString();     // 姓名
            QString talk = _curQueryResult.value(2).toString();     // 对话

            QString ret = serialNum + " " + time + " " + name + " " + talk;

            qDebug() << ret;
            ui->textBrowser_db->append(ret);
        }
    }
}

void MainWindow::selectHistoryWho()
{
    QString name = ui->lineEditWho->text();
    int recordQuantity = ui->spinBoxNum_who->value();
    qDebug() << "要查询指定" << recordQuantity << "条聊天记录";

    _sqlCmd = "SELECT * FROM [tableName] where name=\"[name]\" order by time desc;";
    _sqlCmd.replace("[tableName]", _tableNameChat);
    _sqlCmd.replace("[name]", name);

    qDebug() << _sqlCmd;

    QSqlQuery _sqOpt;

    if (_sqOpt.exec(_sqlCmd))
    {
        int i = 0;

        while (_sqOpt.next() && (i < recordQuantity))
        {
            QString serialNum = QString("(%1)").arg(QString(++i));//编号
            QString time = _sqOpt.value(0).toString();     // 时间
            QString name = _sqOpt.value(1).toString();     // 姓名
            QString talk = _sqOpt.value(2).toString();     // 对话

            QString ret = serialNum + " " + time + " " + name + " " + talk;

            qDebug() << ret;
            ui->textBrowser_db->append(ret);
        }
    }
}

void MainWindow::pushButtonClearSlot()
{
    ui->textBrowser_db->clear();
}
