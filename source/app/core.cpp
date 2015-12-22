#include "core.h"
#include <QDebug>
#include <QQmlApplicationEngine>
#include "core.h"
Core::Core(int & argc, char ** argv): QApplication(argc,argv)
{
    //setWindowIcon(QIcon(QPixmap("ico.ico")));
    qRegisterMetaType<Cities>("Cities");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    root = engine.rootObjects()[0];
    map = root->findChild<QObject*>("map");
    bruteForceProcessor = new BruteForceSearchAlgorithmProcessor();
    branchProcessor = new BranchAndBoundAlgorithmProcessor();
    antProcessor = new antColonyAlgorithmProcessor();
    QObject::connect(root,SIGNAL(start(QString,QVariant)),this,SLOT(start(QString,QVariant)));


    QObject::connect(bruteForceProcessor,SIGNAL(newBestFound(QList<City>)),
                     this,SLOT(showBruteForcePath(Cities)));
    QObject::connect(branchProcessor,SIGNAL(newBestFound(QList<City>)),
                     this,SLOT(showBranchesPath(Cities)));
    QObject::connect(antProcessor,SIGNAL(newBestFound(QList<City>)),
                     this,SLOT(showAntColonyPath(Cities)));

    namesToMethods["Перебор"] = bruteForceProcessor;
    namesToMethods["Ветви и границы"]=branchProcessor;
    namesToMethods["Муравьи"]=antProcessor;

    btns["Перебор"] = root->findChild<QObject*>("bruteForceBtn");
    btns["Ветви и границы"] = root->findChild<QObject*>("branchBtn");
    btns["Муравьи"] = root->findChild<QObject*>("antBtn");
    textResults["Перебор"]="bruteForceResult";
    textResults["Ветви и границы"]="branchedResult";
    textResults["Муравьи"]="antColonyResult";
    workerThreads.append(new QThread());
    workerThreads.append(new QThread());
    workerThreads.append(new QThread());
    bruteForceProcessor->moveToThread(workerThreads[0]);
    branchProcessor->moveToThread(workerThreads[1]);
    antProcessor->moveToThread(workerThreads[2]);
    for(int i =0;i<workerThreads.size();i++)
        workerThreads[i]->start();

    QObject::connect(this,SIGNAL(startBruteForce(Cities)),
                     bruteForceProcessor,SLOT(start(Cities)));
    QObject::connect(this,SIGNAL(startBranches(Cities)),
                     branchProcessor,SLOT(start(Cities)));
    QObject::connect(this,SIGNAL(startAntColony(Cities)),
                     antProcessor,SLOT(start(Cities)));

    QObject::connect(bruteForceProcessor, SIGNAL(done(Cities)),
                     this,SLOT(bruteFroceDone(Cities)));
    QObject::connect(branchProcessor, SIGNAL(done(Cities)),
                     this, SLOT(branchesDone(Cities)));
    QObject::connect(antProcessor,SIGNAL(done(QList<City>)),
                     this,SLOT(antColonyDone(Cities)));

}
Core::~Core(){
    delete bruteForceProcessor;
    delete branchProcessor;
}

void Core::start(QString methodName, QVariant rawdata)
{
    QVariantList data = rawdata.toList();
    QList<City> points;
    for(int i=0;i<data.size();i++){
        QMap<QString,QVariant> p = data[i].toMap();
        points.append(City(p["x"].toDouble(), p["y"].toDouble(), p["name"].toString()));
    }

    if (methodName == "Перебор")
        emit(startBruteForce(points));
    else if (methodName == "Ветви и границы")
        emit(startBranches(points));
    else if (methodName == "Муравьи"){

        antProcessor->setGreed(root->findChild<QObject*>("antGreedy")->property("value").toDouble());
        antProcessor->setHerdy(root->findChild<QObject*>("antHerdy")->property("value").toDouble());
        antProcessor->setIterations(root->findChild<QObject*>("antIterations")->property("value").toInt());
        antProcessor->setVaporization(root->findChild<QObject*>("antVaporization")->property("value").toDouble());
        emit(startAntColony(points));
    }
    startTimes[methodName] = QTime::currentTime();
    btns[methodName]->setProperty("enabled", false);
}



void Core::showPath(QList<City> path, QString name){
    QStringList stringPath;
    for(int i=0;i<path.size();i++)
        stringPath.append(path[i].name());

    QVariant returnedValue;
    QMetaObject::invokeMethod(map, "show",
            Q_RETURN_ARG(QVariant, returnedValue),
            Q_ARG(QVariant, stringPath),
            Q_ARG(QVariant, name));
}

void Core::done(Cities route,QString methodName){
    showPath(route, methodName);
    QString routeString;
    for(int i=0;i<route.size();i++)
        routeString+= route[i].name() + QString(" -> ");
    routeString += route[0].name();
    btns[methodName]->setProperty("enabled",true);
    QTime elapsedTime(0,0,0);
    elapsedTime = elapsedTime.addMSecs(startTimes[methodName].elapsed());
    root->findChild<QObject*>(textResults[methodName])->setProperty("text",methodName + " " + elapsedTime.toString("mm:ss:zzz"));
    root->findChild<QObject*>(textResults[methodName]+"Length")->setProperty("text",MethodProcessor::estimate(route));
    root->findChild<QObject*>(textResults[methodName]+"Route")->setProperty("text",routeString);
}
void Core::bruteFroceDone(Cities cities){
    done(cities,"Перебор");
}

void Core::branchesDone(Cities cities){
    done(cities,"Ветви и границы");
}

void Core::antColonyDone(Cities cities){
    done(cities,"Муравьи");
}

void Core::showBruteForcePath(Cities cities){
    showPath(cities,"Перебор");
}

void Core::showBranchesPath(Cities cities){
    showPath(cities,"Ветви и границы");
}

void Core::showAntColonyPath(Cities cities){
    showPath(cities,"Муравьи");
}
