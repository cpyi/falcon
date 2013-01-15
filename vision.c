/*
vision.c
maitain the number of cameras, number of courts and vision operation.
*/
#include "vision.h"
scene *vision_init()
{
    scene *first_scene;
    first_scene=(scene *)malloc(sizeof(scene));
    strcpy(first_scene->name,"FIRST SCENE");
    strcpy(first_scene->source,"..\\res\\input.avi");
    first_scene->mode=file;
    first_scene->state=0;
    first_scene->capture=NULL;
    first_scene->ipl_image=NULL;
    first_scene->ipl_image_modified=NULL;
    first_scene->image=NULL;
    first_scene->image_modified=NULL;
    first_scene->next=NULL;
    return first_scene;
}
void vision_loop(scene *first_scene_ptr)
{
    scene *ptr;
    while(1)
    {
        ptr=first_scene_ptr;
        maintain_scene(ptr);
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
            maintain_scene(ptr);
        }
    }
}
void maintain_scene(scene *scene_ptr)
{
    if(scene_ptr->capture==NULL)
    {
        if(scene_ptr->mode==file)
        {
            scene_ptr->capture=cvCaptureFromAVI(scene_ptr->source);
        }
        else if(scene_ptr->mode==camera)
        {
            /*implement getting camera capture*/
        }
        if(scene_ptr->capture==NULL)
        {
            printf("open capture error\n");
        }
    }
    scene_ptr->ipl_image=cvQueryFrame(scene_ptr->capture);
    modify_ipl_image(scene_ptr);
    ipl_image_to_gtk_image(scene_ptr);
}
void modify_ipl_image(scene *scene_ptr)
{
    printf("YA!");
    if(scene_ptr->ipl_image==NULL)
    {
        printf("modify_ipl_image() error, without original pointer\n");
    }
    /*implement image operation*/
    scene_ptr->ipl_image_modified=scene_ptr->ipl_image;
}
void ipl_image_to_gtk_image(scene *scene_ptr)
{
    if(scene_ptr->ipl_image==NULL)
    {
        printf("ipl_image_to_gtk_image() error, without ipl_image pointer\n");
        return;
    }
    if(scene_ptr->ipl_image_modified==NULL)
    {
        printf("ipl_image_to_gtk_image() error, without ipl_image_modefied pinter\n");
        return;
    }
    cvCvtColor(scene_ptr->ipl_image,scene_ptr->ipl_image,CV_BGR2RGB);
    GdkPixbuf *pixbuf;
    IplImage *img;
    img=scene_ptr->ipl_image;
    pixbuf=gdk_pixbuf_new_from_data((guchar *)img->imageData,GDK_COLORSPACE_RGB,FALSE,img->depth,img->width,img->height,img->widthStep,NULL,NULL);
    if(pixbuf==NULL)
    {
        printf("in ipl_image_to_gtk_image(), pixbuf open error\n");
        return;
    }
    scene_ptr->image=gtk_image_new_from_pixbuf(pixbuf);
    /*implement detailed later*/
    scene_ptr->image_modified=scene_ptr->image;
}
