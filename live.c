/*
live.c
Show immediatly the situation of the court,
and the immediatly detecting
*/
#include <gtk/gtk.h>
#include "live.h"
GtkWidget *create_page_live()
{
    GtkWidget *combo_box,*left_image,*right_image,*row_box,*box;
    const gchar *left_image_filename="..\\res\\test.png",*right_image_filename="..\\res\\test.png";
    combo_box=gtk_combo_box_new_text();
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo_box),"caterpillar");
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo_box),"momor");
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo_box),"hamimi");
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo_box),"bush");
    left_image=gtk_image_new_from_file(left_image_filename);
    right_image=gtk_image_new_from_file(right_image_filename);
    row_box=gtk_hbox_new(FALSE,5);
    box=gtk_vbox_new(FALSE,5);
    gtk_box_pack_start(GTK_BOX(row_box),left_image,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(row_box),right_image,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(box),combo_box,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(box),row_box,TRUE,TRUE,5);
    gtk_widget_show_all(box);
    return box;
}
void update_page_live(gchar *scene_name,scene *sce)
{
}
