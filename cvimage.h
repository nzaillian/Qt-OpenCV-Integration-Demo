#ifndef CV_IMAGE_H
#define CV_IMAGE_H

#include <cxcore.h>
#include <QtGui/QImage>

#include "cvutil.h" 
/*!
A simple class to encapsulate IplImage-QImage pairs.
*/
class CVImage
{
public:
        CVImage();
        CVImage(IplImage ipl_image);
        CVImage(QImage q_image);
        CVImage(IplImage ipl_image, QImage q_image);
        virtual ~CVImage();

        /*member variables*/
        IplImage ipl_image;
        QImage q_image;
};

#endif
