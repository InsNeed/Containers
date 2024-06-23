#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QTcpSocket>
#include <QPushButton>
#include <QString>

namespace Ui
{
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    // 检测 ip输入格式
    static bool isRightInt(QString);

    // 检测输入的IP地址格式的有效性
    static bool isRightFormatIP(QString);

private:
    Ui::Dialog *ui;
    QTcpSocket *client; // 和服务器通信的tcp客户端对象(有IO能力)

private slots:
    // 点击了 连接 按钮
    void btnConnectClickedSlot();

    // 点击了 发送 按钮
    void btnSendClickedSlot();

    // 连接上了 后改变按钮状态
    void connectTcpServerSlot();

    // 连接断开了，改变按钮状态
    void disconnectedTcpServerSlot();

    // 接收到消息了的信号槽
    void readReadSlot();

    // 查询指定数目的历史记录
    void selectNumHistoryClinet();

    // 查询指定数目和姓名的历史记录
    void selectNumWhoHistoryClinet();

    // 清屏 db
    void dbClearScreenSlot();
};

#endif // DIALOG_H
