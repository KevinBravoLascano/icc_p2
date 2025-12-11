#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Interp.h"
double fun(double x);
int main(){
    // Variables para el numero de puntos, intervalo y tipo de nodo
    int n, tipo;
    double a,b;
    // Solicitar datos al usuario
    printf("Ingrese el numero de puntos de interpolacion: ");
    scanf("%d", &n);

    printf("Ingrese el intervalo [a,b]: ");
    scanf("%lf %lf", &a, &b);

    printf("Seleccione el tipo de nodo:\n1. equidistantes\n2. cchebyshev\n");
    scanf("%d", &tipo);

     // Reservar memoria para nodos y valores
    double *x = malloc((n+1) * sizeof(double));
    double *y = malloc((n+1) * sizeof(double));
    
    if (!x || !y) {
        printf("Error: no se pudo reservar memoria.\n");
        return -1;
    }
    // Generar nodos
    if (tipo == 1) {
        // Nodos equidistantes
        for (int j = 0; j <= n; j++) {
            x[j] = a + j * (b - a) / n;
        }
    }else if (tipo == 2) {
        // Nodos de Chebyshev
        for (int j = 0; j <= n; j++) {
            x[j] = 0.5 * (a + b) + 0.5 * (b - a) * cos(M_PI * (2 * j + 1) / (2 * (n + 1)));
        }
    } else {
        printf("Tipo de nodo invalido.\n");
        free(x);
        free(y);
        return -1;
    }
    // Calcular valores de la función en los nodos
    for (int j = 0; j <= n; j++) {
        y[j] = fun(x[j]);
    }
    // Calcular coeficientes de Newton
    if (difdiv(n, x, y) == -1) {
        printf("Error: denominador demasiado pequeño en difdiv.\n");
        free(x); free(y);
        return -1;
    }
    

    // Evaluar en 1000 puntos equidistantes en [a,b]
    int m = 1000;
    FILE *fp = fopen("salida.dat", "w");
    if (!fp) {
        printf("Error al abrir salida.dat\n");
        free(x); free(y);
        return -1;
    }

    for (int j = 0; j < m; j++) {
        double z = a + j * (b - a) / (m - 1);   // punto de evaluación
        double pz = horner(z, n, x, y);         // evaluar polinomio
        double fz = fun(z);                      // valor exacto
        double error = fabs(fz - pz);            // error

        fprintf(fp, "%.15lf %.15lf %.15lf %.15lf\n", z, fz, pz, error);
    }

    fclose(fp);
    printf("Datos generados en salida.dat\n");
        return 0;
}