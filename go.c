#include <gtk/gtk.h>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include <stdio.h>

int main(int argc,char *argv[])
{
    IplImage *img=cvLoadImage("test.png",CV_LOAD_IMAGE_ANYCOLOR);
    if(img==NULL)
    {
        printf("cvLoadImage() error\n");
        system("pause");
        return 0;
    }
    //IplImage *img_rgb;
    cvCvtColor(img,img,CV_BGR2RGB);
    GtkWidget *window;
    GdkPixbuf *pixbuf;
    gtk_init(&argc,&argv);
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"OpenCV and GTK are good friends"); 
    pixbuf=gdk_pixbuf_new_from_data((guchar *)img->imageData,GDK_COLORSPACE_RGB,FALSE,img->depth,img->width,img->height,img->widthStep,NULL,NULL);
    if(pixbuf==NULL)
    {
        printf("pixbuf open error\n");
        system("pause");
        return 0;
    }
    GtkWidget *img_widget;
    img_widget=gtk_image_new_from_pixbuf(pixbuf);
    gtk_container_add(GTK_CONTAINER(window),img_widget);
    gtk_widget_show(window);
    gtk_widget_show(img_widget);
    gtk_main();
    return 0;
}
