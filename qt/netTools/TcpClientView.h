#ifndef TCPCLIENTVIEW_H
#define TCPCLIENTVIEW_H

#include <QWidget>
#include <QSettings>
#include <QTcpSocket>

namespace Ui {
class TcpClientView;
}

class TcpClientView : public QWidget
{
    Q_OBJECT
public:
    explicit TcpClientView(QWidget *parent = nullptr);
    ~TcpClientView();

private:
    void Init();
    void RecvData();
    bool SendData(const QByteArray &buf);
    void connetTcp(const QHostAddress &addr, quint16 port);
    void disConnetTcp();

private slots:
    void on_pushButton_clear_clicked();
    void on_pushButton_connect_clicked();
    void on_pushButton_disconnect_clicked();
    void on_pushButton_send_clicked();
    void on_lineEdit_ipaddr_textChanged(const QString &arg1);
    void on_spinBox_port_valueChanged(int arg1);

private:
    Ui::TcpClientView *ui;
    QTcpSocket* socket_;
    QSettings paramIni_;
};

#endif // TCPCLIENTVIEW_H
