#ifndef CV_WIDGET_H
#define CV_WIDGET_H

#include "cvutil.h"
#include "cvimage.h"
#include "imageprocessingthread.h"
#include "cvlabel.h"
#include "GlobalEnums.h"

#include <QtGui/QImage>
#include <QtGui/QLabel>
#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtCore/QRect>
#include <QtCore/QList>
#include <QtGui/QWidget>
#include <QtCore/QThread>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QPixmap>
#include <QMutex>
#include <QDebug>

#include<cv.h>
#include<cvaux.h>
#include <cxcore.h>
#include <highgui.h>


class CVWidget : QWidget{
    Q_OBJECT
public:
    explicit CVWidget(QWidget *parent = 0);
    virtual ~CVWidget();
    void set_framerate(double framerate);
    void capture_frame();
    void set_image_display_area(CVLabel *label);
    bool set_haar_cascade(QString cascade_name);

    /*public member variables*/
    CVLabel *image_display_area;
    ImageProcessingMode current_mode;

public slots:
    void display_current_frame();
    void start_capture();
    void stop_capture();
    void connect_image_processor_to_display_method();

private:
    ImageProcessingThread *image_processing_thread;
    CVImage *shared_cv_image;
    QImage *cur_image_qimage;
    IplImage *cur_image_iplimage;
    QMutex *mutex;
    void start_image_processing_thread();
    void stop_image_processing_thread();
    void outline_face();
};

#endif
