#include "Circle.h"

void Circle::draw(QPainter *painter, const QRectF &rect)
{
    painter->setBrush(m_bgColor);
    painter->setPen(QPen(m_color, 0.5));

    painter->drawEllipse(m_position.rx(), m_position.ry()
                         , 2*m_radius, 2*m_radius);

    painter->setPen(QPen(Qt::blue, 10));
    painter->drawPoint(m_position);
    qreal x = m_position.rx()+m_radius;
    qreal y = m_position.ry()+m_radius;
    QPointF c = {x,y};
    painter->drawPoint(c);
}

bool Circle::pointBelongs(Position position)
{
    double Xcenter = m_position.rx()+m_radius;
    double Ycenter = m_position.ry()+m_radius;
    Position center = {Xcenter, Ycenter};
    if(distance(center, position) <= m_radius) {
        return true;
    }
    return false;
}
