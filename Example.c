/**************************************************
 * �I���ؼҡA�B�ʪ����˴�
 *      
 **************************************************/
 
/***********************************************************************
 * OpenCV example
 * By Shiqi Yu 2006
 ***********************************************************************/
 
 
#include <stdio.h>
 
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
 
int main( int argc, char** argv )
{
  const char avi_name[]="..\\res\\de.avi";
  //�n��IplImage���w
  IplImage* pFrame = NULL; 
  IplImage* pFrImg = NULL;
  IplImage* pBkImg = NULL;
 
  CvMat* pFrameMat = NULL;
  CvMat* pFrMat = NULL;
  CvMat* pBkMat = NULL;
 
  CvCapture* pCapture = NULL;
 
  int nFrmNum = 0;
 
  //�Ыص���
  cvNamedWindow("video", 1);
  cvNamedWindow("background",1);
  cvNamedWindow("foreground",1);
  //�ϵ������ǱƦC
  cvMoveWindow("video", 30, 0);
  cvMoveWindow("background", 360, 0);
  cvMoveWindow("foreground", 690, 0);
 
 
 
  if( argc > 2 )
    {
      fprintf(stderr, "Usage: bkgrd [video_file_name]\n");
      return -1;
    }
 
  //���}�ṳ�Y
  if (argc ==1)
    if( !(pCapture = cvCaptureFromAVI(avi_name)))
      {
	fprintf(stderr, "Can not open camera.\n");
	return -2;
      }
 
  //���}���W���
  if(argc == 2)
    if( !(pCapture = cvCaptureFromFile(argv[1])))
      {
	fprintf(stderr, "Can not open video file %s\n", argv[1]);
	return -2;
      }
 
  //�v�VŪ�����W
  while(pFrame = cvQueryFrame( pCapture ))
    {
      nFrmNum++;
 
      //�p�G�O�Ĥ@�V�A�ݭn�ӽаO����A�ê�l��
      if(nFrmNum == 1)
	{
	  pBkImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),  IPL_DEPTH_8U,1);
	  pFrImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),  IPL_DEPTH_8U,1);
 
	  pBkMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
	  pFrMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
	  pFrameMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
 
	  //��Ʀ���q�D�Ϲ��A�B�z
	  cvCvtColor(pFrame, pBkImg, CV_BGR2GRAY);
	  cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
 
	  cvConvert(pFrImg, pFrameMat);
	  cvConvert(pFrImg, pFrMat);
	  cvConvert(pFrImg, pBkMat);
	}
      else
	{
	  cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
	  cvConvert(pFrImg, pFrameMat);
	  //�����o�i���A�H���ƹϹ�
	  //cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);
 
	  //��e�V��I���Ϭ۴�
	  cvAbsDiff(pFrameMat, pBkMat, pFrMat);
 
	  //�G�Ȥƫe����
	  cvThreshold(pFrMat, pFrImg, 60, 255.0, CV_THRESH_BINARY);
 
	  //�i��κA���o�i�A�h������  
	  //cvErode(pFrImg, pFrImg, 0, 1);
	  //cvDilate(pFrImg, pFrImg, 0, 1);
 
	  //��s�I��
	  cvRunningAvg(pFrameMat, pBkMat, 0.003, 0);
	  //�N�I����Ƭ��Ϲ��榡�A�ΥH���
	  cvConvert(pBkMat, pBkImg);
 
	  //��ܹϹ�
	  cvShowImage("video", pFrame);
	  cvShowImage("background", pBkImg);
	  cvShowImage("foreground", pFrImg);
 
	  //�p�G������ƥ�A�h���X�j��
	  //�����ݤ]��cvShowImage��ƴ��Ѯɶ��������
	  //���ݮɶ��i�H�ھ�CPU�t�׽վ�
	  if( cvWaitKey(2) >= 0 )
	    break;
 
 
	}
 
    }
 
 
 
 
  //�P������
  cvDestroyWindow("video");
  cvDestroyWindow("background");
  cvDestroyWindow("foreground");
 
  //����Ϲ��M�x�}
  cvReleaseImage(&pFrImg);
  cvReleaseImage(&pBkImg);
 
  cvReleaseMat(&pFrameMat);
  cvReleaseMat(&pFrMat);
  cvReleaseMat(&pBkMat);
 
  cvReleaseCapture(&pCapture);
 
  return 0;
}
