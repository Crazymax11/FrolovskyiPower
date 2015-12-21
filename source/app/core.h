#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QThread>
#include <QSignalMapper>
#include <QTIme>
#include "algorithms/methodprocessor.h"
#include "algorithms/branchandboundalgorithmprocessor.h"
#include "algorithms/bruteforcesearchalgorithmprocessor.h"
#include "algorithms/antcolonyalgorithmprocessor.h"
class Core : public QApplication
{
    Q_OBJECT
public:
    Core(int & argc, char ** argv);
    ~Core();
signals:
    void startBruteForce(QList<City>);
    void startBranches(Cities);
    void startAntColony(Cities);
public slots:
    void start(QString methodName, QVariant data);
private slots:
    void showPath(QList<City>, QString name);
    void done(Cities route,QString methodName);

    void bruteFroceDone(Cities);
    void branchesDone(Cities);
    void antColonyDone(Cities);

    void showBruteForcePath(Cities);
    void showBranchesPath(Cities);
    void showAntColonyPath(Cities);
private:
    QQmlApplicationEngine engine;
    BruteForceSearchAlgorithmProcessor* bruteForceProcessor;
    BranchAndBoundAlgorithmProcessor* branchProcessor;
    antColonyAlgorithmProcessor* antProcessor;
    QList<MethodProcessor*> methods;
    QList<QThread*> workerThreads;
    QMap<QString, MethodProcessor*> namesToMethods;
    QMap<QString, QObject*> btns;

    QSignalMapper finishSignalsaMapper;
    QObject* root;
    QObject* map;
    QMap<QString, QString> textResults;
    QMap<QString, QTime> startTimes;
};

#endif // CORE_H
