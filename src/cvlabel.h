#ifndef CVLABEL_H
#define CVLABEL_H

#include <QLabel>

#include <QPainter>
#include <QPen>

#include "cvimageprocessor.h"

class CVLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CVLabel(QWidget *parent = 0);
    virtual ~CVLabel();
    void set_image_processor(CVImageProcessor* cv_image_processor);
    CVImageProcessor* get_image_processor();
    virtual void paintEvent(QPaintEvent *event);
    void set_cur_image_pixmap(QPixmap pixmap);
    void set_cur_overlay(QPixmap pixmap);
signals:

public slots:

private:
    CVImageProcessor* cv_image_processor;
    QPixmap cur_image_pixmap;
    QPixmap cur_overlay_pixmap;
};

#endif // CVLABEL_H
