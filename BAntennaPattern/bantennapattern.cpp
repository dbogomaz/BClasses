#include "bantennapattern.h"

// constructors
BAntennaPattern::BAntennaPattern(QWidget *parent) : QWidget(parent)
  , m_angleTickCount(13)
  , m_gridColor(Qt::gray)
  , m_margin(10, 5, 10, 18)
  , m_maxAngle(90)
  , m_maxValue(1)
  , m_polar(false)
  , m_polarMargin(22, 14, 22, 5)
  , m_valueTickCount(5)
{
    m_patternSeriesList = new QList<BAntennaPatternSeries>;
}


// getters
int BAntennaPattern::angleTickCount() const
{
    return m_angleTickCount;
}

QColor BAntennaPattern::gridColor() const
{
    return m_gridColor;
}

bool BAntennaPattern::isPolar() const
{
    return m_polar;
}

int BAntennaPattern::maxAngle() const
{
    return m_maxAngle;
}

double BAntennaPattern::maxValue() const
{
    return m_maxValue;
}

int BAntennaPattern::valueTickCount() const
{
    return m_valueTickCount;
}

void BAntennaPattern::clear()
{
    m_patternSeriesList->clear();
}

void BAntennaPattern::addSeries(BAntennaPatternSeries *series)
{
    m_patternSeriesList->append(*series);
}



// setters
void BAntennaPattern::setAngleTickCount(int angleTickCount)
{
    if (angleTickCount > 1) {
        m_angleTickCount = angleTickCount;
        repaint();
    }
}

void BAntennaPattern::setGridColor(const QColor &gridColor)
{
    m_gridColor = gridColor;
    repaint();
}

void BAntennaPattern::setMaxAngle(int maxAngle)
{
    m_maxAngle = maxAngle;
    repaint();
}

void BAntennaPattern::setMaxValue(double maxValue)
{
    if (maxValue) {
        m_maxValue = maxValue;
        repaint();
    }
}

void BAntennaPattern::setPolar(bool polar)
{
    m_polar = polar;
    repaint();
}

void BAntennaPattern::setValueTickCount(int valueTickCount)
{
    m_valueTickCount = valueTickCount;
    repaint();
}



// QWidget interface
void BAntennaPattern::paintEvent(QPaintEvent *event)
{
    drawBackGround();
    if (isPolar()) {
        drawPolarGrid();
        drawPolarSeries();
    } else {
        drawGrid();
        drawSeries();
    }
}



// inside functions
void BAntennaPattern::drawBackGround()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int w = this->size().width();
    int h = this->size().height();
    int radius = 5;// закругление углов
    QColor backGroundColor(Qt::white);
    QRect rect(0, 0, w, h);

//    QPen pen(backGroundColor);
//    QBrush brush(backGroundColor);
//    painter.setPen(pen);
//    painter.setBrush(brush);
//    painter.drawRoundedRect(rect, radius, radius);

    QPainterPath painterPath;
    painterPath.addRoundedRect(rect, radius, radius);
    painter.fillPath(painterPath, QBrush(backGroundColor));

}

void BAntennaPattern::drawGrid()
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
    double step = m_maxAngle * 2 / (m_angleTickCount - 1);
    double hScale = double(w - m_margin.left() - m_margin.right()) / (m_maxAngle * 2);// масштаб
    for (double angle = -m_maxAngle; angle <= m_maxAngle; angle += step) {
        pen.setColor(m_gridColor);
        pen.setWidth(lineWidth);
        if (angle == 0) {
            pen.setWidth(centralLineWidth);
        }
        painter.setPen(pen);
        int x = m_margin.left() + (angle + m_maxAngle) * hScale;
        painter.drawLine(QPointF(x, h - m_margin.bottom()),
                         QPointF(x, m_margin.top()));

        // настраиваем подписи верт.линий
        pen.setColor(textColor);
        painter.setPen(pen);
        if (angle == 0) {
            x -= 4;
        }
        if (angle < 0) {
            x -= 11;
        }
        if (angle > 0) {
            x -= 7;
        }
        int y = h - 5;
        // подписываем
        painter.drawText(QPointF(x, y), QString::number(angle));
    }

    // рисуем горизонтальные линии
    double vScale = double(h - m_margin.top() - m_margin.bottom()) / (m_valueTickCount - 1);// масштаб
    for (int val = 0; val < m_valueTickCount; ++val) {
        pen.setColor(m_gridColor);
        pen.setWidth(lineWidth);
        if (val == m_valueTickCount - 1) {
            pen.setWidth(centralLineWidth);
        }
        painter.setPen(pen);
        int y = m_margin.top() + val * vScale;
        painter.drawLine(QPointF(m_margin.left(), y),
                         QPointF(w - m_margin.right(), y));

        // настраиваем подписи гор.линий
        double hLineStep = m_maxValue / (m_valueTickCount - 1);
        pen.setColor(textColor);
        painter.setPen(pen);
        if (val != m_valueTickCount - 1) {
           int x = w / 2 + 2;
           y += 12;
           double value = m_maxValue - hLineStep * val;
           // подписываем
           painter.drawText(QPointF(x, y), QString::number(value));
        }
    }
}

