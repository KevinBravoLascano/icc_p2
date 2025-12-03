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