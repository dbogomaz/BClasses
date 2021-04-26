/* Класс представляет собой виджет, основанный на QChart
 * не забыть подключить в pro файле
 * "QT       += core gui charts"
 */
#ifndef BOSCILLOSCOPE_H
#define BOSCILLOSCOPE_H

#include <QWidget>
#include <QtCharts>

class BOscilloscope : public QWidget
{
    Q_OBJECT
public:
    // constructors
    explicit BOscilloscope(QWidget *parent = nullptr);

    // getters
    int axisXRange() const; // дискретность построения по оси Х
    double scaleX() const;  // размер шкалы по оси X
    double scaleY() const;  // размер шкалы по оси Y
    double shiftX() const;  // смещение по оси X
    double shiftY() const;  // смещение по оси Y

    // setters
    void addSignal(double (*signal)(double t)); // добавить сигнал
    void setAxisXRange(int axisXRange);         // установить дискретность построения по оси Х
    void setScaleX(double scaleX);              // установить значение размера шкалы по оси X
    void setScaleY(double scaleY);              // установить значение размера шкалы по оси Y
    void setShiftX(double shiftX);              // установить смещение по оси X
    void setShiftY(double shiftY);              // установить смещение по оси Y

    // operators overloading


signals:

public slots:
    void updateChart();

private:
    QValueAxis *m_axisX;                    // ось X
    int m_axisXRange;                       // дискретность построения по оси Х
    QValueAxis *m_axisY;                    // ось Y
    QChart *m_chart;                        // график
    QChartView  *m_chartView;               // отображение графика
    QHBoxLayout *m_layout;                  // слой виджета
    double m_scaleX;                        // размер шкалы по оси X
    double m_scaleY;                        // размер шкалы по оси Y
    QList<QLineSeries*> m_seriesList;       // список серий для сигналов
    double m_shiftX;                        // смещение по оси X
    double m_shiftY;                        // смещение по оси Y
    double (*m_signal)(double t);           // указатель на функцию - сигнал
    QList<double(*)(double)> m_signalsList; // список сигналов

    void updateScaleX();

};

#endif // BOSCILLOSCOPE_H
