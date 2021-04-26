#include "bfixedvaluedial.h"

BFixedValueDial::BFixedValueDial(QWidget *parent) : QWidget(parent)
{
    // инициализируем виджеты
    m_text = new QLabel;
    m_strValue = new QLabel;
    m_dial = new QDial;
    m_layout = new QVBoxLayout;

    // настройка m_text
    setText();

    // настройка m_strValue
    m_strValue->setFrameShape(QFrame::Panel);
    m_strValue->setFrameShadow(QFrame::Sunken);
    m_strValue->setStyleSheet("background-color: white");
    m_strValue->setAlignment(Qt::AlignHCenter);
    m_strValue->setMinimumWidth(50);

    // настройка m_dial
    m_dial->setNotchesVisible(true);
    m_dial->resize(50, 50);
    m_dial->setMinimumSize(50, 50);
    m_dial->setMaximumSize(50, 50);
//    m_dial->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_dial->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(m_dial, &QDial::valueChanged, this, &BFixedValueDial::setValue);
//    m_dial->setValue(2);

    // формируем layout
    m_layout->addWidget(m_text, 0, Qt::AlignCenter);
    m_layout->addWidget(m_strValue, 0, Qt::AlignCenter);
    m_layout->addWidget(m_dial, 0, Qt::AlignCenter);
    m_layout->setMargin(0);
    m_layout->setSpacing(0);
    setLayout(m_layout);

    // начальная инициализация
//    setValue();

    this->setMinimumSize(0, 0);
    this->setMaximumSize(100, 100);

//    emit valueChanged(0);

}

QString BFixedValueDial::text() const
{
    return m_text->text();
}

void BFixedValueDial::setText(const QString &text)
{
    m_text->setVisible(false);
    if (!text.isEmpty()) {
        m_text->setText(text);
        m_text->setVisible(true);
    }
}

void BFixedValueDial::setMap(const QMap<double, QString> &map)
{
    m_map = map;
    m_dial->setMaximum(m_map.count() - 1);

//    qDebug() << "m_map.count() =" << m_map.count();
    QMap<double, QString>::const_iterator iterator = m_map.begin();
    while (iterator != m_map.end()) {
//        qDebug() << iterator.key() << "-" << iterator.value();
        iterator++;
    }
    setValue();

}

void BFixedValueDial::nextValue()
{
    if (m_dial->value() != m_dial->maximum()) {
        m_dial->setValue(m_dial->value() + 1);
    }
}

void BFixedValueDial::prefValue()
{
    if (m_dial->value() != m_dial->minimum()) {
        m_dial->setValue(m_dial->value() - 1);
    }
}

void BFixedValueDial::setValue(int value)
{
//    qDebug() << endl << "* BFixedValueDial::setValue(" << value << ") *";
//    qDebug() << m_dial->value();
    // проверка наличия данных в m_map
    if (m_map.isEmpty()) {
        emit valueChanged(0);
    } else {
        // установка m_strValue
        m_strValue->setText(m_map.values().at(value));

        // формирование сигнала valueChanged(double)
        emit valueChanged(m_map.keys().at(value));
    }

//    qDebug() << "End of BFixedValueDial";

}
