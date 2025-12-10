import numpy as np
import matplotlib.pyplot as plt

# Cargar datos
data = np.loadtxt("salida.dat")
z = data[:,0]
fz = data[:,1]
Pn = data[:,2]
error = data[:,3]

# Graficar función y polinomio interpolador
plt.figure(figsize=(8,5))
plt.plot(z, fz, label='f(z)', color='blue')
plt.plot(z, Pn, label='P_n(z)', color='red', linestyle='--')
plt.xlabel('z')
plt.ylabel('Valor')
plt.title('Interpolación de Lagrange')
plt.legend()
plt.grid(True)
plt.show()

# Graficar el error
plt.figure(figsize=(8,5))
plt.plot(z, error, color='green')
plt.xlabel('z')
plt.ylabel('|f(z) - P_n(z)|')
plt.title('Error de interpolación')
plt.grid(True)
plt.show()
