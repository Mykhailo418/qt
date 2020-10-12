#include "mainwindow.h"

#include <QObject>
#include <QApplication>
#include <QPushButton>
#include <QFont>
#include <QProgressBar>
#include <QLabel>
#include <QFontDialog>

QPushButton* createPushButton(QWidget* parent);
QProgressBar* createProgressbar(QWidget* parent);
void setLabelWithFontDialog(QWidget* parent);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(600, 300);

    QPushButton* btn = createPushButton(&w);
    QProgressBar* proggressBar = createProgressbar(&w);
    QPushButton* btnPassword = new QPushButton("Set Password", &w);
    QPushButton* btnSetFont = new QPushButton("Set Font", &w);
    QPushButton* btnSetColor = new QPushButton("Set Color", &w);

    QLabel* someLabel = new QLabel("some label",  &w);
    w.someLabel = someLabel;

    btn->move(0, 50);
    btnPassword->move(0, 0);
    btnSetFont->move(400, 0);
    btnSetColor->move(0, 25);
    someLabel->move(200, 0);
    proggressBar->setGeometry(150, 130, 150, 40); // set coordinates , width and height

    QObject::connect(btn, &QPushButton::clicked, &w, &MainWindow::onPushBtn);
    QObject::connect(btnPassword, &QPushButton::clicked, &w, &MainWindow::onAskPassword);
    QObject::connect(btnSetFont, &QPushButton::clicked, &w, &MainWindow::setLabelWithFontDialog);
    QObject::connect(btnSetColor, &QPushButton::clicked, &w, &MainWindow::setLabelColor);

    w.show();
//    btn->show();
//    proggressBar->show();

    return a.exec();
}

QPushButton* createPushButton(QWidget* parent)
{
    QPushButton* btn = new QPushButton("QPushButton Button", parent); // set parent to show in parent(window)
    btn->setText("new caption");
    btn->setToolTip("tooltip");
    QFont MyFont("Arial", 12, QFont::Bold, true);
    btn->setFont(MyFont);
    return btn;
}

QProgressBar* createProgressbar(QWidget* parent)
{
    QProgressBar* progressbar = new QProgressBar(parent);
    progressbar->setValue(50);
    return progressbar;
}
