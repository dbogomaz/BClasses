/* Виджет для отображения диаграммы направленности антенны
 *
 */

#ifndef BANTENNAPATTERN_H
#define BANTENNAPATTERN_H

#include <QWidget>
#include <QPainter>
//#include <qmath.h>
#include <QtMath>

#include <QDebug>

// линия на диаграмме
class BAntennaPatternSeries
{
public:
    // constructors
    explicit BAntennaPatternSeries(QVector<QPointF> pointList,
                                   QColor color,
                                   int widht = 1,
                                   QString name = "");

    QColor color() const;
    void setColor(const QColor &color);

    int widht() const;
    void setWidht(int widht);

    QString name() const;
    void setName(const QString &name);

    QVector<QPointF> pointVector() const;
    void setPointVector(const QVector<QPointF> &pointVector);

private:
    QVector<QPointF> m_pointVector;
    QColor m_color;
    int m_widht;
    QString m_name;
};

class BAntennaPattern : public QWidget
{
    Q_OBJECT
public:
    // constructors
    explicit BAntennaPattern(QWidget *parent = nullptr);

    // getters
    int    angleTickCount() const;  // количество линий сетки по углам
    QColor gridColor() const;       // цвет сетки
    bool   isPolar() const;         // признак является ли диаграмма полярной
    int    maxAngle() const;        // максимальный угол
    double maxValue() const;        // максимальное значение
    int    valueTickCount() const;  // количество линий сетки по значениям

    void clear();
    void addSeries(BAntennaPatternSeries *series);

    // setters
    void setAngleTickCount(int angleTickCount); // количество линий сетки по углам
    void setGridColor(const QColor &gridColor); // цвет сетки
    void setMaxAngle(int maxAngle);             // максимальный угол
    void setMaxValue(double maxValue);          // максимальное значение
    void setPolar(bool isPolar);                // признак является ли диаграмма полярной
    void setValueTickCount(int valueTickCount); // количество линий сетки по значениям

    // operators overloading

signals:

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    int      m_angleTickCount;  // количество линий сетки по углам
    QColor   m_gridColor;       // цвет сетки
    QMargins m_margin;          // поля диаграммы
    double   m_maxAngle;        // максимальный угол
    double   m_maxValue;        // максимальное значение
    bool     m_polar;           // признак является ли диаграмма полярной
    QMargins m_polarMargin;     // поля полярной диаграммы
    int      m_valueTickCount;  // количество линий сетки по значениям

    QList<BAntennaPatternSeries> *m_patternSeriesList;

    // inside functions
    void    drawBackGround();   // нарисовать задний фон
   void    drawGrid();         // нарисовать сетку
    void    drawPolarGrid();    // нарисовать полярную сетку
    void    drawSeries();
    void    drawPolarSeries();
    QPointF polarToCartesian(QPointF polar, QPointF center);    // пересчет полярной координаты в декартову относительно центра
};



#endif // BANTENNAPATTERN_H
