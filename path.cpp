#include "path.h"

#include <QPainterPath>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <qmath.h>

#include "sketcher.h"
#include "point.h"
#include "controlpoint.h"

VectorPath::VectorPath(Sketcher *parent) :
     QGraphicsItem((QGraphicsItem*)parent)
{
    _sketcher = parent;
    _zoom = 1.0;
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void VectorPath::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {


    painter->setRenderHint(QPainter::Antialiasing,true);

    // Get path
    QPainterPath path = this->path();

    if(isSelected()) {
        // Show edit mode selection
        double penWidth = 1.0*(1.0/_zoom);
        painter->setPen(QPen(Qt::black,penWidth,Qt::DotLine));
        painter->drawPath(path);
        painter->drawRect(this->boundingRect());
    } else {
        // Show actual path
        painter->setPen(QPen(Qt::blue,3));
        painter->drawPath(path);
    }
}

QPainterPath VectorPath::path() const {
    QPainterPath path;
    if(_points.count() > 0) {
        path.moveTo(_points.first()->pos());
        foreach(Point *handle, _points) {
            if(handle->prev() && handle->prev()->handleType() == POINT_TYPE_CUBIC) {
                QPointF c1;
                c1 = handle->c1()->pos()+handle->pos();
                if(handle->prev()) c1 = handle->prev()->c2()->pos()+handle->prev()->pos();
                path.cubicTo(
                            c1,
                            handle->c1()->pos()+handle->pos(),
                            handle->pos());
            } else if(handle->handleType() == POINT_TYPE_LINE) {
                path.lineTo(handle->pos());
            } else if(handle->handleType() == POINT_TYPE_CUBIC) {
                QPointF c1;
                c1 = handle->c1()->pos()+handle->pos();
                if(handle->prev()) c1 = handle->prev()->c2()->pos()+handle->prev()->pos();
                path.cubicTo(
                            c1,
                            handle->c1()->pos()+handle->pos(),
                            handle->pos());
            }
        }
    }
    return path;
}

void VectorPath::save(QSettings *settings)
{
}

void VectorPath::load(QSettings *settings)
{
}

QRectF VectorPath::boundingRect() const {


    //int padding = 10.0*(1.0/_zoom);
    //return this->path().boundingRect().adjusted(-padding,-padding,padding,padding);


    if(_points.count() == 0) return QRectF(0,0,0,0);
    double minX = INT_MAX;
    double minY = INT_MAX;
    double maxX = INT_MIN;
    double maxY = INT_MIN;
    foreach(Point *handle, _points) {
        if(handle->pos().x() < minX) minX = handle->pos().x();
        if(handle->pos().x() > maxX) maxX = handle->pos().x();
        if(handle->pos().y() < minY) minY = handle->pos().y();
        if(handle->pos().y() > maxY) maxY = handle->pos().y();
        if(handle->c1()->isVisible()) {
            if(handle->c1()->parentPos().x() < minX) minX = handle->c1()->parentPos().x();
            if(handle->c1()->parentPos().x() > maxX) maxX = handle->c1()->parentPos().x();
            if(handle->c1()->parentPos().y() < minY) minY = handle->c1()->parentPos().y();
            if(handle->c1()->parentPos().y() > maxY) maxY = handle->c1()->parentPos().y();
        }
        if(handle->c2()->isVisible()) {
            if(handle->c2()->parentPos().x() < minX) minX = handle->c2()->parentPos().x();
            if(handle->c2()->parentPos().x() > maxX) maxX = handle->c2()->parentPos().x();
            if(handle->c2()->parentPos().y() < minY) minY = handle->c2()->parentPos().y();
            if(handle->c2()->parentPos().y() > maxY) maxY = handle->c2()->parentPos().y();
        }
    }
    double padding = 10.0*(1.0/_zoom);
    return QRectF(minX-padding,minY-padding,maxX-minX+padding*2.0,maxY-minY+padding*2.0);

}


bool VectorPath::isSelected() {
    if(QGraphicsItem::isSelected()) return true;
    foreach(Point *handle, _points) {
        if(this->scene()->selectedItems().contains(handle)) return true;
        else if(this->scene()->selectedItems().contains(handle->c1())) return true;
        else if(this->scene()->selectedItems().contains(handle->c2())) return true;
    }
    return false;
}

void VectorPath::setZoom(double z) {
    _zoom = z;
    foreach(Point *handle, _points) {
        handle->setZoom(z);
    }
}

void VectorPath::mouseDoubleClickEvent (QGraphicsSceneMouseEvent *event) {
    addPointLocal(event->pos().x(),event->pos().y());
}

void VectorPath::addPointLocal(int localX, int localY) {
    // Create handle
    Point *newPoint = new Point(this);
    newPoint->setZoom(_zoom);
    newPoint->setPos(localX,localY);

    // Auto-insert?
    if(true) {
        double minDistance = INT_MAX;
        int insertion = 0;
        int i = 0;
        foreach(Point *handle, _points) {
            double dx = newPoint->x() - handle->x();
            double dy = newPoint->y() - handle->y();
            double distance = qSqrt(dx*dx + dy*dy);
            if(distance < minDistance) {
                insertion = i+1;
                minDistance = distance;
            }
            i++;
        }
        _points.insert(insertion,newPoint);
    } else {
        _points.append(newPoint);
    }

    // Rehook
    int index = _points.indexOf(newPoint);
    Point *prev = NULL;
    Point *next = NULL;
    if(index > 0) prev = _points.at(index-1);
    if(index < _points.count()-1) next = _points.at(index+1);
    newPoint->setPrev(prev);
    newPoint->setNext(next);
    if(prev != NULL) prev->setNext(newPoint);
    if(next != NULL) next->setPrev(newPoint);

    // Make sure we are selected and redraw
    this->setSelected(true);
    this->scene()->update();
}

void VectorPath::addPointAbsolute(int absoluteX, int absoluteY) {
    addPointLocal(-this->x()+absoluteX,-this->y()+absoluteY);
}
