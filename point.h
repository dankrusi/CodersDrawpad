#ifndef POINT_H
#define POINT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QSettings>

#define POINT_TYPE_LINE 1
#define POINT_TYPE_CUBIC 2

class VectorPath;
class ControlPoint;

class Point : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Point(VectorPath *parent = 0);
    virtual ~Point();
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    virtual bool isSelected();
    virtual void setZoom(double z);
    virtual void save(QSettings *settings);
    virtual void load(QSettings *settings);
    inline int handleType() { return _handleType; }
    inline ControlPoint* c1() { return _c1; }
    inline ControlPoint* c2() { return _c2; }
    inline Point* prev() { return _prev; }
    inline Point* next() { return _next; }
    void setPrev(Point* val);
    void setNext(Point* val);
    inline VectorPath* path() { return _path; }
    inline int uid() { return _uid; }
    
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    
public slots:
    void setHandleType(int val);

private:
    int _uid;
    int _handleType;
    double _size;
    double _zoom;
    VectorPath *_path;
    ControlPoint *_c1;
    ControlPoint *_c2;
    Point *_next;
    Point *_prev;
    
};




#endif // POINT_H
