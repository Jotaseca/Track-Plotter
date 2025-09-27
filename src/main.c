// main
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include "conversions.c"
#include "coordinateinsertion.c"
#include "creator.c"
#include "functions.c"
#include "loader.c"
#include "trackfragmenter.c"
#include "trackoptimizer.c"
#include "trackplotter.c"

static void activate (GtkApplication *app, gpointer user_data) {

    GtkWidget *window;
    GtkWidget *loadUnloadSelection;
    GtkWidget *loadProjectButton;
    GtkWidget *newProjectButton;

    window = gtk_application_window_new (app); // creates window and stores it in pointer
    gtk_window_set_title (GTK_WINDOW (window), "Track Plotter"); // sets window title
    gtk_window_set_default_size (GTK_WINDOW (window), 800, 600); // sets window size

    loadUnloadSelection = gtk_grid_new ();
    gtk_window_set_child (GTK_WINDOW (window), loadUnloadSelection);

    gtk_widget_set_halign(loadUnloadSelection, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(loadUnloadSelection, GTK_ALIGN_CENTER);

    loadProjectButton = gtk_button_new_with_label ("Load Project");
    newProjectButton = gtk_button_new_with_label ("New Project");

    gtk_grid_attach (GTK_GRID (loadUnloadSelection), loadProjectButton, 0,0,1,1);
    gtk_grid_attach (GTK_GRID (loadUnloadSelection), newProjectButton, 1,0,1,1);

    //g_signal_connect (loadProjectButton, "clicked", G_CALLBACK (/*ligar a loader*/), NULL);
    g_signal_connect (loadProjectButton, "clicked", G_CALLBACK(loaderWindow), app);
    g_signal_connect (newProjectButton, "clicked", G_CALLBACK(creatorWindow), app);

    gtk_window_present (GTK_WINDOW (window)); // shows window

}

int main (int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.track-plotter", G_APPLICATION_DEFAULT_FLAGS); // creates new application
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL); // activates window
    status = g_application_run (G_APPLICATION (app), argc, argv); // runs window, when closed returns status
    g_object_unref (app); // frees from memory the gtk application

    return status;
}
