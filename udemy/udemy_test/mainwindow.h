#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT  // also needed to create slots

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onPushBtn();
    void onAskPassword();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
