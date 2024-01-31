#include "ShapeBase.h"

double ShapeBase::distance(Position a, Position b)
{
    double xSquared = (a.rx()-b.rx()) * (a.rx()-b.rx());
    double ySquared = (a.ry()-b.ry()) * (a.ry()-b.ry());
//    qDebug() << a.rx() << ", " << a.ry() << "; "
//             << a.rx()-b.rx() << "; "
//             << b.rx() << ", " << b.ry() << "; "
//             << a.ry()-b.ry() << "; "
//             << sqrt(xSquared + ySquared);
    return sqrt(xSquared + ySquared);
}

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
    // TODO: добавить это как член
    double Xcenter = m_position.rx()+m_radius;
    double Ycenter = m_position.ry()+m_radius;
    Position center = {Xcenter, Ycenter};
    if(distance(center, position) <= m_radius) {
        return true;
    }
    return false;
}

void Square::draw(QPainter *painter, const QRectF &rect)
{
    painter->setBrush(m_bgColor);
    painter->setPen(QPen(m_color, 0.5));

    painter->drawRect(m_position.rx(), m_position.ry()
                      , m_side, m_side);

    painter->setPen(QPen(Qt::blue, 10));
    painter->drawPoint(m_position);
}

bool Square::pointBelongs(Position position)
{

//  0,0            0+x,0
//    ---------------
//    |             |
//    |             |
//    ---------------
//  0,0+y          0+x,0+y


    // TODO: добавить это как члены
    Position northWest = m_position;
    Position northEast = {m_position.rx()+m_side, m_position.ry()};
    Position southEast = {m_position.rx()+m_side, m_position.ry()+m_side};
    Position southWest = {m_position.rx(), m_position.ry()+m_side};

//    (Bx - Ax) * (Py - Ay) - (By - Ay) * (Px - Ax)
//    где (Px, Py) - наша точка, а (Ax, Ay)-(Bx, By) - очередная сторона МНОГОугольника
//    в каком-то фиксированном направлении обхода.
//    Если знаки совпадают, то точка лежит внутри. При обходе против часовой стрелки
//    все такие произведения будут положительными, если точка лежит строго внутри.
//    При обходе по часовой стрелке - отрицательными.

    // TODO: сторону как объект
    double north = evaluateBelong(position, northEast, northWest);
    double west = evaluateBelong(position, northWest, southWest);
    double south = evaluateBelong(position, southWest, southEast);
    double east = evaluateBelong(position, southEast, northEast);

    bool allNonNegative = north >= 0 && west >= 0
                       && south >= 0 && east >= 0;

    bool allNegative = north < 0 && west < 0
                       && south < 0 && east < 0;

    return allNonNegative || allNegative;
}
