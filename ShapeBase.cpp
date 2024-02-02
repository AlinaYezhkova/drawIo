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
