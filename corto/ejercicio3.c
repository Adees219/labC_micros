//Ejercicio 3: serie de fibonacci

#include <stdio.h>

/*int main(){
    int i;
    for (i=1; i<=10; i++)
    {
        printf("%d ",i);
    }
    return 0;
*/

int main(){
    int N, i, a, b, c;
    a = 0;
    b = 1;
    
    printf("Ingrese la cantidad de terminos para la serie de Fibonacci: ");
    scanf("%d", &N);

    for (i=0; i<=N; i++)
    {   
        c = b+a; 
        a = b;
        b = c;
        printf("%d ",c);
    }
    return 0;

}