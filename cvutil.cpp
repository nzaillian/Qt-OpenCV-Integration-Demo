/*
   Note: thanks to Umanga for IplImage/QImage conversion functions.
   see: http://umanga.wordpress.com/2010/04/19/how-to-covert-qt-qimage-into-opencv-iplimage-and-wise-versa.

    There are a lot of gotchas to working with OpenCV library functions, including certain subtleties relating
    to struct/object allocation/ownership.  Make sure that you only clean up after objects for which you are responsible,
    otherwise you will be looking at a lot of "object being freed was not allocated"-type errs.

*/

#include "cvutil.h"


IplImage* CVUtil::iplimage_from_qimage(QImage *qimg)
{
   IplImage *imgHeader = cvCreateImageHeader( cvSize(qimg->width(), qimg->width()), IPL_DEPTH_8U, 4);
   imgHeader->imageData = (char*) qimg->bits();

   uchar* newdata = (uchar*) malloc(sizeof(uchar) * qimg->byteCount());
   memcpy(newdata, qimg->bits(), qimg->byteCount());
   imgHeader->imageData = (char*) newdata;

   return imgHeader;
}



/*note: dynamically allocates the qimg it returns, so don't forget to delete said qimg*/
QImage* CVUtil::qimage_from_ipl_image(IplImage *iplimg)
{
    int h = iplimg->height;
    int w = iplimg->width;
    int channels = iplimg->nChannels;

    QImage *qimg = new QImage(w, h, QImage::Format_ARGB32);

    char *data = iplimg->imageData;

    for (int y = 0; y < h; y++, data += iplimg->widthStep)
    {
        for (int x = 0; x < w; x++)
        {
            char r, g, b, a = 0;
            if (channels == 1)
            {
                r = data[x*channels];
                g = data[x*channels];
                b = data[x*channels];
            }
            else if (channels == 3 || channels == 4)
            {
                r = data[x*channels+2];
                g = data[x*channels+1];
                b = data[x*channels];
            }

            if (channels == 4)
            {
                a = data[x*channels+3];
                qimg->setPixel(x, y, qRgba(r, g, b, a));
            }
            else
            {
                 qimg->setPixel(x, y, qRgb(r, g, b));
            }
         }
    }
    return qimg;
}

bool CVUtil::resource_to_file(QString resource_name, QString target_file_name)
{
    QFile file(resource_name);
    QFile target_file(target_file_name);
    if ( !target_file.open( QIODevice::ReadWrite | QIODevice::Text) )
        return false;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return false;

    else {
        /*we are going to rewrite the file entirely...*/
        target_file.remove();

        if ( !target_file.open( QIODevice::ReadWrite | QIODevice::Text) )
            return false;

        QTextStream stream( &file );
        QString line;

        while ( !stream.atEnd() ) {
            line = stream.readLine() + "\n"; // line of text excluding '\n'
            target_file.write(line.toUtf8());
        }
    }

    target_file.close();
    file.close();
   // bool did_rename_succeed = target_file.write(&file);// file.copy(target_file_name);


    return true;//did_rename_succeed;
}
