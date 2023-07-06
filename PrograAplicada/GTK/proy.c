/* 
 *@file ProyectoFinal.c

 *@brief Este programa realiza el modo cliente de una pension para perros.
 
 *@authors Adrian Octavio Diaz Gaxiola, Ayelin Hazell Hernandez Martinez, German Turnbull Agraz. 
 *@date 2/05/2021
*/

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

typedef struct perros {
  char Nombre[20];
  char IDPerro[10];
  char IDCliente[10];
  char Estatus;
  struct perros *sig;
}tipoperro;

typedef struct clientes
{
  char Telefono[15];
  char Nombre[30], Paterno[20], Materno[20];
  char ID[10];
  char Correo[50];
  char Estatus;
  struct clientes *der, *izq;
  struct perros *Perro;
}tipocliente;

typedef struct datos{
  GtkWidget *vertical; 
  GtkWidget *ventana;
  GtkWidget *entry, *entryNC, *entryAP, *entryAM, *entrytel, *entrycorr, *entryest;
  GtkWidget *boton1, *spinner1, *spinner2, *spinner3;
  GtkWidget *label1, *label2, *labelNC, *labelAP, *labelAM, *labeltel, *labelcorr, *labelest;
  GtkWidget *rb1, *rb2, *rb3, *rb4, *rb5;
  int NumClientes, arg, maxg, maxm, maxc;;
  tipocliente *raiz, *cliente;
}tipodato;

void StopTheApp(GtkWidget *window, gpointer data);
void CrearInicio (GtkButton *button, gpointer data);
void Admin_Crear_Inicio (GtkWidget *button, gpointer data);
void Configurar (GtkWidget *button, gpointer data);
void Guardar_Capacidad(GtkWidget *button, gpointer data);
void MostrarSalvar (GtkWidget *button, gpointer data);
void ModRegCliente (GtkWidget *button, gpointer data);
void ModRegPerro (GtkWidget *button, gpointer data);
void Acerca_de (GtkWidget *button, gpointer data);
void ModRegPerro2 (GtkWidget *button, gpointer data);
void GuardarRegistroPerro(GtkWidget *button, gpointer data);
void ManualAdmin (GtkWidget *button, gpointer data);
void Registrarse(GtkWidget *window, gpointer data);
void RegistroExitoso(GtkButton *button, gpointer data);
void ValidarEntrada (GtkButton *button, gpointer data);
void RegistrarPerro (GtkButton *button, gpointer data);
void ModificarPerro (GtkWidget *button, gpointer data);
void ValidarRegistro(GtkButton *button, gpointer data);
void IniciarSesion(GtkButton *button, gpointer data);
void AgendarCita (GtkButton *button, gpointer data);
void Arroba(GtkButton *button, gpointer data);
void Buscar_Cliente (tipocliente *raiz, char Tel[], tipocliente **temp, int *Bandera);
int CrearID (int *NumClientes);
void Insertar_Cliente(tipocliente **Raiz, char Tel[], char Nom[], char ID[], char Estatus, char Paterno[], char Materno[], char Email[]);
void Imprime_Cliente (tipocliente *Raiz);
void Libera_Cliente (tipocliente *Raiz);
void Libera_Perro (tipoperro **Primero);

gint main (gint argc, gchar *argv[])
{
  GtkWidget *window;
  tipodato parametro;
  
  gtk_init(&argc, &argv);
  
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  parametro.ventana = window;//Se guarda la direccion de la memoria de la ventana en el parametro de al estructura
  gtk_window_set_default_size(GTK_WINDOW(window),320,200);
  gtk_container_border_width(GTK_CONTAINER(window),5);

  parametro.raiz = NULL;
  parametro.NumClientes = 0;
  parametro.vertical = NULL;
  parametro.arg = argc;
  
  if (argc == 1)
    {
      CrearInicio (NULL, &parametro);
    }
  else
    {
      if (argc==2)
	{
	  if (strcmp(argv[1],"-a")==0)
	    {
	      Admin_Crear_Inicio(NULL,&parametro);
	    }
	  else
	    {
	      parametro.label1 = gtk_label_new("El argumento debe ser <-a> para entrar en modo administrador.\nPuedes cerrar la ventana e intentarlo de nuevo.\nQue tengas buen dia.");
	      gtk_container_add(GTK_CONTAINER(parametro.ventana),parametro.label1);
	    }
	}
      else
	{
	  parametro.label1 = gtk_label_new("Solo pueden haber maximo dos argumentos.\nPuedes cerrar la ventana e intentarlo de nuevo.\nQue tengas buen dia.");
	  gtk_container_add(GTK_CONTAINER(parametro.ventana),parametro.label1);
	}
    }  

  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(StopTheApp),&parametro);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}

/*
 * Esta funcion recibe la direccion de memoria de la estructura donde se almacena la informacion 
 * del programa. En esta funcion se crea el menu de inicio para el modo cliente que tiene dos botones, 
 * "Registrate" e "Iniciar Sesion", los cuales estan conectados con sus respectivas funciones:
 * Registrarse e IniciarSesion. Los botones se introducen en una caja vertical, la cual se despliega
 * en la ventana.
 * Funcion de tipo void, no regresa alguna variable.
 * @author Ayelin Hazell Hernandez Martinez
 * @param GtkButton *button    El boton que recibe, al llamar esta funcion de la main, es NULL 
 * @param gpointer data   La direccion de memoria de la variable de tipodato parametro 
 */
void CrearInicio (GtkButton *button, gpointer data)
{
  tipodato *parametro = (tipodato *)data;
  GtkWidget *button1, *button2;
  GtkWidget *verticalbox;

  if (parametro->vertical != NULL)
    gtk_widget_destroy (parametro->vertical);

  verticalbox = gtk_vbox_new(TRUE,5);
  parametro->vertical = verticalbox;//Se pasa la direccion de memoria de verticalbox a vertical de la variable con el parametro

  button1 = gtk_button_new_with_label ("Registrate");
  gtk_box_pack_start(GTK_BOX(verticalbox),button1,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button1),"clicked",GTK_SIGNAL_FUNC(Registrarse),parametro);

  button2 = gtk_button_new_with_label ("Iniciar sesion");
  gtk_box_pack_start(GTK_BOX(verticalbox),button2,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button2),"clicked",GTK_SIGNAL_FUNC(IniciarSesion),parametro);
  
  gtk_container_add(GTK_CONTAINER(parametro->ventana),verticalbox);

  gtk_widget_show_all(parametro->ventana);
}

/* Esta funcion es el menu del modo administrador. Se muestra un boton para configurar, para mostrar y salvar citas, para registrar y modificar clientes, para modificar y registrar perros, para mostrar informacion acerca de, y para ver el manual del usuario. 
 * Al principio se destruye la caja vertical y luego se vuelve a crear. Esto se hace por si la funcion viene de una ventana posterior, en ese caso se elimina la posterior y luego se crea la que esta en la funcion.
 *@autor German Turbull Agraz
 *@date 4 de mayo del 2021
 *@param GtkWidget *button, si se llama de la funcion principal este parametro es null. Si se pasa de otra funcion, sirve solamente para cerrar la caja de la ventana anterior.
 *@param gpointer data este parametro es la estructura del parametro
 */
