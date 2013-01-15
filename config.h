/*
config.h
configure camera number, range of detection
*/
GtkWidget *create_page_config();
GtkWidget *create_court_list();
GtkWidget *create_court_list_add_button();
GtkWidget *create_court_list_remove_button();
GtkWidget *create_court_list_box();
GtkWidget *create_court_list_box_model();
GtkWidget *button_with_image(gchar *filename,gchar *text);

GtkWidget *create_court_settings();
GtkWidget *create_court_settings_source_row();
GtkWidget *create_court_settings_range_row();
enum
{
    PIXBUF_COL,
    TEXT_COL
};