void BAntennaPattern::drawPolarGrid()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int w = this->size().width();
    int h = this->size().height();
    int lineWidth = 1;// ширина линии сетки
    int centralLineWidth = 2;// ширина центральной линии
    QColor textColor(Qt::black);// цвет подписей
    QPen pen;

    // вычисляем центр диаграммы
    QPointF center;
    center.setX(w / 2);
    center.setY(h - m_polarMargin.bottom());

    // вычисляем возможные радиусы и выбираем минимальный
    QList<int> rList;
    rList << center.x() - m_polarMargin.left(); // от центра в левую сторону
    rList << center.x() - m_polarMargin.right();// от центра в правую сторону
    rList << center.y() - m_polarMargin.top();// от центра в верx
    int r = *std::min_element(rList.begin(), rList.end());

    // рисуем угловые линии
    double step = m_maxAngle * 2 / (m_angleTickCount - 1);
    for (double angle = -m_maxAngle; angle <= m_maxAngle; angle += step) {
        pen.setColor(m_gridColor);
        pen.setWidth(lineWidth);
        if (angle == 0 ||
            angle == -m_maxAngle ||
            angle == m_maxAngle) {
            pen.setWidth(centralLineWidth);
        }
        painter.setPen(pen);
        painter.drawLine(center, polarToCartesian(QPointF(angle, r), center));

        // настраиваем подписи углов
        pen.setColor(Qt::black);
        painter.setPen(pen);
        QPointF textPoint = polarToCartesian(QPointF(angle, r), center);
        textPoint.ry() -= 4;
        if (angle == 0) {
            textPoint.rx() -= 3;
        }
        if (angle < 0) {
            textPoint.rx() += 9 * (qSin(qDegreesToRadians(double(angle))) - 1);
        }
        if (angle > 0) {
            textPoint.rx() += 7 * (qSin(qDegreesToRadians(double(angle))) - 1);
        }
        // подписываем
        painter.drawText(textPoint, QString::number(angle));
    }

    // рисуем радиальные линии
    double rScale = r / (m_valueTickCount - 1);
    for (int val = 1; val < m_valueTickCount; ++val) {
        pen.setColor(m_gridColor);
        pen.setWidth(lineWidth);
        painter.setPen(pen);
        QRect rect(center.x() - val * rScale,
                   center.y() - val * rScale,
                   2 * val * rScale,
                   2 * val * rScale);
        painter.drawArc(rect, (90 - m_maxAngle) * 16, (2 * m_maxAngle) * 16);

        // настраиваем подписи радиальных линий
        double hLineStep = m_maxValue / (m_valueTickCount - 1);
        pen.setColor(textColor);
        painter.setPen(pen);
//        if (val != m_valueTickCount - 1) {
           int x = center.x() + 2;
           int y = center.y() - (m_valueTickCount - val) * rScale;
           y += 12;
           double value = m_maxValue - hLineStep * (val - 1);
           // подписываем
           painter.drawText(QPointF(x, y), QString::number(value));
//        }
    }
}

