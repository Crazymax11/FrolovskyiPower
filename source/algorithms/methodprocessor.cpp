#include "methodprocessor.h"
#include "math.h"

MethodProcessor::MethodProcessor(QObject *parent) : QObject(parent)
{
    init();
}

void MethodProcessor::init(){
    m_bestEstimatedValue = qInf();
    m_bestRoute.clear();
}

qreal MethodProcessor::estimate(QList<City> points){
    qreal result = 0;
    for(int i=0;i<points.size();i++){
        result +=estimatePoints(points[i], points[(i+1)%points.size()]);
    }
    return result;
}

qreal MethodProcessor::estimatePoints(const City& p1,const City& p2){
    return sqrt(pow(p1.x() - p2.x(),2) + pow(p1.y() - p2.y(),2));
}
