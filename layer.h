#ifndef DRAWINGLAYER_H
#define DRAWINGLAYER_H

#include <QObject>

class QPainter;

class Layer
{
public:
    Layer();

    QRect geometry();
    void paint(QPainter&);

    void draw(QPair<QPoint, float> from, QPair<QPoint, float> to);
    void preview(QPair<QPoint, float> from, QPair<QPoint, float> to);

    QWidget* toolController();
    QObject* currentTarget();

signals:
    void toolsChanged(QWidget* toolControls);
    void targetChanged(QObject* propertiesTarget);
    void geometryChanged(QRect geometry);
};

#endif // DRAWINGLAYER_H
