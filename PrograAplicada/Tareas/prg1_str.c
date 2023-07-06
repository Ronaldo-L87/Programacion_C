#include <stdio.h>
#include <stdio_ext.h>
#define TAM_FRASE 100 // Etiqueta para el tamanio de las frases

// Encabezados de funciones 
int Mi_strlen(char Frase1[]);
void Mi_strcpy(char Frase1[], char Frase2[]);
void Mi_strcat(char Frase1[], char Frase2[]);
int Mi_strcmp(char Frase1[], char Frase2[]);

// @fn Funcion principal
int main(void)
{
  char Frase1[TAM_FRASE], Frase2[TAM_FRASE];
  int Opcion; 
  // Menu de opciones
  do
    {
      printf("Este programa puede emular 4 funciones de la libreria string.h:\n1. strlen\n2. strcpy\n3. strcat\n4. strcmp\n");	
      printf("Ingresa una opcion: ");
      scanf("%d", &Opcion);
    }while(Opcion < 0 || Opcion > 4);
  __fpurge(stdin);
  if(Opcion == 1)
    {
      // Opcion para la funcion de Mi_strlen
      printf("\n\tFuncion para contar los caracteres de una frase (strlen)\n.");
      printf("Dame una frase: ");
      gets(Frase1);
      printf("Tu frase tiene %d caracteres.\n", Mi_strlen(Frase1));
    }
  if(Opcion == 2)
    {
      // Opcion para la funcion de Mi_strcpy
      printf("\n\tFuncion para copiar una cadena en otra (strcpy)\n");
      printf("Dame una frase: ");
      gets(Frase2);
      Mi_strcpy(Frase1, Frase2);
      printf("Tu frase copiada es: %s\n", Frase1);	
    }
  if(Opcion == 3)
    {
      // Opcion para la funcion de Mi_strcat
      printf("\n\tFuncion para concatenar cadenas (strcat)\n");
      printf("Dame una frase: ");
      gets(Frase1);
      printf("Dame otra frase: ");
      gets(Frase2);
      Mi_strcat(Frase1, Frase2);
      printf("La frase resultante es: %s\n", Frase1);	
    }
  if(Opcion == 4)
    {
      // Opcion para la funcion de Mi_strcmp
      printf("\n\tFuncion para comparar una cadena con otra (strcmp)\n");
      printf("Dame una frase: ");
      gets(Frase1);
      printf("Dame otra fase: ");
      gets(Frase2);
      if(Mi_strcmp(Frase1, Frase2) < 0)
	{
	  printf("La primer frase es menor que la segunda frase.\n");
	}
      else if(Mi_strcmp(Frase1, Frase2) == 0)
	{
	  printf("La primer frase es igual a la segunda frase.\n");
	}
      if(Mi_strcmp(Frase1, Frase2) > 0)
	{
	  printf("La primer frase es mayor que la segunda frase.\n");
	}  
    }
}

/* @Fn Funcion que cuenta los caracteres de una frase o cadena.
   @param Frase
   @rn Regresa un valor entero equivalente para la longitud de una cadena. */
int Mi_strlen(char Frase1[])
{
  int n=0;
  while(Frase1[n] != '\0')
    {
      n++;
    }
  return n;
}

/* @Fn Funcion que copia una cadena dentro de otra.
   @param Frase1, Frase2.
   @rn No retorna valor */
void Mi_strcpy(char Frase1[], char Frase2[])
{
  int n= 0;
  while(Frase2[n] != '\0')
    {
      Frase1[n] = Frase2[n];
    }
}

/* @Fn Funcion que concatena o une dos cadenas.
   @param Frase1, Frase2
   @rn No retorna valor. */
void Mi_strcat(char Frase1[], char Frase2[])
{
  int i=0, j=0;
  while(Frase1[i] != '\0')
    {
      i++;
    }
  while(Frase2[j] != '\0')
    {
      Frase1[i] = Frase2[j];
      j++;
      i++;
    }
}

/* @Fn Funcion que compara dos cadenas alfabeticamente.
   @param Frase1, Frase2
   @rn Retorna un valor entero positivo, negativo o igual a 0. */
int Mi_strcmp(char Frase1[], char Frase2[])
{
  int i=0;
  while(1)
    {
      if(Frase1[i] < Frase2[i])
       	return -1;
      if(Frase1[i] > Frase2[i])
	return 1;
      if(Frase1[i] == '\0' && Frase2[i] == '\0')
	return 0;
      i++;
    }
}
