#ifndef SIMULATEDANNEALINGPROCESSOR_H
#define SIMULATEDANNEALINGPROCESSOR_H

#include <QObject>
#include <methodprocessor.h>
class SimulatedAnnealingProcessor: public MethodProcessor
{
    Q_OBJECT
public:
    SimulatedAnnealingProcessor();
public slots:
    void start(QList<QPair<qreal, qreal>> points) override;
};

#endif // SIMULATEDANNEALINGPROCESSOR_H
