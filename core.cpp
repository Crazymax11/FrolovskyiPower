#include "core.h"
#include <QDebug>
Core::Core(QObject *parent) : QObject(parent)
{
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject* root = engine.rootObjects()[0];
    bruteForceProcessor = new BruteForceSearchAlgorithmProcessor();
    branchProcessor = new BranchAndBoundAlgorithmProcessor();
    QObject::connect(root,SIGNAL(start(QString,QString)),this,SLOT(start(QString,QString)));

    QObject::connect(this,SIGNAL(startBruteForce(QList<QPair<qreal,qreal> >)),
                     bruteForceProcessor,SLOT(start(QList<QPair<qreal,qreal>>)));
    QObject::connect(bruteForceProcessor,SIGNAL(done(QList<QPair<qreal,qreal> >)),
                     this,SLOT(bruteForceDone(QList<QPair<qreal,qreal> >)));

    QObject::connect(branchProcessor,SIGNAL(done(QList<QPair<qreal,qreal> >)),
                     this,SLOT(bruteForceDone(QList<QPair<qreal,qreal> >)));

    namesToMethods["Метод прямого исчерпывающего перебора вариантов"] = bruteForceProcessor;
    namesToMethods["Метод ветвей и границ"]=branchProcessor;
}
Core::~Core(){
    delete bruteForceProcessor;
    delete branchProcessor;
}

void Core::start(QString methodName, QString data)
{
    QList < QPair <qreal,qreal > > points;
    QStringList rawPoints = data.split(";");
    QString temp;
    foreach(temp, rawPoints){
        if (!temp.isEmpty()){
            QStringList xy = temp.split("!");
            points.append(QPair<qreal,qreal> (xy[0].toDouble(), xy[1].toDouble()));
        }
    }
    namesToMethods[methodName]->start(points);
}

void Core::bruteForceDone(QList<QPair<qreal, qreal>> route){
    qDebug() << "done";
}
