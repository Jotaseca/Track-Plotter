// main program.
// uses the inserted data.
/* takes section speed, tries to create a curve from initial heading and tilt with minimum radius
taking in consideration speed and max angle, max lateral g and vertical g, and at the same time
does the same thing beggining at the end point and heading, little by little until the first
curve and the last curve are pointing at the each other, and then tries to male a straight line
between them.
It only needs to deduce if the curve needs to go right or left.
Obviously if it is set to max speed both curves will end at the same place.
Height map is calculated after this to avoid issues.
changes in curve, angle, tilt have to be gradual taking in consideration speed.*/

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "coordinateinsertion.c"

static void dynamicGridDraw(cairo_t *cr, int width, int height) { // Draw a grid.

    cairo_set_source_rgb(cr, 0.7, 0.7, 0.7);
    cairo_set_line_width(cr, 1.0);
    for(int i=0;i<width;i+=50){
        cairo_move_to(cr, i, 0);
        cairo_line_to(cr, i, height); // drawing invisible lines, a path
    }
    for(int i=0;i<height;i+=50){
        cairo_move_to(cr, 0, i);
        cairo_line_to(cr, width, i);
    }

    cairo_stroke(cr); // actually draws the lines.

}

static void mapView(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data) { // cairo_t - paintbrush

    cairo_set_source_rgb(cr, 0.9, 0.9, 0.9); // this cairo stuff is like the stuff i used in python
    cairo_paint(cr); // bucket tool. fills the entire screen

    dynamicGridDraw(cr, width, height); // draws grid.

}

static void trackPlotterWindow(gpointer user_data) { // main map window, will brach to other windows.

    GtkApplication *app = GTK_APPLICATION(user_data);
    GtkWidget *window = gtk_application_window_new (app); // creates window and stores it in pointer
    gtk_window_set_title (GTK_WINDOW (window), "Track Plotter"); // sets window title
    gtk_window_set_default_size (GTK_WINDOW (window), 1920, 1080); // sets window size

    // ----------------------------------------

    GtkWidget *tools = gtk_header_bar_new();

    // gtk_header_bar_set_title_widget(GTK_HEADER_BAR(tools), gtk_label_new("Track Plotter"));
    gtk_window_set_titlebar(GTK_WINDOW(window), tools);

    GtkWidget *saveButton = gtk_button_new_with_label("Save");
    GtkWidget *coordinatesButton = gtk_button_new_with_label("Coordinates");
    GtkWidget *plotButton = gtk_button_new_with_label("Plot");
    GtkWidget *zoomInButton = gtk_button_new_with_label("+");
    GtkWidget *zoomOutButton = gtk_button_new_with_label("-");
    
    gtk_header_bar_pack_start(GTK_HEADER_BAR(tools), saveButton);
    gtk_header_bar_pack_start(GTK_HEADER_BAR(tools), coordinatesButton);
    gtk_header_bar_pack_start(GTK_HEADER_BAR(tools), plotButton);

    gtk_header_bar_pack_end(GTK_HEADER_BAR(tools), zoomInButton);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(tools), zoomOutButton);

    g_signal_connect(coordinatesButton, "clicked", G_CALLBACK(coordinateInsertionWindow), app);

    // ----------------------------------------

    GtkWidget *mapWindowMainScroll = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(mapWindowMainScroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC); // idk wtf this is. but i need it

    GtkWidget *mapWindowMain = gtk_drawing_area_new(); // where this will draw the stuff
    gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(mapWindowMain), 2560); // i just pu tin my resolution. not optimal
    gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(mapWindowMain), 1440);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(mapWindowMain), mapView, NULL, NULL);

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(mapWindowMainScroll), mapWindowMain); // put sthe drawing window inside the scroll window.

    gtk_window_set_child(GTK_WINDOW(window), mapWindowMainScroll); // maybe i dont need this

    gtk_window_present (GTK_WINDOW (window)); // shows window
}
