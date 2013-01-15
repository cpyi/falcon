/*  Falcon
    court people detect system
    written by cpyi
    2012/12/27
    */
#include <stdio.h>
#include <cv.h>
#include <highgui.h>

int main(int argc,char **argv)
{
    /*Use 1000 point for initial possible points, create two arrays to save them*/
    const int corner_count=1000;
    int i;
    CvPoint2D32f *corners1;
    CvPoint2D32f *corners2;  
    corners1 = (CvPoint2D32f *) cvAlloc (corner_count * sizeof (CvPoint2D32f));  
    corners2 = (CvPoint2D32f *) cvAlloc (corner_count * sizeof (CvPoint2D32f));
    /*SEE DETAIL OF THIS FUNCTION*/
    CvTermCriteria criteria;  
    criteria = cvTermCriteria (CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 64, 0.01);
    /*frame datastructure*/
    IplImage *original_frame;
    IplImage *new_frame;
    IplImage *original_frame_gray;
    IplImage *new_frame_gray;
    /*Special data structure in this algorithm*/
    IplImage *eig_img;
    IplImage *temp_img;
    IplImage *prev_pyramid;
    IplImage *curr_pyramid;
    
    const char avi_name[]="..\\res\\de240.avi";
    CvCapture* capture;
    /*Open OpenCV capture handler from a file
      Use cvCaptureFromCAM(  CV_CAP_ANY ); for real case*/
    capture=cvCaptureFromAVI(avi_name);
    if(capture==NULL)
    {
        printf("File open error\n");
        system("pause");
        return;
    }
    /*handle status for each corner*/
    char *corner_status;
    corner_status=(char*)cvAlloc(corner_count);
    /*detect loop*/
    while(1)
    {
        /*get a frame from the capture handler*/
        original_frame=cvQueryFrame(capture);
        /*get the frame size for creating image later*/
        CvSize frame_size=cvGetSize(original_frame); 
        /*create image space, last parameter for number of channels, and convert original frame into gray*/
        original_frame_gray=cvCreateImage(frame_size,IPL_DEPTH_8U,1);
        cvCvtColor(original_frame,original_frame_gray, CV_RGB2GRAY);
        
        new_frame=cvQueryFrame(capture);
        new_frame_gray=cvCreateImage(frame_size,IPL_DEPTH_8U, 1);
        cvCvtColor(new_frame,new_frame_gray,CV_RGB2GRAY);
        
        eig_img=cvCreateImage(frame_size,IPL_DEPTH_32F,1); 
        temp_img=cvCreateImage(frame_size,IPL_DEPTH_32F,1);
        
        prev_pyramid = cvCreateImage (cvSize(original_frame_gray->width+8,original_frame_gray->height/3),IPL_DEPTH_8U,1);  
        curr_pyramid = cvCreateImage (cvSize(original_frame_gray->width+8,original_frame_gray->height/3),IPL_DEPTH_8U,1);
        
        /*trace possible point initially, SEE DETAIL OF THIS FUNCTION*/
        cvGoodFeaturesToTrack(original_frame_gray,eig_img,temp_img,corners1,&corner_count,0.001,5,NULL,3,0,0.04);
        /*optical flow, SEE DETAIL OF THIS FUNCTION*/
        cvCalcOpticalFlowPyrLK(original_frame_gray,new_frame_gray,prev_pyramid,curr_pyramid,corners1,corners2,corner_count,cvSize(5,5),4,corner_status,NULL,criteria,0);
        /*draw to indicate*/
        for(i=0;i<corner_count;i++) 
        {    
            if(corner_status[i])
            {
                /*SEE DETAIL OF THIS FUNCTION*/
                cvLine(new_frame,cvPointFrom32f(corners1[i]),cvPointFrom32f(corners2[i]),CV_RGB(255, 0, 0),1,CV_AA,0);
            }
        }
        cvShowImage ("Image",new_frame);  
        cvWaitKey (1); 
        cvReleaseImage (&original_frame_gray);  
        cvReleaseImage (&new_frame_gray); 
        cvReleaseImage (&eig_img); 
        cvReleaseImage (&temp_img);  
        cvReleaseImage (&prev_pyramid);  
        cvReleaseImage (&curr_pyramid);
    }
    cvDestroyWindow ("Image");
    cvReleaseImage (&original_frame); 
    cvReleaseImage(&new_frame);
    return 0;
}
