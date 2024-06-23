#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent),
                                  ui(new Ui::Dialog)
{
    ui->setupUi(this);

    /* 初始化相关 */

    //setWindowFlags(Qt::WindowStaysOnTopHint);不要这个

    // 没连接前不能发送
    ui->pushButtonSend->setEnabled(false);

    // 背景
    //QPalette pal;
    //this->setPalette(pal);

    /*服务器部分*/
    // 建立对象TCP CLINET SOCKET
    client = new QTcpSocket(this);

    //连接 按钮
    connect(ui->pushButtonConnect, SIGNAL(clicked()), this, SLOT(btnConnectClickedSlot()));

    //发送 按钮
    connect(ui->pushButtonSend, SIGNAL(clicked()), this, SLOT(btnSendClickedSlot()));

    //连接上 改变按钮状态
    connect(client, SIGNAL(connected()), this, SLOT(connectTcpServerSlot()));

    //断开连接 改变按钮状态
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnectedTcpServerSlot()));

    //接收消息信号槽
    connect(client, SIGNAL(readyRead()), this, SLOT(readReadSlot()));

    /*网络 查询 数据库*/
    // 查询 ，会自动区分是否有名字
    connect(ui->pushButtonSelect, SIGNAL(clicked()), this, SLOT(selectNumHistoryClinet()));

    // 清屏
    connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(dbClearScreenSlot()));
}

Dialog::~Dialog()
{
    // 失能该信号槽，避免点击关闭按钮的断开弹窗
    disconnect(client, SIGNAL(disconnected()), this, SLOT(disconnectedTcpServerSlot()));

    // 如果还在连接
    if (client->isOpen())
        client->close();

    delete ui;
}

bool Dialog::isRightInt(QString str)
{
    bool isInt;
    int ret = str.toInt(&isInt);
    if (isInt != true)
        return isInt;
    else
    {
        if (ret < 0 || ret > 255)
            return false;
        else
            return true;
    }
}
bool Dialog::isRightFormatIP(QString ip)
{
    QStringList lis1 = ip.split(".");

    // 判断几个部分
    if (lis1.count() != 4)
    {
        qDebug() << "不是4部分";
        return false;
    }

    // 判断每个部分是否是数字
    if (!(isRightInt(lis1.at(0)) && isRightInt(lis1.at(1)) && isRightInt(lis1.at(2)) && isRightInt(lis1.at(3))))
    {
        qDebug() << "不是每个部分都是正确数字";
        return false;
    }

    return true;
}

// 点击了 连接 按钮
void Dialog::btnConnectClickedSlot()
{
    QString ip = ui->lineEdit_IP->text();
    if (!isRightFormatIP(ip))
    {
        QMessageBox::warning(this, "警告", "ip地址格式不对");
        return;
    }

    bool ok;
    QString portText = ui->lineEdit_PORT->text();
    quint16 port = portText.toInt(&ok);
    if (!ok)
    {
        QMessageBox::warning(this, "警告", "port转换错误");
        return;
    }

    // 发起连接请求
    client->connectToHost(ip, port);
    if (!client->waitForConnected(3000))
    {
        QMessageBox::warning(this, "警告", "超时连接失败");

        ui->pushButtonConnect->setEnabled(true);
        ui->pushButtonConnect->setText("再次连接");

        return;
    }
}

// 点击了 发送 按钮
void Dialog::btnSendClickedSlot()
{

    // 获得昵称和消息内容
    QString name = ui->lineEdit_name->text();
    QString talk = ui->lineEdit_inpuit->text();
    if (name == "")
    {
        QMessageBox::warning(this, "提示", "请输入昵称！");
        return;
    }
    if (talk == "")
    {
        QMessageBox::warning(this, "提示", "请输入要发送的消息！");
        return;
    }

    // 最终内容
    QString msg = name.append(":").append(talk);

    // 创建文本流对象，并发送
    QTextStream output(client);

    // 连续输出发送 //u ser << ":" << msg
    output << msg;

    // 清空消息输入框
    ui->lineEdit_inpuit->clear();

    // 公屏显示
    msg.prepend("(我)");
    qDebug() << msg;
    ui->textBrowser->append(msg);
}

// 连接上了 后改变按钮状态
void Dialog::connectTcpServerSlot()
{
    // 屏蔽连接按钮，开启发送按钮
    ui->pushButtonConnect->setEnabled(false);
    ui->pushButtonConnect->setText("已连接");
    ui->pushButtonSend->setEnabled(true);
}

// 连接断开了，改变按钮状态
void Dialog::disconnectedTcpServerSlot()
{
    // 开启连接按钮，屏蔽发送按钮
    ui->pushButtonConnect->setEnabled(true);
    ui->pushButtonConnect->setText("再次连接");
    ui->pushButtonSend->setEnabled(false);

    qDebug() << "连接已断开！";
    ui->textBrowser->append("连接已断开！");
    QMessageBox::warning(this, "提示", "连接已断开！");
}

// 接收到消息了的信号槽
void Dialog::readReadSlot()
{
    QTextStream input(client);
    QString text = input.readAll();
    qDebug() << text;

    if (text.at(0) == '(' && text.at(2) == ')')
    {
        ui->textBrowserDB->append(text);
    }
    else
    {

        ui->textBrowser->append(text);
    }
}

// 查询指定数目的历史记录
void Dialog::selectNumHistoryClinet()
{
    // 如果没有连接
    if (!client->isOpen())
    {
        QMessageBox::warning(this, "提示", "先连接网络");
        qDebug() << "先连接网络";
        return;
    }

    // 可能存在的名字
    QString name = ui->lineEdit_inpuitName->text();

    // 要查询的数量
    QString numText = ui->spinBoxNum->text();

    // 拼装的命令
    QString sqlCmd = "";

    if (name.isEmpty())
    {
        // 拼装命令，只有个数
        sqlCmd = "[sql],[num]";
        sqlCmd.replace("[sql]", "selectNum");
        sqlCmd.replace("[num]", numText);
    }
    else
    {
        // 拼装命令,带名字
        sqlCmd = "[sql],[num],[name]";
        sqlCmd.replace("[sql]", "selectNumWho");
        sqlCmd.replace("[num]", numText);
        sqlCmd.replace("[name]", name);
    }

    qDebug() << "要发送的命令" << sqlCmd;

    QTextStream output(client);
    output << sqlCmd;
}

// 查询指定数目和姓名的历史记录
void Dialog::selectNumWhoHistoryClinet()
{
    // 如果没有连接
    if (!client->isOpen())
    {
        QMessageBox::warning(this, "提示", "先连接网络");
        qDebug() << "先连接网络";
        return;
    }

    // 要查询的数量
    QString numText = ui->spinBoxNum->text();
    // 要查询的名字
    QString name = ui->lineEdit_name->text();

    // 拼装命令
    QString sqlCmd = "[sql],[num],[name]";
    sqlCmd.replace("[sql]", "selectNumWho");
    sqlCmd.replace("[num]", numText);
    sqlCmd.replace("[name]", name);
    qDebug() << sqlCmd;

    QTextStream output(client);
    output << sqlCmd;
}

void Dialog::dbClearScreenSlot()
{
    ui->textBrowserDB->clear();
}
