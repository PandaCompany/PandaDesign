#include "window.h"
#include "ui_window.h"
#include "drawsner.h"

#include <QScrollArea>
#include <QFileDialog>

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    QScrollArea* area = new QScrollArea();
    area->setFrameShape(QFrame::NoFrame);
    area->setWidget(new Drawsner());
    area->setWidgetResizable(true);

    ui->tabWidget->addTab(area, "Untitled");

    area = new QScrollArea();
        area->setFrameShape(QFrame::NoFrame);
        area->setWidget(new Drawsner());
        area->setWidgetResizable(true);

        ui->tabWidget->addTab(area, "Horses");
        connect(ui->actionExport, SIGNAL(triggered()), this, SLOT(exportScene()));
}

void Window::exportScene() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export Scene"), "",
             tr("PNG Image (*.png);;JPEG Image (*.jpg,*.jpeg);;All Files (*)"));
    if(!fileName.isNull())
        ((Drawsner*)((QScrollArea*)ui->tabWidget->currentWidget())->widget())->exportImage().save(fileName);
}

void Window::importScene() {
}

Window::~Window()
{
    delete ui;
}
