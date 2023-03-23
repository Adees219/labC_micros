//ejercicio 4 
#include <stdio.h>
#include "library.h"

int main(){
    
    int a, b;
    float res[5];
    
    printf("Ingrese 2 numeros separados por un espacio para operarlos: ");
    scanf("%d %d", &a, &b);
    
    res[0] = pi();
    res[1] = suma(a,b);
    res[2] = resta(a,b);
    res[3] = divi(a,b);
    res[4] = mult(a,b);
    
    printf("\nResultados:\n PI: %.5f\n suma:%.2f\n resta:%.2f\n division:%.2f\n multiplicacion:%.2f\n", res[0], res[1], res[2], res[3], res[4]);
    return 0;
}
