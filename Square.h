#pragma once

#include "ShapeBase.h"

class Square : public ShapeBase
{
    qreal m_side;

public:

    Square(Position position, qreal side, QColor color, QColor bgColor)
        : ShapeBase(position, color, bgColor), m_side(side) {};

    void draw(QPainter *painter, const QRectF &rect) override;
    bool pointBelongs(Position position) override;

    double evaluateBelong(Position p, Position a, Position b) {
        return (b.rx() - a.rx()) * (p.ry() - a.ry()) - (b.ry() - a.ry()) * (p.rx() - a.rx());
    }
};

