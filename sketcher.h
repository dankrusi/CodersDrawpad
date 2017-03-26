#ifndef SKETCHER_H
#define SKETCHER_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QList>

class VectorPath;

class Sketcher : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Sketcher(QObject *parent = 0);
    virtual ~Sketcher() {}
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void setZoom(double z);


protected:
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event );
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent *event);

signals:
    
public slots:
    void loadImage(QString filename) {
        _image.load(filename);
        _centerX = _image.width()/2;
        _centerY = _image.height()/2;
        update();
    }

private:
    QPixmap _image;
    double _centerX;
    double _centerY;
    double _zoom;
    VectorPath *_currentPath;
    
};

#endif // SKETCHER_H
