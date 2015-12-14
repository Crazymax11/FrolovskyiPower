#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QQmlApplicationEngine>

#include "methodprocessor.h"
#include "dynamicprogrammicalgorithmprocessor.h"
#include "geneticalgorithmprocessor.h"
#include "branchandboundalgorithmprocessor.h"
#include "bruteforcesearchalgorithmprocessor.h"
#include "antcolonyalgorithmprocessor.h"
#include "simulatedannealingprocessor.h"
class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = 0);
    ~Core();
signals:
    void startBruteForce(QList<QPair<qreal,qreal>>);
public slots:
    void start(QString methodName, QString data);
private slots:
    void bruteForceDone(QList<QPair<qreal,qreal>>);
private:
    QQmlApplicationEngine engine;
    BruteForceSearchAlgorithmProcessor* bruteForceProcessor;
    BranchAndBoundAlgorithmProcessor* branchProcessor;
    QList<MethodProcessor*> methods;
    QMap<QString, MethodProcessor*> namesToMethods;
};

#endif // CORE_H
