/*
live.h
Show immediatly the situation of the court,
and the immediatly detecting
*/
#ifndef _LIVE_H_
#define _LIVE_H_
#include "vision.h"
GtkWidget *create_page_live();
void update_page_live(gchar *scene_name,scene *sce);
#endif
