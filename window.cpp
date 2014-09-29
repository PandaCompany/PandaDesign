#include "window.h"
#include "ui_window.h"
#include "freehandcontrols.h"
#include "canvas.h"

#include <QScrollArea>
#include <QFileDialog>

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    connect(ui->actionExport, SIGNAL(triggered()), this, SLOT(exportScene()));

    QScrollArea* area = new QScrollArea();
    area->setFrameShape(QFrame::NoFrame);
    area->setWidget(new Canvas());
    area->setWidgetResizable(true);

    connect(ui->actionTabsNorth, SIGNAL(triggered()), this, SLOT(setTabsNorth()));
    connect(ui->actionTabsWest, SIGNAL(triggered()), this, SLOT(setTabsWest()));
    connect(ui->actionTabsEast, SIGNAL(triggered()), this, SLOT(setTabsEast()));
    connect(ui->actionTabsSouth, SIGNAL(triggered()), this, SLOT(setTabsSouth()));

    ui->scenes->addTab(area, "Untitled Scene*");
    syncLayout();
}

void Window::setTabPosition(QTabWidget::TabPosition pos) {
    ui->scenes->setTabPosition(pos);
    settings.setValue("tabPosition", (quint8)pos);
}

void Window::syncLayout() {
    setTabPosition((QTabWidget::TabPosition)settings.value("tabPosition", (quint8)QTabWidget::North).value<quint8>());
    restoreGeometry(settings.value("geom").toByteArray());
    restoreState(settings.value("state").toByteArray());
}

void Window::exportScene() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export Scene"), "",
             tr("PNG Image (*.png);;JPEG Image (*.jpg,*.jpeg);;All Files (*)"));
    if(!fileName.isNull())
        ((Canvas*)((QScrollArea*)ui->scenes->currentWidget())->widget())->exportImage().save(fileName);
}

void Window::importScene() {
}

Window::~Window()
{
    settings.setValue("geom", saveGeometry());
    settings.setValue("state", saveState());
    delete ui;
}
