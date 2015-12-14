#include "bruteforcesearchalgorithmprocessor.h"

BruteForceSearchAlgorithmProcessor::BruteForceSearchAlgorithmProcessor()
{

}

void BruteForceSearchAlgorithmProcessor::start(QList<City> points){
    QList<City> emptyPath;
    extendPath(emptyPath, points);
    emit(done(m_bestRoute));
}


void BruteForceSearchAlgorithmProcessor::extendPath(QList<City> route, QList<City> points){
    for(int i=0;i<points.size();i++){
        QList<City> tempPoints = points;
        route.append(tempPoints.at(i));
        tempPoints.removeAt(i);
        extendPath(route,tempPoints);
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