void Admin_Crear_Inicio (GtkWidget *button, gpointer data)
{
  tipodato *parametro = (tipodato *)data;
  GtkWidget *horizontal1, *horizontal2, *horizontal3;
   
  if (button != NULL)
    {
      gtk_widget_destroy (parametro->vertical);
    }
  
  horizontal1 = gtk_hbox_new(TRUE,5);
  horizontal2 = gtk_hbox_new(TRUE,5);
  horizontal3 = gtk_hbox_new(TRUE,5);
  parametro->vertical = gtk_vbox_new(TRUE,5);
  
  //BOTON CONFIGURAR
  parametro->boton1 = gtk_button_new_with_label("Configurar Capacidad");
  gtk_box_pack_start(GTK_BOX(horizontal1),parametro->boton1,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(parametro->boton1),"clicked",GTK_SIGNAL_FUNC(Configurar),parametro);

  //BOTON MOSTRAR Y SALVAR
  parametro->boton1 = gtk_button_new_with_label("Mostrar y salvar citas");
  gtk_box_pack_start(GTK_BOX(horizontal1),parametro->boton1,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(parametro->boton1),"clicked",GTK_SIGNAL_FUNC(MostrarSalvar),parametro);

  //BOTON REGISTRAR Y MODIFICAR CLIENTES
  parametro->boton1 = gtk_button_new_with_label("Registrar y Modificar Clientes");
  gtk_box_pack_start(GTK_BOX(horizontal2),parametro->boton1,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(parametro->boton1),"clicked",GTK_SIGNAL_FUNC(ModRegCliente),parametro);

  //BOTON REGISTRAR Y MODIFICAR PERROS
  parametro->boton1 = gtk_button_new_with_label("Registrar y Modificar Perros");
  gtk_box_pack_start(GTK_BOX(horizontal2),parametro->boton1,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(parametro->boton1),"clicked",GTK_SIGNAL_FUNC(ModRegPerro),parametro);

  //BOTON ATRAS
  parametro->boton1 = gtk_button_new_with_label("Acerca de");
  gtk_box_pack_start(GTK_BOX(horizontal3),parametro->boton1,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(parametro->boton1),"clicked",GTK_SIGNAL_FUNC(Acerca_de),parametro);

  //BOTON MANUAL DE AYUDA
  parametro->boton1 = gtk_button_new_with_label("Manual de ayuda");
  gtk_box_pack_start(GTK_BOX(horizontal3),parametro->boton1,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(parametro->boton1),"clicked",GTK_SIGNAL_FUNC(ManualAdmin),parametro);

  //EMPACAR CAJAS
  gtk_box_pack_start(GTK_BOX(parametro->vertical),horizontal1, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(parametro->vertical),horizontal2, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(parametro->vertical),horizontal3, TRUE, TRUE, 0);
  
  gtk_container_add(GTK_CONTAINER(parametro->ventana),parametro->vertical);
  gtk_widget_show_all(parametro->ventana);
}

/*
 * Esta funcion destruye la ventana anterior, y crea los widgets necesarios para que el cliente introduzca
 * sus datos de registro. Se crean etiquetas del lado izquierdo con el nombre del dato a introducir y etiquetas
 * del lado derecho que desplegaran mensajes de error en caso de ser requeridos al validar los datos, y se guardan en cajas horizontales.
 * Se guardan en el parametro con la estructura las direcciones de memoria de las entrybox y de las etiquetas
 * ya que se requeriran en la funcion que valida el registro.
 * Funcion de tipo void, no regresa alguna variable.
 * El boton de cancelar regresa al menu de inicio del cliente y el de confirmar conecta con la funcion para validar el registro.
 * @author Adrian Octavio Diaz Gaxiola
 * @date 02/05/2021
 * @param GtkButton *button    El boton de "Registrarse"
 * @param gpointer data   La direccion de memoria de la variable de tipodato parametro
 */
void Registrarse(GtkWidget *window, gpointer data)
{
  tipodato *parametro = (tipodato *)data;
  GtkWidget *label0, *label1izq, *label1der, *label2izq, *label2der, *label3izq, *label3der, *label4izq, *label4der, *label5izq, *label5der, *label6;
  GtkWidget *entrybox1, *entrybox2, *entrybox3, *entrybox4, *entrybox5; 
  GtkWidget *Radio1, *Radio2;
  GtkWidget *button0, *button1, *button2;
  GtkWidget *verticalbox; 
  GtkWidget *hbox1, *hbox2, *hbox3, *hbox4, *hbox5, *hbox6, *hbox7;

  gtk_widget_destroy (parametro->vertical);
  
  verticalbox = gtk_vbox_new(TRUE,5);
  parametro->vertical = verticalbox;

  label0 = gtk_label_new ("Introduce tus datos");
  gtk_box_pack_start(GTK_BOX(verticalbox),label0,FALSE,TRUE,0);

  //Caja horizontal 1
  hbox1 = gtk_hbox_new(TRUE,5);
  
  label1izq = gtk_label_new ("Nombre");
  gtk_box_pack_start(GTK_BOX(hbox1),label1izq,FALSE,FALSE,0);

  label1der = gtk_label_new (NULL);//Etiqueta para imprimir mensaje de error al validar el nombre
  parametro->labelNC = label1der;
  gtk_box_pack_start(GTK_BOX(hbox1),label1der,FALSE,TRUE,0);
  
  gtk_box_pack_start(GTK_BOX(verticalbox),hbox1,FALSE,TRUE,0);
  
  entrybox1 = gtk_entry_new_with_max_length (25);
  parametro->entryNC = entrybox1;
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox1,FALSE,TRUE,0);

  //Caja horizontal 2
  hbox2 = gtk_hbox_new(TRUE,5);
  
  label2izq = gtk_label_new ("Apellido paterno");
  gtk_box_pack_start(GTK_BOX(hbox2),label2izq,FALSE,TRUE,0);

  label2der = gtk_label_new (NULL);//Etiqueta para imprimir mensaje de error al validar el apellido paterno
  parametro->labelAP = label2der;
  gtk_box_pack_start(GTK_BOX(hbox2),label2der,FALSE,TRUE,0);

  gtk_box_pack_start(GTK_BOX(verticalbox),hbox2,FALSE,TRUE,0);

  entrybox2 = gtk_entry_new_with_max_length (15);
  parametro->entryAP = entrybox2;
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox2,FALSE,TRUE,0);

  //Caja horizontal 3
  hbox3 = gtk_hbox_new(TRUE,5);
  
  label3izq = gtk_label_new ("Apellido materno");
  gtk_box_pack_start(GTK_BOX(hbox3),label3izq,FALSE,TRUE,0);

  label3der = gtk_label_new (NULL);//Etiqueta para imprimir mensaje de error al validar el apellido materno
  parametro->labelAM = label3der;
  gtk_box_pack_start(GTK_BOX(hbox3),label3der,FALSE,TRUE,0);

  gtk_box_pack_start(GTK_BOX(verticalbox),hbox3,FALSE,TRUE,0);

  entrybox3 = gtk_entry_new_with_max_length (15);
  parametro->entryAM = entrybox3;
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox3,FALSE,TRUE,0);

  //Caja horizontal 4
  hbox4 = gtk_hbox_new(TRUE,5);

  label4izq = gtk_label_new ("Telefono");
  gtk_box_pack_start(GTK_BOX(hbox4),label4izq,FALSE,TRUE,0);

  label4der = gtk_label_new (NULL);//Etiqueta para imprimir mensaje de error al validar el apellido materno
  parametro->labeltel = label4der;
  gtk_box_pack_start(GTK_BOX(hbox4),label4der,FALSE,TRUE,0);

  gtk_box_pack_start(GTK_BOX(verticalbox),hbox4,FALSE,TRUE,0);
   
  entrybox4 = gtk_entry_new_with_max_length (10);
  parametro->entrytel = entrybox4;
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox4,FALSE,TRUE,0);

  //Caja horizontal 5
  hbox5 = gtk_hbox_new(TRUE,5);

  entrybox5 = gtk_entry_new_with_max_length (40);
  parametro->entrycorr = entrybox5;

  label5izq = gtk_label_new ("Correo electronico");
  gtk_box_pack_start(GTK_BOX(hbox5),label5izq,FALSE,TRUE,0);

  button0 = gtk_button_new_with_label ("Insertar '@'");
  gtk_box_pack_start(GTK_BOX(hbox5),button0,FALSE,TRUE,20);
  gtk_signal_connect(GTK_OBJECT(button0),"clicked",GTK_SIGNAL_FUNC(Arroba),entrybox5);

  label5der = gtk_label_new (NULL);//Etiqueta para imprimir mensaje de error al validar el correo electronico
  parametro->labelcorr = label5der;
  gtk_box_pack_start(GTK_BOX(hbox5),label5der,FALSE,TRUE,0);

  gtk_box_pack_start(GTK_BOX(verticalbox),hbox5,FALSE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox5,FALSE,TRUE,0);

  //Label de estatus
  label6 = gtk_label_new ("Estatus");
  gtk_box_pack_start(GTK_BOX(verticalbox),label6,FALSE,TRUE,0);

  //Caja horizontal 6
  hbox6 = gtk_hbox_new(TRUE,5);

  Radio1 = gtk_radio_button_new_with_label (NULL, "Activo");
  parametro->rb1 = Radio1;
  Radio2 = gtk_radio_button_new_with_label (gtk_radio_button_get_group(GTK_RADIO_BUTTON (Radio1)), "Inactivo");
  parametro->rb2 = Radio2;
  gtk_box_pack_start(GTK_BOX(hbox6),Radio1,FALSE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(hbox6),Radio2,FALSE,TRUE,0);  
  gtk_box_pack_start(GTK_BOX(verticalbox),hbox6,FALSE,TRUE,0);

  //Caja horizontal 7
  hbox7 = gtk_hbox_new(TRUE,5);

  button1 = gtk_button_new_with_label ("Cancelar");
  gtk_box_pack_start(GTK_BOX(hbox7),button1,FALSE,TRUE,20);
  gtk_signal_connect(GTK_OBJECT(button1),"clicked",GTK_SIGNAL_FUNC(CrearInicio),parametro);

  button2 = gtk_button_new_with_label ("Confirmar");
  gtk_box_pack_start(GTK_BOX(hbox7),button2,FALSE,TRUE,20);
  gtk_signal_connect(GTK_OBJECT(button2),"clicked",GTK_SIGNAL_FUNC(ValidarRegistro),parametro);

  gtk_box_pack_start(GTK_BOX(verticalbox),hbox7,FALSE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(parametro->ventana),verticalbox);

  gtk_widget_show_all(parametro->ventana);
}

