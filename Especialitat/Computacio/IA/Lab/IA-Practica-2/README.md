# Sistema Experto para Recomendación de Visitas a Museo

## Descripción
Este sistema experto implementado en CLIPS ayuda a generar recomendaciones personalizadas de rutas de visita para un museo de arte, basándose en las preferencias y características del visitante.

## Funcionalidades

### 1. Recopilación de Datos del Visitante
- Número de personas en el grupo
- Presencia de niños pequeños 
- Duración de la visita (días y horas)
- Nivel de conocimiento sobre arte
- Preferencias específicas:
  - Temática artística
  - Época histórica
  - Estilo artístico
  - Pintores

### 2. Base de Conocimiento
El sistema incluye una extensa base de datos con:
- Obras de arte
- Pintores
- Estilos artísticos
- Épocas históricas
- Temáticas
- Información detallada de cada obra:
  - Dimensiones
  - Ubicación (sala)
  - Importancia
  - Complejidad
  - Fecha de creación

### 3. Proceso de Recomendación
1. **Abstracción de datos**: Convierte las respuestas del usuario en categorías útiles
2. **Asociación heurística**: Relaciona preferencias con obras disponibles
3. **Generación de ruta**: Crea un recorrido optimizado según:
   - Preferencias del visitante
   - Ubicación de las obras
   - Importancia de las piezas

### 4. Restriciones del primer prototipo
- De momento el protoipo solo puede tener una preferencia de cada tipo (epoca, estilo, tematica y pintor).
- El tiempo para observar cada obra esta fijo a una constante aun falta hacer el calculo.
