/* Виджет, включающий Spin и Slider, соединенные между собой
 */

#ifndef BSPINSLIDER_H
#define BSPINSLIDER_H

#include <QWidget>
#include <QSlider>
#include <QSpinBox>
#include <QHBoxLayout>

class BSpinSlider : public QWidget
{
    Q_OBJECT
public:
    explicit BSpinSlider(QWidget *parent = nullptr);
    void setMaximum(int val);
    void setMinimum(int val);
    int value();
    void setValue(int val);
    void setSpinMinimumSize(int value); // установка минимального размера Spin

signals:
    void valueChanged(int val);

public slots:

private slots:

private:
    void spinValueChanged(int val);
    QSpinBox *m_spin;
    QSlider *m_slider;
    QHBoxLayout *m_layout;

};

#endif // BSPINSLIDER_H
