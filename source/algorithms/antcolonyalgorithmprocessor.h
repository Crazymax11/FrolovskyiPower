#ifndef ANTCOLONYALGORITHMPROCESSOR_H
#define ANTCOLONYALGORITHMPROCESSOR_H

#include <QObject>
#include <algorithms/methodprocessor.h>
#include <QtMath>
class antColonyAlgorithmProcessor: public MethodProcessor
{
    Q_OBJECT
    Q_PROPERTY (int iterations READ iterations WRITE setIterations)
    Q_PROPERTY (double greed READ greed WRITE setGreed)
    Q_PROPERTY (double herdy READ herdy WRITE setHerdy)
    Q_PROPERTY (double vaporization READ vaporization WRITE setVaporization)
public:
    antColonyAlgorithmProcessor();
public slots:
    void start(QList<City> points) override;
    double greed() const{return m_greed;}
    double herdy() const{return m_herdy;}
    double vaporization() const{return m_vaporization;}
    int iterations() const{return m_iterations;}
    bool setIterations(int iterations);
    bool setGreed(double greed);
    bool setHerdy(double herdy);
    bool setVaporization(double vaporization);
private:
    double m_greed;
    double m_herdy;
    double m_vaporization;
    int m_iterations;
};

#endif // ANTCOLONYALGORITHMPROCESSOR_H
