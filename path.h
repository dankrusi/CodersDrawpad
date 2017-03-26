#ifndef PATH_H
#define PATH_H

#include <QGraphicsItem>
#include <QList>
#include <QGraphicsScene>
#include <QPainterPath>
#include <QSettings>

class Sketcher;
class Point;


class VectorPath : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit VectorPath(Sketcher *sketcher);
    virtual ~VectorPath() {}
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;
    virtual bool isSelected();
    void setZoom(double z);
    QPainterPath path() const;
    virtual void save(QSettings *settings);
    virtual void load(QSettings *settings);

protected:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    virtual void	focusOutEvent ( QFocusEvent * event ) {
        update();
        scene()->update();
    }

signals:
    
public slots:
    void addPointLocal(int localX, int localY);
    void addPointAbsolute(int absoluteX, int absoluteY);

private:
    double _zoom;
    Sketcher *_sketcher;
    QList<Point*> _points;
    
};

#endif // PATH_H
