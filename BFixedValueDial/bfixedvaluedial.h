#ifndef BFIXEDVALUEDIAL_H
#define BFIXEDVALUEDIAL_H

#include <QBoxLayout>
#include <QDial>
#include <QLabel>
#include <QMap>
#include <QWidget>

#include <QDebug>

class BFixedValueDial : public QWidget
{
    Q_OBJECT
public:
    explicit BFixedValueDial(QWidget *parent = nullptr);

    QString text() const;
    void setText(const QString &text = QString());

    void setMap(const QMap<double, QString> &map);
    void setValue(int value = 0);

public slots:
    void nextValue();
    void prefValue();

signals:
    void valueChanged(double value);

private:
    QLabel *m_text;
    QLabel *m_strValue;
    QDial *m_dial;
    QVBoxLayout *m_layout;
    QMap<double, QString> m_map;

};

#endif // BFIXEDVALUEDIAL_H
