#include <stdio.h>
 
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
int main()
{
    int i;
    CvPoint v1,v2;
    char *cascade_name="..\\haarcascades\\haarcascade_lowerbody.xml";
    IplImage *image=cvLoadImage("..\\res\\test2.png",1);
    if(image==NULL)
    {
        printf("open image error\n");
        system("pause");
        return 1;
    }
    CvHaarClassifierCascade* cascade=(CvHaarClassifierCascade*)cvLoad(cascade_name,0,0,0);
    if(cascade==NULL)
    {
        printf("open cascade error\n");
        system("pause");
        return 1;
    }
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* faces=cvHaarDetectObjects(image,cascade,storage,1.1,2,0/*CV_HAAR_DO_CANNY_PRUNING*/,cvSize(30,30));
    for(i=0;i<faces->total;i++) 
    { 

        /* extract the rectanlges only */ 
        CvRect* face_rect = (CvRect*)cvGetSeqElem( faces, i );         
        v1=cvPoint(face_rect->x,face_rect->y);
        v2=cvPoint((face_rect->x+face_rect->width),(face_rect->y+face_rect->height));
        cvRectangle(image,v1,v2,CV_RGB(255,0,0),2,CV_AA,0);

    }
    cvNamedWindow("Rectangle",1);
    cvShowImage("Rectangle",image);
    cvWaitKey(0);
    free(&v1);
    free(&v2);
    cvReleaseImage(&image);
    cvReleaseMemStorage(&storage);
    
    return 0;
}
