#!/bin/bash

# Archivo de salida para guardar los resultados
archivo_salida="resultados.txt"

# Iterar desde el número 62 hasta el 100
for ((numero=65; numero<=100; numero++)); do
    # Construir la ruta del archivo
    archivo="Laberintos_100/laberinto_${numero}.txt"

    # Verificar si el archivo existe
    if [ ! -e "$archivo" ]; then
        echo "El archivo $archivo no existe."
        continue
    fi
    echo -e "DFS" >> "$archivo_salida"
    # Ejecutar el comando con el tiempo para DFS_algo y guardar la salida en el archivo
    { time ./DFS < "$archivo"; } >> $"$archivo_salida" 2>> "$archivo_salida"
    echo -e "BFS" >> "$archivo_salida"
    # Ejecutar el comando con el tiempo para BFS_algo y guardar la salida en el archivo
    { time ./BFS < "$archivo"; } >> $"$archivo_salida" 2>> "$archivo_salida"
    
done

echo "Proceso completado. Los resultados se han guardado en $archivo_salida."
