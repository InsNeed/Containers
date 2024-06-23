#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QMessageBox>
#include <QMenu>
#include <QWidget>
#include <QDebug>
#include <QStringList>
#include <QList>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QSqlDatabase> // 数据库连接类
#include <QSqlError>    // 错误信息类
#include <QSqlQuery>    //操作类
#include <QDateTime>    // 时间日期类
#include <QTimer>       // 定时器
#include <QPainter>     // 画家类
#include <QTcpServer>   //连接管理类，无IO能力
#include <QTcpSocket>   // 连接类，有IO能力
#include <QTextStream>  // 文本流 qt专用

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString getCurrentTimeByFormat(); // 获取当前时间
    QString read_ipv4_address();      // 获取当前ip

private:
    Ui::MainWindow *ui;
    void timerLcd();         // 设置lcd
    QTimer *timerLcd_1;      // 定时器对象
    int MAXNUM_CONNECT = 20; // 最大连接数量

    QTcpServer *server;                 // 管理对象
    QTcpSocket *socketNewClinet = NULL; // 新连接对象
    QList<QTcpSocket *> clinetList;     // 存储新连接的对象

    QSqlDatabase db;                        // 数据库连接对象
    QString _dbName = "chatServer.db";      // 数据库 名称
    QString _tableNameChat = "chatHistory"; // 表名
    QSqlError _infoErr;                     // 错误信息封装类
    QString _textErr;                       // 提取的错误信息
    QString _sqlCmd;                        // sql命令

    bool initDBServer();                               // 连接到数据库
    void createTable();                                // 建表，或者打开默认表
    void insertData(const QString &, const QString &); // 插入记录
    bool judge_sqlcmd(QString &);                      // 判断是否是sql命令

private slots:
    // 新连接来了的槽函数
    void newConnectSlot();

    // 客户端连接掉线的信号槽
    void disconnetedSlot();

    // 有数据可读时的槽函数
    void readyReadSlot();

    // 设置lcd
    void timeroutLcdSlot();

    // 查询指定数量的记录
    void  selectHistoryNum();

    // 查询 某人 指定数量的记录
    void selectHistoryWho();

    // 清屏
    void pushButtonClearSlot();
};

#endif // MAINWINDOW_H
