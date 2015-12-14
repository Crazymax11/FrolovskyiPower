#include "branchandboundalgorithmprocessor.h"

BranchAndBoundAlgorithmProcessor::BranchAndBoundAlgorithmProcessor()
{

}


void BranchAndBoundAlgorithmProcessor::start(QList<QPair<qreal, qreal> > points){
    emit(done(points));
    return;
}
