#include "bcartesianchart.h"


BCartesianChart::BCartesianChart(QWidget *parent) : QWidget(parent)
  , m_gridColor(Qt::gray)
  , m_margin(10, 5, 10, 5)
  , m_maxValueX(10)
  , m_maxValueY(10)
  , m_tickCountX(10)
  , m_tickCountY(10)
{
    m_seriesList = new QList<BCartesianSeries>;
}

// getters
int BCartesianChart::tickCountX() const
{
    return m_tickCountX;
}

int BCartesianChart::tickCountY() const
{
    return m_tickCountY;
}

double BCartesianChart::maxValueX() const
{
    return m_maxValueX;
}

double BCartesianChart::maxValueY() const
{
    return m_maxValueY;
}

QMargins BCartesianChart::margin() const
{
    return m_margin;
}

QColor BCartesianChart::gridColor() const
{
    return m_gridColor;
}


// setters
void BCartesianChart::setTickCountX(int tickCountX)
{
    m_tickCountX = tickCountX;
    repaint();
}

void BCartesianChart::setTickCountY(int tickCountY)
{
    m_tickCountY = tickCountY;
    repaint();
}

void BCartesianChart::setMaxValueX(double maxValueX)
{
    if (maxValueX) {
        m_maxValueX = maxValueX;
        repaint();
    }
}

void BCartesianChart::setMaxValueY(double maxValueY)
{
    m_maxValueY = maxValueY;
}

void BCartesianChart::setMargin(const QMargins &margin)
{
    m_margin = margin;
}

void BCartesianChart::setGridColor(const QColor &gridColor)
{
    m_gridColor = gridColor;
    repaint();
}



// QWidget interface

void BCartesianChart::paintEvent(QPaintEvent *event)
{
    drawBackGround();
    drawGrid();
    drawSeries();
}

QList<BCartesianSeries> *BCartesianChart::seriesList() const
{
    return m_seriesList;
}


void BCartesianChart::drawBackGround()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int w = this->size().width();
    int h = this->size().height();
    int radius = 5;// закругление углов
    QColor backGroundColor(Qt::white);
    QRect rect(0, 0, w, h);
    QPainterPath painterPath;
    painterPath.addRoundedRect(rect, radius, radius);
    painter.fillPath(painterPath, QBrush(backGroundColor));
}

void BCartesianChart::drawGrid()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int w = this->size().width();
    int h = this->size().height();
    int lineWidth = 1;// ширина линии сетки
    int centralLineWidth = 2;// ширина центральной линии
    QColor textColor(Qt::black);// цвет подписей
    QPen pen;

    // рисуем вертикальные линии
    double stepX = m_maxValueX / m_tickCountX;
    double scaleX = double(w - m_margin.left() - m_margin.right()) / (m_maxValueX * 2);// масштаб
    for (double i = -m_maxValueX; i <= m_maxValueX; i += stepX) {
        pen.setColor(m_gridColor);
        pen.setWidth(lineWidth);
        if (i == 0) {
            pen.setWidth(centralLineWidth);
        }
        painter.setPen(pen);
        int x = m_margin.left() + (i + m_maxValueX) * scaleX;
        painter.drawLine(QPointF(x, h - m_margin.bottom()),
                         QPointF(x, m_margin.top()));

        // настраиваем подписи оси X
        pen.setColor(textColor);
        painter.setPen(pen);
        int y = h / 2;
        QRect textRect(x - stepX * scaleX / 2, y, stepX * scaleX, 15);
//        painter.fillRect(textRect, QBrush(Qt::red));
        // подписываем
        painter.drawText(textRect, Qt::AlignHCenter, QString::number(i));
    }

    // рисуем горизонтальные линии
    double stepY = m_maxValueY / m_tickCountY;
    double scaleY = double(h - m_margin.top() - m_margin.bottom()) / (m_maxValueY * 2);// масштаб
    for (double i = -m_maxValueY; i <= m_maxValueY; i += stepY) {
        pen.setColor(m_gridColor);
        pen.setWidth(lineWidth);
        if (i == 0) {
            pen.setWidth(centralLineWidth);
        }
        painter.setPen(pen);
        int y = m_margin.top() + (m_maxValueY - i) * scaleY;
        painter.drawLine(QPointF(m_margin.left(), y),
                         QPointF(w - m_margin.right(), y));

        // настраиваем подписи оси X
        pen.setColor(textColor);
        painter.setPen(pen);
        int x = w / 2 - stepY * scaleY - 2;
        QRect textRect(x, y - 10, stepY * scaleY, 15);
//        painter.fillRect(textRect, QBrush(Qt::red));
        // подписываем
        painter.drawText(textRect, Qt::AlignRight, QString::number(i));
    }
}

void BCartesianChart::drawSeries()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;

    int w = this->size().width();
    int h = this->size().height();

    QPolygonF polygon;

    double scaleX = double(w - m_margin.left() - m_margin.right()) / (m_maxValueX * 2);// масштаб
    double scaleY = double(h - m_margin.top() - m_margin.bottom()) / (m_maxValueY * 2);// масштаб
    QPointF center(m_margin.left() + m_maxValueX * scaleX, m_margin.top() + m_maxValueY * scaleY);

    QList<BCartesianSeries>::const_iterator it = m_seriesList->begin();
    for (;  it < m_seriesList->end(); ++it) {
        QVector<QPointF> vector = it->pointVector();
        QColor color = it->color();
        int width = it->widht();
        int type = it->type();

        pen.setWidth(width);
        pen.setColor(color);
        painter.setPen(pen);

        polygon.clear();

        QVector<QPointF> *resultVector = new QVector<QPointF>;
        QVector<QPointF>::const_iterator it = vector.begin();
        for (; it < vector.end(); ++it) {
            QPointF point(center.x() + it->x() * scaleX, center.y() - it->y() * scaleY);
            resultVector->append(point);
        }
        polygon << *resultVector;

        if (type == chartType::points) {
            painter.drawPoints(polygon);
        }
        if (type == chartType::polyline) {
            painter.drawPolyline(polygon);
        }
        if (type == chartType::polygon) {
            painter.drawPolygon(polygon);
        }
        if (type == chartType::fillpath) {
            QPainterPath path;
            path.addPolygon(polygon);
            painter.fillPath(path, QBrush(color));
        }
   }
}

void BCartesianChart::clear()
{
    m_seriesList->clear();
    repaint();
}

void BCartesianChart::addSeries(BCartesianSeries *series)
{
    m_seriesList->append(*series);
    repaint();
}






// BCartesianSeries functions
BCartesianSeries::BCartesianSeries(QVector<QPointF> pointVector,
                                   QColor color,
                                   chartType type,
                                   int widht,
                                   QString name)
{
    m_pointVector = pointVector;
    m_color = color;
    m_type = type;
    m_widht = widht;
    m_name = name;
}

QColor BCartesianSeries::color() const
{
    return m_color;
}

void BCartesianSeries::setColor(const QColor &color)
{
    m_color = color;
}

int BCartesianSeries::widht() const
{
    return m_widht;
}

void BCartesianSeries::setWidht(int widht)
{
    m_widht = widht;
}

QString BCartesianSeries::name() const
{
    return m_name;
}

void BCartesianSeries::setName(const QString &name)
{
    m_name = name;
}

QVector<QPointF> BCartesianSeries::pointVector() const
{
    return m_pointVector;
}

void BCartesianSeries::setPointVector(const QVector<QPointF> &pointVector)
{
    m_pointVector = pointVector;
}

int BCartesianSeries::type() const
{
    return m_type;
}

void BCartesianSeries::setType(int type)
{
    m_type = type;
}
