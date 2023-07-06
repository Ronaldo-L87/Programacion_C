#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
    GtkWidget *window;
    GtkWidget *vbox;

    GtkWidget *TreeView;
    //GtkWidget *title;

    GtkWidget *hbox1;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *entry3;
    GtkWidget *hbox2;
    GtkWidget *btn1;
    GtkWidget *btn2;
    gtk_init(&argc, &argv);
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"hellow world");
    g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
    //gtk_widget_set_size_request(window,500,690);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    TreeView= gtk_tree_view_new();

    entry1= gtk_entry_new(); //this is the entry
    entry2= gtk_entry_new();
    entry3= gtk_entry_new();

    btn1= gtk_button_new_with_label("add");
    btn2= gtk_button_new_with_label("remove");

    hbox1= gtk_hbox_new(0, 3); //this is the hbox
    hbox2= gtk_hbox_new(0, 3);

    gtk_box_pack_start(GTK_BOX(hbox1), entry1, FALSE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(hbox1), entry2, FALSE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(hbox1), entry3, FALSE, TRUE, 3);

    gtk_box_pack_start(GTK_BOX(hbox2), btn1, FALSE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(hbox2), btn2, FALSE, TRUE, 3);

    vbox= gtk_vbox_new(0,3);
    gtk_box_pack_start(GTK_BOX(vbox), TreeView, 1, 1, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox1,FALSE, TRUE, 3);
    gtk_box_pack_start (GTK_BOX (vbox), hbox2, FALSE, TRUE, 3);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
    gtk_main();
}
