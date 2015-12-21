#ifndef BRANCHANDBOUNDALGORITHMPROCESSOR_H
#define BRANCHANDBOUNDALGORITHMPROCESSOR_H

#include <algorithms/methodprocessor.h>

#include <QMap>
struct BPar{
    BPar(int i, QList<int> m){this->i = i; M= m;}
    bool operator< (const BPar b) const {return i<b.i;}
    int i;
    QList<int> M;
};

class BranchAndBoundAlgorithmProcessor: public MethodProcessor
{
    Q_OBJECT
public:
    BranchAndBoundAlgorithmProcessor();
public slots:
    void start(QList<City> points) override;
private slots:
    double front(double** fr_array, int size,  QList<int> way);
    double ves(double** array, int size, QList<int> lok_way);
private:
    Cities m_points;
    //поиск путя из i через M до 0
    Cities B(int i, QList<int> M);
    QMap<BPar, Cities> Bs;
    double GltBestSol = qInf();
    QList<int> GltBestWay;
    QList<int> GltTempWay;

};


#endif // BRANCHANDBOUNDALGORITHMPROCESSOR_H
