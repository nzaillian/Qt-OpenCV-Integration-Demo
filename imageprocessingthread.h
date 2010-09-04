#ifndef IMAGEPROCESSINGTHREAD_H
#define IMAGEPROCESSINGTHREAD_H
#include "cvimage.h"
#include "cvimageprocessor.h"
#include <QThread>
#include <QMutex>
#include <QDebug>

class ImageProcessingThread : public QThread
{
    Q_OBJECT
public:
    explicit ImageProcessingThread(CVImage *shared_cv_image, QMutex *mutex, QObject *parent = 0);
    virtual ~ImageProcessingThread();
    void run();
    CVImageProcessor* get_image_processor();

signals:
   void image_processor_instantiated();

private:
    CVImage *shared_cv_image;
    CVImageProcessor *image_processor;
    QMutex *mutex;
};

#endif // IMAGEPROCESSINGTHREAD_H
