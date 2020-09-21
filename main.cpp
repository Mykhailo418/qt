#include "mainwindow.h"

#include <iostream>
#include <QApplication>
#include <QObject>
#include <qdebug.h>
#include <QThread>
#include <QMetaObject>
#include <QMetaMethod>
#include "receiver.h"
#include "sender.h"
#include "MyFunctor.h"
#include "printer.h"
#include <QThreadPool>
#include <QRunnable>
#include <QtConcurrent/QtConcurrent>

void objectsHierarchy();
void typeInformation();
void properties();
void invokable();
int signalsSlots(int argc, char* argv[]);
int threads(int argc, char* argv[]);
int threadPool();
void concurrencyFunc();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    qDebug() << "---- START QOBJECT";
    objectsHierarchy();
    typeInformation();
    properties();
    invokable();
    concurrencyFunc();
    containers();
    qDebug() << "---- END QOBJECT";
    return a.exec(); // run Qt cycle

    // only one QApplication should be created
    //return signalsSlots(argc, argv);
    //return threads(argc, argv);
    //return threadPool();
}

void objectsHierarchy()
{
    qDebug() << "-- Objects Hierarchy:";
    QObject parent; // QObject - main object of Qt that has access to Qt functionality
    parent.setObjectName("parent");

    auto child1 = new QObject(&parent); // QObject instance can not be copied
    (*child1).setObjectName("child1");
    qDebug() << "child1->parent()" << child1->parent();

    auto child2 = new QObject(&parent);
    (*child2).setObjectName("child2");
    delete child1;

    auto child3 = new QObject(&parent);
    (*child3).setObjectName("child3");
}

void typeInformation()
{
    qDebug() << "-- Type Information:";
    QObject obj;
    obj.setObjectName("test");
    qDebug() << obj.metaObject()->className(); // get object class Name
    qDebug() << "inherits('QObject')? " << obj.inherits("QObject"); // check if object inherits from specific class
    qDebug() << "inherits('QLabel')? " << obj.inherits("QLabel");
    QThread* thread = qobject_cast<QThread*>(&obj); // qobject_cast like dynamic_cast but without RTTI
    //Q_ASSERT( thread != nullptr ); // Check that a cast was successfull
    qDebug() << thread;
    qDebug() << qobject_cast<QObject*>(&obj);
}

void properties()
{
    qDebug() << "-- Properties:";
    QObject test;
    test.setObjectName("test");
    qDebug() << test.property("someProperty");
    test.setProperty("someProperty", "cat");
    qDebug() << test.property("someProperty");
}

void invokable()
{
    qDebug() << "-- invokable";
    QObject test;
    bool invokeVal; // here result will be saved
    test.setObjectName("test");
    // QMetaObject::invokeMethod run method of object
    QMetaObject::invokeMethod(&test, "inherits", Qt::DirectConnection, //Qt::AutoConnection - detect connection automatically, Qt::DirectConnection - in the same stream, etc https://doc.qt.io/archives/qtjambi-4.5.2_01/com/trolltech/qt/core/Qt.ConnectionType.html
                              Q_RETURN_ARG(bool, invokeVal),
                              Q_ARG(QString, "QObject"));
    qDebug() << "invokeVal = " << invokeVal;
    int indOfMethod = test.metaObject()->indexOfMethod("inherits(QString)");
    QMetaMethod method = test.metaObject()->method(indOfMethod); // get method in specific object form(QMetaMethod)
    qDebug() << "parameter Types: " << method.parameterTypes(); // get parameter types of method
    qDebug() << "parameter Names: " << method.parameterNames(); // get parameter names of method
}

int signalsSlots(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    Receiver receiver;
    auto sender = new Sender(2, &receiver);

    QObject::connect(sender, &Sender::sendMessage, &receiver, &Receiver::receiveMessage); //  QObject::connect - connect signal method and slot method
    QObject::connect(sender, &Sender::sendMessage, MyFunctor());
    QObject::connect(sender, &Sender::sendMessage, [](QString message) {
        qDebug() << "Receive in lamda: " << message;
    });
    QObject::connect(sender, &Sender::sendMessage, []() {
        qDebug() << "Receive in lamda: ";
    });
    return a.exec();
}

int threads (int argc, char* argv[])
{
    qDebug() << "-- Threads: ";
    QCoreApplication a(argc, argv);
    qDebug() << "Current thread: " << QThread::currentThreadId();
    Printer printer(6);
    QThread thread;
    printer.moveToThread(&thread); // move printer to another thread
    thread.start();
    Sender sender(2);
    //QObject::connect(&sender, &Sender::sendMessage, &printer, &Printer::print); // in this case sender send masseges one by one and  printer print them after 6 seconds according queue of sended messages
    QObject::connect(&sender, &Sender::sendMessage, &printer, &Printer::print, Qt::BlockingQueuedConnection); // here sender will wait until printer finish print message

    return a.exec();
}

int loopFunction(int n)
{
    for(int i = 0; i < n; ++i) {
        qDebug() << "loopFunction: " << i;
        QThread::sleep(1);
    }
    return n * n;
}

class LoopTask : public QRunnable {
    void run() override {
         loopFunction(5);
    }
};

int threadPool()
{
    qDebug() << "-- QThreadPool: ";
    QThreadPool::globalInstance()->start(new LoopTask); // QThreadPool - just if you need to send some task in separate thread and you do not need to get results from them
    loopFunction(2);
    return 0;
}

void concurrencyFunc()
{
    qDebug() << "-- QtConcurrent: ";
    auto future = QtConcurrent::run(loopFunction, 4); // run function in separate thread
    qDebug() << "future.result()" << future.result();
    loopFunction(6);
}

void containers()
{
    qDebug() << "-- Containers: ";
    QList<int> intQlist {3, 4, 5, 1, 4, 4, 1 , 1};
    qDebug() << intQlist.toStdList();
    std::sort(intQlist.begin(), intQlist.end());
    qDebug() << intQlist;

    QListIterator<int> javaUter(intQlist);
    while(javaUter.hasNext()) {
        qDebug() << javaUter.next();
    }
}
