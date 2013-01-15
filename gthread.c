/*gthead.c
gthread test
13/1/15
by cpyi
*/
#include <gtk/gtk.h>
gpointer bifurcation(gpointer data)
{
    while(1)
    {
        printf("%s",data);
    }
}
int main(int argc,char *argv[])
{
    gtk_init(&argc,&argv);
    if(!g_thread_supported())
    {
        printf("GThread not supported\n");
        system("pause");
        return 0;
    }
    g_thread_create(bifurcation,"hello",FALSE,NULL);
    gtk_main();
    return 0;
}
