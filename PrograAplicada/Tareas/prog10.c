#include <stdio.h>

void Pedir_Fechas(int *dia, int *mes, int *anio);
int Validar_Fechas(int dia1, int dia2, int mes1, int mes2, int anio1, int anio2);
void Calcular_Fechas(int dia1, int dia2, int mes1, int mes2, int anio1, int anio2, int *res);
void Desplegar(int res);

int main(void)
{
  int dia1, dia2, mes1, mes2, anio1, anio2, res;
	
  Pedir_Fechas(&dia1, &mes1, &anio1);
  Pedir_Fechas(&dia2, &mes2, &anio2);
  if(Validar_Fechas(dia1, dia2, mes1, mes2, anio1, anio2) == 0);
  {
    printf("XDD\n");
    Calcular_Fechas(dia1, dia2, mes1, mes2, anio1, anio2, &res);
    Desplegar(res);
  }
  return 0;
}

void Pedir_Fechas(int *dia, int *mes, int *anio)
{
  printf("Ingresa una fecha: ");
  scanf("%d/%d/%d", dia, mes, anio);	
}

int Validar_Fechas(int dia1, int dia2, int mes1, int mes2, int anio1, int anio2)
{
  printf("%d/%d/");
  if(anio1 <= anio2)
    {
      if(mes1 <= mes2)
	{
	  if(dia1 <= dia2)
	    {
	      return 0;
	    }
	}
    }
  return 1;
}
void Calcular_Fechas(int dia1, int dia2, int mes1, int mes2, int anio1, int anio2, int *res)
{
	
}
void Desplegar(int res)
{
	
}
