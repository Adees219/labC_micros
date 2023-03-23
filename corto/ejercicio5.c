//ejercicio 5

#include <stdio.h>

int main()
{
  int numeros[10];
  int i, valor;
  
  for(i=0; i<10; i++) //ciclo para almacenar en cada posicion del arreglo un valor
  { 
      
    printf("ingrese un numero para el arreglo en la posicion %d: ", i+1);
    scanf("%d", &valor);
    numeros[i] = valor;
  }
  

  printf("El arreglo es: ");

  //ciclo para mostrar  los valores del array
    for(i=0; i<10; i++)
    {
    printf("%d ",numeros[i]);  
    }
   
    printf("\nEl nuevo arreglo es: ");
    int * Pnumeros = &numeros[0];         //puntero vinculado a la direccion de memoria de numeros

    for(i=0; i<10; i++) //ciclo donde se utiliza el puntero para obtener el valor de cada localidad del arreglo
    {        
        int temporal= *(numeros+i); //obtiene el valor ubicado en ese espacio de memoria
        temporal *=  2;    // se guarda en si mismo el doble del valor que encontro en la localidad
        printf("%d ", temporal);
    }

}