#include "bruteforcesearchalgorithmprocessor.h"

BruteForceSearchAlgorithmProcessor::BruteForceSearchAlgorithmProcessor()
{

}

void BruteForceSearchAlgorithmProcessor::start(QList<QPair<qreal, qreal>> points){
    QList<QPair<qreal, qreal>> emptyPath;
    extendPath(emptyPath, points);
    emit(done(m_bestRoute));
}


void BruteForceSearchAlgorithmProcessor::extendPath(QList<QPair<qreal, qreal>> route, QList<QPair<qreal, qreal> > points){
    for(int i=0;i<points.size();i++){
        QList<QPair<qreal,qreal>> tempPoints = points;
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