/*
 * Esta funcion muestra un mensaje de exito de guardado de datos e incluye un boton para registrar un perro.
 * Tambien se utiliza para la pantalla de inicio al iniciar sesion, y se valida si el usuario ya tiene un perro registrado, caso en el que se muestra el boton de agendar cita.
 * Es de tipo void por lo que no regresa ninguna variable.
 * @author Adrian Octavio Diaz Gaxiola
 * @date 04/05/2021
 * @param GtkWidget *button      El boton de confirmar el registro, o NULL cuando se inicia sesion. Con este boton se realizan validaciones.
 * @param gpointer data     El parametro que incluye los datos de la estructura tipodato
*/
void RegistroExitoso (GtkButton *button, gpointer data)
{
  GdkColor color;
  tipodato *parametro = (tipodato *)data;
  GtkWidget *button1, *button2, *button3;
  GtkWidget *label;
  GtkWidget *hbox;
  GtkWidget *verticalbox;
  char Bienvenida[90];

  gtk_widget_destroy (parametro->vertical);

  verticalbox = gtk_vbox_new(TRUE,5);
  parametro->vertical = verticalbox;

  if (button != NULL)//Cuando la funcion se llama desde el registro, el parametro de boton no es NULL
    {
      gdk_color_parse("#00ff00", &color);
      label = gtk_label_new ("Datos guardados exitosamente");
      gtk_widget_modify_fg(GTK_WIDGET(label), GTK_STATE_NORMAL, &color);
      gtk_box_pack_start(GTK_BOX(verticalbox),label,FALSE,TRUE,0);
    }
  else//Cuando se inicia sesion
    {  
      gdk_color_parse("#0000ff", &color);
      sprintf (Bienvenida, "Hola de nuevo, %s %s",(parametro->cliente)->Nombre, (parametro->cliente)->Paterno);
      label = gtk_label_new (Bienvenida);
      gtk_widget_modify_fg(GTK_WIDGET(label), GTK_STATE_NORMAL, &color);   
      gtk_box_pack_start(GTK_BOX(verticalbox),label,FALSE,TRUE,0);  
    }
      
  hbox =  gtk_hbox_new(TRUE,5);

  button1 = gtk_button_new_with_label ("Salir");
  gtk_box_pack_start(GTK_BOX(hbox),button1,FALSE,TRUE,20);
  gtk_signal_connect(GTK_OBJECT(button1),"clicked",GTK_SIGNAL_FUNC(CrearInicio),parametro);

  button2 = gtk_button_new_with_label ("Registrar un perro");
  gtk_box_pack_start(GTK_BOX(hbox),button2,FALSE,TRUE,20);
  gtk_signal_connect(GTK_OBJECT(button2),"clicked",GTK_SIGNAL_FUNC(RegistrarPerro),parametro);

  if (((parametro->cliente)->Perro)!=NULL && button == NULL)//Si el usuario tiene al menos un perro registrado
    {
      gtk_button_set_label (GTK_BUTTON(button2), "Registrar otro perro");
      button3 = gtk_button_new_with_label ("Agendar Cita");
      gtk_box_pack_start(GTK_BOX(verticalbox),button3,FALSE,TRUE,20);
      gtk_signal_connect(GTK_OBJECT(button3),"clicked",GTK_SIGNAL_FUNC(AgendarCita),parametro);
    }
  
  gtk_box_pack_start(GTK_BOX(verticalbox),hbox,FALSE,TRUE,20);

  gtk_container_add(GTK_CONTAINER(parametro->ventana),verticalbox);

  gtk_widget_show_all(parametro->ventana);
}

/*
 * Esta funcion despliega la ventana en la que se piden los datos del perro.
 * Se pide el nombre del perro en un entrybox y el tamanio del perro solamente. Los demas datos del perro ya los tiene el programa o los genera automaticamente.
 *@author German Turnbull Agraz
 *@date 5 de mayo del 2021
 *@param button es el boton que mando llamar funcion, no tiene una funcion aqui
 *@param data es la estructura del parametro
 */
