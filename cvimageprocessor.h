#ifndef CVIMAGEPROCESSOR_H
#define CVIMAGEPROCESSOR_H

#include <QObject>
#include <QDebug>
#include <QList>
#include <QTimer>
#include <QString>
#include <QImage>
#include <QMutex>
#include <QPoint>
#include <QFile>
#include <QFileInfo>

#include <cxcore.h>
#include <highgui.h>
#include <cv.h>

#include "cvimage.h"
#include "GlobalEnums.h"

class CVImageProcessor : public QObject
{
    Q_OBJECT
public:
    explicit CVImageProcessor(CVImage *shared_cv_image, QMutex *mutex, QObject *parent = 0);
    virtual ~CVImageProcessor();
    void set_framerate(double framerate);
    void set_haar_cascade(QString cascade_name);

    /*public member variables*/
    ImageProcessingMode current_mode;
    QList<QRect> get_face_locations();
    CvHaarClassifierCascade* haar_cascade;
    CvMemStorage *storage;
    CVImage *shared_cv_image;

signals:
    void current_frame_updated();

public slots:
    void capture_frame();
    void start_capture();
    void stop_capture();

protected:
    virtual void detect_face();
    bool load_haar_cascade();
    double framerate;
    QImage *cur_image_qimage;
    IplImage *cur_image_iplimage;
    CvCapture *capture_device;
    QString haar_cascade_name;
    QTimer *timer;
    QMutex *mutex;
    QList<QRect> face_locations;
    int x_deviation_threshold;
    int y_deviation_threshold;
};

#endif // CVIMAGEPROCESSOR_H
