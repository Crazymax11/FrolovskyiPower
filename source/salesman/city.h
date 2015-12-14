#ifndef CITY_H
#define CITY_H

#include <QObject>

class City : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    City(QObject *parent = 0): QObject(parent){setX(-1);setY(-1);setName("");}
    City(qreal x, qreal y, QString name = "", QObject *parent = 0): QObject(parent){setX(x);setY(y);setName(name);}
    City& operator=(const City& b){setX(b.x());setY(b.y());setName(b.name());return *this;}
    City (const City& b, QObject* parent = 0): QObject(parent){*this=b;}
signals:
    void xChanged(qreal newx);
    void yChanged(qreal newy);
    void nameChanged(const QString& newName);
public slots:
    qreal x() const{return m_x;}
    qreal y() const{return m_y;}
    const QString& name() const {return m_name;}
    City& setY(qreal newy){m_y = newy; emit(yChanged(m_y));return *this;}
    City& setX(qreal newx){m_x = newx; emit(xChanged(m_x));return *this;}
    City& setName(const QString& newname){m_name = newname; emit(nameChanged(m_name));return *this;}
private:
    qreal m_x;
    qreal m_y;
    QString m_name;
};

#endif // CITY_H
