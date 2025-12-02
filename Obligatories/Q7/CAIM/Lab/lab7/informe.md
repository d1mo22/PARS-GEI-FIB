# Informe: Lab 7 - MapReduce y Spark RDDs

**Autores:** David Morais, Guillem Cabré  
**Fecha:** 2 de diciembre de 2025

---

## Introducción

Este laboratorio explora el procesamiento distribuido de datos usando la API RDD de Apache Spark. Implementamos dos algoritmos clave usando el paradigma MapReduce: un índice invertido para búsqueda de texto y PageRank para análisis de grafos sobre datos de Wikipedia.

---

## Ejercicio 1: Índice Invertido

### Implementación

El índice invertido mapea cada término a una lista ordenada de IDs de documentos donde aparece. Nuestra implementación sigue estos pasos:

1. **Detección de Stopwords:** Identificamos las 40 palabras más frecuentes como stopwords usando conteo de palabras con `reduceByKey`.

2. **Construcción del Índice:**
   - `flatMap`: Tokeniza cada título y emite pares (palabra, doc_id), filtrando stopwords
   - `distinct`: Elimina pares duplicados (misma palabra varias veces en un documento)
   - `groupByKey`: Agrupa todos los doc_ids para cada palabra
   - `map`: Ordena la posting list para cada término
   - `sortByKey`: Ordena los términos alfabéticamente

### Decisiones de Diseño

- **Variables broadcast:** El conjunto de stopwords se hace broadcast a todos los workers para evitar enviarlo con cada tarea
- **distinct() antes de groupByKey:** Reduce el shuffle eliminando duplicados temprano
- **Filtrado:** Se eliminan tokens numéricos y palabras muy cortas para mejorar la calidad del índice

---

## Ejercicio 2: PageRank con MapReduce

### Implementación

Nuestra implementación de PageRank maneja damping, teletransportación y nodos sin salida (sinks) usando operaciones RDD distribuidas.

**Componentes clave:**

1. **Cálculo de Out-degrees:** Mapea cada arista a su nodo fuente y cuenta aristas salientes usando `reduceByKey`.

2. **Algoritmo Principal:** Calcula PageRank iterativamente hasta convergencia.

### Decisiones de Diseño

- **Broadcast pr_div:** Evita un join costoso entre aristas y valores pr; cada worker lee de la variable broadcast
- **Collect contributions:** Como contributions es de tamaño O(n) (uno por nodo con aristas entrantes), hacer collect al driver es aceptable
- **Manejo de sinks:** Los nodos sin salida redistribuyen su PR uniformemente a todos los nodos
- **Convergencia:** La norma L1 asegura detectar cuándo PR se estabiliza

---

## Preguntas de Discusión

### 1. Pre-calcular la Matriz de Google

Si calculáramos la matriz de Google G por adelantado (combinando adyacencia, damping y teletransportación):

**Pros:** 
- Simplifica la iteración a solo multiplicación matriz-vector

**Contras:** 
- **Explosión de memoria:** G es densa (n×n), requiriendo almacenamiento O(n²)
- No cabe en memoria distribuida para grafos grandes
- Derrota el propósito de MapReduce para escalabilidad

El enfoque con matriz de Google solo funciona para grafos pequeños que caben completamente en memoria.

### 2. Rendimiento Secuencial vs Distribuido

**Comparación con Lab 6:**

- **Corrección:** Ambas implementaciones producen resultados idénticos
- **Velocidad:** La versión secuencial es **más rápida** para este dataset

**Razones:**
- n ≈ 4M vértices cabe en memoria de una sola máquina
- Overhead de Spark: serialización, planificación de tareas, shuffle
- Costes de comunicación de red superan beneficios de paralelización
- Computación local con NumPy está altamente optimizada

**Cuándo gana Spark:** Grafos demasiado grandes para memoria de una sola máquina, o cuando se usa un cluster real con muchos nodos.

### 3. Pre-calcular Vecinos Entrantes con groupByKey

**Enfoque:** Agrupar aristas por destino para obtener (v, [lista de vecinos entrantes])

**Análisis:**

- **¿Más rápido?** No necesariamente

**Problemas:**
- `groupByKey` sin combiner → shuffle masivo de todas las aristas
- Nodos de alto grado crean hotspots de memoria (particiones sesgadas)
- Debe materializar listas completas de vecinos en memoria
- Nuestro enfoque (`reduceByKey` sobre contribuciones) usa combiners, reduciendo shuffle

**Mejor alternativa:** Usar `reduceByKey` como hicimos, que agrega incrementalmente y minimiza movimiento de datos.

### 4. Si n es Demasiado Grande para Memoria

**Estrategias cuando n no cabe en memoria del driver/worker:**

1. **Particionar vector PR:** Almacenar pr como RDD en vez de array NumPy
   - Usar operaciones `join` en vez de broadcast
   - Cambiar memoria por computación/comunicación

2. **Representación dispersa:** La mayoría de grafos reales tienen distribuciones PR dispersas
   - Solo almacenar/actualizar contribuciones no-cero
   - Usar formatos dispersos comprimidos

3. **Procesamiento por bloques:** Particionar nodos en bloques que caben en memoria
   - Procesar un bloque a la vez
   - Checkpointing para manejar fallos

4. **Algoritmos de memoria externa:** Volcar a disco cuando sea necesario
   - Niveles de persistencia de Spark: `MEMORY_AND_DISK`
   - Aceptar I/O más lenta para mayor escala

---

## Detalles de Implementación

### Estructuras de Datos

- **RDDs:** Colecciones distribuidas inmutables, particionadas entre workers
- **Variables broadcast:** Variables de solo lectura cacheadas en cada worker (stopwords, outdegree, pr_div)
- **Arrays NumPy:** Vectores densos en el driver para pr, outdeg, teleport (memoria O(n))

### Técnicas de Optimización

- **Caching:** `edges_rdd.cache()`, `titles_rdd.cache()` para reutilizar computaciones costosas
- **Combiners:** `reduceByKey` en vez de `groupByKey` para minimizar shuffle
- **Particionamiento:** `repartition(6)` para balancear carga entre cores
- **Evaluación perezosa:** Spark construye plan de ejecución; computación se dispara solo con acciones

### Desafíos Encontrados

- **Filtrado de stopwords:** La versión inicial no usaba broadcast, causando overhead de serialización
- **Gestión de memoria:** Broadcasts grandes requieren unpersist() para liberar memoria
- **Rutas de archivos:** Hubo que usar rutas absolutas para los archivos de datos

---

## Conclusiones

Este laboratorio demostró el poder del modelo de programación MapReduce para procesamiento distribuido, al mismo tiempo que resaltó cuándo los algoritmos secuenciales siguen siendo superiores. Conclusiones clave:

1. **Las abstracciones importan:** Los RDDs proporcionan tolerancia a fallos y paralelización automática
2. **Comprender tus datos:** Datasets pequeños pueden no beneficiarse de la distribución
3. **Minimizar shuffle:** Usar combiners, evitar groupByKey cuando sea posible
4. **Jerarquía de memoria:** Hacer broadcast de datos pequeños, particionar datos grandes
5. **Trade-offs:** Los sistemas distribuidos añaden complejidad; solo usar cuando sea necesario

Las implementaciones de índice invertido y PageRank muestran cómo algoritmos complejos pueden expresarse elegantemente en MapReduce, aunque el rendimiento práctico depende fuertemente de la escala de datos y recursos del cluster.

---