#include "sketcher.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>

#include "path.h"

Sketcher::Sketcher(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    _currentPath = new VectorPath(this);
    _zoom = 1.0;
}

void Sketcher::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {


    int w = _image.width();
    int h = _image.height();

    // Image
    painter->setOpacity(0.2);
    painter->drawPixmap(0,0,_image);

    // Center cross
    double pw = (2.0)*(1.0/_zoom);
    painter->setPen(QPen(Qt::green,pw));
    painter->drawLine(_centerX,0,_centerX,h);
    painter->drawLine(0,_centerY,w,_centerY);


}

QRectF Sketcher::boundingRect() const {
    return QRectF(0,0,_image.width(),_image.height());
}

void Sketcher::setZoom(double z) {
    _zoom = z;
    _currentPath->setZoom(z);
    this->scene()->update();
}

void Sketcher::mousePressEvent ( QGraphicsSceneMouseEvent * event ) {
    QGraphicsItem::mousePressEvent(event);
}

void Sketcher::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseMoveEvent(event);
}

void Sketcher::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

    if(event->button() == Qt::LeftButton) {
        if(event->modifiers().testFlag(Qt::ControlModifier)) {
            _centerX = event->pos().x();
            _centerY = event->pos().y();
        } else {
            //_points.append(event->pos());
            //_currentPath->addPoint(event->pos().x(),event->pos().y());
        }
    }
    if(event->button() == Qt::RightButton) {
        //if(!_points.empty()) _points.removeLast();
    }

    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

void Sketcher::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent *event) {
    _currentPath->addPointAbsolute(event->pos().x(),event->pos().y());
}
