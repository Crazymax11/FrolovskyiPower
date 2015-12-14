#ifndef BRUTEFORCESEARCHALGORITHMPROCESSOR_H
#define BRUTEFORCESEARCHALGORITHMPROCESSOR_H

#include <QObject>
#include "methodprocessor.h"
class BruteForceSearchAlgorithmProcessor: public MethodProcessor
{
    Q_OBJECT
public:
    BruteForceSearchAlgorithmProcessor();
public slots:
    void start(QList<QPair<qreal, qreal>> points) override;
private:
    void extendPath(QList<QPair<qreal, qreal>> curPath, QList<QPair<qreal, qreal>> points);
};

#endif // BRUTEFORCESEARCHALGORITHMPROCESSOR_H
