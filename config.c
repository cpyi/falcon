/*
config.c
configure camera number, range of detection
*/
#include <gtk/gtk.h>
#include "config.h"
GtkWidget *create_page_config()
{
    GtkWidget *box,*court_list,*court_settings;
    box=gtk_hbox_new(FALSE,5);
    court_list=create_court_list();
    court_settings=create_court_settings();
    gtk_box_pack_start(GTK_BOX(box),court_list,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(box),court_settings,TRUE,TRUE,5);
    return box;
}
GtkWidget *create_court_list()
{
    GtkWidget *add_button,*remove_button,*list_box,*row1_box,*list;
    add_button=create_court_list_add_button();
    remove_button=create_court_list_remove_button();
    list=create_court_list_box();
    row1_box=gtk_hbox_new(TRUE,5);
    list_box=gtk_vbox_new(FALSE,5);
    gtk_box_pack_start(GTK_BOX(row1_box),add_button,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(row1_box),remove_button,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(list_box),row1_box,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(list_box),list,FALSE,FALSE,5);
    return list_box;
}
GtkWidget *create_court_list_add_button()
{
    const gchar *add_button_image_filename="..\\res\\add.png";
    GtkWidget *add_button_context,*add_button;
    add_button_context=button_with_image(add_button_image_filename,NULL);
    add_button=gtk_button_new();
    gtk_container_add(GTK_CONTAINER(add_button),add_button_context);
    gtk_widget_show(add_button_context);
    gtk_widget_show(add_button);
    return add_button;
}
GtkWidget *create_court_list_remove_button()
{
    const gchar *remove_button_image_filename="..\\res\\remove.png";
    GtkWidget *remove_button_context,*remove_button;
    remove_button_context=button_with_image(remove_button_image_filename,NULL);
    remove_button=gtk_button_new();
    gtk_container_add(GTK_CONTAINER(remove_button),remove_button_context);
    gtk_widget_show(remove_button_context);
    gtk_widget_show(remove_button);
    return remove_button;
}
GtkWidget *create_court_list_box_model()
{
    const gchar *icon_file="..\\res\\src_img.png";
    GdkPixbuf *pixbuf;
    GtkTreeIter iter;
    GtkListStore *store;
    gint i;
    pixbuf=gdk_pixbuf_new_from_file(icon_file,NULL);
    store=gtk_list_store_new(2,GDK_TYPE_PIXBUF,G_TYPE_STRING);
    for(i=0;i<5;i++)
    {
        gtk_list_store_append(store,&iter);
        gtk_list_store_set(store,&iter,PIXBUF_COL,pixbuf,TEXT_COL,"ITEM",-1);
    }
    gdk_pixbuf_unref(pixbuf);
    return GTK_TREE_MODEL(store);
}
GtkWidget *create_court_list_box()
{
    GtkWidget *tree_view;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeSelection *selection;
    tree_view=gtk_tree_view_new_with_model(create_court_list_box_model());
    renderer=gtk_cell_renderer_pixbuf_new();
    column=gtk_tree_view_column_new_with_attributes("Icon",renderer,"pixbuf",PIXBUF_COL,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),column);
    renderer=gtk_cell_renderer_text_new();
    column=gtk_tree_view_column_new_with_attributes("Filename",renderer,"text",TEXT_COL,NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view),column);
    return tree_view;
}
GtkWidget *button_with_image(gchar *filename,gchar *text)
{
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *image;
    box=gtk_hbox_new(FALSE,5);
    gtk_container_set_border_width(GTK_CONTAINER(box),2);
    image=gtk_image_new_from_file(filename);
    label=gtk_label_new(text);
    gtk_box_pack_start(GTK_BOX(box),image,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,5);
    gtk_widget_show(image);
    gtk_widget_show(label);
    return box;
}
GtkWidget *create_court_settings()
{
    GtkWidget *box,*source_row_box,*range_row_box;
    source_row_box=create_court_settings_source_row();
    range_row_box=create_court_settings_range_row();
    box=gtk_vbox_new(FALSE,5);
    gtk_box_pack_start(GTK_BOX(box),source_row_box,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(box),range_row_box,TRUE,TRUE,5);
    return box;
}
GtkWidget *create_court_settings_source_row()
{
    GtkWidget *box,*label,*text;
    box=gtk_hbox_new(FALSE,5);
    label=gtk_label_new("Source:");
    text=gtk_entry_new();
    gtk_entry_set_editable(text,TRUE);
    gtk_box_pack_start(GTK_BOX(box),label,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(box),text,TRUE,TRUE,5);
    return box;
}
GtkWidget *create_court_settings_range_row()
{
    GtkWidget *box,*label,*pixbuf;
    box=gtk_hbox_new(FALSE,5);
    label=gtk_label_new("Range:");
    pixbuf=gtk_image_new_from_file("..\\res\\test.png");
    gtk_box_pack_start(GTK_BOX(box),label,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(box),pixbuf,TRUE,TRUE,5);
    return box;
}
