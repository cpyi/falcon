/*
legend.c
show live siuation with simple line and points
*/
#include <gtk/gtk.h>
#include "legend.h"
GtkWidget *create_page_legend()
{
    int i;
    /*These var should be used globally*/
    int court_num=1;
    int court_used[6]={1,0,0,0,0,0};
    gchar *court_name[6]={"1st","2nd","3th","4th","5th","6th"};
    const int legend_rows=2;
    const int legend_column=3;
    
    GtkWidget *court_frame[6];
    GtkWidget *court_label[6];
    GtkWidget *row1_box,*row2_box,*vbox;
    for(i=0;i<6;i++)
    {
        court_frame[i]=gtk_frame_new(court_name[i]);
        court_label[i]=gtk_label_new(NULL);
    }
    for(i=0;i<6;i++)
    {
        if(i<court_num)
        {
            if(court_used[i]>0)
            {
                gtk_label_set_markup(GTK_LABEL(court_label[i]),"  Used  ");
            }
            else
            {
                gtk_label_set_markup(GTK_LABEL(court_label[i]),"Unused");
            }
        }
        else
        {
            gtk_label_set_markup(GTK_LABEL(court_label[i]),"No Data");
        }
    }
    for(i=0;i<6;i++)
    {
        gtk_container_add(GTK_CONTAINER(court_frame[i]),court_label[i]);
    } 
    row1_box=gtk_hbox_new(FALSE,5);
    row2_box=gtk_hbox_new(FALSE,5);
    vbox=gtk_vbox_new(TRUE,5);
    for(i=0;i<3;i++)
    {
        gtk_box_pack_start(GTK_BOX(row1_box),court_frame[i],TRUE,TRUE,5);
    }
    for(i=3;i<6;i++)
    {
        gtk_box_pack_start(GTK_BOX(row2_box),court_frame[i],TRUE,TRUE,5);
    }
    gtk_box_pack_start(GTK_BOX(vbox),row1_box,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(vbox),row2_box,TRUE,TRUE,5);
    return vbox;
}
