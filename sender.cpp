#include "sender.h"
#include <qdebug.h>
#include <QTime>
#include <QTimerEvent>

Sender::Sender(int timeout, QObject *parent) : QObject(parent)
{
    qDebug() << "Sender with timeout: " << timeout;
    startTimer(timeout * 1000); // this method will run this method Sender::timerEvent every timeout * 1000 miliseconds
}

void Sender::timerEvent(QTimerEvent*)
{
    auto message = QTime::currentTime().toString();
    qDebug() << "Send: " << message;
    emit sendMessage(message);
}
