
#include <gtk/gtk.h>
#include <string.h>

void StopTheApp(GtkWidget *window, gpointer data);
void ButtonClicked(GtkWidget *window, gpointer data);
void ButtonClicked2(GtkWidget *window, gpointer data);
void ButtonClickedOp(GtkWidget *button, gpointer data);

gint main ( gint argc, gchar *argv[])
{

  GtkWidget *window;
  GtkWidget *button1;
  GtkWidget *button2;
  GtkWidget *button3;
  GtkWidget *button4;
  GtkWidget *button5;
  GtkWidget *button6;
  GtkWidget *button7;
  GtkWidget *button8;
  GtkWidget *button9;
  GtkWidget *button0;
  GtkWidget *buttonMul;
  GtkWidget *buttonDiv;
  GtkWidget *buttonSum;
  GtkWidget *buttonRes;
  GtkWidget *buttonIgual;
  GtkWidget *label;
  GtkWidget *menu, *menu1, *root_menu, *menu_bar,*op1, *op2, *op3;
   
  
  GtkWidget *box;
  GtkWidget *horizontalMomx;

  GtkWidget *vertbox1;
  GtkWidget *vertbox2;
  GtkWidget *vertbox3;
  GtkWidget *vertbox4;
  GtkWidget *vertbox5;
  
  
  GtkWidget *entrybox;
  
  
  gtk_init(&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),320,200);
  gtk_container_border_width(GTK_CONTAINER(window),5);

  
  horizontalMomx = gtk_hbox_new(TRUE,0);
  vertbox1  = gtk_vbox_new(TRUE,0);
  vertbox2 = gtk_vbox_new(TRUE,0);
  vertbox3 = gtk_vbox_new(TRUE,0);
  vertbox4 = gtk_vbox_new(TRUE,0);
  vertbox5 = gtk_vbox_new(TRUE,0);

  
  entrybox = gtk_entry_new();
  
  box = gtk_vbox_new(TRUE,5); 
  //button = AddButton(box,"pon texto",ButtonClicked,entrybox);
  //button = AddButton(box,"captura texto",HelloAction,entrybox);
  /*
  GtkTextBuffer *table;
  table = gtk_text_buffer_new (NULL);
  gtk_box_pack_start(GTK_BOX(window),table,FALSE,TRUE,0);
  */

  //menu
  menu1=gtk_menu_new();
  op1=gtk_menu_item_new_with_label("Subop1");
  op2=gtk_menu_item_new_with_label("Subop2");
  op3=gtk_menu_item_new_with_label("Subop3");
  gtk_menu_append(GTK_MENU(menu1), op1);
  gtk_menu_append(GTK_MENU(menu1), op2);
  gtk_menu_append(GTK_MENU(menu1), op3);


  menu=gtk_menu_new();
  op1=gtk_menu_item_new_with_label("Op1");
  op2=gtk_menu_item_new_with_label("Op2");
  op3=gtk_menu_item_new_with_label("Salir");

  gtk_signal_connect(GTK_OBJECT(op3),"activate", GTK_SIGNAL_FUNC(StoptheApp), NULL);
  
gtk_menu_append(GTK_MENU(menu), op1);

 gtk_item_set_submenu_(GTK_MENU_ITEM(op1), menu1);
 
 gtk_menu_append(GTK_MENU(menu), op2);
 gtk_menu_append(GTK_MENU(menu), op3);

 root_menu= gtk_menu_item_new_with_label("Calculadora");
  
gtk_item_set_submenu_(GTK_MENU_ITEM(root_menu), menu);
gtk_item_set_submenu_(GTK_MENU_ITEM(menu_bar), root_menu);


//sub2
 menu=gtk_menu_new();
  op1=gtk_menu_item_new_with_label("Leer");
  op2=gtk_menu_item_new_with_label("Guardar");
  op3=gtk_menu_item_new_with_label("Nuevo");
  gtk_menu_append(GTK_MENU(menu1), op1);
  gtk_menu_append(GTK_MENU(menu1), op2);
  gtk_menu_append(GTK_MENU(menu1), op3);

