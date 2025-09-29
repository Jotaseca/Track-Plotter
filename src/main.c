// main
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
//#include "conversions.c"
//#include "coordinateinsertion.c"
#include "creator.c"
//#include "functions.c"
#include "loader.c"
//#include "trackfragmenter.c"
//#include "trackoptimizer.c"
//#include "trackplotter.c"

static void activate (GtkApplication *app, gpointer user_data) {

    GtkWidget *window;
    GtkWidget *loadUnloadSelection;
    GtkWidget *loadProjectButton;
    GtkWidget *newProjectButton;

    GtkCssProvider *provider = gtk_css_provider_new(); // makes everyting sexier with CSS
    gtk_css_provider_load_from_string(provider,
        "window { background-color: #808080ff; color: #eceff4; }"
        "box { padding: 10px; }"
        "label { font-size: 14px; font-weight: bold; color: #000000ff; }"
        "entry { border-radius: 5px; padding: 5px; background-color: #000000ff; color: #eceff4; border: 1px solid #5e81ac; }"
        "entry:focus { border-color: #81a1c1; box-shadow: 0 0 5px #81a1c1; }"
        "list { background-color: #000000ff; border-radius: 5px; }"
        "list row { padding: 10px; border-bottom: 1px solid #4c566a; }"
        "list row:hover { background-color: #434c5e; }"
    );
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    window = gtk_application_window_new (app); // creates window and stores it in pointer
    gtk_window_set_title (GTK_WINDOW (window), "Track Plotter - Project Manager"); // sets window title
    gtk_window_set_default_size (GTK_WINDOW (window), 800, 600); // sets window size

    loadUnloadSelection = gtk_grid_new ();
    gtk_window_set_child (GTK_WINDOW (window), loadUnloadSelection);

    gtk_widget_set_halign(loadUnloadSelection, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(loadUnloadSelection, GTK_ALIGN_CENTER);

    loadProjectButton = gtk_button_new_with_label ("Load Project");
    newProjectButton = gtk_button_new_with_label ("New Project");

    gtk_grid_attach (GTK_GRID (loadUnloadSelection), loadProjectButton, 0,0,1,1);
    gtk_grid_attach (GTK_GRID (loadUnloadSelection), newProjectButton, 1,0,1,1);

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
