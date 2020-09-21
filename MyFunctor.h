#ifndef MYFUNCTOR_H
#define MYFUNCTOR_H

#endif // MYFUNCTOR_H

#include <QString>
#include <QDebug>

class MyFunctor {
public:
    void operator()(const QString& message) {
        qDebug() << "Receive in functor: " << message;
    }
};
