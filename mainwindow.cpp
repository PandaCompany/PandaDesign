#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawsner.h"

#include <QScrollArea>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QScrollArea* area = new QScrollArea();
    area->setFrameShape(QFrame::NoFrame);
    area->setWidget(new Drawsner());

    connect(ui->actionExport, SIGNAL(triggered()), this, SLOT(exportScene()));

    ui->tabWidget->addTab(area, "Untitled");
}

void MainWindow::exportScene() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export Scene"), "",
             tr("PNG Image (*.png);;JPEG Image (*.jpg,*.jpeg);;All Files (*)"));
    if(!fileName.isNull())
        ((Drawsner*)((QScrollArea*)ui->tabWidget->currentWidget())->widget())->exportImage().save(fileName);
}

void MainWindow::importScene() {

}

MainWindow::~MainWindow()
{
    delete ui;
}
