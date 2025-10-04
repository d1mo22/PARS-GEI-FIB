import pandas as pd

# Leer el archivo CSV
df = pd.read_csv('hotel_sample_5000.csv')

# Primero vamos a ver los nombres de las columnas para detectar el problema
print("Nombres de las columnas:")
print(df.columns.tolist())
print("\n")

# Limpiar los nombres de las columnas (eliminar espacios extra)
df.columns = df.columns.str.strip()

# Ahora vamos a ver los nombres limpios
print("Nombres de las columnas después de limpiar:")
print(df.columns.tolist())
print("\n")

# Contar cuántas meals hay definidas como "Undefined"
undefined_meals = df[df['"meal"'] == 'NULL'].shape[0]

print(f"Número de registros con meal = 'Undefined': {undefined_meals}")

# También puedes ver todos los valores únicos de la columna meal
print("\nTodos los tipos de meal en el dataset:")
print(df['"meal"'].value_counts())

# O específicamente buscar registros con "Undefined"
if undefined_meals > 0:
    print(f"\nRegistros con meal 'Undefined':")
    print(df[df['"meal"'] == 'Undefined']
          [['hotel', 'meal', 'country', 'customer_type']])
