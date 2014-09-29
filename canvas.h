#ifndef DRAWSNER_H
#define DRAWSNER_H

#include <QWidget>
#include <QImage>
#include <QTimer>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);

    void addLayer(QString name, QSize size =QSize(900, 700));

    QImage exportImage();
    bool event(QEvent *);
    void paint();

private slots:
    void doRepaint();

private:
    typedef QPair<QString, QImage> LAYER;

    QRect dirty;
    QPoint lastPos;
    qreal lastPressure;
    QTimer repaint;
    QList<LAYER> layers;
    QPixmap cursor;
};

#endif // DRAWSNER_H
