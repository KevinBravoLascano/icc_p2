//empezar algo
#include <math.h>
int lagrange_eval(double z, int n, double *x, double *y, double *pz){
    //calcular el polinomio interpolador es un punto z
    double lagrange=0.0;
    for(int i=0;i<=n;i++){
        
        double liz=1;
        
        for(int j=0;j<=n;j++){ //calcular li
            if(j==i){
                continue;
            }
            double numerador=z-x[j];
            double denominador=x[i]-x[j];
            //comprobador de condicion return -1
            if(fabs(denominador)<1e-12){
                return -1;
            }
            double resultado=numerador/denominador;

            liz=liz*resultado;
        }
        
        lagrange+=y[i]*liz;
    }
    *pz=lagrange;
    return 0;
}

double horner(double z, int n, double *x, double *c){
// Empezamos con el coeficiente más grande
    double resultado = c[n];
    
    // Iteramos hacia atrás desde n-1 hasta 0
    for (int i = n - 1; i >= 0; i--) {
        resultado = resultado * (z - x[i]) + c[i];
    }
    
    return resultado;
}
int difdiv(int n, double *x, double *y) {


    for (int j = 1; j <= n; j++) {          // orden de la diferencia
        for (int i = n; i >= j; i--) {      // recorrido desde atrás para no sobrescribir
            double denom = x[i] - x[i - j];
            if (fabs(denom) < 1e-12) {      // comprobación del denominador
                return -1;                   // error, denominador demasiado pequeño
            }
            y[i] = (y[i] - y[i - 1]) / denom;  // cálculo de la diferencia dividida
        }
    }
    return 0;  // todo correcto
}

double trap_full(int n, double a, double b){
    double h = (b - a) / n;
    double integral = 0.5 * (fun(a) + fun(b));
    for (int j = 1; j < n; j++) {
        double x_i = a + j * h;
        integral += fun(x_i);
    }   
    integral *= h;
    return integral; 
}
