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
    p.setBrush(Qt::black);
    p.setPen(Qt::NoPen);

    for(int i=1; i<=10; i++) {
        p.setOpacity((1.0 - i/10.0) * 0.8);
        p.drawEllipse(QPoint(10, 10), i, i);
    }
    cursor = QPixmap::fromImage(circle);

    repaint.setInterval(0);
    repaint.setSingleShot(true);
    connect(&repaint, SIGNAL(timeout()), this, SLOT(doRepaint()));


    setCursor(QCursor(cursor, 10, 10));
}

QImage Drawsner::exportImage() {
    QImage image(minimumSize(), QImage::Format_RGB32);
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
        QPoint sizeOffset(qMax(0, width()/2-minimumWidth()/2), qMax(0, height()/2-minimumHeight()/2));
        QPoint offset(cursor.width()/2, cursor.height()/2);
        QPoint pos = ((QTabletEvent*)ev)->pos();
        qDebug() << "Moved from" << lastPos << "to" << pos;

        int xDistance = pos.x() - lastPos.x();
        int yDistance = pos.y() - lastPos.y();
        int distance = qMax(qAbs(xDistance), qAbs(yDistance));
        if(distance < 1)
            break;

        QPointF move = QPointF((float)xDistance/(float)distance, (float)yDistance/(float)distance);
        QPointF cPos = lastPos - offset - sizeOffset;
        QPainter p(&layers[0].second);
        p.setRenderHint(QPainter::Antialiasing);
        p.setRenderHint(QPainter::SmoothPixmapTransform);
        p.setRenderHint(QPainter::HighQualityAntialiasing);
        p.setOpacity(1);

        qDebug() << "Calculations" << xDistance << yDistance << distance << move;
        for(int i=0; i<distance; i++) {
            p.setOpacity(((QTabletEvent*)ev)->pressure()*0.4);
            p.drawPixmap(cPos, cursor);
            cPos += move;
        }

        QPoint topLeft(qMin(lastPos.x(), pos.x()), qMin(lastPos.y(), pos.y()));
        QPoint bottomRight(qMax(lastPos.x(), pos.x()), qMax(lastPos.y(), pos.y()));
        dirty |= QRect(topLeft - offset, bottomRight + offset);
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
    QPoint sizeOffset(qMax(0, width()/2-minimumWidth()/2), qMax(0, height()/2-minimumHeight()/2));
    paint.fillRect(QRect(sizeOffset,minimumSize()),Qt::white);

    foreach(LAYER layer, layers)
        paint.drawImage(sizeOffset, layer.second);
}