gtk_signal_connect(GTK_OBJECT(op3),"activate", GTK_SIGNAL_FUNC(lee), NULL);
 gtk_signal_connect(GTK_OBJECT(op3),"activate", GTK_SIGNAL_FUNC(guarda), NULL);
 gtk_signal_connect(GTK_OBJECT(op3),"activate", GTK_SIGNAL_FUNC(limpia), NULL);

 root_menu=gtk_menu_item_new_with_label("Opc3");
 gtk_signal_connect(GTK_OBJECT(root_menu),"activate", GTK_SIGNAL_FUNC(StopTheApp), NULL);
 gtk_menu_bar_append(GTK_MENU_BAR(menumenu_bar), root_menu);


 //fin del menu
 
// boton 1
    button1 = gtk_button_new_with_label("1");
    gtk_box_pack_start(GTK_BOX(vertbox1),button1,FALSE,TRUE,0);
     gtk_signal_connect(GTK_OBJECT(button1),"clicked",GTK_SIGNAL_FUNC(ButtonClicked),entrybox);
    
// boton 2
    button2 = gtk_button_new_with_label("2");
    gtk_box_pack_start(GTK_BOX(vertbox2),button2,FALSE,TRUE,0);
     gtk_signal_connect(GTK_OBJECT(button2),"clicked",GTK_SIGNAL_FUNC(ButtonClicked),entrybox);
    
// boton 3
    button3 = gtk_button_new_with_label("3");
    gtk_box_pack_start(GTK_BOX(vertbox3),button3,FALSE,TRUE,0);
     gtk_signal_connect(GTK_OBJECT(button3),"clicked",GTK_SIGNAL_FUNC(ButtonClicked),entrybox);
    

    // boton 4
    button4 = gtk_button_new_with_label("4");
    gtk_box_pack_start(GTK_BOX(vertbox1),button4,FALSE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button4),"clicked",GTK_SIGNAL_FUNC(ButtonClicked),entrybox);
    

    // boton 5
    button5 = gtk_button_new_with_label("5");
    gtk_box_pack_start(GTK_BOX(vertbox2),button5,FALSE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button5),"clicked",GTK_SIGNAL_FUNC(ButtonClicked),entrybox);
    
// boton 6
    button6 = gtk_button_new_with_label("6");
    gtk_box_pack_start(GTK_BOX(vertbox3),button6,FALSE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button6),"clicked",GTK_SIGNAL_FUNC(ButtonClicked),entrybox);
    

    // boton 7
    button7 = gtk_button_new_with_label("7");
    gtk_box_pack_start(GTK_BOX(vertbox1),button7,FALSE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button7),"clicked",GTK_SIGNAL_FUNC(ButtonClicked),entrybox);
    

    // boton 8
    button8 = gtk_button_new_with_label("8");
    gtk_box_pack_start(GTK_BOX(vertbox2),button8,FALSE,TRUE,0);
      gtk_signal_connect(GTK_OBJECT(button8),"clicked",GTK_SIGNAL_FUNC(ButtonClicked),entrybox);


    // boton 9
    button9 = gtk_button_new_with_label("9");
    gtk_box_pack_start(GTK_BOX(vertbox3),button9,FALSE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button9),"clicked",GTK_SIGNAL_FUNC(ButtonClicked),entrybox);

    // boton 0
    button0 = gtk_button_new_with_label("0");
    gtk_box_pack_start(GTK_BOX(vertbox2),button0,FALSE,TRUE,0);
      gtk_signal_connect(GTK_OBJECT(button0),"clicked",GTK_SIGNAL_FUNC(ButtonClicked),entrybox);

      //label. Sirve para dejar un espacio y que todos los numeros sean del mismo tamano
      label = gtk_label_new(" ");
      gtk_box_pack_start(GTK_BOX(vertbox1), label, FALSE, TRUE,0);

      
   // boton =
    buttonIgual = gtk_button_new_with_label("=");
    gtk_box_pack_start(GTK_BOX(vertbox3),buttonIgual,FALSE,TRUE,0);
     gtk_signal_connect(GTK_OBJECT(buttonIgual),"clicked",GTK_SIGNAL_FUNC(ButtonClicked2),entrybox);
    
    // botonMul
    buttonMul = gtk_button_new_with_label("*");
    gtk_box_pack_start(GTK_BOX(vertbox4),buttonMul,FALSE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(buttonMul),"clicked",GTK_SIGNAL_FUNC(ButtonClickedOp),entrybox);
    


    // boton div
    buttonDiv = gtk_button_new_with_label("/");
    gtk_box_pack_start(GTK_BOX(vertbox4),buttonDiv,FALSE,TRUE,0);
        gtk_signal_connect(GTK_OBJECT(buttonDiv),"clicked",GTK_SIGNAL_FUNC(ButtonClickedOp),entrybox);
       
    // boton sum
    buttonSum = gtk_button_new_with_label("+");
    gtk_box_pack_start(GTK_BOX(vertbox4),buttonSum,FALSE,TRUE,0);
     gtk_signal_connect(GTK_OBJECT(buttonSum),"clicked",GTK_SIGNAL_FUNC(ButtonClickedOp),entrybox);
    


