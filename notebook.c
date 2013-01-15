/*
notebook.c
maintain all tabs
*/
#include <gtk/gtk.h>
#include "notebook.h"
#include "live.h"
#include "legend.h"
#include "config.h"
GtkWidget* create_tab(gchar *image_filename,gchar *label_text)
{
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *image;
    
    box=gtk_hbox_new(FALSE,5);
    gtk_container_set_border_width(GTK_CONTAINER(box),2);
    
    image=gtk_image_new_from_file(image_filename);
    label=gtk_label_new(label_text);
    
    gtk_box_pack_start(GTK_BOX(box),image,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,5);
    
    gtk_widget_show(image);
    gtk_widget_show(label);
    
    return box;
}
GtkWidget* create_notebook()
{
    GtkWidget *notebook,*tab,*page;
    /*deal directory name for windows and linux*/
    const gchar *image_filename[5]={"..\\res\\tab_live.png","..\\res\\tab_legend.png","..\\res\\tab_config.png","..\\res\\tab_statistic.png","..\\res\\tab_database.png"};
    const gchar *label_text[5]={"Live","Legend","Config","Statistic","Database"};
    const int tab_num=5;
    int i;
    notebook=gtk_notebook_new();
    for(i=0;i<tab_num;i++)
    {
        tab=create_tab(image_filename[i],label_text[i]);
        switch(i)
        {
            case 0:
                page=create_page_live();
                gtk_notebook_append_page(GTK_NOTEBOOK(notebook),page,tab);
            break;
            case 1:
                page=create_page_legend();
                gtk_notebook_append_page(GTK_NOTEBOOK(notebook),page,tab);
            break;
            case 2:
                page=create_page_config();
                gtk_notebook_append_page(GTK_NOTEBOOK(notebook),page,tab);
            break;
        }
    }
    return notebook;
}
