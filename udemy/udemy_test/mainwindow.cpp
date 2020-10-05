#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPushBtn()
{
    int answer = QMessageBox::question(this, "Question", "Yes or No?", QMessageBox::Yes | QMessageBox::No);
    if (answer == QMessageBox::Yes) {
        QMessageBox::information(this, "Information", "Your answer Yes");
    } else if (answer == QMessageBox::No) {
        QMessageBox::information(this, "Information", "Your answer No");
    }
}