// boton Res
    buttonRes = gtk_button_new_with_label("-");
    gtk_box_pack_start(GTK_BOX(vertbox4),buttonRes,FALSE,TRUE,0);
        gtk_signal_connect(GTK_OBJECT(buttonRes),"clicked",GTK_SIGNAL_FUNC(ButtonClickedOp),entrybox);
    ;


    

  gtk_box_pack_start(GTK_BOX(horizontalMomx),vertbox1,FALSE,TRUE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalMomx),vertbox2,FALSE,TRUE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalMomx),vertbox3,FALSE,TRUE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalMomx),vertbox4,FALSE,TRUE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalMomx),vertbox5,FALSE,TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box),entrybox,FALSE,TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box),horizontalMomx,FALSE,TRUE,0);
  
 
  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(StopTheApp),NULL);
  
    
  gtk_container_add(GTK_CONTAINER(window), box);

  gtk_box_pack_start(GTK_BOX(vertical2), menu_bar), FALSE,FALSE ,0);
  gtk_box_pack_start(GTK_BOX(vertical2), box5, TRUE,TRUE, 0);

  
  gtk_widget_show_all(window);
  
  gtk_main();

  return 0;

}


void ButtonClicked(GtkWidget *button, gpointer data)
{
  const gchar *text, *text2;
  char texto2[25];

  text= gtk_button_get_label(GTK_BUTTON(button));

  text2= gtk_entry_get_text(GTK_ENTRY(data));
  strcpy(texto2, text2);
  strcat(texto2, text);
  gtk_entry_set_text(GTK_ENTRY(data), texto2);

}


void ButtonClickedOp(GtkWidget *button, gpointer data)
{
  const gchar *text;
 int op1, op2;
 //  int res;
  //char operacion, resultado[30];

  text= gtk_entry_get_text(GTK_ENTRY(data));
  sscanf(text, "%d", &op1);
  gtk_entry_set_text(GTK_ENTRY(data), " ");
  /*switch(operacion)
    {
    case '*' :
      res= op1*op2;
      break ;
       case '/' :
      res= op1/op2;
      break ;
       case '+' :
      res= op1+op2;
      break ;
       case '-' :
      res= op1-op2;
      break ;
    }
  sprintf(resultado, "%d", res);
  gtk_entry_set_text(GTK_ENTRY(data), resultado);*/
}








void ButtonClicked2(GtkWidget *button, gpointer data)
{
  const gchar *text;
 int op1, op2;
  int res;
  char operacion, resultado[30];

  text= gtk_entry_get_text(GTK_ENTRY(data));
  sscanf(text, "%d%c%d", &op1, &operacion, &op2);
  switch(operacion)
    {
    case '*' :
      res= op1*op2;
      break ;
       case '/' :
      res= op1/op2;
      break ;
       case '+' :
      res= op1+op2;
      break ;
       case '-' :
      res= op1-op2;
      break ;
    }
  sprintf(resultado, "%d", res);
  gtk_entry_set_text(GTK_ENTRY(data), resultado);
}



  
void StopTheApp(GtkWidget *window, gpointer data)
{
    gtk_main_quit();
    

}



/*
void *AddButton(GtkWidget *thebox, const gchar *buttonText, gpointer CallBackFunction, GtkWidget )
{
  const gchar *text, *text2;
  char texto2[25];

  text= gtk_button_get_label(GTK_BUTTON(button));

  text2= gtk_entry_get_text(GTK_ENTRY(data));
  strcpy(texto2, text2);
  strcat(texto2, text);
  gtk_entry_set_text(GTK_ENTRY(data), texto2);

}
*/
