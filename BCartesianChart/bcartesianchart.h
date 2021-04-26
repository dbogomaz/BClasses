/* Виджет - декартовые координты
 */

#ifndef BCARTESIANCHART_H
#define BCARTESIANCHART_H

#include <QWidget>
#include <QPainter>
#include <QDebug>

#include <QPainterPath>

enum chartType {points, polyline, polygon, fillpath};

// линия на диаграмме
class BCartesianSeries
{
public:
    // constructors
    explicit BCartesianSeries(QVector<QPointF> pointList,
                              QColor color = Qt::blue,
                              chartType type = points,
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

    int type() const;
    void setType(int type);

private:
    QVector<QPointF> m_pointVector;
    QColor           m_color;
    int              m_widht;
    QString          m_name;
    int              m_type;
};


class BCartesianChart : public QWidget
{
    Q_OBJECT
public:
    // constructors
    explicit BCartesianChart(QWidget *parent = nullptr);

    // getters
    QColor gridColor() const;
    QMargins margin() const;
    double maxValueX() const;
    double maxValueY() const;
    int tickCountX() const;
    int tickCountY() const;
    QList<BCartesianSeries> *seriesList() const;

    // setters
    void setGridColor(const QColor &gridColor);
    void setMargin(const QMargins &margin);
    void setMaxValueX(double maxValueX);
    void setMaxValueY(double maxValueY);
    void setTickCountX(int tickCountX);
    void setTickCountY(int tickCountX);

    void clear();
    void addSeries(BCartesianSeries *series);


    // operators overloading



signals:


    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QColor   m_gridColor;       // цвет сетки
    QMargins m_margin;          // поля диаграммы
    double   m_maxValueX;       // максимальное значение X
    double   m_maxValueY;       // максимальное значение Y
    int      m_tickCountX;      // количество линий сетки X
    int      m_tickCountY;      // количество линий сетки Y

    QList<BCartesianSeries> *m_seriesList;

    // inside functions
    void    drawBackGround();   // нарисовать задний фон
    void    drawGrid();         // нарисовать сетку
    void    drawSeries();
};

#endif // BCARTESIANCHART_H
