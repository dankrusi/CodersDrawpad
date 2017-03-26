#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H

#include <QObject>
#include <QGraphicsItem>

class Point;

class ControlPoint : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit ControlPoint(Point *parent = 0);
    virtual ~ControlPoint();
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void setZoom(double z);
    QPointF parentPos() { return QPointF(this->x()+this->parentItem()->x(), this->y()+this->parentItem()->y()); };

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:

public slots:

private:
    double _size;
    double _zoom;
    Point *_point;

};

#endif // CONTROLPOINT_H
