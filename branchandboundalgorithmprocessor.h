#ifndef BRANCHANDBOUNDALGORITHMPROCESSOR_H
#define BRANCHANDBOUNDALGORITHMPROCESSOR_H

#include "methodprocessor.h"
class BranchAndBoundAlgorithmProcessor: public MethodProcessor
{
    Q_OBJECT
public:
    BranchAndBoundAlgorithmProcessor();
public slots:
    void start(QList<QPair<qreal, qreal>> points) override;
};

#endif // BRANCHANDBOUNDALGORITHMPROCESSOR_H
