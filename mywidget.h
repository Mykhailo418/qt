#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

namespace Ui {
class MyWidget;
}

class MyWidgetTest : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidgetTest(QWidget *parent = nullptr);
    ~MyWidgetTest();

private:
    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
