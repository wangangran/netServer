#include "stdafx.h"
#include "TcpClientView.h"
#include "ui_TcpClientView.h"
#include <QHostAddress>

TcpClientView::TcpClientView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpClientView),
    paramIni_(QCoreApplication::applicationDirPath() + QString("/param.ini"), QSettings::IniFormat, this)
{
    ui->setupUi(this);
    Init();
}

TcpClientView::~TcpClientView()
{
    delete ui;
}

void TcpClientView::Init()
{
    socket_ = new QTcpSocket(this);
    if (nullptr == socket_) {
        return;
    }

    connect(socket_, &QTcpSocket::readyRead, this, &TcpClientView::RecvData);

    ui->lineEdit_ipaddr->setText(paramIni_.value("IP").toString());
    ui->spinBox_port->setValue(paramIni_.value("Port").toInt());
}

void TcpClientView::RecvData()
{
    if (nullptr == socket_) {
        return;
    }

    if (QAbstractSocket::ConnectedState != socket_->state()) {
        return;
    }

    QByteArray recvBuf = socket_->readAll();
    ui->textBrowser_recv->insertPlainText(recvBuf);
    ui->textBrowser_recv->insertPlainText("\n");
    ui->textBrowser_recv->moveCursor(QTextCursor::End);
}

bool TcpClientView::SendData(const QByteArray &buf)
{
    if (nullptr == socket_) {
        return false;
    }

    if (QAbstractSocket::ConnectedState != socket_->state()) {
        return false;
    }

    int ret = socket_->write(buf);
    return ret >= 0;
}

void TcpClientView::connetTcp(const QHostAddress &addr, quint16 port)
{
    if (nullptr == socket_) {
        return;
    }

    disConnetTcp();
    socket_->connectToHost(addr, port);
}

void TcpClientView::disConnetTcp()
{
    if (nullptr == socket_) {
        return;
    }

    if (QAbstractSocket::ConnectedState == socket_->state()) {
        socket_->disconnectFromHost();
    }
}

void TcpClientView::on_pushButton_clear_clicked()
{
    ui->textBrowser_recv->clear();
}

void TcpClientView::on_pushButton_connect_clicked()
{
    QHostAddress addr(ui->lineEdit_ipaddr->text());
    quint16 port = ui->spinBox_port->value();
    connetTcp(addr, port);
}

void TcpClientView::on_pushButton_disconnect_clicked()
{
    disConnetTcp();
}

void TcpClientView::on_pushButton_send_clicked()
{
    SendData(ui->lineEdit_send->text().toLatin1());
}

void TcpClientView::on_lineEdit_ipaddr_textChanged(const QString &arg1)
{
    paramIni_.setValue("IP", arg1);
}

void TcpClientView::on_spinBox_port_valueChanged(int arg1)
{
    paramIni_.setValue("Port", arg1);
}

