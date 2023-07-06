/* calcula.c
   Este ejercicio muestra el uso de contenedores, botones y
   espacios de entrada con sus funciones de callback y seniales
   generando una calculadora sencilla

*/

#include <gtk/gtk.h>
#include <string.h>


typedef struct def_param
{
  GtkWidget *entry;
  GtkWidget *texto;
  char operacion[15];
} tipo_param;
  
GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox);
GtkWidget *AddButton2(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, tipo_param *EntryBox);
void ButtonClicked(GtkButton *button, gpointer data);
void StopTheApp(GtkWidget *window, gpointer data);
void ButtonClicked2(GtkButton *button, gpointer data);
void ButtonClicked3(GtkButton *button, gpointer data);
void Cambiaopcion1(GtkToggleButton *button, gpointer data);
void lee(GtkToggleButton *button, gpointer data);
void guarda(GtkToggleButton *button, gpointer data);
void limpia(GtkToggleButton *button, gpointer data);

gint main ( gint argc, gchar *argv[])
{

  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *box1, *box2, *box3, *box4, *box5;
  GtkWidget *verticalbox, *vertical2, *vertical3;
  GtkWidget *entrybox;
  GtkWidget *label;
  GtkWidget *texto;
  GtkWidget *menu, *menu1, *root_menu, *menu_bar, *op1, *op2, *op3, *rb1, *rb2;
  char buf[128];
  int i;

  tipo_param parametro;
  
  gtk_init(&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),320,200);
  gtk_window_move(GTK_WINDOW(window),500,400);
  gtk_container_border_width(GTK_CONTAINER(window),5);

  texto=gtk_text_view_new();
  
  verticalbox = gtk_vbox_new(TRUE,5);
  vertical2 = gtk_vbox_new(FALSE,0);
  vertical3 = gtk_vbox_new(FALSE,0);
  
  entrybox = gtk_entry_new();
  gtk_entry_set_editable(entrybox,FALSE);
  gtk_entry_set_alignment(entrybox,1);
  gtk_entry_set_max_length (entrybox,10);

  parametro.entry = entrybox;
  parametro.texto = texto;

  //menu
  menu_bar = gtk_menu_bar_new();

   //subsub1
  menu1=gtk_menu_new();
  op1=gtk_menu_item_new_with_label("Subop1");
  op2=gtk_menu_item_new_with_label("Subop2");
  op3=gtk_menu_item_new_with_label("Subop3");
  gtk_menu_append(GTK_MENU(menu1),op1);
  gtk_menu_append(GTK_MENU(menu1),op2);
  gtk_menu_append(GTK_MENU(menu1),op3);


  menu=gtk_menu_new();
  op1=gtk_menu_item_new_with_label("op1");
  op2=gtk_menu_item_new_with_label("op2");
  op3=gtk_menu_item_new_with_label("Salir");

  gtk_signal_connect(GTK_OBJECT(op3),"activate",GTK_SIGNAL_FUNC(StopTheApp),NULL);

  gtk_menu_append(GTK_MENU(menu),op1);

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(op1),menu1);
    
  gtk_menu_append(GTK_MENU(menu),op2);
  gtk_menu_append(GTK_MENU(menu),op3);

  root_menu=gtk_menu_item_new_with_label("Calculadora");
  
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu),menu);
  
  gtk_menu_bar_append(GTK_MENU_BAR(menu_bar), root_menu);



  //sub2
  menu=gtk_menu_new();
  op1=gtk_menu_item_new_with_label("Leer");
  op2=gtk_menu_item_new_with_label("Guardar");
  op3=gtk_menu_item_new_with_label("Nuevo");

  gtk_menu_append(GTK_MENU(menu),op1);
  gtk_menu_append(GTK_MENU(menu),op2);
  gtk_menu_append(GTK_MENU(menu),op3);

  gtk_signal_connect(GTK_OBJECT(op1),"activate",GTK_SIGNAL_FUNC(lee),NULL);
  gtk_signal_connect(GTK_OBJECT(op2),"activate",GTK_SIGNAL_FUNC(guarda),NULL);
  gtk_signal_connect(GTK_OBJECT(op3),"activate",GTK_SIGNAL_FUNC(limpia),NULL);
  
  root_menu=gtk_menu_item_new_with_label("Juego");
  
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu),menu);

  gtk_menu_bar_append(GTK_MENU_BAR(menu_bar), root_menu);

  //sub3
  root_menu=gtk_menu_item_new_with_label("Salir");
  gtk_signal_connect(GTK_OBJECT(root_menu),"activate",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  gtk_menu_bar_append(GTK_MENU_BAR(menu_bar),root_menu);
  

  //fin del menu
  
  box1 = gtk_hbox_new(TRUE,5); 
  box2 = gtk_hbox_new(TRUE,5); 
  box3 = gtk_hbox_new(TRUE,5); 
  box4 = gtk_hbox_new(TRUE,5);

  box5 = gtk_hbox_new(TRUE,5); //gral

  button = AddButton(box1,"1",ButtonClicked,entrybox);
  button = AddButton(box1,"2",ButtonClicked,entrybox);
  button = AddButton(box1,"3",ButtonClicked,entrybox);
  button = AddButton(box1,"CL",ButtonClicked,entrybox);

  //label = gtk_label_new(" ");
  //gtk_box_pack_start(GTK_BOX(box1),label,FALSE,TRUE,0);
  
  

  button = AddButton(box2,"4",ButtonClicked,entrybox);
  button = AddButton(box2,"5",ButtonClicked,entrybox);
  button = AddButton(box2,"6",ButtonClicked,entrybox);
  button = AddButton2(box2,"+",ButtonClicked3,&parametro);
 
  button = AddButton(box3,"7",ButtonClicked,entrybox);
  button = AddButton(box3,"8",ButtonClicked,entrybox);
  button = AddButton(box3,"9",ButtonClicked,entrybox);
  button = AddButton2(box3,"-",ButtonClicked3,&parametro);
 
  button = AddButton(box4,"0",ButtonClicked,entrybox);
  button = AddButton2(box4,"*",ButtonClicked3,&parametro);
  button = AddButton2(box4,"/",ButtonClicked3,&parametro);
  button = AddButton2(box4,"=",ButtonClicked2,&parametro);
 
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(verticalbox),box1,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(verticalbox),box2,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(verticalbox),box3,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(verticalbox),box4,TRUE,TRUE,0);
  
  gtk_box_pack_start(GTK_BOX(box5),verticalbox,TRUE,TRUE,0);

  // radio buttons
  rb1 = gtk_radio_button_new_with_label(NULL,"Opcion 1   "); 
  gtk_box_pack_start(GTK_BOX(vertical3),rb1,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb1),"toggled",GTK_SIGNAL_FUNC(Cambiaopcion1),"1");

  rb2 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON (rb1)),"Opcion 2   "); 
  gtk_box_pack_start(GTK_BOX(vertical3),rb2,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb2),"toggled",GTK_SIGNAL_FUNC(Cambiaopcion1),"2");

  rb2 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON (rb1)),"Opcion 3   "); 
  gtk_box_pack_start(GTK_BOX(vertical3),rb2,FALSE,FALSE,0);
  gtk_signal_connect(GTK_OBJECT(rb2),"toggled",GTK_SIGNAL_FUNC(Cambiaopcion1),"3");

  gtk_box_pack_start(GTK_BOX(vertical3),texto,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box5),vertical3,TRUE,TRUE,0);

  
  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);



  gtk_box_pack_start(GTK_BOX(vertical2),menu_bar,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(vertical2),box5,TRUE,TRUE,0);


  gtk_container_add(GTK_CONTAINER(window),vertical2);
  
  gtk_widget_show_all(window);
  
  gtk_main();

  return 0;

}



