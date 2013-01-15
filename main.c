/*
main.c
deal with whole things
*/
#include <gtk/gtk.h>
#include "notebook.h"
#include "vision.h"
int main(int argc,char *argv[])
{
    scene *first_scene;
    GtkWidget *window,*notebook;
    gtk_init(&argc,&argv);
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"Falcon alpha");
    gtk_window_set_default_size(GTK_WINDOW(window),300,350);
    notebook=create_notebook();
    gtk_container_add(GTK_CONTAINER(window),notebook);
    gtk_widget_show_all(window);
    first_scene=vision_init();
    g_thread_create(vision_loop,first_scene,FALSE,NULL);
    gtk_main();
    return 0;
}
