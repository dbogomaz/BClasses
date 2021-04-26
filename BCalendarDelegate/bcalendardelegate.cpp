#include "bcalendardelegate.h"

BCalendarDelegate::BCalendarDelegate(const QModelIndex &index, QWidget *parent)
    : QDialog(parent)
{
    this->setWindowFlag(Qt::SplashScreen);

    m_index = index;
    m_cw = new QCalendarWidget;
    m_cw->setGridVisible(true);
    m_cw->setSelectedDate(m_index.model()->data(m_index, Qt::EditRole).toDate());

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(m_cw);
    setLayout(layout);

    connect(m_cw, &QCalendarWidget::activated, this, &BCalendarDelegate::accept);
}

void BCalendarDelegate::accept()
{
    emit activated(m_index, m_cw->selectedDate());
    this->close();
}
