#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QApplication>

#include "algorithms/methodprocessor.h"
#include "algorithms/branchandboundalgorithmprocessor.h"
#include "algorithms/bruteforcesearchalgorithmprocessor.h"
class Core : public QApplication
{
    Q_OBJECT
public:
    Core(int & argc, char ** argv);
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
