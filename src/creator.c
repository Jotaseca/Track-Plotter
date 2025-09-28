// creates a new project.
// makes all the necessary data structures.
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h> // checks for errors
#include <string.h> // for strlen.

// FOR NOW YOU HAVE TO CLICK ENTER FOR THE DATA TO BE INSERTED. NO FEEDBACK WILL BE GIVEN.

// ----------------------------------------

#if defined(_WIN32)
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#include <sys/stat.h>
#include <sys/types.h>
#define MKDIR(path) mkdir(path, 0777)
#endif

// ----------------------------------------

static char *projectT = NULL;
static float Gauge = 0.0;
static float MaxHAngle = 0.0;
static float MaxGForceLateral = 0.0;
static float MaxGForceVertical = 0.0;
static float ProjectResolution = 0.0; // i have yet to decide how the resolution will be measured.
static float MaxStructuralSpeed = 0.0;

static void projectCreator (GtkEntry *entry, gpointer user_data) { // is going rto generate the file structure, data etc
    // the variables are gonna be acessed globaly

    if(!projectT || (strlen(projectT)==0)) { // if the project has no name, will have to change this later.
        projectT = g_strdup("newProject"); // automatically allocates and sets name.
    }

    if (MKDIR("data") != 0 && errno != EEXIST) { // checks if directory already exists, errno != EEXIST
        g_print("Failed to create data directory.\n");
        return;
    }

    char projectPath[256];
    sprintf(projectPath, "data/%s", projectT);
    if (MKDIR(projectPath) == 0) {
        // creates folder with project name
        g_print("Project folder created.\n");
    } else if (errno == EEXIST) {
        g_print("Project folder already exists.\n");
    } else {
        g_print("Failed to create project folder.\n");
    }

    // Create the settings file on the newlu created folder

    char settingsPath[256];
    sprintf(settingsPath, "data/%s/settings.txt", projectT); // sprintf -> adds a chunk of string to a already existing string.
    FILE *f = fopen(settingsPath, "w"); // writes and creates if not already present.
    if (f) { // f is a poitner to a file structure, or file stream , or whatever...
        fprintf(f, "project_title=%s\n", projectT);
        fprintf(f, "gauge=%f\n", Gauge);
        fprintf(f, "max_h_angle=%f\n", MaxHAngle);
        fprintf(f, "max_g_force_lateral=%f\n", MaxGForceLateral);
        fprintf(f, "max_g_force_vertical=%f\n", MaxGForceVertical);
        fprintf(f, "project_resolution=%f\n", ProjectResolution);
        fprintf(f, "max_structural_speed=%f\n", MaxStructuralSpeed);
        fclose(f);
        g_print("Settings saved to %s\n", settingsPath);
    } else {
        g_print("Failed to save settings.\n");
    }

}

static void on_entry_activate_string(GtkEntry *entry, gpointer user_data) {
    char **theentry = (char **)user_data;
    g_free(*theentry);
    *theentry = g_strdup(gtk_editable_get_text(GTK_EDITABLE(entry))); // ???
    g_print("Input (activate): %s\n", *theentry);
}

static void on_entry_activate_float(GtkEntry *entry, gpointer user_data) {
    float *theentry = (float *)user_data;
    const char *text = gtk_editable_get_text(GTK_EDITABLE(entry));
    char *tofloat;
    float value = strtof(text, &tofloat);
    *theentry = value;
    g_print("Input (activate): %f\n", *theentry);
}


static void on_window_destroy(GtkWidget *widget, gpointer user_data) { // prob gong to have to delete this later
    g_free(projectT);
    projectT = NULL;
}