GtkWidget *AddButton(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget *EntryBox)
{
    GtkWidget *button;
    button = gtk_button_new_with_label(buttonText);
    gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,TRUE,0);
   // gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,FALSE,0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CallBackFunction),EntryBox);
    gtk_widget_show(button);
    return button;
}

GtkWidget *AddButton2(GtkWidget *theBox, const gchar *buttonText, gpointer CallBackFunction, tipo_param *EntryBox)
{
    GtkWidget *button;
    button = gtk_button_new_with_label(buttonText);
    gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,TRUE,0);
   // gtk_box_pack_start(GTK_BOX(theBox),button,FALSE,FALSE,0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CallBackFunction),EntryBox);
    gtk_widget_show(button);
    return button;
}

void Cambiaopcion1(GtkToggleButton *button, gpointer data)
{
   char *cad = (char *)data;


   if(gtk_toggle_button_get_active(button))
      g_print("boton seleccionado %s \n",cad);

}


void ButtonClicked(GtkButton *button, gpointer data)
{
   const gchar *text, *text2;
    char texto2[22];

    text =gtk_button_get_label(GTK_BUTTON(button));
    if(strcmp(text,"CL")!=0)
   {
       text2 =gtk_entry_get_text(GTK_ENTRY(data));
       strcpy(texto2,text2);
       strcat(texto2,text);
    }
    else
        texto2[0] = '\0';
    gtk_entry_set_text(GTK_ENTRY(data),texto2);

}

