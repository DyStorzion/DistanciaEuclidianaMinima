import pandas as pd
import matplotlib
import matplotlib.pyplot as plt

# Abrir un archivo CSV
df1 = pd.read_csv('test_bf.csv')
df2 = pd.read_csv('test_bfImp.csv')
df3 = pd.read_csv('test_dac.csv')
df4 = pd.read_csv('test_dacImp.csv')

# Graficar cada línea
# plot(x=valores, y=valores, label, marker)
plt.plot(df1['n'], df1['t_mean'], label='Brute Force', marker='o')
plt.plot(df2['n'], df2['t_mean'], label='Improved Brute Force', marker='D')
plt.plot(df3['n'], df3['t_mean'], label='Divide and Conquer', marker='x')
plt.plot(df4['n'], df4['t_mean'], label='Improved Divide and Conquer', marker='+')

# Etiquetas de los ejes
plt.xlabel('Input size')
plt.ylabel('Running time (nanoseconds)(log)')

# Escala logarítmica en el eje Y


# Mostrar la leyenda
plt.legend()

# Guardar el gráfico en un archivo
plt.savefig('plot1.png')
