#include "receiver.h"
#include <qdebug.h>

Receiver::Receiver(QObject *parent) : QObject(parent)
{

}

void Receiver::receiveMessage(QString message)
{
    qDebug() << "Receiver receive: " << message;
}
