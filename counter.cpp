#include "counter.h"
#include <QThread>
#include <QDebug>

Counter::Counter(int n, QObject *parent) : QObject(parent), mN(n)
{

}

void Counter::count()
{
    for(int i = 0; i < mN; ++i){
        qDebug() << "count: " << i;
        QThread::sleep(1);
    }
}
