int lagrange_eval(double z, int n, double *x, double *y, double *pz);
double horner(double z, int n, double *x, double *c);
int difdiv(int n, double *x, double *y);
double trap_full(int n, double a, double b);
double trap_refined(double Tn, int n, double a, double b);
