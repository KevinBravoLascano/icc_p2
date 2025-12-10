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
    // calcular valores de la funcion en los nodos
    for (int j = 0; j <= n; j++) {
        y[j] = fun(x[j]);
    }
    // Abrir archivo salida
    FILE *fp = fopen("salida.dat", "w");
    if (!fp) {
        printf("Error al abrir salida.dat\n");
        free(x); free(y);
        return -1;
    }

    //evaluar en 1000 puntos
    int m = 1000;
    for (int j = 0; j < m; j++) {
        double z = a + j * (b - a) / (m - 1);
        double pz;

        int err = lagrange_eval(z, n, x, y, &pz);
        if (err == -1) {
            printf("Error: lagrange_eval devolvió -1 en z = %lf\n", z);
            fclose(fp);
            free(x); free(y);
            return -1;
        }

        double fz = fun(z);
        double error = fabs(fz - pz);

        fprintf(fp, "%.15lf %.15lf %.15lf %.15lf\n", z, fz, pz, error);
    }

    fclose(fp);
    free(x);
    free(y);

    printf("Datos generados en salida.dat\n");
    return 0;
}