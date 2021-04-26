/* Класс синусоидального сигнала
 * Частота в герцах
 * Фаза в градусах (0 - 360)
 * Время t в секундах
 */
#ifndef BSINSIGNAL_H
#define BSINSIGNAL_H

#include <QObject>
#include <QtMath>

#include <QDebug>

class BSinSignal : public QObject
{
    Q_OBJECT
public:
    explicit BSinSignal(QObject *parent = nullptr);
    BSinSignal(const BSinSignal &sinSignal);

    int amplitude() const;
    int frequence() const;
    int phase() const;

    double value(double t); // значение сигнала в момент времени t

    // operators overloading
    BSinSignal &operator= (const BSinSignal &sinSignal);

signals:
    void parametrsChanged();

public slots:
    void setAmplitude(int value);
    void setFrequency(int value);
    void setPhase(int value);

private:
    int m_amplitude;    // амплитуда
    int m_frequency;    // частота
    int m_phase;        // фаза
};

#endif // BSINSIGNAL_H
