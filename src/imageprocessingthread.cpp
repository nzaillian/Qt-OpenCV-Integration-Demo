#include "imageprocessingthread.h"

/*Class'run method instantiates a CVImageProcessing object and begins its own 
event loop.*/

ImageProcessingThread::ImageProcessingThread(CVImage *shared_cv_image, QMutex *mutex, QObject *parent) :
    QThread(parent)
{
    this->shared_cv_image = shared_cv_image;
    this->mutex = mutex;
    this->image_processor = NULL;
}

ImageProcessingThread::~ImageProcessingThread()
{
}

void ImageProcessingThread::run()
{
    this->image_processor = new CVImageProcessor(this->shared_cv_image, this->mutex);
    emit image_processor_instantiated();
    this->image_processor->start_capture();

    exec();
}

CVImageProcessor* ImageProcessingThread::get_image_processor(){ return this->image_processor; };
