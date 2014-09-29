#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>

#include <QSettings>

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

public slots:
    void exportScene();
    void importScene();

    inline void setTabsNorth() {
        setTabPosition(QTabWidget::North);
    }
    inline void setTabsWest() {
        setTabPosition(QTabWidget::West);
    }
    inline void setTabsEast() {
        setTabPosition(QTabWidget::East);
    }
    inline void setTabsSouth() {
        setTabPosition(QTabWidget::South);
    }

    void setTabPosition(QTabWidget::TabPosition pos);

    void syncLayout();

private:
    QSettings settings;
    Ui::Window *ui;
};

#endif // MAINWINDOW_H
