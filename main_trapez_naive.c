#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Interp.h"
double fun(double x);
int main(){
    int n;
    double a,b;
    double precision = 1e-6;
    printf("Ingrese el numero de subintervalos para la integral: ");
    scanf("%d", &n);
    printf("Ingrese el intervalo [a,b]: ");
    scanf("%lf %lf", &a, &b);

    double resultado = trap_full(n, a, b);
    printf("El valor aproximado de la integral es: %.10lf\n", resultado);

    return 0;
}