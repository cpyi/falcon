/**************************************************
 * 背景建模，運動物體檢測
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
  //聲明IplImage指針
  IplImage* pFrame = NULL; 
  IplImage* pFrImg = NULL;
  IplImage* pBkImg = NULL;
 
  CvMat* pFrameMat = NULL;
  CvMat* pFrMat = NULL;
  CvMat* pBkMat = NULL;
 
  CvCapture* pCapture = NULL;
 
  int nFrmNum = 0;
 
  //創建視窗
  cvNamedWindow("video", 1);
  cvNamedWindow("background",1);
  cvNamedWindow("foreground",1);
  //使視窗有序排列
  cvMoveWindow("video", 30, 0);
  cvMoveWindow("background", 360, 0);
  cvMoveWindow("foreground", 690, 0);
 
 
 
  if( argc > 2 )
    {
      fprintf(stderr, "Usage: bkgrd [video_file_name]\n");
      return -1;
    }
 
  //打開攝像頭
  if (argc ==1)
    if( !(pCapture = cvCaptureFromAVI(avi_name)))
      {
	fprintf(stderr, "Can not open camera.\n");
	return -2;
      }
 
  //打開視頻文件
  if(argc == 2)
    if( !(pCapture = cvCaptureFromFile(argv[1])))
      {
	fprintf(stderr, "Can not open video file %s\n", argv[1]);
	return -2;
      }
 
  //逐幀讀取視頻
  while(pFrame = cvQueryFrame( pCapture ))
    {
      nFrmNum++;
 
      //如果是第一幀，需要申請記憶體，並初始化
      if(nFrmNum == 1)
	{
	  pBkImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),  IPL_DEPTH_8U,1);
	  pFrImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),  IPL_DEPTH_8U,1);
 
	  pBkMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
	  pFrMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
	  pFrameMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
 
	  //轉化成單通道圖像再處理
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
	  //高斯濾波先，以平滑圖像
	  //cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);
 
	  //當前幀跟背景圖相減
	  cvAbsDiff(pFrameMat, pBkMat, pFrMat);
 
	  //二值化前景圖
	  cvThreshold(pFrMat, pFrImg, 60, 255.0, CV_THRESH_BINARY);
 
	  //進行形態學濾波，去掉噪音  
	  //cvErode(pFrImg, pFrImg, 0, 1);
	  //cvDilate(pFrImg, pFrImg, 0, 1);
 
	  //更新背景
	  cvRunningAvg(pFrameMat, pBkMat, 0.003, 0);
	  //將背景轉化為圖像格式，用以顯示
	  cvConvert(pBkMat, pBkImg);
 
	  //顯示圖像
	  cvShowImage("video", pFrame);
	  cvShowImage("background", pBkImg);
	  cvShowImage("foreground", pFrImg);
 
	  //如果有按鍵事件，則跳出迴圈
	  //此等待也為cvShowImage函數提供時間完成顯示
	  //等待時間可以根據CPU速度調整
	  if( cvWaitKey(2) >= 0 )
	    break;
 
 
	}
 
    }
 
 
 
 
  //銷毀視窗
  cvDestroyWindow("video");
  cvDestroyWindow("background");
  cvDestroyWindow("foreground");
 
  //釋放圖像和矩陣
  cvReleaseImage(&pFrImg);
  cvReleaseImage(&pBkImg);
 
  cvReleaseMat(&pFrameMat);
  cvReleaseMat(&pFrMat);
  cvReleaseMat(&pBkMat);
 
  cvReleaseCapture(&pCapture);
 
  return 0;
}
