#include "boscilloscope.h"

// constructors

BOscilloscope::BOscilloscope(QWidget *parent) : QWidget(parent)
  , m_scaleX(0)
  , m_scaleY(0)
  , m_shiftX(0)
  , m_shiftY(0)
{
    m_layout = new QHBoxLayout;
    m_chartView = new QChartView;
    m_chart = new QChart;

    m_axisX = new QValueAxis;
    m_axisY = new QValueAxis;

    m_chart->addAxis(m_axisX, Qt::AlignBottom);
    m_chart->addAxis(m_axisY, Qt::AlignLeft);

//    chart->setTitle("qqq");
    m_chart->legend()->setVisible(false);
    m_chartView->setChart(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);// сглаживание
    m_layout->addWidget(m_chartView);
    m_layout->setMargin(0);
    setLayout(m_layout);

    setAxisXRange(1000);
    setShiftX(-0.025);
//    setScaleY(1);

}

// getters

int BOscilloscope::axisXRange() const
{
    return m_axisXRange;
}

double BOscilloscope::scaleX() const
{
    return m_scaleX;
}

double BOscilloscope::scaleY() const
{
    return m_scaleY;
}

double BOscilloscope::shiftX() const
{
    return m_shiftX;
}

double BOscilloscope::shiftY() const
{
    return m_shiftY;
}

// setters

void BOscilloscope::addSignal(double (*signal)(double))
{
    m_signal = signal;
    m_signalsList.append(signal);

    QLineSeries *series = new QLineSeries;
    m_chart->addSeries(series);
    series->attachAxis(m_axisX);
    series->attachAxis(m_axisY);
    m_seriesList.append(series);

//    qDebug() << "m_signalsList.count()" << m_signalsList.count();
//    qDebug() << "m_seriesList.count()" << m_seriesList.count();

    updateChart();

}

void BOscilloscope::setAxisXRange(int axisXRange)
{
    m_axisXRange = axisXRange;
}

void BOscilloscope::setScaleX(double scaleX)
{
    m_scaleX = scaleX;
    updateScaleX();
}

void BOscilloscope::setScaleY(double scaleY)
{
    //    qDebug() << "BOscilloscope::setScaleY(" << scaleY << ")";
    m_scaleY = scaleY;

    m_axisY->setRange(-m_scaleY, m_scaleY);
    m_axisY->setTickCount(9);
    m_axisY->setLabelFormat("%g");
    updateChart();
}

void BOscilloscope::setShiftX(double shiftX)
{
    m_shiftX = shiftX;
    updateScaleX();
}

void BOscilloscope::setShiftY(double shiftY)
{
    m_shiftY = shiftY;
}

// public slots

void BOscilloscope::updateChart()
{
    foreach (QLineSeries *series, m_seriesList) {
        series->clear();
    }

    QList<double(*)(double)>::const_iterator signalIterator = m_signalsList.begin();
    QList<QLineSeries*>::iterator seriesIterator = m_seriesList.begin();       // список серий для сигналов
    for (; signalIterator != m_signalsList.end(); ++signalIterator, ++seriesIterator) {
        for (int i = 0; i <= m_axisXRange; ++i) {
            double t = m_shiftX + double(i) / double(m_axisXRange) * m_scaleX;
            (*seriesIterator)->append(t, (*signalIterator)(t));
        }
     }
/*        // обращение через индекс
//        for (int i = 0; i < m_signalsList.count(); ++i) {
//            m_seriesList.at(i)->append(double(t), m_signalsList.at(i)(double(t)));
//        }
*/
}

void BOscilloscope::updateScaleX()
{
    m_axisX->setRange(m_shiftX, m_scaleX + m_shiftX);
    m_axisX->setTickCount(5);
    m_axisX->setLabelFormat("%g");
    updateChart();
}

