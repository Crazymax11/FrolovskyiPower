#ifndef BRANCHANDBOUNDALGORITHMPROCESSOR_H
#define BRANCHANDBOUNDALGORITHMPROCESSOR_H

#include <algorithms/methodprocessor.h>
class BranchAndBoundAlgorithmProcessor: public MethodProcessor
{
    Q_OBJECT
public:
    BranchAndBoundAlgorithmProcessor();
public slots:
    void start(QList<City> points) override;
};

#endif // BRANCHANDBOUNDALGORITHMPROCESSOR_H
