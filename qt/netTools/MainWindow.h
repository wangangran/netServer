#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainHead;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow* getMainWindow();
private:
    Ui::MainWindow *ui;
    QWidget*    baseWidget_ = nullptr;
    MainHead*	pHeadWidget_ = nullptr;
    QStackedWidget* pStackPages_ = nullptr;
};
#endif // MAINWINDOW_H
