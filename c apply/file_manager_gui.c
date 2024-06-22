#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

GtkWidget *create_entry;
GtkWidget *content_entry;
GtkWidget *read_entry;
GtkWidget *delete_entry;
GtkWidget *output_textview;
GtkTextBuffer *output_buffer;

void create_file(GtkWidget *widget, gpointer data) {
    const char *filename = gtk_entry_get_text(GTK_ENTRY(create_entry));
    const char *content = gtk_entry_get_text(GTK_ENTRY(content_entry));
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        gtk_text_buffer_set_text(output_buffer, "Error creating file!\n", -1);
        return;
    }
    fprintf(file, "%s", content);
    fclose(file);
    gtk_text_buffer_set_text(output_buffer, "File created successfully.\n", -1);
}

void read_file(GtkWidget *widget, gpointer data) {
    const char *filename = gtk_entry_get_text(GTK_ENTRY(read_entry));
    char ch;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        gtk_text_buffer_set_text(output_buffer, "Error reading file! Make sure the file exists.\n", -1);
        return;
    }
    GtkTextIter iter;
    gtk_text_buffer_set_text(output_buffer, "", -1);
    gtk_text_buffer_get_iter_at_offset(output_buffer, &iter, 0);
    while ((ch = fgetc(file)) != EOF) {
        gchar str[2] = {ch, '\0'};
        gtk_text_buffer_insert(output_buffer, &iter, str, -1);
    }
    fclose(file);
}

void delete_file(GtkWidget *widget, gpointer data) {
    const char *filename = gtk_entry_get_text(GTK_ENTRY(delete_entry));
    if (remove(filename) == 0) {
        gtk_text_buffer_set_text(output_buffer, "File deleted successfully.\n", -1);
    } else {
        gtk_text_buffer_set_text(output_buffer, "Error deleting file! Make sure the file exists.\n", -1);
    }
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *create_label;
    GtkWidget *content_label;
    GtkWidget *read_label;
    GtkWidget *delete_label;
    GtkWidget *create_button;
    GtkWidget *read_button;
    GtkWidget *delete_button;
    GtkWidget *scrolled_window;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Simple File Manager");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    create_label = gtk_label_new("Create File:");
    gtk_grid_attach(GTK_GRID(grid), create_label, 0, 0, 1, 1);
    create_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), create_entry, 1, 0, 1, 1);
    content_label = gtk_label_new("Content:");
    gtk_grid_attach(GTK_GRID(grid), content_label, 0, 1, 1, 1);
    content_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), content_entry, 1, 1, 1, 1);
    create_button = gtk_button_new_with_label("Create");
    gtk_grid_attach(GTK_GRID(grid), create_button, 2, 0, 1, 2);
    g_signal_connect(create_button, "clicked", G_CALLBACK(create_file), NULL);

    read_label = gtk_label_new("Read File:");
    gtk_grid_attach(GTK_GRID(grid), read_label, 0, 2, 1, 1);
    read_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), read_entry, 1, 2, 1, 1);
    read_button = gtk_button_new_with_label("Read");
    gtk_grid_attach(GTK_GRID(grid), read_button, 2, 2, 1, 1);
    g_signal_connect(read_button, "clicked", G_CALLBACK(read_file), NULL);

    delete_label = gtk_label_new("Delete File:");
    gtk_grid_attach(GTK_GRID(grid), delete_label, 0, 3, 1, 1);
    delete_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), delete_entry, 1, 3, 1, 1);
    delete_button = gtk_button_new_with_label("Delete");
    gtk_grid_attach(GTK_GRID(grid), delete_button, 2, 3, 1, 1);
    g_signal_connect(delete_button, "clicked", G_CALLBACK(delete_file), NULL);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_vexpand(scrolled_window, TRUE);
    gtk_grid_attach(GTK_GRID(grid), scrolled_window, 0, 4, 3, 1);

    output_textview = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(output_textview), FALSE);
    gtk_container_add(GTK_CONTAINER(scrolled_window), output_textview);
    output_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(output_textview));

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
