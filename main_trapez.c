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
    const double I_exact = exp(1.0) - 1.0;  // Integral exacta

    FILE *fp = fopen("trapez_2n.dat", "w");
    if (!fp) {
        printf("ERROR: No se puede abrir 'trapez_2n.dat'\n");
        return 1;
    }

    // Empezamos con T1
    double Tn = 0.5 * (f(a) + f(b)) * (b - a); // Aproximación inicial
    int n = 1;

    while (n <= MAX_IT) {
        double T2n = trap_refined(Tn, n, a, b);
        double diff = fabs(T2n - Tn);
        double error = fabs(I_exact - T2n);

        // Escribir en archivo
        fprintf(fp, "%d %.10f %.10f %.10f\n", 2*n, T2n, diff, error);

        if (diff < PRECISION) {
            printf("Proceso detenido: |T2n - Tn| < %.1e con n=%d\n", PRECISION, n);
            Tn = T2n;
            break;
        }

        Tn = T2n;
        n *= 2;  // Doblar el número de subintervalos

        if (n > MAX_IT) {
            printf("Proceso detenido: alcanzado máximo de iteraciones (%d)\n", MAX_IT);
        }
    }

    fclose(fp);

    double final_error = fabs(I_exact - Tn);

    // Mostrar resultados finales
    printf("\n=== RESULTADOS FINALES ===\n");
    printf("Aproximación final T2n = %.10f\n", Tn);
    printf("Valor exacto I          = %.10f\n", I_exact);
    printf("Error final             = %.10f\n", final_error);
    printf("Archivo generado: trapez_2n.dat\n");

    return 0;
}