#include "stdafx.h"
#include "MainHead.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QEvent>
#include <QDebug>
#include <QApplication>
#include <MainWindow.h>

MainHead::MainHead(QWidget* parent) : QFrame(parent)
{
    setObjectName("MainHead");
    setAutoFillBackground(true);
    this->setPalette(QPalette(QColor("#505050")));


    QWidget* root = this;
    while (root->parentWidget()) {
        root = root->parentWidget();
    }
        root->installEventFilter(this);

    QVBoxLayout* col = new QVBoxLayout;
    col->setContentsMargins(0, 0, 0, 0);
    col->setSpacing(0);
    {
        minimize_ = new QPushButton(this);
        minimize_->setObjectName("TitleMinimezeBtn");
        minimize_->setFixedSize(18, 18);
        minimize_->setToolTip(tr("最小化"));

        maximize_ = new QPushButton(this);
        maximize_->setObjectName("TitleMaximizeBtn");
        maximize_->setFixedSize(18, 18);
        maximize_->setToolTip(tr("最大化"));

        restore_ = new QPushButton(this);
        restore_->setObjectName("TitleRestoreBtn");
        restore_->setFixedSize(18, 18);
        restore_->hide();

        close_ = new QPushButton(this);
        close_->setObjectName("TitleCloseBtn");
        close_->setFixedSize(18, 18);
        close_->setToolTip(tr("关闭"));

        QHBoxLayout* row = new QHBoxLayout;
        row->setContentsMargins(0, 0, 0, 0);
        row->setSpacing(2);
        {
            row->addStretch();
            row->addWidget(minimize_);
            row->addWidget(maximize_);
            row->addWidget(restore_);
            row->addWidget(close_);
            row->addStretch();
        }

        col->addLayout(row);
        col->addStretch();
        col->addStretch();
    }

    QHBoxLayout* row = new QHBoxLayout(this);
    row->setContentsMargins(0, 0, 0, 0);
    row->setSpacing(0);
    row->addStretch(1);
    row->addLayout(col);
    row->addSpacing(10);

    setFixedHeight(80);

    connect(minimize_, &QPushButton::clicked, this, &MainHead::handleMinimizeBtnClicked);
    connect(maximize_, &QPushButton::clicked, this, &MainHead::handleMaximizeBtnClicked);
    connect(restore_, &QPushButton::clicked, this, &MainHead::handleRestoreBtnClicked);
    connect(close_, &QPushButton::clicked, this, &MainHead::handleCloseBtnClicked);
}

int MainHead::currentCheckedId() const
{
    return btnGroup_->checkedId();
}

void MainHead::setPixmap(QPixmap pixmap)
{
    pixmap_ = new QPixmap(pixmap);

    delete scaledpixmap_;
    scaledpixmap_ = nullptr;
    update();
}

void MainHead::mousePressEvent(QMouseEvent* event)
{
    if (Qt::LeftButton == event->button()) {
        startPoint = event->globalPos();
        windowStartPonit = MainWindow::getMainWindow()->frameGeometry().topLeft();
        move = true;
    }
}

void MainHead::mouseReleaseEvent(QMouseEvent* event)
{
    if (Qt::LeftButton == event->button()) {
        move = false;
    }
}

void MainHead::mouseMoveEvent(QMouseEvent* event)
{
    if ((event->buttons() & Qt::LeftButton) && move)
    {
        QPoint relativePos = event->globalPos() - startPoint;
        MainWindow::getMainWindow()->move(windowStartPonit + relativePos);
    }
}

bool MainHead::eventFilter(QObject* obj, QEvent* e)
{
    if (e->type() == QEvent::ParentChange) {
        QWidget* root = parentWidget();
        while (root->parentWidget())
            root = root->parentWidget();
        root->installEventFilter(this);
        obj->removeEventFilter(this);
    }
    else if (e->type() == QEvent::WindowStateChange) {
        Qt::WindowStates state = window()->windowState();
        switch (state) {
        case Qt::WindowMaximized: {
            maximize_->hide();
            restore_->show();
            QEvent e(QEvent::Leave);
            QApplication::sendEvent(restore_, &e);
            break;
        }
        case Qt::WindowNoState: {
            restore_->hide();
            maximize_->show();
            QEvent e(QEvent::Leave);
            QApplication::sendEvent(maximize_, &e);
            break;
        }
        }
    }

    return false;
}

void MainHead::paintEvent(QPaintEvent* e)
{
    QFrame::paintEvent(e);

    if (pixmap_ && !pixmap_->isNull()) {
        QSize scaledSize = contentsRect().size() * devicePixelRatioF();
        if (!scaledpixmap_ || scaledpixmap_->size() != scaledSize) {
            delete  cachedimage_;
            cachedimage_ = new QImage(pixmap_->copy(0, 0, pixmap_->width(), (int)((qreal)pixmap_->width() / rect().width() * height())).toImage());

            QImage scaledImage = cachedimage_->scaled(scaledSize,
                Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

            delete scaledpixmap_;
            scaledpixmap_ = new QPixmap(QPixmap::fromImage(scaledImage));
            scaledpixmap_->setDevicePixelRatio(devicePixelRatioF());
        }
        QPainter p(this);
        p.drawPixmap(scaledpixmap_->rect(), *scaledpixmap_, scaledpixmap_->rect());
    }
}


void MainHead::handleMinimizeBtnClicked()
{
    window()->showMinimized();
}

void MainHead::handleMaximizeBtnClicked()
{
    window()->showMaximized();
}

void MainHead::handleRestoreBtnClicked()
{
    window()->showNormal();
}

void MainHead::handleCloseBtnClicked()
{
    qApp->exit();
}
