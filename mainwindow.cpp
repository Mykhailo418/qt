#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QDebug>
#include <QThread>
#include <QObject>
#include <QPushButton>
#include "counter.h"
#include <QFileSystemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // setup ui form from Forms/mainwindow.ui
    setStyleSheet("QPushButton { color: blue}"
                  "QLabel {color: blue}"
                  "QRadioButton {color: blue}");
    setupFileSystem();

    // --- Setup Custom Ui ---
//    resize(600, 400);

//    auto rootWidget = new QWidget();
//    setCentralWidget(rootWidget);

//    mLabel = new QLabel("Label Label:", rootWidget);
//    mLabel->move(0, 10);
//    auto worldButton = new QPushButton("World", rootWidget);
//    worldButton->move(50, 50);

//    auto helloButton = new QPushButton("Hello", rootWidget);
//    helloButton->move(100, 100);

//    auto someWidget = new QWidget(rootWidget);
//    someWidget->move(150, 150);
//    auto childLabel = new QLabel("Child Label", someWidget);
//    childLabel->move(10, 10);
//    qDebug() << "childLabel->pos(): " << childLabel->pos();
//    qDebug() << "childLabel->mapToGlobal({0, 0}): " << childLabel->mapToGlobal({0, 0}); // get position of element according global window

//    connect(worldButton, &QPushButton::clicked, [this]() { // after clicking on worldButton mLabel will change text
//       mLabel->setText("World");
//    });
//    connect(helloButton, &QPushButton::clicked, this, &MainWindow::setLabelTextFromButton);

//    auto counter = new Counter(10);
//    auto mCounterThread = new QThread(this);
//    counter->moveToThread(mCounterThread); // if remove this line, while counter works you can not do anything with interface
//    connect(worldButton, &QPushButton::clicked, counter, &Counter::count);
//    mCounterThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLabelTextFromButton()
{
    auto button = qobject_cast<QPushButton*>(QObject::sender()); // QObject::sender - get object that has send a signal
    mLabel->setText(button->text());
}

void MainWindow::setupFileSystem()
{
    auto fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath(QDir::rootPath());
    fileSystemModel->setReadOnly(false);

    ui->listView->setModel(fileSystemModel);
    ui->listView->setRootIndex(fileSystemModel->index(QDir::homePath()));

    //ui->tableView->setModel(fileSystemModel);
    //ui->tableView->setRootIndex(fileSystemModel->index(QDir::homePath()));
}

void MainWindow::onPushButtonCLicked()
{
    //auto text = mDisplsyWithTooltipModel->index(1, 0, QModelIndex()).data().toString();
    //mDisplsyWithTooltipModel->addDisplayWithTooltip({text: "Dog"});
}
