import numpy as np
import matplotlib.pyplot as plt

# Cargar datos
# Suponemos que el archivo tiene 6 columnas:
# 1: x, 2: f(x), 3: P_Lag, 4: |f-P_Lag|, 5: P_Newton, 6: |f-P_Newton|
data = np.loadtxt("exp3_n30_Cheb_compare.txt")

x = data[:,0]
f = data[:,1]
P_Lag = data[:,2]
err_Lag = data[:,3]
P_New = data[:,4]
err_New = data[:,5]

# Crear figura con dos subplots
fig, axs = plt.subplots(2, 1, figsize=(10,8))

# Grafico superior: función y polinomios
axs[0].plot(x, f, label="f(x)", color='blue', lw=2)
axs[0].plot(x, P_Lag, label="P_Lagrange", color='red', lw=2)
axs[0].plot(x, P_New, label="P_Newton", color='green', lw=2)
axs[0].set_ylabel("Valor")
axs[0].set_title("Interpolación de f(x)=exp(3x) con n=30 y nodos de Chebyshev")
axs[0].grid(True)
axs[0].legend()

# Grafico inferior: errores
axs[1].plot(x, err_Lag, label="Error Lagrange", color='red', lw=2)
axs[1].plot(x, err_New, label="Error Newton", color='green', lw=2)
axs[1].set_xlabel("x")
axs[1].set_ylabel("Error absoluto")
axs[1].grid(True)
axs[1].legend()

plt.tight_layout()
plt.show()
# Guardar la figura