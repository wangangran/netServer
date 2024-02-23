#include "stdafx.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <MainHead.h>
#include <TcpClientView.h>

static MainWindow* g_MainWindow = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    g_MainWindow = this;
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    baseWidget_ = new QWidget();
    pHeadWidget_ = new MainHead(baseWidget_);

    pStackPages_ = new QStackedWidget(baseWidget_);
    TcpClientView* tcpClientView = new TcpClientView(baseWidget_);
    pStackPages_->addWidget(tcpClientView);
    pStackPages_->setCurrentIndex(0);

    QLabel* line1 = new QLabel(baseWidget_);
    line1->setFixedHeight(1);
    line1->setStyleSheet("background:#d6d8dd");

    QVBoxLayout* full = new QVBoxLayout;
    full->setContentsMargins(0, 0, 0, 0);
    full->setSpacing(0);
    full->addWidget(pHeadWidget_);
    full->addWidget(line1);
    full->addWidget(pStackPages_);
    baseWidget_->setLayout(full);

    baseWidget_->setMinimumSize(600, 600);
    this->resize(600, 600);

    this->setCentralWidget(baseWidget_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow *MainWindow::getMainWindow()
{
    return g_MainWindow;
}

