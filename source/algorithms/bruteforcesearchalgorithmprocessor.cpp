#include "bruteforcesearchalgorithmprocessor.h"
#include "windows.h"
BruteForceSearchAlgorithmProcessor::BruteForceSearchAlgorithmProcessor()
{

}

void BruteForceSearchAlgorithmProcessor::start(Cities points){
    init();
    QList<City> emptyPath;
    emptyPath.append(points.at(0));
    points.removeAt(0);
    extendPath(emptyPath, points);
    emit(done(m_bestRoute));
}


void BruteForceSearchAlgorithmProcessor::extendPath(QList<City> route, QList<City> points){
    for(int i=0;i<points.size();i++){
        QList<City> tempRoute = route;
        QList<City> tempPoints = points;
        tempRoute.append(tempPoints.at(i));
        tempPoints.removeAt(i);
        extendPath(tempRoute,tempPoints);
    }
    //если точек не осталось- нужно считать эстимейт
    if (points.size() == 0){
        qreal result = estimate(route);
        if (result < m_bestEstimatedValue){
            m_bestEstimatedValue = result;
            m_bestRoute = route;
            emit(newBestFound(route));
        }
    }
}
