This application demonstrates one approach to integrating the OpenCV computer vision library with the Qt cross-platform application framework.

The application leverages Qt's QThread class to isolate resource-intensive image-processing tasks from UI event handling and other, less intensive tasks.  Certain classes in the UI thread and the processing thread share a common CVImage object (IplImage-QImage pair).  The CVImageProcessor class, which inhabits the image processing thread, emits a signal ("current_frame_updated()") whenever it finishes processing a frame.  The CVWidget class, which inhabits the UI thread, receives this signal and reads the processed frame.  Mutexes are used to prevent concurrent access to the shared CVImage object so that its data isn't corrupted (though this may not actually be necessary -- Qt's access serialization model for shared objects in multithreaded apps is a little nebulous to me.  You might actually be able to remove the Mutexes and be alright...).  This particular demo does face detection, and the outlining of the detected face, which is ordinarily done using functions from OpenCV's highgui library is, for demonstrative purposes, done using a QPainter (within the CVLabel class).  I hope that this source might be useful to anyone struggling integrate Qt and OpenCV in a slick manner.

NOTES:

You will likely need to modify the header/library search paths listed in the .pro file.  I installed OpenCV using Macports, and the paths listed in the .pro here are the default install path selected by Macports for those files (/opt/local/include/opencv and /opt/local/lib).

I have tested this program with version 4.6 of Qt and version 2.0 of OpenCV on Mac OS X.

BUILD INSTRUCTIONS:

Assuming you have satisfied the dependencies (Qt Framework and OpenCV), just run qmake to generate a makefile or XCode/Visual Studio project, build and run!  Alternately, you can load the project into Qt Creator and build in that environment.



