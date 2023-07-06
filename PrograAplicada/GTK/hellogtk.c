#include <gtk/gtk.h>

// FUNCION CONECTADA CON EL BOTON 
void hello(GtkWidget *widget, gpointer data)
{
  g_print("Hola Perro Mundo \n");
}

// FUNCION PARA CERRAR LA VENTANA
void destroy(GtkWidget *widget, gpointer data)
{
  gtk_main_quit();
}

int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *button;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL); // Crear ventana

  gtk_signal_connect(GTK_OBJECT(window),"destroy", GTK_SIGNAL_FUNC(destroy), NULL); // Para cerrar la ventana

  gtk_container_set_border_width(GTK_CONTAINER(window),10); // Borde de la ventana

  button=gtk_button_new_with_label("Hola Mundo"); // Poner etiqueta al boton

  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(hello), NULL); // Para conectar el boton con una funcion

  gtk_container_add(GTK_CONTAINER(window),button); // Para colocar el boton dentro de la ventana

  gtk_widget_show(button); // Mostrar el boton
  gtk_widget_show(window); // Mostrar la ventana

  gtk_main(); // Correr la parte grafica

  return(0);
}