void RegistrarPerro (GtkButton *button, gpointer data)
{
  tipodato *parametro = (tipodato *)data;
  GtkWidget *separador;
  GtkWidget *vertical1, *horizontal1;
  GtkWidget *boton1;
  
  gtk_widget_destroy(parametro->vertical);

  parametro->vertical = gtk_vbox_new(FALSE,5);
  vertical1 = gtk_vbox_new(TRUE,2);
  horizontal1 = gtk_hbox_new(TRUE,5);

  parametro->label2 = gtk_label_new("Introduce los datos del perro,\ntodos los campos son obligatorios.");
  gtk_box_pack_start(GTK_BOX(parametro->vertical),parametro->label2,TRUE,TRUE,4);
  
  separador = gtk_hseparator_new();
  gtk_box_pack_start(GTK_BOX(parametro->vertical),separador,TRUE,TRUE,4);
  
  //NOMBRE
  parametro->label2 = gtk_label_new("Nombre");
  gtk_box_pack_start(GTK_BOX(horizontal1),parametro->label2,TRUE,TRUE,0);
  parametro->label1 = gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(horizontal1),parametro->label1,TRUE,TRUE,0);
  parametro->entry = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(parametro->vertical),horizontal1,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(parametro->vertical),parametro->entry,TRUE,TRUE,0);

  separador = gtk_hseparator_new();
  gtk_box_pack_start(GTK_BOX(parametro->vertical),separador,TRUE,TRUE,4);

  horizontal1 = gtk_hbox_new(TRUE,5);
  
  //TAMANIO DE RAZA
  parametro->label2 = gtk_label_new("Tamanio de raza");
  gtk_box_pack_start(GTK_BOX(horizontal1),parametro->label2,FALSE,FALSE,0);

  parametro->rb1 = gtk_radio_button_new_with_label(NULL,"Grande");
 
  parametro->rb2 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(parametro->rb1)),"Mediano");
  parametro->rb3 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(parametro->rb1)),"Chico");
  gtk_box_pack_start(GTK_BOX(vertical1),parametro->rb1,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(vertical1),parametro->rb2,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(vertical1),parametro->rb3,TRUE,TRUE,0);

  gtk_box_pack_start(GTK_BOX(horizontal1),vertical1,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(parametro->vertical),horizontal1,TRUE,TRUE,0);

  separador = gtk_hseparator_new();
  gtk_box_pack_start(GTK_BOX(parametro->vertical),separador,TRUE,TRUE,0);
  /*
  //ESTATUS
  vertical1 = gtk_vbox_new(TRUE,5);
  horizontal1 = gtk_hbox_new(TRUE,5);
  parametro->label2 = gtk_label_new("Estatus");
  gtk_box_pack_start(GTK_BOX(horizontal1),parametro->label2,TRUE,TRUE,0); 
  
  parametro->rb4 = gtk_radio_button_new_with_label(NULL,"Activo");
  parametro->rb5 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(parametro->rb4)),"Inactivo");
  gtk_box_pack_start(GTK_BOX(parametro->vertical3),parametro->rb4,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(parametro->vertical3),parametro->rb5,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(parametro->horizontal1),parametro->vertical3,TRUE,TRUE,0);

  gtk_box_pack_start(GTK_BOX(parametro->vertical2),parametro->horizontal1,TRUE,TRUE,0);
  
  separador = gtk_hseparator_new();
  gtk_box_pack_start(GTK_BOX(parametro->vertical2),separador,TRUE,TRUE,0);
  */
  
  //CANCELAR
  horizontal1 = gtk_hbox_new(TRUE,5);
  boton1 = gtk_button_new_with_label("Atras");
  gtk_box_pack_start(GTK_BOX(horizontal1),boton1,TRUE,TRUE,3);
  gtk_signal_connect(GTK_OBJECT(boton1),"clicked",GTK_SIGNAL_FUNC(ModRegPerro2),parametro);

  parametro->label2 = gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(horizontal1),parametro->label2,TRUE,TRUE,3);

  //GUARDAR
  boton1 = gtk_button_new_with_label("Guardar");
  gtk_box_pack_start(GTK_BOX(horizontal1),boton1,TRUE,TRUE,3);
  gtk_signal_connect(GTK_OBJECT(boton1),"clicked",GTK_SIGNAL_FUNC(GuardarRegistroPerro), parametro);

  gtk_box_pack_start(GTK_BOX(parametro->vertical),horizontal1,TRUE,TRUE,0);
  
  gtk_container_add(GTK_CONTAINER(parametro->ventana),parametro->vertical);
  gtk_widget_show_all(parametro->ventana);
  g_print ("Registrar Perro\n");
}

/*
 * Esta funcion crea la ventana para iniciar sesion en el modo cliente.
 * Crea un entrybox para ingresar el telefono y un boton para confirmar y otro para cancelar y salir.
 * El boton de confirmar conecta con la funcion de validar entrada.
 * Es de tipo void por lo que no regresa ninguna variable.
 * @author Ayelin Hazell Hernandez Martinez
 * @date 04/05/2021
 * @param GtkWidget *button      El boton de iniciar sesion
 * @param gpointer data     El parametro que incluye los datos de la estructura tipodato
*/
void IniciarSesion(GtkButton *button, gpointer data)
{
  tipodato *datos = (tipodato *)data;
  GtkWidget *label1, *label2;
  GtkWidget *entrybox;
  GtkWidget *hbox;
  GtkWidget *verticalbox;
  GtkWidget *button1, *button2;

  if (button != NULL)
    gtk_widget_destroy (datos->vertical);

  verticalbox = gtk_vbox_new(TRUE,5);
  datos->vertical = verticalbox;

  label1 = gtk_label_new ("Ingresa tu numero de telefono (max. 10 digitos y sin espacios)");
  gtk_box_pack_start(GTK_BOX(verticalbox),label1,FALSE,TRUE,0);

  label2 = gtk_label_new (NULL);
  datos->labeltel = label2;
  gtk_box_pack_start(GTK_BOX(verticalbox),label2,FALSE,TRUE,0);
   
  entrybox = gtk_entry_new_with_max_length (10);
  datos->entrytel = entrybox;
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox,FALSE,TRUE,0);
  
  hbox = gtk_hbox_new(TRUE,5);
  
  button1 = gtk_button_new_with_label ("Atras");
  gtk_box_pack_start(GTK_BOX(hbox),button1,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button1),"clicked",GTK_SIGNAL_FUNC(CrearInicio),datos);

  button2 = gtk_button_new_with_label ("Siguiente");
  gtk_box_pack_start(GTK_BOX(hbox),button2,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button2),"clicked",GTK_SIGNAL_FUNC(ValidarEntrada),datos);

  gtk_box_pack_start(GTK_BOX(verticalbox),hbox,FALSE,TRUE,0);
  gtk_container_add(GTK_CONTAINER(datos->ventana),verticalbox);
  gtk_widget_show_all(datos->ventana);
}

void AgendarCita (GtkButton *button, gpointer data)
{
}

/*
 * Esta funcion se utiliza para validar que el telefono introducido al ingresar sesion sea valido, y ademas que este registrado con un usuario existente.
 * Si el telefono es valido, se llama a la funcion de RegistroExitoso, con NULL como parametro de boton.
 * @author Ayelin Hazell Hernandez Martinez
 * @date 04/05/2021
 * @param GtkButton *button     El boton de Siguiente en la funcion de Registrarse
 * @param gpointer data     La variable que contiene los datos de la estructura de tipodato
 */
void ValidarEntrada (GtkButton *button, gpointer data)
{
  GdkColor color;
  tipodato *datos = (tipodato *)data;
  const gchar *Entrada;
  int i, Bandera = 0;
  char ValidarEntrada = 'T', Tel[15];

  gdk_color_parse("#eb360f", &color);//Color rojo

  Entrada = gtk_entry_get_text (GTK_ENTRY (datos->entrytel));
  if (strlen(Entrada)<10)
    {
    ValidarEntrada = 'F';
    gtk_label_set_text (GTK_LABEL(datos->labeltel), "*Obligatorio");
    }
  else
    {
      for (i=0; i<=9; i++)
	{
	  if (!(Entrada[i]>='0' && Entrada[i]<='9'))
	    {
	      ValidarEntrada = 'F';
	      gtk_label_set_text (GTK_LABEL(datos->labeltel), "*Introducir solo numeros");
	      break;
	    }
	}
    }


  if (ValidarEntrada == 'T')
    {
      strcpy (Tel, Entrada);
      Buscar_Cliente (datos->raiz, Tel, &(datos->cliente), &Bandera);
      Bandera=1;
      if (Bandera!=1)//Si no se encontro el numero
	{
	  ValidarEntrada = 'F';
	  gtk_label_set_text (GTK_LABEL(datos->labeltel), "*Numero no registrado");
	}
      else
	{
	  if (datos->arg == 1)
	    RegistroExitoso(NULL, datos);
	  else
	    ModRegPerro2(NULL, datos);
	}
    }
}

