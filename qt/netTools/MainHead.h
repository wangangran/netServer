#ifndef MAINHEAD_H
#define MAINHEAD_H

#include <QtWidgets>

class QLabel;
class QPushButton;
class QButtonGroup;
class MainHead : public QFrame
{
    Q_OBJECT
public:
    explicit MainHead(QWidget *parent = nullptr);

    int currentCheckedId() const;
    void setPixmap(QPixmap pixmap);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    bool eventFilter(QObject *obj, QEvent *e) override;
    void paintEvent(QPaintEvent* e) override;

signals:
    void signalCheckUpdate();

public slots:
    void handleMinimizeBtnClicked();
    void handleMaximizeBtnClicked();
    void handleRestoreBtnClicked();
    void handleCloseBtnClicked();
private:
    QPushButton* minimize_;
    QPushButton* maximize_;
    QPushButton* restore_;
    QPushButton* close_;
    QButtonGroup* btnGroup_;


    QPixmap* pixmap_ = nullptr;
    QPixmap* scaledpixmap_ = nullptr;
    QImage* cachedimage_ = nullptr;

    bool  move = false;
    QPoint startPoint;
    QPoint windowStartPonit;

};

#endif // MAINHEAD_H
