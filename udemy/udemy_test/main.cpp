#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QFont>
#include <QProgressBar>

QPushButton* createPushButton();
QProgressBar* createProgressbar();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QPushButton* btn = createPushButton();
    QProgressBar* proggressBar = createProgressbar();
    btn->show();
    proggressBar->show();

    return a.exec();
}

QPushButton* createPushButton()
{
    QPushButton* btn = new QPushButton("QPushButton Button");
    btn->setText("new caption");
    btn->setToolTip("tooltip");
    QFont MyFont("Arial", QFont::Bold, true);
    btn->setFont(MyFont);
    return btn;
}

QProgressBar* createProgressbar()
{
    QProgressBar* progressbar = new QProgressBar();
    progressbar->setValue(50);
    return progressbar;
}
