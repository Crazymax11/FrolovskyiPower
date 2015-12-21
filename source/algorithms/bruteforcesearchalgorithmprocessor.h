#ifndef BRUTEFORCESEARCHALGORITHMPROCESSOR_H
#define BRUTEFORCESEARCHALGORITHMPROCESSOR_H

#include <QObject>
#include <algorithms/methodprocessor.h>
class BruteForceSearchAlgorithmProcessor: public MethodProcessor
{
    Q_OBJECT
public:
    BruteForceSearchAlgorithmProcessor();
public slots:
    void start(Cities points) override;
private:
    void extendPath(QList<City> curPath, QList<City> points);
};

#endif // BRUTEFORCESEARCHALGORITHMPROCESSOR_H