void BAntennaPattern::drawSeries()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;

    int w = this->size().width();
    int h = this->size().height();

    QPolygonF polygon;

    double hScale = double(w - m_margin.left() - m_margin.right()) / (m_maxAngle * 2);// масштаб
    double vScale = double(h - m_margin.top() - m_margin.bottom()) / m_maxValue;// масштаб
    QPointF center(m_margin.left() + m_maxAngle * hScale, h - m_margin.bottom());

    QList<BAntennaPatternSeries>::const_iterator it = m_patternSeriesList->begin();
    for (;  it < m_patternSeriesList->end(); ++it) {
        QVector<QPointF> vector = it->pointVector();
        QColor color = it->color();
        int width = it->widht();

        pen.setWidth(width);
        pen.setColor(color);
        painter.setPen(pen);

        polygon.clear();

        QVector<QPointF> *resultVector = new QVector<QPointF>;
        QVector<QPointF>::const_iterator it = vector.begin();
        for (; it < vector.end(); ++it) {
            QPointF point(center.x() + it->x() * hScale, center.y() - it->y() * vScale);
//            qDebug() << *it;
            resultVector->append(point);
        }
        polygon << *resultVector;

        painter.drawPolyline(polygon);

//        QPainterPath path;
//        path.addPolygon(polygon);
//        painter.fillPath(path, QBrush(color));
    }
}

void BAntennaPattern::drawPolarSeries()
{

    int w = this->size().width();
    int h = this->size().height();

    // вычисляем центр диаграммы
    QPointF center;
    center.setX(w / 2);
    center.setY(h - m_polarMargin.bottom());

    // вычисляем возможные радиусы и выбираем минимальный
    QList<int> rList;
    rList << center.x() - m_polarMargin.left(); // от центра в левую сторону
    rList << center.x() - m_polarMargin.right();// от центра в правую сторону
    rList << center.y() - m_polarMargin.top();// от центра в верx
    int r = *std::min_element(rList.begin(), rList.end());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;
    QPolygonF polygon;

    QList<BAntennaPatternSeries>::const_iterator it = m_patternSeriesList->begin();
    for (;  it < m_patternSeriesList->end(); ++it) {
        QVector<QPointF> vector = it->pointVector();
        QColor color = it->color();
        int width = it->widht();

        pen.setWidth(width);
        pen.setColor(color);
        painter.setPen(pen);

        polygon.clear();

        QVector<QPointF> *resultVector = new QVector<QPointF>;
        QVector<QPointF>::const_iterator it = vector.begin();
        for (; it < vector.end(); ++it) {
            QPointF point(it->x(), it->y() * r);
            resultVector->append(polarToCartesian(point, center));
        }
        polygon << *resultVector;

        painter.drawPolyline(polygon);

//        QPainterPath path;
//        path.addPolygon(polygon);
//        painter.fillPath(path, QBrush(color));
    }
}

QPointF BAntennaPattern::polarToCartesian(QPointF polar, QPointF center)
{
    QPointF cartesian;
    cartesian.setX(qSin(qDegreesToRadians(polar.x())) * polar.y() + center.x());
    cartesian.setY(center.y() - qCos(qDegreesToRadians(polar.x())) * polar.y());

    return cartesian;
}


// BAntennaPatternSeries functions
BAntennaPatternSeries::BAntennaPatternSeries(QVector<QPointF> pointVector, QColor color, int widht, QString name)
{
    m_pointVector = pointVector;
    m_color = color;
    m_widht = widht;
    m_name = name;
}

QColor BAntennaPatternSeries::color() const
{
    return m_color;
}

void BAntennaPatternSeries::setColor(const QColor &color)
{
    m_color = color;
}

int BAntennaPatternSeries::widht() const
{
    return m_widht;
}

void BAntennaPatternSeries::setWidht(int widht)
{
    m_widht = widht;
}

QString BAntennaPatternSeries::name() const
{
    return m_name;
}

void BAntennaPatternSeries::setName(const QString &name)
{
    m_name = name;
}

QVector<QPointF> BAntennaPatternSeries::pointVector() const
{
    return m_pointVector;
}

void BAntennaPatternSeries::setPointVector(const QVector<QPointF> &pointVector)
{
    m_pointVector = pointVector;
}
