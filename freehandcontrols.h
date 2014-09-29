#ifndef FREEHANDCONTROLS_H
#define FREEHANDCONTROLS_H

#include <QWidget>

namespace Ui {
class FreehandControls;
}

class FreehandControls : public QWidget
{
    Q_OBJECT

public:
    explicit FreehandControls(QWidget *parent = 0);
    ~FreehandControls();

private:
    Ui::FreehandControls *ui;
};

#endif // FREEHANDCONTROLS_H
