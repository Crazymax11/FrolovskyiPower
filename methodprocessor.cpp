#include "methodprocessor.h"
#include "math.h"

MethodProcessor::MethodProcessor(QObject *parent) : QObject(parent)
{
    m_bestEstimatedValue = qInf();
}

qreal MethodProcessor::estimate(QList<QPair<qreal,qreal>> points){
    QPair<qreal,qreal> point;
    qreal result = 0;
    for(int i=0;i<points.size()-1;i++){
        result += sqrt(pow(points[i].first - points[i+1].first,2) + pow(points[i].second - points[i+1].second,2));
    }
    //возвращение обратно
    result += sqrt(pow(points[points.size()-1].first - points[0].first,2) + pow(points[points.size()-1].second - points[0].second,2));
    return result;
}