/*
 * Esta funcion valida los datos introducidos en la funcion de Registrarse.
 * Valida en contra de caracteres invalidos, tales como todos aquellos que no sean letras
 * en las entrybox del nombre y apellidos, y tambien en contra de todos aquellos caracteres
 * diferentes de numeros en la parte del telefono.
 * Crea tambien arreglos donde se guardan los datos en caso de ser validos, donde se les quitan
 * espacios sobrantes.
 * Valida tambien que las entrybox no esten vacias.
 * Siempre que haya un dato mal introducido se desplegara el mensaje de error correspondiente.
 * La validacion del telefono llama a la funcion de buscar cliente, con la cual se validara que el numero
 * a registrar no este ya en uso.
 * Se utiliza la variable ValidarRegistro para validar que todo este correcto, en caso de serlo se creara el ID
 * y se insertara el cliente en el arbol con los datos de los restos de los clientes.
 * @author Adrian Octavio Diaz Gaxiola
 * @date 03/05/2021
 * @param GtkWidget *button      El boton de confirmar el registro
 * @param gpointer data     El parametro que incluye los datos de la estructura tipodato
*/  
void ValidarRegistro (GtkButton *button, gpointer data)
{
  GdkColor color;
  tipodato *datos = (tipodato *)data;
  const gchar *Nombre, *ApellidoP, *ApellidoM, *Tel, *Corr;
  char Nombre2[30], ApellidoP2[20], ApellidoM2[20], Tel2[15], ID[10], Email[50], Status;
  int i, j, k, Bandera;
  char ValidarRegistro = 'T';

  gdk_color_parse("#eb360f", &color);//Color rojo

  //Se le asigna a las etiquetas de error el color rojo
  gtk_widget_modify_fg(GTK_WIDGET(datos->labelNC), GTK_STATE_NORMAL, &color);
  gtk_widget_modify_fg(GTK_WIDGET(datos->labelAP), GTK_STATE_NORMAL, &color);
  gtk_widget_modify_fg(GTK_WIDGET(datos->labelAM), GTK_STATE_NORMAL, &color);
  gtk_widget_modify_fg(GTK_WIDGET(datos->labeltel), GTK_STATE_NORMAL, &color);
  gtk_widget_modify_fg(GTK_WIDGET(datos->labelcorr), GTK_STATE_NORMAL, &color);   
  Nombre = gtk_entry_get_text (GTK_ENTRY (datos->entryNC));
  //Validar que si haya introducido algun caracter el usuario
  if (strlen(Nombre)<1)
    {
      ValidarRegistro = 'F';
      gtk_label_set_text (GTK_LABEL(datos->labelNC), "*Obligatorio");
    }
  //Si se introduzco algo
  else
    {
      //Validar que el nombre no contenga caracteres invalidos
      for (i=0; i<strlen(Nombre); i++)
	{
	  if (!((Nombre[i]>='a' && Nombre[i]<='z')||(Nombre[i]>='A' && Nombre[i]<='Z') || Nombre[i]==' '))
	    {
              ValidarRegistro = 'F';
              gtk_label_set_text (GTK_LABEL(datos->labelNC), "*Caracter(es) invalido(s)");
              break;
            }
	}
      //Si el nombre contiene caracteres validos
      if (i==strlen(Nombre))
	{
	  i = 0;
	  j = 0;
	  //Algoritmo para eliminar espacios sobrantes
	  while (Nombre[i] != '\0')
	    {
	      if (Nombre[i] == ' ')
		{
		  if (i==0)//Si hay espacios al inicio, se recorrera hasta encontrar un caracter diferente
		    k = i;
		  else
		    k = i + 1;
		  if (Nombre[k] != '\0')
		    {
		      while (Nombre[k] == ' ' && Nombre[k] !=  '\0')
			{
			  i++;
			  k++;
			}
		    }
		}
	      if (!(Nombre[i] == ' ' && Nombre[i+1] == '\0'))//Si el caracter a copiar es el ultimo y es un espacio, no se copiara ya que es sobrante
		{
		  Nombre2[j] = Nombre[i];//Se copia el nombre sin espacios sobrantes
		  j++;
		}
		i++;
	    }
	  Nombre2[j] = '\0';
	  if (strlen(Nombre2)<1)//Si el usuario introdujo solo espacios
	    {
	      ValidarRegistro = 'F';
	      gtk_label_set_text (GTK_LABEL(datos->labelNC), "*Obligatorio");
	    }
	  else//Si el nombre es valido
	    {
	      gtk_label_set_text (GTK_LABEL(datos->labelNC), NULL);
	    }
	}
    }

  ApellidoP = gtk_entry_get_text (GTK_ENTRY (datos->entryAP));
  if (strlen(ApellidoP)<1)
    {
      ValidarRegistro = 'F';
      gtk_label_set_text (GTK_LABEL(datos->labelAP), "*Obligatorio");
     }
  else
    {
      //Validar que el apellido paterno  no contenga caracteres invalidos
      for (i=0; i<strlen(ApellidoP); i++)
        {
          if (!((ApellidoP[i]>='a' && ApellidoP[i]<='z')||(ApellidoP[i]>='A' && ApellidoP[i]<='Z') || ApellidoP[i]==' '))
            {
              ValidarRegistro = 'F';
              gtk_label_set_text (GTK_LABEL(datos->labelAP), "*Caracter(es) invalido(s)");
              break;
            }
        }
      //Si el apellido paterno contiene caracteres validos
      if (i==strlen(ApellidoP))
        {
          i = 0;
          j = 0;
          while (ApellidoP[i] != '\0')
            {
              if (ApellidoP[i] == ' ')
                {
                  if (i==0)//Si hay espacios al inicio, se recorrera hasta encontrar un caracter diferente
                    k = i;
                  else
                    k = i + 1;
                  if (ApellidoP[k] != '\0')
		    {
                      while (ApellidoP[k] == ' ' && ApellidoP[k] !=  '\0')
                        {
                          i++;
                          k++;
                        }
                    }
                }
              if (!(ApellidoP[i] == ' ' && ApellidoP[i+1] == '\0'))//Si el caracter a copiar es el ultimo y es un espacio, no se copiara ya que es sobrante
                {
                  ApellidoP2[j] = ApellidoP[i];//Se copia el nombre sin espacios sobrantes
                  j++;
                }
	      i++;
            }
          ApellidoP2[j] = '\0';
          if (strlen(ApellidoP2)<1)//Si el usuario introdujo solo espacios
            {
              ValidarRegistro = 'F';
              gtk_label_set_text (GTK_LABEL(datos->labelAP), "*Obligatorio");
            }
          else//Si el nombre es valido
	    {
	      gtk_label_set_text (GTK_LABEL(datos->labelAP), NULL);
	    }
	}
    }

  ApellidoM = gtk_entry_get_text (GTK_ENTRY (datos->entryAM));
  if (strlen(ApellidoM)<1)
    {
      ValidarRegistro = 'F';
      gtk_label_set_text (GTK_LABEL(datos->labelAM), "*Obligatorio");
    }
  else
    {
      //Validar que el apellido materno  no contenga caracteres invalidos
      for (i=0; i<strlen(ApellidoM); i++)
        {
          if (!((ApellidoM[i]>='a' && ApellidoM[i]<='z')||(ApellidoM[i]>='A' && ApellidoM[i]<='Z') || ApellidoM[i]==' '))
            {
              ValidarRegistro = 'F';
              gtk_label_set_text (GTK_LABEL(datos->labelAM), "*Caracter(es) invalido(s)");
              break;
            }
        }
      //Si el apellido paterno contiene caracteres validos
      if (i==strlen(ApellidoM))
        {
          i = 0;
          j = 0;
          while (ApellidoM[i] != '\0')
            {
              if (ApellidoM[i] == ' ')
                {
                  if (i==0)//Si hay espacios al inicio, se recorrera hasta encontrar un caracter diferente
                    k = i;
                  else
                    k = i + 1;
                  if (ApellidoM[k] != '\0')
                    {
                      while (ApellidoM[k] == ' ' && ApellidoM[k] !=  '\0')
                        {
                          i++;
                          k++;
                        }
                    }
                }
              if (!(ApellidoM[i] == ' ' && ApellidoM[i+1] == '\0'))//Si el caracter a copiar es el ultimo y es un espacio, no se copiara ya que es sobrante
                {
                  ApellidoM2[j] = ApellidoM[i];//Se copia el nombre sin espacios sobrantes
                  j++;
                }
              i++;
            }
          ApellidoM2[j] = '\0';
          if (strlen(ApellidoM2)<1)//Si el usuario introdujo solo espacios
            {
              ValidarRegistro = 'F';
              gtk_label_set_text (GTK_LABEL(datos->labelAM), "*Obligatorio");
            }
          else//Si el nombre es valido
	    {
	      gtk_label_set_text (GTK_LABEL(datos->labelAM), NULL);
	    }
	}
    }

  Tel = gtk_entry_get_text (GTK_ENTRY (datos->entrytel));
  if (strlen(Tel)<1)
    {
      ValidarRegistro = 'F';
      gtk_label_set_text (GTK_LABEL(datos->labeltel), "*Obligatorio");
    }
  else
    {
      for (i=0; i<strlen(Tel); i++)
        {
	  if (Tel[i] == ' ' || Tel[i] == '-')//Validar que el telefono no contenga espacios ni guiones
	    {
	      ValidarRegistro = 'F';
	      gtk_label_set_text (GTK_LABEL(datos->labeltel), "*No introducir espacios ni guiones");
	      break;
	    }
          if (!((Tel[i]>='0' && Tel[i]<='9')))//Validar que el telefono solo contenga numeros
	    {
	      ValidarRegistro = 'F';
              gtk_label_set_text (GTK_LABEL(datos->labeltel), "*Caracter(es) invalido(s)");
              break;
            }
        }
      if (i==strlen(Tel))//Si el telefono es valido
	{
	  strcpy (Tel2, Tel);
	  Tel2[i] = '\0';
	  Bandera = 0;
	  Buscar_Cliente (datos->raiz, Tel2, &(datos->cliente), &Bandera);//Funcion para validar si el numero ya esta en uso
	  if (Bandera==1)//Si el numero ya esta en uso
	    {
	      ValidarRegistro = 'F';
	      gtk_label_set_text (GTK_LABEL(datos->labeltel), "*Numero ya en uso");
	    }
	  else
	    gtk_label_set_text (GTK_LABEL(datos->labeltel), NULL);
	}
    }

  Corr = gtk_entry_get_text (GTK_ENTRY (datos->entrycorr));
  if (strlen(Corr)<1)
    {
      ValidarRegistro = 'F';
      gtk_label_set_text (GTK_LABEL(datos->labelcorr), "*Obligatorio");
    }
  else
    {
      j = 0;
      for (i=0; i<strlen(Corr); i++)
        {
	  if (Corr[i] == ' ')
	    {
	      ValidarRegistro = 'F';
	      gtk_label_set_text (GTK_LABEL(datos->labelcorr), "*No introducir espacios");
	      j=1;
	      break;
	    }
          if (Corr[i] == '@')//Validar en busca de arrobas
	    j++;
	}
      if (j!=1)//Si no contiene exactamente una arroba
	{
	  ValidarRegistro = 'F';
	  if (j<1)
	    gtk_label_set_text (GTK_LABEL(datos->labelcorr), "*Debe contener una ""@""");
	  else
	    gtk_label_set_text (GTK_LABEL(datos->labelcorr), "*Max. 1 ""@""");
	}
      else
	{
        gtk_label_set_text (GTK_LABEL(datos->labelcorr), NULL);
	strcpy (Email, Corr);
	}
    }

  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(datos->rb1)))
    {
      Status = 'A';
      g_print ("Activo\n");
    }
  else
    {
      Status = 'I';
      g_print ("Inactivo\n");
    }
  if (ValidarRegistro=='T')
    {
      sprintf (ID, "CL%06d", CrearID (&(datos->NumClientes)));
      Insertar_Cliente(&(datos->raiz),Tel2, Nombre2, ID, Status,ApellidoP2,ApellidoM2, Email);
      RegistroExitoso (button, datos);
    }
}

