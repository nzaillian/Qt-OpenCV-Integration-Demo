#define DEFAULT_FRAMERATE 29.0
#define DEFAULT_HAAR_CASCADE_RESOURCE_PATH ":/resources/haarcascade_frontalface_default.xml"
#define DEFAULT_HAAR_CASCADE_FILE_NAME "haarcascade_frontalface_default_file.xml"
#define DEFAULT_X_DEVIATION_THRESHOLD 190
#define DEFAULT_Y_DEVIATION_THRESHOLD 190

#include "cvimageprocessor.h"

CVImageProcessor::CVImageProcessor(CVImage *shared_cv_image, QMutex *mutex, QObject *parent) :
    QObject(parent)
{
    /*bind our instance's shared_cv_image and mutex member vars to the CVImage* and QMutex* passed to this constructor*/
    this->shared_cv_image = shared_cv_image;
    this->mutex = mutex;

    /*timer governs capture interval*/
    this->timer = new QTimer(this);

    /*defaults*/
    this->current_mode = FACE_DETECT_SIMPLE;
    this->framerate = DEFAULT_FRAMERATE;

    QString fname=QString(DEFAULT_HAAR_CASCADE_RESOURCE_PATH);
    QString tname = QString(DEFAULT_HAAR_CASCADE_FILE_NAME);

    CVUtil::resource_to_file(fname,tname);

    this->haar_cascade_name = DEFAULT_HAAR_CASCADE_FILE_NAME;


    this->set_haar_cascade(this->haar_cascade_name);
    this->storage = cvCreateMemStorage(0);

    this->x_deviation_threshold = 	DEFAULT_X_DEVIATION_THRESHOLD;
    this->y_deviation_threshold = DEFAULT_Y_DEVIATION_THRESHOLD;

    /*capture from first detected device*/
    this->capture_device = cvCaptureFromCAM( CV_CAP_ANY );

	/*default to NULL for instance's IplImage and QImage pointers*/
    this->cur_image_iplimage = NULL;
    this->cur_image_qimage = NULL;

    /*set the capture interval*/
    this->timer->setInterval((1000/this->framerate));

    /*bind QTimer::timeout() for timer to our frame-grabbing function*/
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(capture_frame()));

    this->start_capture();

}

CVImageProcessor::~CVImageProcessor()
{
    /*delete heap-allocated objects*/
    delete this->timer;
    cvReleaseMemStorage(&this->storage);
}

void CVImageProcessor::start_capture()
{
    this->timer->start();
}

void CVImageProcessor::stop_capture()
{
    this->timer->stop();
}

void CVImageProcessor::capture_frame()
{
    if(this->cur_image_qimage != NULL)
    {
        delete this->cur_image_qimage;
    }

    this->cur_image_iplimage = cvQueryFrame(this->capture_device);

    if(this->cur_image_iplimage)
        this->cur_image_qimage = CVUtil::qimage_from_ipl_image(this->cur_image_iplimage);

        /*write to the shared cv image object (lock before writing)...*/
        mutex->lock();
            if(this->cur_image_iplimage != NULL)
                this->shared_cv_image->ipl_image = *this->cur_image_iplimage;
            if(this->cur_image_qimage != NULL)
                this->shared_cv_image->q_image = *this->cur_image_qimage;
        mutex->unlock();
        /*...remove lock*/


    if(this->current_mode == FACE_DETECT_SIMPLE)
    {
        this->detect_face();
    }
    if (!this->face_locations.isEmpty())
    {
		/*write coords to terminal*/
        qDebug()<<"face coords: x="<<this->face_locations.at(0).x()<<"   y: "<<this->face_locations.at(0).y();
    }

    emit current_frame_updated();

}

void CVImageProcessor::set_framerate(double framerate)
{
    this->framerate = framerate;
    this->timer->setInterval(1000/this->framerate);
}

void CVImageProcessor::set_haar_cascade(QString cascade_name)
{
    this->haar_cascade_name = cascade_name;
    this->load_haar_cascade();
}

bool CVImageProcessor::load_haar_cascade()
{

    QFileInfo cascade_path_rel(this->haar_cascade_name);
    qDebug()<<cascade_path_rel.canonicalFilePath();
    std::string cascade_path = "./" + this->haar_cascade_name.toStdString();
    this->haar_cascade = (CvHaarClassifierCascade*) cvLoad(cascade_path.c_str());//"/Users/nickzaillian/Dropbox/Projects/Stache2/resources/haarcascade_frontalface_default.xml", 0, 0, 0 );

    /*return false if haar_cascade failed to load*/
    if (!this->haar_cascade)
    {
        return false;
    }
    else
        return true;

}

void CVImageProcessor::detect_face()
{
    /*
        Note: a more thorough treatment of this logic can be found at: http://opencv.willowgarage.com/wiki/FaceDetection
        (which was my source for much of the routine, aside from the use of the mutex to ensure thread-safety and
        the fact that we are storing the bounding rectangle for the detected faces in a QList of QRects rather than drawing
        it right onto the IplImage from within the function).
    */

    int scale = 1;

    CvPoint pt1, pt2;
    int i;

    if (this->storage)
        cvClearMemStorage( this->storage );


    if( this->haar_cascade != NULL && this->storage != NULL)
    {


        CvSeq* faces = NULL;

          if (this->cur_image_iplimage != NULL)
                 faces = cvHaarDetectObjects( this->cur_image_iplimage, this->haar_cascade, this->storage, 2.0, 3, CV_HAAR_DO_CANNY_PRUNING, cvSize(40,40) );

        if(faces != NULL)
        {
            for( i = 0; i < (faces ? faces->total : 0); i++ )
            {

                CvRect* r = (CvRect*)cvGetSeqElem( faces, i );

                pt1.x = r->x*scale;
                pt2.x = (r->x+r->width)*scale;
                pt1.y = r->y*scale;
                pt2.y = (r->y+r->height)*scale;

                if(this->face_locations.isEmpty())
                {
                    this->face_locations.append(QRect(QPoint(pt1.x, pt1.y), QPoint(pt2.x, pt2.y)));
                }
                else
                {
                    /*if we have detected a new (i.e. second, third, fourth, etc) face...*/
                    if(i >= this->face_locations.size())
                    {
                        this->face_locations.append(QRect(QPoint(pt1.x, pt1.y), QPoint(pt2.x, pt2.y)));
                    }
                    /*else only modify face locations array if loc of face detected is within [threshold] pixels of last face detected at its index*/
                    else if( (qAbs(pt1.x - this->face_locations.at(i).x()) > this->x_deviation_threshold) != TRUE && (qAbs(pt1.y - this->face_locations.at(i).y() > this->y_deviation_threshold) != TRUE) )
                    {
                        this->face_locations[i]=QRect(QPoint(pt1.x, pt1.y), QPoint(pt2.x, pt2.y));
                    }
                 }
          }
        }

    }


}

QList<QRect> CVImageProcessor::get_face_locations()
{
    return this->face_locations;
}
