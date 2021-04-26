#include "bsinsignal.h"

BSinSignal::BSinSignal(QObject *parent) : QObject(parent)
  , m_amplitude(0)
  , m_frequency(0)
  , m_phase(0)
{

}

BSinSignal::BSinSignal(const BSinSignal &sinSignal) : QObject()
{
    m_amplitude = sinSignal.amplitude();
    m_frequency = sinSignal.frequence();
    m_phase = sinSignal.phase();
}

void BSinSignal::setAmplitude(int value)
{
    m_amplitude = value;
    emit parametrsChanged();
}

void BSinSignal::setFrequency(int value)
{
    m_frequency = value;
    emit parametrsChanged();
}

void BSinSignal::setPhase(int value)
{
    m_phase = value;
    emit parametrsChanged();
}

int BSinSignal::amplitude() const
{
    return m_amplitude;
}

int BSinSignal::frequence() const
{
    return m_frequency;
}

int BSinSignal::phase() const
{
    return m_phase;
}

double BSinSignal::value(double t)
{
    int amplitude = m_amplitude;
    double frequency = 2 * M_PI * m_frequency;
    double phase = 2 * M_PI * m_phase / 360;

    double value = amplitude * qSin(frequency * t + phase);

    return value;
}

// operators overloading
BSinSignal &BSinSignal::operator=(const BSinSignal &sinSignal)
{
    if(this == &sinSignal) {
        return *this;
    }
    m_amplitude = sinSignal.amplitude();
    m_frequency = sinSignal.frequence();
    m_phase = sinSignal.phase();

    return *this;
}