/*
 * Esta funcion inserta un simbolo arroba en la entrybox del correo electronico al presionar un boyon.
 * Es de tipo void por lo que no regresa ninguna variable.
 * @author Adrian Octavio Diaz Gaxiola
 * @date 03/05/2021
 * @param GtkWidget *button      El boton de insertar '@'
 * @param gpointer data     El entrybox del correo electronico
 */
void Arroba(GtkButton *button, gpointer data)
{
  gtk_entry_append_text(GTK_ENTRY(data),"@");
}

/* 
 * Esta funcion determina si un cliente existe, y si es asi encuentra su posicion en el arbol.
 * Tambien es usada para determinar si el numero de telefono registrado esta en uso o no.
 * Es de tipo void por lo que no regresa ninguna variable.
 * @author Adrian Octavio Diaz Gaxiola
 * @date 03/05/2021
 * @param tipocliente *raiz     La raiz del arbol de clientes
 * @param char Tel[]     El numero de telefono utilizado para localizar un cliente
 * @param tipocliente     El nodo que contiene la informacion del cliente localizado. Si la funcion fue llamada desde validar registro, este parametro es NULL
 * @param int *Bandera     Bandera utilizada para determinar si se encontro el cliente con ese numero
 */
void Buscar_Cliente (tipocliente *raiz, char Tel[], tipocliente **temp, int *Bandera)
{
  if (raiz!=NULL)
    {
      if (strcmp(Tel,raiz->Telefono)>0)//Se recorre a la derecha del arbol
	Buscar_Cliente(raiz->der,Tel,temp,Bandera);
      else
	{
	  if (strcmp(Tel,raiz->Telefono)<0)//Se recorre a la izquierda del arbol
	    {
	      Buscar_Cliente(raiz->izq,Tel,temp,Bandera);
	    }
	  else
	    if (strcmp(Tel,raiz->Telefono)==0)//Si se encontro un cliente con ese numero
	      {
		if (*temp != NULL)
		  *temp = raiz;
		*Bandera = 1;
	      }
	}
    }
}

/*
 * Esta funcion recibe la variable que guarda el numero de clientes en la estructura y le agrega uno. 
 * Despues la variable local n toma el valor del numero de clientes y la funcion regresa este valor.
 * @author Adrian Octavio Diaz Gaxiola
 * @date 03/05/2021
 * @param int *NumClientes     El numero de clientes en el sistema
 * @return int
 */
int CrearID (int *NumClientes)
{
  int n;
  *NumClientes = *NumClientes + 1;
  n = *NumClientes;
  return n;
}

/*
 * Esta funcion inserta a un cliente registrado de manera no recursiva en el arbol que contiene los datos de los clientes.
 * Se utiliza tanto en el modo cliente como en el modo administrador, en el ultimo para lo cual se valida que el usuario a registrar 
 * no exista ya. 
 * Es de tipo void por lo que no regresa ninguna variable.
 * @author Adrian Octavio Diaz Gaxiola
 * @date 03/05/2021
 * @param tipocliente **Raiz      La raiz del arbol de clientes
 * @param char Tel[]     El arreglo con el telefono del cliente
 * @param char Nom[]     El nombre del cliente
 * @param char ID[]     El arreglo con el ID del cliente
 * @param char Estatus      El estatus del cliente
 * @param char Paterno[]     El arreglo con el apellido paterno del cliente
 * @param char Materno[]     El arreglo con el apellido materno del cliente
 */
void Insertar_Cliente(tipocliente **Raiz, char Tel[], char Nom[], char ID[], char Estatus, char Paterno[], char Materno[], char Email[])
{
  tipocliente *nuevo, *avanza, *temp;
  int Bandera = 0;
  
  Buscar_Cliente (*Raiz, Tel, &temp, &Bandera);

  if (Bandera == 0)
    {
      avanza = *Raiz;
      if ((nuevo=(tipocliente *)malloc(sizeof(tipocliente)))==NULL)
	{
	  printf ("No hay memoria\n");
	  exit(1);
	}

      strcpy(nuevo->Telefono,Tel);//Se copian los datos al nuevo nodo
      //(nuevo->Telefono)[10] = '\0';
      strcpy(nuevo->Nombre, Nom);
      strcpy(nuevo->ID, ID);
      strcpy(nuevo->Paterno, Paterno);
      strcpy(nuevo->Materno, Materno);
      strcpy(nuevo->Correo, Email);
      nuevo->Estatus = Estatus;
      nuevo->der = NULL;
      nuevo->izq = NULL;
      nuevo->Perro = NULL;

      //Algoritmo para crear el arbol de manera no recursiva
      while (avanza!=NULL)
	{
	  if (strcmp(Tel, avanza->Telefono)>0)
	    {
	      if (avanza->der!=NULL)
		avanza = avanza->der;
	      else
		{
		  avanza->der = nuevo;
		  return;
		}
	    }
	  if (strcmp(Tel,avanza->Telefono)<0)
	    {
	      if (avanza->izq!=NULL)
		avanza=avanza->izq;
	      else
		{
		  avanza->izq=nuevo;
		  return;
		}
	    }
	}
      avanza = nuevo;
      *Raiz = avanza;
    }
  else
    printf ("Ya esta ese usuario.\n");
}

