#include "mywidget.h"
#include "ui_mywidget.h"

MyWidgetTest::MyWidgetTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
}

MyWidgetTest::~MyWidgetTest()
{
    delete ui;
}
