#ifndef BTIMEBEFORE_H
#define BTIMEBEFORE_H

#include <QObject>
#include <QTime>

class BTimeBefore : public QObject
{
    Q_OBJECT
public:
    // constructors
    explicit BTimeBefore(QObject *parent = nullptr);

    // getters

    // setters

    // operators overloading

signals:

private:
    QDateTime m_currentDateTime; // текущая дата и время
    QDateTime m_eventDate; // дата события
};

#endif // BTIMEBEFORE_H