/*
 * En esta funcion lo primero que se hace es destruit la caja de la ventana anterior.
 * Esta funcion sirve para configurar la capacidad de perros que hay, esta formada por tres spin buttons que son para configurar la capacidad. 
 * El boton <atras> sirve para regresar a la funcion donde esta el menu del administrador y el boton guardar manda a llamar a otra funcion y ahi se van a guardar las capacidades dentro de la estructura parametro. 
 *@author German Turnbull Agraz
 *@date 4 de mayo del 2021
 *@para: el boton con el que se mando llamar la funcion y la estructura del parametro
 */
void Configurar (GtkWidget *button, gpointer data)
{
   tipodato *parametro = (tipodato *)data;
  GtkWidget *label, *vertical2, *horizontal1, *horizontal2;
  GtkWidget *separador1;
  
  gtk_widget_destroy(parametro->vertical);
  
  parametro->vertical = gtk_vbox_new(FALSE,5);
  vertical2 = gtk_vbox_new(TRUE,2);
  horizontal1 = gtk_hbox_new(FALSE,5);
  horizontal2 = gtk_hbox_new(TRUE,5);
  
  //PERROS GRANDES
  label = gtk_label_new("Cantidad de perros grandes");
  gtk_box_pack_start(GTK_BOX(vertical2),label,TRUE,TRUE,0);
  parametro->spinner1 = gtk_spin_button_new_with_range(0, 999, 1);
  gtk_box_pack_start(GTK_BOX(vertical2),parametro->spinner1,TRUE,TRUE,0);
  label = gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(vertical2),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(horizontal1),vertical2,TRUE,TRUE,0);
  
  separador1 = gtk_vseparator_new();
  gtk_box_pack_start(GTK_BOX(horizontal1),separador1,TRUE,TRUE,0);

  vertical2 = gtk_vbox_new(TRUE,2);
  
  //PERROS MEDIANOS
  label = gtk_label_new("Cantidad de perros medianos");
  gtk_box_pack_start(GTK_BOX(vertical2),label,TRUE,TRUE,0);
  parametro->spinner2 = gtk_spin_button_new_with_range(0, 999, 1);
  gtk_box_pack_start(GTK_BOX(vertical2),parametro->spinner2,TRUE,TRUE,0);
  label = gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(vertical2),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(horizontal1),vertical2,TRUE,TRUE,0);
  
  separador1 = gtk_vseparator_new();
  gtk_box_pack_start(GTK_BOX(horizontal1),separador1,TRUE,TRUE,0);
  
  vertical2 = gtk_vbox_new(TRUE,2);
  
  //PERROS CHICOS
  label = gtk_label_new("Cantidad de perros chicos");
  gtk_box_pack_start(GTK_BOX(vertical2),label,TRUE,TRUE,0);
  parametro->spinner3 = gtk_spin_button_new_with_range(0, 999, 1);
  gtk_box_pack_start(GTK_BOX(vertical2),parametro->spinner3,TRUE,TRUE,0);
  label = gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(vertical2),label,TRUE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(horizontal1), vertical2,TRUE,TRUE,0);
  
  gtk_box_pack_start(GTK_BOX(parametro->vertical),horizontal1,TRUE,FALSE,0);
  // gtk_box_pack_start(GTK_BOX(parametro->vertical2),parametro->horizontal2,TRUE,FALSE,0);

  //Atras
  parametro->boton1 = gtk_button_new_with_label("Atras");
  gtk_signal_connect(GTK_OBJECT(parametro->boton1),"clicked",GTK_SIGNAL_FUNC(Admin_Crear_Inicio),parametro);
  gtk_box_pack_start(GTK_BOX(horizontal2),parametro->boton1,TRUE,TRUE,5);

  label = gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(horizontal2),label,TRUE,TRUE,0);

  //GuardarSpinner
  parametro->boton1 = gtk_button_new_with_label("Guardar");
  gtk_box_pack_start(GTK_BOX(horizontal2),parametro->boton1,TRUE,TRUE,5);
  gtk_signal_connect(GTK_OBJECT(parametro->boton1),"clicked",GTK_SIGNAL_FUNC(Guardar_Capacidad),parametro);
  gtk_signal_connect(GTK_OBJECT(parametro->boton1),"clicked",GTK_SIGNAL_FUNC(Admin_Crear_Inicio),parametro);

  //label2 = gtk_label_new("ola");
  //gtk_box_pack_start(GTK_BOX(parametro->vertical2),label2,TRUE,TRUE,0);
  
  gtk_box_pack_start(GTK_BOX(parametro->vertical),horizontal2,FALSE,FALSE,0);

  gtk_container_add(GTK_CONTAINER(parametro->ventana),parametro->vertical);
  gtk_widget_show_all(parametro->ventana);
  
  g_print ("Configurar\n");
}

/* En esta funcion se guarda la capacidad maxima de perros por cada tamanio.
 * Los valores se almacenan dentro de la estructura
 *@author German Turnbull
 *@date 4 de mayo del 2021
 *@param button, esta variable no se usa en realidad, solo es el boton que manda la senial.
 *@param data, este es la estructura de tipo parametro.
 */
void Guardar_Capacidad(GtkWidget *button, gpointer data)
{
  tipodato *parametro = (tipodato *)data;
  gint Chico, Grande, Mediano;
  Grande = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(parametro->spinner1));
  Mediano = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(parametro->spinner2));
  Chico = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(parametro->spinner3));
  parametro->maxg = Grande;
  parametro->maxm = Mediano;
  parametro->maxc = Chico;
  g_print ("Guardar\n");
  g_print ("%d, %d, %d\n",parametro->maxg, parametro->maxm, parametro->maxc);
}

void MostrarSalvar (GtkWidget *button, gpointer data)
{}
void ModRegCliente (GtkWidget *button, gpointer data)
{}

/*
 * En esta funcion se pide el numero para que despues se registre o se modifique un perro desde el modo administrador.
 * Si se oprime el boton <siguiente>, se manda llamar la funcion para validar el numero y de ahi, se manda llamar la funcion ModRegPerro2
 *@author German Turnbull Agraz
 *@date 4 de mayo del 2021
 *@param button es el boton con el que se manda llamar la funcion.
 *@param data es la estructura del parametro 
 */
void ModRegPerro (GtkWidget *button, gpointer data)
{
 tipodato *datos = (tipodato *)data;
  GtkWidget *label1, *label2;
  GtkWidget *entrybox;
  GtkWidget *hbox, *boton;
  GtkWidget *verticalbox;
  
  gtk_widget_destroy (datos->vertical);

  verticalbox = gtk_vbox_new(TRUE,5);
  datos->vertical = verticalbox;

  label1 = gtk_label_new ("Ingresa el numero telefonico del duenio del perro");
  gtk_box_pack_start(GTK_BOX(verticalbox),label1,FALSE,TRUE,0);

  label2 = gtk_label_new (NULL);
  datos->labeltel = label2;
  gtk_box_pack_start(GTK_BOX(verticalbox),label2,FALSE,TRUE,0);
   
  entrybox = gtk_entry_new_with_max_length (10);//gtk_entry_new ();
  datos->entrytel = entrybox;
  gtk_box_pack_start(GTK_BOX(verticalbox),entrybox,FALSE,TRUE,0);
  
  hbox = gtk_hbox_new(TRUE,5);
  
  boton = gtk_button_new_with_label ("Atras");
  gtk_box_pack_start(GTK_BOX(hbox),boton,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(boton),"clicked",GTK_SIGNAL_FUNC(Admin_Crear_Inicio),datos);
  
  boton = gtk_button_new_with_label ("Siguiente");
  gtk_box_pack_start(GTK_BOX(hbox),boton,FALSE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(boton),"clicked",GTK_SIGNAL_FUNC(ValidarEntrada),datos);
  
  gtk_box_pack_start(GTK_BOX(verticalbox),hbox,FALSE,TRUE,0);
  gtk_container_add(GTK_CONTAINER(datos->ventana),verticalbox);
  gtk_widget_show_all(datos->ventana);
  g_print ("ModPerro\n");
}

