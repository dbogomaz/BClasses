/* Класс содержит два свзязанных элемента
 * spinBox и dial
 */
#ifndef BSPINDIAL_H
#define BSPINDIAL_H

//#include <QWidget>
//#include <QSlider>
#include <QLabel>
#include <QSpinBox>
#include <QDial>
#include <QBoxLayout>

#include <QDebug>

class BSpinDial : public QWidget
{
    Q_OBJECT
public:
    explicit BSpinDial(QWidget *parent = nullptr);
    void setRange(int min, int max);
    void setMaximum(int val);
    void setMinimum(int val);
    int value();
    void setValue(int val);

    QString text() const;
    void setText(const QString &text = QString());

public slots:

signals:
    void valueChanged(int value);

private:
    void spinValueChanged(int value);
    QLabel *m_label;
    QSpinBox *m_spin;
    QDial *m_dial;
    QVBoxLayout *m_layout;
    void setNotches();
};

#endif // BSPINDIAL_H
