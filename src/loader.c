// loads previous project
#include <gtk/gtk.h>

static void loaderWindow(GtkApplication *button, gpointer user_data) {
    
    GtkApplication *app = GTK_APPLICATION(user_data);
    GtkWidget *window = gtk_application_window_new (app); // creates window and stores it in pointer
    gtk_window_set_title (GTK_WINDOW (window), "Track Plotter - Load Project"); // sets window title
    gtk_window_set_default_size (GTK_WINDOW (window), 800, 600); // sets window size

    gtk_window_present (GTK_WINDOW (window)); // shows window

}

/*
void loadProjectSettings(const char *projectName) {
    char settingsPath[256];
    sprintf(settingsPath, "data/%s/settings.txt", projectName);
    FILE *f = fopen(settingsPath, "r");
    if (!f) {
        g_print("Settings file not found.\n");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        char key[100], value[100];
        if (sscanf(line, "%[^=]=%s", key, value) == 2) {
            if (strcmp(key, "project_title") == 0) {
                g_free(projectT);
                projectT = g_strdup(value);
            } else if (strcmp(key, "gauge") == 0) {
                Gauge = atof(value);
            }
            // Add similar for other keys
        }
    }
    fclose(f);
    g_print("Settings loaded.\n");
}
*/