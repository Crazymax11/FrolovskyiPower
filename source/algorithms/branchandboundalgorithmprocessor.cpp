#include "branchandboundalgorithmprocessor.h"

BranchAndBoundAlgorithmProcessor::BranchAndBoundAlgorithmProcessor()
{

}


void BranchAndBoundAlgorithmProcessor::start(QList<City> points){
    emit(done(points));
    return;
}
