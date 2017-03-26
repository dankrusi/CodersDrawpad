#include "controlpoint.h"

#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "point.h"
#include "path.h"

ControlPoint::ControlPoint(Point *parent) :
    QGraphicsItem(parent)
{
    setVisible(false);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    _size = 10.0;
    _zoom = 1.0;
    _point = parent;
}

ControlPoint::~ControlPoint() {

}

void ControlPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->setRenderHint(QPainter::Antialiasing,true);

    double size = _size*(1.0/_zoom);


    if(_point->path()->isSelected()) {
        if(!_point->isSelected()) painter->setOpacity(0.5);
        // Line to control handle
        double penWidth = 1.0*(1.0/_zoom);
        painter->setPen(QPen(Qt::black,penWidth));
        painter->drawLine(QLineF(0,0,-this->x(),-this->y()));
        // Handle
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::black);
        painter->drawRect(QRectF(-size/2.0,-size/2.0,size,size));
    }
}

QRectF ControlPoint::boundingRect() const {
    double minX = INT_MAX;
    double minY = INT_MAX;
    double maxX = INT_MIN;
    double maxY = INT_MIN;
    #define ASSIGN_IF_BOUNDS(VALX,VALY) if(VALX<minX)minX=VALX;if(VALX>maxX)maxX=VALX;if(VALY<minY)minY=VALY;if(VALY>maxY)maxY=VALY;
    double size = _size*(1.0/_zoom);
    ASSIGN_IF_BOUNDS(-size/2.0,-size/2.0);
    ASSIGN_IF_BOUNDS(size,size);
    ASSIGN_IF_BOUNDS(-this->x()*0.80,-this->y()*0.80);
    double padding = 0;
    return QRectF(minX-padding,minY-padding,maxX-minX+padding*2.0,maxY-minY+padding*2.0);
}

void ControlPoint::setZoom(double z) {
    _zoom = z;
}

void ControlPoint::mousePressEvent (QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mousePressEvent(event);
    this->scene()->update();
}

void ControlPoint::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseMoveEvent(event);
    this->scene()->update();
}

void ControlPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);
    this->scene()->update();
}
