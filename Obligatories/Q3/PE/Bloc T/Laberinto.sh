#!/bin/bash

# Compilar el programa C++ si es necesario
# g++ tu_programa.cpp -o tu_programa

# Directorio para guardar los resultados
results_dir="Laberintos"

# Crear el directorio si no existe
mkdir -p "$results_dir"

# Número de ejecuciones
num_executions=100

# Bucle para ejecutar el programa 100 veces
for ((i=1; i<=$num_executions; i++)); do
    sleep 1
    # Nombre del archivo de resultado
    result_file="$results_dir/laberinto_$i.txt"

    # Ejecutar el programa y guardar el resultado en el archivo
    ./Lab_gen > "$result_file"

    echo "Ejecución $i completada. Resultado guardado en $result_file"
done
