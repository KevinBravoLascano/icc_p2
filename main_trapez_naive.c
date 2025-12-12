#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Interp.h"
double f(double x);

int main() {
    const int MAX_IT = 1024;
    const double PRECISION = 1e-6;
    const double a = 0.0;
    const double b = 1.0;

    const double I_exact = exp(1.0) - 1.0;  // valor exacto e - 1

    FILE *fp = fopen("trapez_naive.dat", "w");
    if (!fp) {
        printf("ERROR: No se puede abrir trapez_naive.dat.\n");
        return 1;
    }

    double T_prev = 0.0;
    double T_curr = 0.0;
    double diff = 0.0;

    

    for (int n = 1; n <= MAX_IT; n++) {

        T_curr = trap_full(n, a, b);
        diff = fabs(T_curr - T_prev);
        double error = fabs(I_exact - T_curr);

        // Escribir en archivo
        fprintf(fp, "%d %.10f %.10f %.10f\n", n, T_curr, diff, error);

        // Comprobar criterio de parada (a partir de n >= 2)
        if (n > 1 && diff < PRECISION) {
            printf("Proceso detenido: |Tn - Tn-1| < %.1e en n = %d\n", PRECISION, n);
            break;
        }

        T_prev = T_curr;

        if (n == MAX_IT) {
            printf("Proceso detenido: alcanzado máximo número de iteraciones (%d)\n",
                   MAX_IT);
        }
    }

    fclose(fp);

    // Mostrar resultados finales
    double final_error = fabs(I_exact - T_curr);

    printf("\n=== RESULTADOS FINALES ===\n");
    printf("Aproximación final Tn = %.10f\n", T_curr);
    printf("Valor exacto I = %.10f\n", I_exact);
    printf("Error |Tn - I| = %.10f\n", final_error);
    printf("Archivo generado: trapez_naive.dat\n\n");

    return 0;
}