#include <stdio.h>
 
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
int main()
{
int i;
IplImage *original = cvLoadImage(".\\src\\0.jpg",1);
IplImage *gray = cvCreateImage(cvGetSize(original), 8, 1);
cvCvtColor( original, gray, CV_BGR2GRAY ); 
CvMemStorage* storage = cvCreateMemStorage(0);
CvSeq *objectKeypoints = 0, *objectDescriptors = 0;
CvSURFParams params = cvSURFParams(500, 0);
cvExtractSURF( gray, 0, &objectKeypoints, &objectDescriptors, storage, params );
printf("Total Object Descriptors: %d\n", objectDescriptors->total);
IplImage* object_color = cvCreateImage(cvGetSize(gray), 8, 3); 
for(i = 0; i < objectKeypoints->total; i++ )
{
CvSURFPoint* r = (CvSURFPoint*)cvGetSeqElem( objectKeypoints, i );
CvPoint center;
center.x = cvRound(r->pt.x);
center.y = cvRound(r->pt.y);
int radius = cvRound(r->size*1.2/9.*2);
cvCircle( original, center, radius, cvScalar(0,0,255), 1, 8, 0 );
}
cvNamedWindow("SURF Result",1);
cvShowImage( "SURF Result", original );

cvWaitKey();

system("pause");
return 0;
}
