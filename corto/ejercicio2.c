//Ejercicio 2: solicitar datos

#include <stdio.h>
int main(){
   /* int a, b, suma;
    printf("Ingrese dos numeros enteros separados por un espacio: ");
    scanf("%d %d", &a, &b);
    suma = a + b;
    printf("La suma de %d y %d es %d\n", a, b, suma);*/
    
    float tFahrenheit, tCelcius;
    printf("Ingrese la temperatura en grados fahrenheit: ");
    scanf("%2f", &tFahrenheit);
    tCelcius = (tFahrenheit-32)/1.8;
    printf("su temperatura en grados celcius es de: %f", tCelcius);
    return 0;
}

