/*
vision.h
maitain the number of cameras, number of courts and vision operation.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <gtk/gtk.h>
#ifndef _VISION_H_
#define _VISION_H_
#define STR_LEN_MAX 100
enum{file,camera};
typedef struct _scene
{
    gchar name[STR_LEN_MAX];
    gchar source[STR_LEN_MAX];
    int mode;
    int state;
    CvCapture *capture;
    IplImage *ipl_image;
    IplImage *ipl_image_modified;
    GtkWidget *image;
    GtkWidget *image_modified;
    struct _scene *next;
} scene;
scene *vision_init();
void vision_loop(scene *first_scene_ptr);
void maintain_scene(scene *scene_ptr);
void modify_ipl_image(scene *scene_ptr);
void ipl_image_to_gtk_image(scene *scene_ptr);
#endif