void ButtonClicked3(GtkButton *button, gpointer data)
{
   tipo_param *dato = (tipo_param *) data;

    const gchar *text, *text2;
    char texto2[11];

    text =gtk_button_get_label(GTK_BUTTON(button));

    text2 =gtk_entry_get_text(GTK_ENTRY(dato->entry));
    strcpy(texto2,text2);
    strcat(texto2,text);
    strcpy(dato->operacion,texto2);

    strcpy(texto2,"");
    gtk_entry_set_text(GTK_ENTRY(dato->entry),texto2);
}


void ButtonClicked2(GtkButton *button, gpointer data)
{
    tipo_param *dato = (tipo_param *) data;
    const gchar *text, *text2;
    int op1,op2;
    int res;
    char operacion,resultado[30];
    GtkTextBuffer *Buff;
    GtkTextIter inicio, fin;
    
    text =gtk_entry_get_text(GTK_ENTRY(dato->entry));
    strcat(dato->operacion,text);
    sscanf(dato->operacion,"%d%c%d",&op1,&operacion,&op2);
    switch (operacion)
	{
		case '+': res=op1+op2;
				break;
		case '-': res=op1-op2;
				break;
		case '*': res=op1*op2;
				break;
		case '/': res=op1/op2;
				break;
	}
       sprintf(resultado,"%d",res);
       gtk_entry_set_text(GTK_ENTRY(dato->entry),resultado);

       sprintf(resultado,"%d%c%d=%d\n",op1,operacion,op2,res);

       Buff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(dato->texto));
       
       gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(Buff),resultado,strlen(resultado));

 
       gtk_text_buffer_get_bounds(Buff,&inicio,&fin);
       text2 = gtk_text_buffer_get_text(Buff,&inicio,&fin,FALSE);
       g_print(text2);
       
}

void StopTheApp(GtkWidget *window, gpointer data)
{
    gtk_main_quit();
    

}

void lee(GtkToggleButton *button, gpointer data)
{
  GtkWidget *dialogo, *otro;
  FILE *archivo;
  char *nombre;
  gint res;
  
  g_print("leer");
  
dialogo = gtk_file_chooser_dialog_new ("Abrir Archivo",
                                      NULL,
                                      GTK_FILE_CHOOSER_ACTION_OPEN,
                                      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                      NULL);

if (gtk_dialog_run(GTK_DIALOG(dialogo)) == GTK_RESPONSE_ACCEPT)
  {
    nombre = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialogo));
    g_print(nombre);
    g_free (nombre);
  }

gtk_widget_destroy(dialogo);
}


void guarda(GtkToggleButton *button, gpointer data)
{

    GtkWidget *dialogo, *otro;
  FILE *archivo;
  char *nombre;
  gint res;
  
  g_print("guardar");
  
dialogo = gtk_file_chooser_dialog_new ("Guardar Archivo",
                                      NULL,
                                      GTK_FILE_CHOOSER_ACTION_SAVE,
                                      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                      GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
                                      NULL);

if (gtk_dialog_run(GTK_DIALOG(dialogo)) == GTK_RESPONSE_ACCEPT)
  {
    nombre = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialogo));
    g_print(nombre);
    g_free (nombre);
  }

gtk_widget_destroy(dialogo);

}

void limpia(GtkToggleButton *button, gpointer data)
{
  g_print("limpiar");
}

