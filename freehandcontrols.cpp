#include "freehandcontrols.h"
#include "ui_freehandcontrols.h"

FreehandControls::FreehandControls(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FreehandControls)
{
    ui->setupUi(this);
}

FreehandControls::~FreehandControls()
{
    delete ui;
}
