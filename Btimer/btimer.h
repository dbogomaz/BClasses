// Класс для измерения времени выполнения кода (тайминга)
//
#ifndef BTIMER_H
#define BTIMER_H

#include <chrono>

class BTimer
{
public:
    // constructors
    BTimer();

    // getters
    double elapsed() const; // прошедшее время

    // setters
    void reset(); // сброс

    // inside members
private:
    // Псевдонимы типов используются для удобного доступа к вложенным типам
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration< double, std::ratio<1> >;

    std::chrono::time_point<clock_t> m_beg {clock_t::now()};
};

#endif // BTIMER_H
