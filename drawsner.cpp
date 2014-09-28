#include "drawsner.h"

#include <QTabletEvent>
#include <QPainter>
#include <QDebug>
#include <QEvent>

Drawsner::Drawsner(QWidget *parent) :
    QWidget(parent)
{
    addLayer("Untitled");
    //setMouseTracking(true);

    QImage circle(20, 20, QImage::Format_ARGB32);
    circle.fill(Qt::transparent);


    QPainter p(&circle);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::HighQualityAntialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    for(int i=1; i<=10; i++) {
        p.setOpacity((1.0 - i/10.0) * 0.8);
        p.drawEllipse(QPoint(10, 10), i, i);
    }

    repaint.setInterval(0);
    repaint.setSingleShot(true);
    connect(&repaint, SIGNAL(timeout()), this, SLOT(doRepaint()));

    cursor = QPixmap::fromImage(circle);

    setCursor(QCursor(cursor, 10, 10));
}

QImage Drawsner::exportImage() {
    QImage image(size(), QImage::Format_RGB32);
    image.fill(Qt::white);

    QPainter paint(&image);
    foreach(LAYER layer, layers)
        paint.drawImage(0, 0, layer.second);

    return image;
}

void Drawsner::doRepaint() {
    qDebug() << "Repainting Dirty Region" << dirty;
    QWidget::repaint(dirty);
    dirty = QRect();
}

void Drawsner::addLayer(QString name, QSize size) {
    QImage buffer(size, QImage::Format_ARGB32);
    buffer.fill(Qt::transparent);

    layers.append(LAYER(name, buffer));

    QSize minSize;
    foreach(LAYER layer, layers) {
        minSize = minSize.expandedTo(layer.second.size());
    }
    setMinimumSize(minSize);
}

bool Drawsner::event(QEvent * ev) {
    switch(ev->type()) {
    case QEvent::Paint:
        paint();
        break;

    case QEvent::TabletEnterProximity:
        qDebug() << "Tablet Pen Ready";
        break;

    case QEvent::TabletLeaveProximity:
        qDebug() << "Tablet Pen Left";
        break;

    case QEvent::TabletMove:
    {
        QPoint offset(cursor.width()/2, cursor.height()/2);
        QPoint pos = ((QTabletEvent*)ev)->pos();
        qDebug() << "Moved from" << lastPos << "to" << pos;

        int xDistance = qAbs(lastPos.x() - pos.x());
        int yDistance = qAbs(lastPos.y() - pos.y());
        int distance = qMax(xDistance, yDistance);
        if(distance < 1)
            break;

        QPointF move = QPointF(xDistance/distance, yDistance/distance);
        QPointF cPos = pos - offset;
        QPainter p(&layers[0].second);
        p.setRenderHint(QPainter::Antialiasing);
        p.setRenderHint(QPainter::SmoothPixmapTransform);
        p.setRenderHint(QPainter::HighQualityAntialiasing);
        for(int i=0; i<distance; i++) {
            p.setOpacity(((QTabletEvent*)ev)->pressure());
            p.drawPixmap(cPos, cursor);
            cPos += move;
        }

        qDebug() << "Adding Dirty Region" << QRect(pos - offset, QSize(xDistance, yDistance) + cursor.size()) << dirty;
        dirty |= QRect(pos - offset, QSize(xDistance, yDistance) + cursor.size());
        qDebug() << "Combined" << dirty;
        repaint.start();
        lastPos = pos;
    }
        break;

    case QEvent::TabletPress:
        lastPos = ((QTabletEvent*)ev)->pos();
        break;

    case QEvent::TabletRelease:
        break;

    default:
        qDebug() << "Unhandled" << ev;
        return QWidget::event(ev);
    }

    return true;
}

void Drawsner::paint() {
    QPainter paint(this);
    paint.fillRect(QRect(QPoint(0,0),size()),Qt::white);

    foreach(LAYER layer, layers)
        paint.drawImage(0, 0, layer.second);
}
