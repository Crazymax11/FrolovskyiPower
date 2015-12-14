#include "methodprocessor.h"
#include "math.h"

MethodProcessor::MethodProcessor(QObject *parent) : QObject(parent)
{
    m_bestEstimatedValue = qInf();
}

qreal MethodProcessor::estimate(QList<City> points){
    qreal result = 0;
    for(int i=0;i<points.size()-1;i++){
        result += sqrt(pow(points[i].x() - points[i+1].x(),2) + pow(points[i].y() - points[i+1].y(),2));
    }
    //возвращение обратно
    result += sqrt(pow(points[points.size()-1].x() - points[0].x(),2) + pow(points[points.size()-1].y() - points[0].y(),2));
    return result;
}
