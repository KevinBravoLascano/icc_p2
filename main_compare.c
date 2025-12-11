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
    double *x2 = malloc((n+1) * sizeof(double));
    double *y2 = malloc((n+1) * sizeof(double));;
    
    if (!x || !y) {
        printf("Error: no se pudo reservar memoria.\n");
        return -1;
    }
    // Generar nodos
    if (tipo == 1) {
        // Nodos equidistantes
        for (int j = 0; j <= n; j++) {
            x[j] = a + j * (b - a) / n;
            x2[j] = a + j * (b - a) / n;
        }
    }else if (tipo == 2) {
        // Nodos de Chebyshev
        for (int j = 0; j <= n; j++) {
            x[j] = 0.5 * (a + b) + 0.5 * (b - a) * cos(M_PI * (2 * j + 1) / (2 * (n + 1)));
            x2[j] = 0.5 * (a + b) + 0.5 * (b - a) * cos(M_PI * (2 * j + 1) / (2 * (n + 1)));
        }
    } else {
        printf("Tipo de nodo invalido.\n");
        free(x);
        free(y);
        free(x2);
        free(y2);
        return -1;
    }
    // Calcular valores de la función en los nodos
    for (int j = 0; j <= n; j++) {
        y[j] = fun(x[j]);
        y2[j] = fun(x2[j]);
    }
    // Calcular coeficientes de Newton
double *y_newton = malloc((n+1)*sizeof(double));
for(int i=0;i<=n;i++) y_newton[i] = y[i];
if(difdiv(n,x,y_newton)==-1){ printf("Error difdiv\n"); return -1; }

int m = 1000;
FILE *fp = fopen("exp3_n30_Cheb_compare.txt ","w");
if(!fp){ printf("Error abrir archivo\n"); return -1; }

double errLagMax=0, errNewMax=0;

for(int j=0;j<m;j++){
    double z = a + j*(b-a)/(m-1);
    double fz = fun(z);

    // Lagrange
    double pLag;
    if(lagrange_eval(z,n,x,y,&pLag)==-1){ printf("Error lagrange\n"); return -1; }
    double errLag = fabs(fz - pLag);
    if(errLag>errLagMax) errLagMax = errLag;

    // Newton
    double pNew = horner(z,n,x,y_newton);
    double errNew = fabs(fz - pNew);
    if(errNew>errNewMax) errNewMax = errNew;

    // Guardar 6 columnas
    fprintf(fp,"%.15lf %.15lf %.15lf %.15lf %.15lf %.15lf\n",z, fz, pLag, errLag, pNew, errNew);
}

    fclose(fp);
    free(y_newton);
    free(x);
    free(y);
    free(x2);
    free(y2);

    printf("Max error Lagrange = %.15lf\n", errLagMax);
    printf("Max error Newton   = %.15lf\n", errNewMax);
    printf("Datos generados en exp3_n30_Cheb_compare.txt \n");

    return 0;
}