/*
 * En esta ventana se decide si se va a modificar un perro o si se va a registrar uno nuevo.
 * En la ventana hay tres botones, uno para registrar el perro nuevo, uno para modificar un perro ya registrado, y la ultima es para regresar a la ventana anterior.
 *@author German Turnbull Agraz
 *@date 4 de mayo del 2021
 *@param, *button, es el boton con la que se llamo la funcion, no tiene una utilidad en esta funcion
 *@param, data, es la estructura de parametro.
 */
void ModRegPerro2 (GtkWidget *button, gpointer data)
{
  tipodato *parametro = (tipodato *)data;
  GtkWidget *horizontal1;
  GtkWidget *boton1;
  
  gtk_widget_destroy(parametro->vertical);

  parametro->vertical = gtk_vbox_new(FALSE,5);
  horizontal1 = gtk_hbox_new(TRUE,5);
  
  boton1 = gtk_button_new_with_label("Registrar Perro");
  gtk_box_pack_start(GTK_BOX(horizontal1),boton1,TRUE,TRUE,3);
  gtk_signal_connect(GTK_OBJECT(boton1),"clicked",GTK_SIGNAL_FUNC(RegistrarPerro),parametro);

  boton1 = gtk_button_new_with_label("Modificar Perro");
  gtk_box_pack_start(GTK_BOX(horizontal1),boton1,TRUE,TRUE,3);
  gtk_signal_connect(GTK_OBJECT(boton1),"clicked",GTK_SIGNAL_FUNC(ModificarPerro),parametro);

  gtk_box_pack_start(GTK_BOX(parametro->vertical),horizontal1,TRUE,TRUE,3);
  
  boton1 = gtk_button_new_with_label("Atras");
  gtk_box_pack_start(GTK_BOX(parametro->vertical),boton1, TRUE,TRUE,3);
  gtk_signal_connect(GTK_OBJECT(boton1),"clicked",GTK_SIGNAL_FUNC(ModRegPerro),parametro);
  
  gtk_container_add(GTK_CONTAINER(parametro->ventana),parametro->vertical);
  gtk_widget_show_all(parametro->ventana);
}

void ModificarPerro (GtkWidget *button, gpointer data)
{}

/*
 * Aqui se valida que el nombre del perro haya sido introducido correctamente y se va a mandar llamar la funcion insertar el perro en la estructura de perros del cliente.
 *@author German Turnbull Agraz
 *@date 5 de mayo del 2021
 *@param el button solo manda llamar la funcion y no tiene utilidad aqui.
 *@param el data es la estructura de parametro donde esta la ventana entre otras cosas.
 */
void GuardarRegistroPerro(GtkWidget *button, gpointer data)
{
  GdkColor color;
  tipodato *datos = (tipodato *)data;
  const gchar *Nombre;
  char Nombre2[30];
  int i, j, k;
  char ValidarRegistro = 'T';
  
  gdk_color_parse("#eb360f", &color);
  gtk_widget_modify_fg(GTK_WIDGET(datos->label1),GTK_STATE_NORMAL,&color);
  
  Nombre = gtk_entry_get_text (GTK_ENTRY (datos->entry));
  //Validar que si haya introducido algun caracter el usuario
  if (strlen(Nombre)<1)
    {
      ValidarRegistro = 'F';
      gtk_label_set_text (GTK_LABEL(datos->label1), "*Obligatorio");
    }
  //Si se introduzco algo
  else
    {
      //Validar que el nombre no contenga caracteres invalidos
      for (i=0; i<strlen(Nombre); i++)
	{
	  if (!((Nombre[i]>='a' && Nombre[i]<='z')||(Nombre[i]>='A' && Nombre[i]<='Z') || Nombre[i]==' '))
	    {
              ValidarRegistro = 'F';
              gtk_label_set_text (GTK_LABEL(datos->label1), "*Caracter(es) invalido(s)");
              break;
            }
	}
      //Si el nombre contiene caracteres validos
      if (i==strlen(Nombre))
	{
	  i = 0;
	  j = 0;
	  //Algoritmo para eliminar espacios sobrantes
	  while (Nombre[i] != '\0')
	    {
	      if (Nombre[i] == ' ')
		{
		  if (i==0)//Si hay espacios al inicio, se recorrera hasta encontrar un caracter diferente
		    k = i;
		  else
		    k = i + 1;
		  if (Nombre[k] != '\0')
		    {
		      while (Nombre[k] == ' ' && Nombre[k] !=  '\0')
			{
			  i++;
			  k++;
			}
		    }
		}
	      if (!(Nombre[i] == ' ' && Nombre[i+1] == '\0'))//Si el caracter a copiar es el ultimo y es un espacio, no se copiara ya que es sobrante
		{
		  Nombre2[j] = Nombre[i];//Se copia el nombre sin espacios sobrantes
		  j++;
		}
	      i++;
	    }
	  Nombre2[j] = '\0';
	  if (strlen(Nombre2)<1)//Si el usuario introdujo solo espacios
	    {
	      ValidarRegistro = 'F';
	      gtk_label_set_text (GTK_LABEL(datos->label1), "*Obligatorio");
	    }
	  else//Si el nombre es valido
	    {
	      gtk_label_set_text (GTK_LABEL(datos->label1), NULL);
	    }
	}
    }
  
  if (ValidarRegistro == 'T')
    {
      g_print ("BIEN\n");
    }
}

void Acerca_de (GtkWidget *button, gpointer data)
{}
void ManualAdmin (GtkWidget *button, gpointer data)
{}

/*
 * Esta funcion termina el programa.
 * Es de tipo void por lo que no regresa ninguna variable
 * @author Ayelin Hazell Hernandez Martinez
 * @date 01/05/2020
 * @param GtkWidget *window     La ventana del programa a destruir
 * @param gpointer data     NULL
 */
void StopTheApp(GtkWidget *window, gpointer data)
{
  tipodato *parametro = (tipodato *)data;
  Imprime_Cliente (parametro->raiz);
  Libera_Cliente (parametro->raiz);  
  gtk_main_quit();
}

void Imprime_Cliente (tipocliente *Raiz)
{/*
  tipoperro *temp;
  
  if (Raiz!=NULL)
    {
      Imprime_Cliente (Raiz->izq);
      printf ("%s,%s,%s,%s,%s,%s,%c\n", Raiz->Telefono, Raiz->Nombre, Raiz->Paterno, Raiz->Materno,Raiz->ID,Raiz->Correo,Raiz->Estatus);
      temp = Raiz->Perro;
      while (temp!=NULL)
	{
	  printf ("%s,%s,%c\n", temp->Nombre, temp->IDPerro, temp->Estatus);
	  temp = temp->sig;
	}
      Imprime_Cliente(Raiz->der);
    }
*/}

/* 
 * En esta funcion se libera la lista de clientes 
 * Tambien se va a llamar a la funcion para liberar perros dentro de esta misma funcion 
 * @author German Turnbull Agraz 
 * @date 03/05/2021 
 * @param tipocliente *Raiz, se libera el arbol usando recursion 
 */
void Libera_Cliente (tipocliente *Raiz)
{
  if (Raiz!=NULL)
    {
      Libera_Cliente(Raiz->izq);
      Libera_Cliente(Raiz->der);
      Libera_Perro(&(Raiz->Perro));
      free(Raiz);
    }
}

/* 
 * En esta funcion se libera la lista de perros que esta dentro de cada nodo del arbol de clientes 
 * Es de tipo void porque no regresa nada 
 * @author German Turnbull Agraz 
 * @date 03/05/2021 
 * @param tipoperro **Primero, se libera la lista recorriendo cada elemento con el temporal 
 */
void Libera_Perro (tipoperro **Primero)
{
  tipoperro *temp;
  while (*Primero!=NULL)
    {
      temp = *Primero;
      *Primero = (*Primero)->sig;
      free(temp);
    }
}
