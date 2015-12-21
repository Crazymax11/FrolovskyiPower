#ifndef METHODPROCESSOR_H
#define METHODPROCESSOR_H

#include <QObject>
#include <QPair>
#include <salesman/city.h>
class MethodProcessor : public QObject
{
    Q_OBJECT

public:
    explicit MethodProcessor(QObject *parent = 0);
    static qreal estimate(QList<City> points);
    static qreal estimatePoints(const City& p1,const City& p2);
signals:
    void newBestFound(QList<City> points);
    void done(QList<City> points);
public slots:
    virtual void start(Cities points) = 0;

protected:
    qreal m_bestEstimatedValue;
    QList<City> m_bestRoute;

    void init();
private:

};

#endif // METHODPROCESSOR_H
