#ifndef METHODPROCESSOR_H
#define METHODPROCESSOR_H

#include <QObject>
#include <QPair>
class MethodProcessor : public QObject
{
    Q_OBJECT

public:
    explicit MethodProcessor(QObject *parent = 0);
    static qreal estimate(QList<QPair<qreal,qreal> > points);
signals:
    void newBestFound(QList<QPair<qreal,qreal>> points);
    void done(QList<QPair<qreal,qreal> > points);
public slots:
    virtual void start(QList<QPair<qreal,qreal> > points) = 0;
protected:
    qreal m_bestEstimatedValue;
    QList<QPair<qreal,qreal> > m_bestRoute;
private:

};

#endif // METHODPROCESSOR_H
