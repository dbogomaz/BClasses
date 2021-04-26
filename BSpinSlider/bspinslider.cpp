#include "bspinslider.h"

BSpinSlider::BSpinSlider(QWidget *parent) : QWidget(parent)
{
    // инициализируем виджеты
    m_spin = new QSpinBox;
    m_slider = new QSlider;
    m_layout = new QHBoxLayout;

    // содединяем спин и слайдер
    connect(m_spin, QOverload<int>::of(&QSpinBox::valueChanged), m_slider, &QSlider::setValue);
    connect(m_slider, &QSlider::valueChanged, m_spin, &QSpinBox::setValue);

    // настраиваем слайдер
    m_slider->setOrientation(Qt::Horizontal);

    // настраиваем спин
    m_spin->resize(0, 0);

    // начальные установки класса
    setMaximum(99);
    setMinimum(0);


    // формируем layout
    m_layout->addWidget(m_slider);
    m_layout->addWidget(m_spin);
    m_layout->setMargin(0);
    setLayout(m_layout);

    connect(m_slider, &QSlider::valueChanged, this, &BSpinSlider::spinValueChanged);

    setMinimumSize(100, 0);

}

void BSpinSlider::setMaximum(int val)
{
    m_spin->setMaximum(val);
    m_slider->setMaximum(val);
    if (m_slider->maximum() <= 10) {
        m_slider->setPageStep(1);
    }
}

void BSpinSlider::setMinimum(int val)
{
    m_spin->setMinimum(val);
    m_slider->setMinimum(val);
}

int BSpinSlider::value()
{
    return m_spin->value();
}

void BSpinSlider::setValue(int val)
{
    m_spin->setValue(val);
}

void BSpinSlider::setSpinMinimumSize(int value)
{
    m_spin->setMinimumWidth(value);

}

void BSpinSlider::spinValueChanged(int val)
{
    emit valueChanged(val);
}
