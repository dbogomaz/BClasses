#include "btimer.h"

// =========== constructors ===========
BTimer::BTimer()
    : m_beg(clock_t::now())
{

}

// =========== getters ===========
double BTimer::elapsed() const
{
    return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
}

// =========== setters ===========
void BTimer::reset()
{
    m_beg = clock_t::now();
}
