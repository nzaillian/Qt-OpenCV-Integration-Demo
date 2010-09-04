#ifndef CVUTIL_H
#define CVUTIL_H

#include <QtGui/QImage>
#include <QTextStream>
#include <QtCore/QFile>

#include<cv.h>
#include<cvaux.h>
#include <cxcore.h>

/*
Class contains utility functions for converting IplImage objects to QImage objects and vice-versa.
(plus a simple function to convert a binary resource to a local file -- used, in this program, to write haar cacade XML
files bundled up as binaries back into local XML files, so that they can be passed into OpenCV library functions that 
only take file paths as params.)
*/
class CVUtil
{
public:
    static IplImage* iplimage_from_qimage(QImage* qimg);
    static QImage* qimage_from_ipl_image(IplImage* iplimg);
    static bool resource_to_file(QString resource_name, QString target_file_name);
};

#endif // CVUTIL_H
