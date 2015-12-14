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
signals:
    void newBestFound(QList<City> points);
    void done(QList<City> points);
public slots:
    virtual void start(QList<City> points) = 0;
protected:
    qreal m_bestEstimatedValue;
    QList<City> m_bestRoute;
private:

};

#endif // METHODPROCESSOR_H
