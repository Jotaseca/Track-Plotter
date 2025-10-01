// handles data coordinate data insertion.
#include <gtk/gtk.h>
#include "data.c"

static void coordinateInsertionWindow(GtkApplication *button, gpointer user_data) {
    
    GtkApplication *app = GTK_APPLICATION(user_data);
    GtkWidget *window = gtk_application_window_new (app); // creates window and stores it in pointer
    gtk_window_set_title (GTK_WINDOW (window), "Track Plotter - Data Insertion"); // sets window title
    gtk_window_set_default_size (GTK_WINDOW (window), 800, 600); // sets window size

    // ----------------------------------------



    gtk_window_present (GTK_WINDOW (window)); // shows window

}

