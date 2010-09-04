#include "toplevelwindow.h"
#include "ui_toplevelwindow.h"

/*
Main display window.
*/
ToplevelWindow::ToplevelWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToplevelWindow)
{
    ui->setupUi(this);
    w = new CVWidget(this);
    ui->label->setText("initializing...");
    w->image_display_area->setParent(ui->frame);
    this->setGeometry(200,200, this->w->image_display_area->width(), this->w->image_display_area->height());
    w->start_capture();
    this->setWindowTitle("Z's Qt/OpenCV Face Tracker");
}

ToplevelWindow::~ToplevelWindow()
{
    delete this->w;
    delete ui;
}

void ToplevelWindow::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
