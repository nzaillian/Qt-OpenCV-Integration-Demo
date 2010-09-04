#include "cvwidget.h"

#define DEFAULT_FRAMERATE 29.0

/*Widget manages a CVImage and CVLabel.  Refreshes image whenever it receives a current_frame_updated() signal from the CVImageProcessor in the image processing thread*/

CVWidget::CVWidget(QWidget *parent) :
        QWidget(parent)
{

    this->shared_cv_image = new CVImage();
    this->mutex = new QMutex();
    this->image_processing_thread = new ImageProcessingThread(this->shared_cv_image, this->mutex);

    this->start_image_processing_thread();

    this->image_display_area = new CVLabel();

    this->current_mode = FACE_DETECT_SIMPLE;

    if(this->image_processing_thread->get_image_processor() != NULL)
        this->image_processing_thread->get_image_processor()->set_framerate(DEFAULT_FRAMERATE);

    this->cur_image_iplimage = NULL;
    this->cur_image_qimage = NULL;

    /*This ensures that once the CVImageProcessor that is instantiated and owned by the image_processing_thread has been allocated,
    its "current_frame_updated()" signal will be connected to this CVWidget instance's "display_current_frame()" slot
    (the connection routine happens in the body of the "connect_image_processor_to_display_method()" slot -- a little hacky, I know, but seemed
    to be the simplest solution to avoiding NULL pointer exceptions within the CVWidget class.*/
    QObject::connect(this->image_processing_thread, SIGNAL(image_processor_instantiated()), this, SLOT(connect_image_processor_to_display_method()));
}

CVWidget::~CVWidget()
{
    delete this->image_display_area;
    this->image_processing_thread->exit();
    //wait for image proc thr to properly exit...
    while(this->image_processing_thread->isRunning()){}
    delete this->image_processing_thread;
}


void CVWidget::connect_image_processor_to_display_method()
{
    QObject::connect(this->image_processing_thread->get_image_processor(), SIGNAL(current_frame_updated()), this, SLOT(display_current_frame()));
    if(this->image_processing_thread->get_image_processor())
        this->image_display_area->set_image_processor(this->image_processing_thread->get_image_processor());
}

void CVWidget::start_image_processing_thread()
{
    this->image_processing_thread->start();
}

/*terminates the image processing thread*/
void CVWidget::stop_image_processing_thread()
{
    this->image_processing_thread->terminate();
}

void CVWidget::start_capture()
{
    if(this->image_processing_thread->get_image_processor() != NULL)
        this->image_processing_thread->get_image_processor()->start_capture();
}

void CVWidget::stop_capture()
{
    if(this->image_processing_thread->get_image_processor() != NULL)
        this->image_processing_thread->get_image_processor()->stop_capture();
}

void CVWidget::set_framerate(double framerate)
{
    if(this->image_processing_thread->get_image_processor() != NULL)
        this->image_processing_thread->get_image_processor()->set_framerate(framerate);
}

void CVWidget::set_image_display_area(CVLabel *label)
{
    this->image_display_area = label;
}

void CVWidget::capture_frame()
{
    if(this->image_processing_thread->get_image_processor() != NULL)
        this->image_processing_thread->get_image_processor()->capture_frame();
}


void CVWidget::display_current_frame()
{
        mutex->lock();
        	this->image_display_area->set_cur_image_pixmap(QPixmap::fromImage(this->shared_cv_image->q_image));
        	this->image_display_area->setPixmap(QPixmap::fromImage(this->shared_cv_image->q_image));
        mutex->unlock();
}

bool CVWidget::set_haar_cascade(QString cascade_name)
{
    if(this->image_processing_thread->get_image_processor()!= NULL)
    {
        this->image_processing_thread->get_image_processor()->set_haar_cascade(cascade_name);
        return true;
    }
    return false;
}



void CVWidget::outline_face()
{

}
