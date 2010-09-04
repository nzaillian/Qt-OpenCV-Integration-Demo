#include <QDebug>
#include "cvlabel.h"

CVLabel::CVLabel(QWidget *parent) :
    QLabel(parent)
{
    this->cur_image_pixmap = QPixmap();
    this->cur_overlay_pixmap = QPixmap();
}

CVLabel::~CVLabel()
{
}

void CVLabel::set_image_processor(CVImageProcessor *cv_image_processor)
{
    this->cv_image_processor = cv_image_processor;
}

CVImageProcessor* CVLabel::get_image_processor()
{
    return this->cv_image_processor;
}

void CVLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(this->cv_image_processor)
    {
        painter.drawPixmap(0,0,this->cur_image_pixmap);

        QPen pen(Qt::green, 4);
        painter.setPen(pen);

       if(!this->cv_image_processor->get_face_locations().isEmpty())
        {
            QRect first_face_loc = this->cv_image_processor->get_face_locations().at(0);
            painter.setPen(pen);
            painter.drawRect(first_face_loc);

            this->cur_image_pixmap = this->cur_image_pixmap.scaled(first_face_loc.size());
            painter.drawPixmap(first_face_loc.x(), first_face_loc.y(), this->cur_overlay_pixmap);
        }
    }

}

void CVLabel::set_cur_image_pixmap(QPixmap pixmap)
{
    this->cur_image_pixmap = pixmap;
}

void CVLabel::set_cur_overlay(QPixmap pixmap)
{
    this->cur_overlay_pixmap = pixmap;
}