static void creatorWindow(GtkApplication *button, gpointer user_data) {
    GtkApplication *app = GTK_APPLICATION(user_data);
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Track Plotter - New Project");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    GtkWidget *verticalBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), verticalBox);

    // ----------------------------------------

    GtkWidget *horizontalProjectTitleBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(verticalBox), horizontalProjectTitleBox);

    GtkWidget *projectTitlelabel = gtk_label_new("Project Title:");
    gtk_box_append(GTK_BOX(horizontalProjectTitleBox), projectTitlelabel);

    GtkWidget *projectTitle = gtk_entry_new();
    gtk_box_append(GTK_BOX(horizontalProjectTitleBox), projectTitle);
    g_signal_connect(projectTitle, "activate", G_CALLBACK(on_entry_activate_string), &projectT);

    // ----------------------------------------

    GtkWidget *horizontalTrackGaugeBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(verticalBox), horizontalTrackGaugeBox);

    GtkWidget *projectGaugelabel = gtk_label_new("Track Gauge (mm):");
    gtk_box_append(GTK_BOX(horizontalTrackGaugeBox), projectGaugelabel);

    GtkWidget *projectGauge = gtk_entry_new();
    gtk_box_append(GTK_BOX(horizontalTrackGaugeBox), projectGauge);
    g_signal_connect(projectGauge, "activate", G_CALLBACK(on_entry_activate_float), &Gauge);

    // ----------------------------------------

    GtkWidget *horizontalMaxHorizontalAngleBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(verticalBox), horizontalMaxHorizontalAngleBox);

    GtkWidget *projectMaxHorizontalAnglelabel = gtk_label_new("Max Track Angle relative to Horizon (deg):");
    gtk_box_append(GTK_BOX(horizontalMaxHorizontalAngleBox), projectMaxHorizontalAnglelabel);

    GtkWidget *projectMaxHorizontalAngle = gtk_entry_new();
    gtk_box_append(GTK_BOX(horizontalMaxHorizontalAngleBox), projectMaxHorizontalAngle);
    g_signal_connect(projectMaxHorizontalAngle, "activate", G_CALLBACK(on_entry_activate_float), &MaxHAngle);

    // ----------------------------------------

    GtkWidget *horizontalMaxLateralGForceBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(verticalBox), horizontalMaxLateralGForceBox);

    GtkWidget *projectMaxLateralGForceBoxlabel = gtk_label_new("Max Lateral G-Force (g):");
    gtk_box_append(GTK_BOX(horizontalMaxLateralGForceBox), projectMaxLateralGForceBoxlabel);

    GtkWidget *projectMaxLateralGForce = gtk_entry_new();
    gtk_box_append(GTK_BOX(horizontalMaxLateralGForceBox), projectMaxLateralGForce);
    g_signal_connect(projectMaxLateralGForce, "activate", G_CALLBACK(on_entry_activate_float), &MaxGForceLateral);

    // ----------------------------------------

    GtkWidget *horizontalMaxVerticalGForceBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(verticalBox), horizontalMaxVerticalGForceBox);

    GtkWidget *projectMaxVerticalGForceBoxlabel = gtk_label_new("Max Vertical G-Force (g):");
    gtk_box_append(GTK_BOX(horizontalMaxVerticalGForceBox), projectMaxVerticalGForceBoxlabel);

    GtkWidget *projectMaxVerticalGForce = gtk_entry_new();
    gtk_box_append(GTK_BOX(horizontalMaxVerticalGForceBox), projectMaxVerticalGForce);
    g_signal_connect(projectMaxVerticalGForce, "activate", G_CALLBACK(on_entry_activate_float), &MaxGForceVertical);

    // ----------------------------------------

    GtkWidget *horizontalProjectResolutionBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(verticalBox), horizontalProjectResolutionBox);

    GtkWidget *projectProjectResolutionBoxlabel = gtk_label_new("Project Resolution (?):");
    gtk_box_append(GTK_BOX(horizontalProjectResolutionBox), projectProjectResolutionBoxlabel);

    GtkWidget *projectProjectResolution = gtk_entry_new();
    gtk_box_append(GTK_BOX(horizontalProjectResolutionBox), projectProjectResolution);
    g_signal_connect(projectProjectResolution, "activate", G_CALLBACK(on_entry_activate_float), &ProjectResolution);

    // ----------------------------------------

    GtkWidget *horizontalMaxStructuralSpeedBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(verticalBox), horizontalMaxStructuralSpeedBox);

    GtkWidget *projectMaxStructuralSpeedBoxlabel = gtk_label_new("Max Structural Speed (km/h):");
    gtk_box_append(GTK_BOX(horizontalMaxStructuralSpeedBox), projectMaxStructuralSpeedBoxlabel);

    GtkWidget *projectMaxStructuralSpeed = gtk_entry_new();
    gtk_box_append(GTK_BOX(horizontalMaxStructuralSpeedBox), projectMaxStructuralSpeed);
    g_signal_connect(projectMaxStructuralSpeed, "activate", G_CALLBACK(on_entry_activate_float), &MaxStructuralSpeed);

    // ----------------------------------------

    GtkWidget *lowerButtonGrid = gtk_grid_new();
    gtk_box_append(GTK_BOX(verticalBox), lowerButtonGrid);

    gtk_widget_set_halign(lowerButtonGrid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(lowerButtonGrid, GTK_ALIGN_CENTER);

    GtkWidget *saveAndStartButton = gtk_button_new_with_label("Save and Create Project");

    g_signal_connect(saveAndStartButton, "clicked", G_CALLBACK(projectCreator), NULL);

    gtk_grid_attach(GTK_GRID(lowerButtonGrid), saveAndStartButton, 0,0,2,1);

    // ----------------------------------------

    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

    gtk_window_present(GTK_WINDOW(window));

}
