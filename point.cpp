#include "point.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "util.h"
#include "path.h"
#include "controlpoint.h"

static int POINT_UID_COUNTER = 0;

Point::Point(VectorPath *parent) :
    QGraphicsItem(parent)
{
    _uid = POINT_UID_COUNTER++;
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    _size = 20.0;
    _zoom = 1.0;
    _path = parent;
    _handleType = POINT_TYPE_LINE;
    _c1 = new ControlPoint(this);
    _c1->setPos(-20,0);
    _c2 = new ControlPoint(this);
    _c2->setPos(+20,0);
    _next = NULL;
    _prev = NULL;

    DEBUG << "uid" << _uid;

}

Point::~Point() {

}

void Point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->setRenderHint(QPainter::Antialiasing,true);

    double size = _size*(1.0/_zoom);

    if(isSelected() || _path->isSelected()) {
        if(!isSelected()) {
            painter->setOpacity(0.5);
        }
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::black);
        painter->drawEllipse(QPointF(0,0),size/2.0,size/2.0);
        if(DEBUG_OUTPUT) {
            painter->setPen(Qt::black);
            QString p = (_prev ? QString("P%1 < ").arg(_prev->uid()) : "");
            QString n = (_next ? QString(" > P%1").arg(_next->uid()) : "");
            painter->drawText(-10,-20,QString("%1[P%2]%3").arg(p).arg(_uid).arg(n));
        }
    }
}

QRectF Point::boundingRect() const {
    double size = _size*(1.0/_zoom);
    return QRectF(-size/2.0,-size/2.0,size,size);
}

bool Point::isSelected() {
    if(QGraphicsItem::isSelected()) return true;
    if(_c1->isSelected()) return true;
    if(_c2->isSelected()) return true;
    return false;
}

void Point::setZoom(double z) {
    _zoom = z;
    _c1->setZoom(z);
    _c2->setZoom(z);
}

void Point::save(QSettings *settings)
{
}

void Point::load(QSettings *settings)
{
}

void Point::mousePressEvent (QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mousePressEvent(event);
    this->scene()->update();
}

void Point::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseMoveEvent(event);
    this->scene()->update();
}

void Point::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);
    if(event->button() == Qt::RightButton) {
        if(_handleType == POINT_TYPE_CUBIC)        setHandleType(POINT_TYPE_LINE);
        else if(_handleType == POINT_TYPE_LINE)    setHandleType(POINT_TYPE_CUBIC);
    }
    this->scene()->update();
}

void Point::setHandleType(int val) {
    _handleType = val;
    if(_handleType == POINT_TYPE_LINE) {

        _c1->setVisible(false);
        _c2->setVisible(false);
        if(_prev) _prev->c2()->setVisible(false);
        if(_next) _next->c1()->setVisible(false);


    } else if(_handleType == POINT_TYPE_CUBIC) {

        _c1->setVisible(true);
        _c2->setVisible(true);
        if(_prev) _prev->c2()->setVisible(true);
        if(_next) _next->c1()->setVisible(true);
    }

    this->scene()->update();
}

void Point::setPrev(Point* val) {
    _prev = val;
}

void Point::setNext(Point* val) {
    _next = val;
}
















