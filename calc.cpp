#include <gtk/gtk.h>
#include <iostream>

using namespace std;

void on_button_clicked(GtkButton* button, gpointer user_data) {
    GtkWidget* num1_entry = (GtkWidget*)g_object_get_data(G_OBJECT(button), "num1_entry");
    GtkWidget* num2_entry = (GtkWidget*)g_object_get_data(G_OBJECT(button), "num2_entry");
    GtkWidget* result_label = (GtkWidget*)g_object_get_data(G_OBJECT(button), "result_label");

    float num1 = atof(gtk_entry_get_text(GTK_ENTRY(num1_entry)));
    float num2 = atof(gtk_entry_get_text(GTK_ENTRY(num2_entry)));
    float result;

    GtkComboBox* operator_combo = (GtkComboBox*)g_object_get_data(G_OBJECT(button), "operator_combo");
    GtkTreeIter iter;
    gchar* active_operator = nullptr;

    if (gtk_combo_box_get_active_iter(operator_combo, &iter)) {
        gtk_tree_model_get(GTK_TREE_MODEL(gtk_combo_box_get_model(operator_combo)), &iter, 0, &active_operator, -1);
    }

    if (active_operator != nullptr) {
        if (strcmp(active_operator, "+") == 0) {
            result = num1 + num2;
        } else if (strcmp(active_operator, "-") == 0) {
            result = num1 - num2;
        } else if (strcmp(active_operator, "*") == 0) {
            result = num1 * num2;
        } else if (strcmp(active_operator, "/") == 0) {
            result = num1 / num2;
        } else {
            g_print("Invalid operator\n");
            return;
        }
    }

    char result_str[50];
    snprintf(result_str, 50, "Result: %.2f", result);
    gtk_label_set_text(GTK_LABEL(result_label), result_str);
}

int main(int argc, char* argv[]) {
    GtkWidget* window;
    GtkWidget* grid;
    GtkWidget* num1_entry;
    GtkWidget* num2_entry;
    GtkComboBox* operator_combo;
    GtkWidget* calculate_button;
    GtkWidget* result_label;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    num1_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), num1_entry, 0, 0, 1, 1);

    operator_combo = GTK_COMBO_BOX(gtk_combo_box_text_new());
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(operator_combo), "+");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(operator_combo), "-");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(operator_combo), "*");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(operator_combo), "/");
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(operator_combo), 1, 0, 1, 1);

    num2_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), num2_entry, 2, 0, 1, 1);

    calculate_button = gtk_button_new_with_label("Calculate");
    gtk_grid_attach(GTK_GRID(grid), calculate_button, 0, 1, 3, 1);

    result_label = gtk_label_new("Result: ");
    gtk_grid_attach(GTK_GRID(grid), result_label, 0, 2, 3, 1);

    g_signal_connect(G_OBJECT(calculate_button), "clicked", G_CALLBACK(on_button_clicked), num1_entry);

    g_object_set_data(G_OBJECT(calculate_button), "num1_entry", num1_entry);
    g_object_set_data(G_OBJECT(calculate_button), "operator_combo", operator_combo);
    g_object_set_data(G_OBJECT(calculate_button), "num2_entry", num2_entry);
    g_object_set_data(G_OBJECT(calculate_button), "result_label", result_label);

    g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
    }


   
