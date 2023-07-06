#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void destroy(GtkWidget *widget, gpointer data);
void ButtonClicked1(GtkWidget *widget, gpointer data);
void ButtonClicked2(GtkWidget *widget, gpointer data);

typedef struct def_dato
{
  GtkWidget *entryP;
  GtkWidget *entryA;
  GtkWidget *label1;
  GtkWidget *label2;
  float peso;
  float altura;
  float imc;
  char num1[15];
  char num2[15];
}tipo_dato;

int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *label1, *label2, *label3, *label4;
  GtkWidget *button1, *button2;
  GtkWidget *entry1, *entry2;
  GtkWidget *hbox1, *hbox2, *hbox3, *hbox4, *hbox5;
  GtkWidget *vbox1;
  GtkWidget *hboxA, *hboxB, *hboxC, *hboxD;
  tipo_dato calcular;
  gtk_init(&argc, &argv);
  //Ventana
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
  //gtk_window_set_default_size(GTK_WINDOW(window), 350, 350);
  gtk_signal_connect(GTK_OBJECT(window),"destroy", GTK_SIGNAL_FUNC(destroy), NULL);
  gtk_window_set_title(GTK_WINDOW(window), " ");
  
  //
  hbox1 = gtk_hbox_new(TRUE,5);
  hbox2 = gtk_hbox_new(TRUE,5);
  hbox3 = gtk_hbox_new(TRUE,5);
  hbox4 = gtk_hbox_new(TRUE,10);
  hbox5 = gtk_hbox_new(TRUE,10);
  hboxA = gtk_hbox_new(TRUE,10);
  hboxB = gtk_hbox_new(TRUE,10);
  hboxC = gtk_hbox_new(TRUE,10);
  hboxD = gtk_hbox_new(TRUE,10);
  vbox1 = gtk_vbox_new(TRUE,5);
  //
  label1 = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label1), "Peso en kg: ");
  //
  label2 = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label2), "Estatura en mt: ");
  //
  label3 = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label3), "");
  calcular.label1 = label3;
  //
  label4 = gtk_label_new(NULL);
  gtk_label_set_text(GTK_LABEL(label3), "");
  calcular.label2 = label4;

  // Boton 1
  button1=gtk_button_new_with_label("Calcular");
  gtk_signal_connect(GTK_OBJECT(button1),"clicked",GTK_SIGNAL_FUNC(ButtonClicked1), &calcular);
  // Boton 2
  button2=gtk_button_new_with_label("Borrar");
  gtk_signal_connect(GTK_OBJECT(button2),"clicked",GTK_SIGNAL_FUNC(ButtonClicked2), &calcular);
  
  //
  entry1 = gtk_entry_new();
  gtk_entry_set_editable(GTK_ENTRY(entry1), TRUE);
  gtk_entry_set_alignment(GTK_ENTRY(entry1),0);
  gtk_entry_set_max_length (GTK_ENTRY(entry1),10);
  calcular.entryP = entry1;

  entry2 = gtk_entry_new();
  gtk_entry_set_editable(GTK_ENTRY(entry2), TRUE);
  gtk_entry_set_alignment(GTK_ENTRY(entry2),0);
  gtk_entry_set_max_length (GTK_ENTRY(entry2),10);
  calcular.entryA = entry2;
  
  gtk_box_pack_start(GTK_BOX(hbox1), label1, FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox1), entry1, FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox1), hboxA, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox2), label2, FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox2), entry2, FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox2), hboxB, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox3), hboxC, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox3), button1, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox3), button2, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox3), hboxD, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox4), label3, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(hbox5), label4, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox1), hbox1, FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox1), hbox2, FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox1), hbox3, FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox1), hbox4, FALSE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox1), hbox5, FALSE, TRUE, 5);
  gtk_container_add(GTK_CONTAINER(window), vbox1);
  
  gtk_widget_show_all(window);  
  gtk_main();
  
  return 0;
}

void destroy(GtkWidget *widget, gpointer data)
{
  gtk_main_quit();
}

void ButtonClicked1(GtkWidget *widget, gpointer data)
{
  tipo_dato *num = (tipo_dato *) data;
  const gchar *peso, *alt;
  float res;
  float kg;
  float mt;
  char resultado[30];
  char salud[50];
  peso = gtk_entry_get_text(GTK_ENTRY(num->entryP));
  alt = gtk_entry_get_text(GTK_ENTRY(num->entryA));
  if(peso == NULL  || alt == NULL)
    {
      kg = 0;
      mt = 1;
    }
  else
    {
      strcpy(num->num1, peso);
      sscanf(num->num1,"%f",&kg);
      strcpy(num->num2, alt);
      sscanf(num->num2,"%f",&mt);
    }
  res = kg / (mt * mt);
  if(res > 25 && res < 30)
    strcpy(salud, "Usted tiene sobrepeso");
  if(res >= 30 && res < 35)
    strcpy(salud, "Usted tiene obesidad grado uno");
  if(res >= 35 && res <= 39.9)
    strcpy(salud, "Usted tiene obesidad grado dos");
  if(res > 39.9)
    strcpy(salud, "Usted tiene obesidad morbida");
  sprintf(resultado, "%.2f", res);
  gtk_label_set_text(GTK_LABEL(num->label1), resultado);
  gtk_label_set_text(GTK_LABEL(num->label2), salud);
}

void ButtonClicked2(GtkWidget *widget, gpointer data)
{
  tipo_dato *num = (tipo_dato *) data;
  gtk_label_set_text(GTK_LABEL(num->label1), "");
  gtk_label_set_text(GTK_LABEL(num->label2), "");
}
