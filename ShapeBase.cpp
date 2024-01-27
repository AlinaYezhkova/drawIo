#include "ShapeBase.h"

void Circle::draw(QPainter *painter, const QRectF &rect)
{
    painter->setBrush(m_bgColor);
    painter->setPen(QPen(m_color, 0.5));

    painter->drawEllipse(m_position.rx(), m_position.ry()
                         , m_position.rx() + 2 * m_radius
                         , m_position.ry() + 2 * m_radius);

}
