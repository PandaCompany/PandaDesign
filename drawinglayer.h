#ifndef DRAWINGLAYER_H
#define DRAWINGLAYER_H

#include <QObject>

class DrawingLayer
{
public:
    DrawingLayer();

signals:
    void toolsChanged(QWidget* toolControls);
    void targetChanged(QObject* propertiesTarget);
};

#endif // DRAWINGLAYER_H
