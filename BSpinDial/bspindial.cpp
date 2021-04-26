#include "bspindial.h"

BSpinDial::BSpinDial(QWidget *parent)
    : QWidget(parent)
{
    // инициализируем виджеты
    m_label = new QLabel;
    m_spin = new QSpinBox;
    m_dial = new QDial;
    m_layout = new QVBoxLayout;
  //  QHBoxLayout *hLayout = new QHBoxLayout;
//    label->setVisible(false);

    // настраиваем Label
    setText();

    // содединяем диал и спин
    connect(m_spin, QOverload<int>::of(&QSpinBox::valueChanged), m_dial, &QDial::setValue);
    connect(m_dial, &QDial::valueChanged, m_spin, &QSpinBox::setValue);

    // настраиваем диал
    m_dial->setNotchesVisible(true);
    m_dial->resize(50, 50);
    m_dial->setMinimumSize(50, 50);
    m_dial->setMaximumSize(50, 50);
//    m_dial->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_dial->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // настраиваем спин
    m_spin->resize(0, 0);


    // формируем layout
    m_layout->addWidget(m_label, 0, Qt::AlignHCenter);
    m_layout->addWidget(m_spin, 0, Qt::AlignHCenter);
    m_layout->addWidget(m_dial, 0, Qt::AlignHCenter);
    m_layout->setMargin(0);
    m_layout->setSpacing(0);
    setLayout(m_layout);

    connect(m_dial, &QDial::valueChanged, this, &BSpinDial::spinValueChanged);

    // начальные установки класса
//    setMaximum(1000);
//    setMinimum(0);
    this->setMinimumSize(0, 0);
    this->setMaximumSize(100, 100);

}

void BSpinDial::setRange(int min, int max)
{
    setMinimum(min);
    setMaximum(max);
}

void BSpinDial::setMaximum(int val)
{
    m_spin->setMaximum(val);
    m_dial->setMaximum(val);
//    setNotches();
}

void BSpinDial::setMinimum(int val)
{
    m_spin->setMinimum(val);
    m_dial->setMinimum(val);
//    setNotches();
}

int BSpinDial::value()
{
    return m_spin->value();
}

void BSpinDial::setValue(int val)
{
    m_spin->setValue(val);
}

void BSpinDial::spinValueChanged(int val)
{
    emit valueChanged(val);
}

void BSpinDial::setNotches()
{
    const int RATE_NOTCHES_TARGET = 10;
    int span = m_spin->maximum() - m_spin->minimum();
//    qDebug() << span;
    m_dial->setNotchTarget(span / RATE_NOTCHES_TARGET);
    qDebug() << "m_dial->notchTarget() =" << m_dial->notchTarget();
}

QString BSpinDial::text() const
{
    return m_label->text();
}

void BSpinDial::setText(const QString &text)
{
    m_label->setVisible(false);
    if (!text.isEmpty()) {
        m_label->setText(text);
        m_label->setVisible(true);
    }
}
