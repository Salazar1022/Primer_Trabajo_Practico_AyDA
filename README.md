<div align="center">

  <h1>Primer Trabajo Práctico - Análisis y Diseño de Algoritmos</h1>

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![LaTeX](https://img.shields.io/badge/LaTeX-Informes-green.svg)
![Enfoque](https://img.shields.io/badge/Metodos-Fuerza%20Bruta%20%7C%20Backtracking-orange.svg)
</div>

---

## 👥 Información del equipo

| Nombre | Código |
|--------|--------|
| **Andrés Felipe Velez Alvarez** | 1021923619 |
| **Nathalia Valentina Cardoza Azuaje** | 4992531 |
| **Sebastian Salazar Henao** | 1022003377 |

**Universidad:** Universidad EAFIT  
**Curso:** Análisis y Diseño de Algoritmos  
**Semestre:** 5to semestre  
**Fecha:** Abril 05, 2026

---

## 📋 Descripción del proyecto

Este repositorio contiene el desarrollo del **Primer Trabajo Práctico de Análsis y Diseño de Algoritmos**, enfocado en la comparación entre enfoques de **fuerza bruta** y **backtracking** para problemas combinatorios.

Se implementan dos ejercicios:

1. **Ejercicio 1 - Permutaciones con restricción**.
2. **Ejercicio 2 - Coloración de grafos con k colores**.

En ambos casos se incluye implementación en C++, análisis de complejidad y soporte documental en LaTeX.

## 🎯 Objetivos del trabajo

### Objetivo general

- Aplicar técnicas de diseño de algoritmos para resolver problemas combinatorios.
- Comparar el comportamiento de fuerza bruta y backtracking.
- Medir y analizar el desempeño según el tamaño de entrada.
- Validar corrección de resultados mediante conteos y verificación cruzada.

## 📂 Estructura del repositorio

```text
Primer_Trabajo_Practico_AyDA/
├── README.md
├── Ejercicio1_Permutaciones/
│   ├── informe.tex
│   ├── permutaciones.cpp
│   └── pseudocodigo_permutaciones.psc
└── Ejercicio2_Coloracion/
    ├── Informe_2_ejercicio.pdf
    ├── informe_ejercicio2.tex
    ├── main_ejercicio2.cpp
    └── solucion.exe
```

## 🚫 Ejercicio 1: Permutaciones con restricción

✅ Archivo principal: `Ejercicio1_Permutaciones/permutaciones.cpp`

### 🎯 Objetivo del ejercicio

Generar todas las permutaciones de un arreglo de enteros y conservar solo aquellas que cumplan la condición:

\[
P[i] \leq 2 \cdot P[i+1]
\]

### 🔑 Características principales

- Generación de permutaciones en orden lexicográfico.
- Verificación de restricción para cada permutación.
- Conteo de permutaciones totales generadas y válidas.
- Medición de tiempo de ejecución con `chrono`.

### 👾 Flujo del algoritmo

1. Leer `n` y los `n` elementos del arreglo.
2. Ordenar el arreglo de menor a mayor.
3. Generar permutaciones sucesivas (`next_permutation_test`).
4. Validar la condición en cada permutación.
5. Reportar permutaciones válidas y estadísticas finales.

### 🚀 Cómo compilar y ejecutar

```bash
cd Ejercicio1_Permutaciones
g++ -std=gnu++17 -O2 -o permutaciones permutaciones.cpp
./permutaciones
```

### 💡 Salida esperada

- Listado de permutaciones válidas.
- Total de permutaciones posibles (`n!`).
- Total de permutaciones generadas.
- Total de permutaciones validas.
- Tiempo de ejecución.

## 🎨 Ejercicio 2: Coloración de grafos con k colores

✅ Archivo principal: `Ejercicio2_Coloracion/main_ejercicio2.cpp`

### 🎯 Objetivo del ejercicio

Determinar y contar coloraciones válidas de un grafo con `k` colores, comparando dos métodos:

- **Backtracking**
- **Fuerza bruta**

### 🔑 Características principales

- Entrada por matriz de adyacencia de tamaño `n x n`.
- Conteo de coloraciones válidas para ambos enfoques.
- Registro de nodos explorados por método.
- Medición de tiempo en nanosegundos y formateo automático de unidad.
- Verificación cruzada de resultados entre backtracking y fuerza bruta.

### 👾 Flujo del algoritmo

1. Leer `n`, `k` y la matriz de adyacencia.
2. Ejecutar backtracking para encontrar coloraciones válidas con poda.
3. Ejecutar fuerza bruta para enumerar todas las combinaciones `k^n`.
4. Comparar conteos y tiempos de ambos métodos.
5. Mostrar una primera solución válida (en caso de que exista).

### 🚀 Cómo compilar y ejecutar

```bash
cd Ejercicio2_Coloracion
g++ -std=gnu++17 -O2 -o coloracion main_ejercicio2.cpp
./coloracion
```

### 💡 Salida esperada

- Número de coloraciones válidas por método.
- Nodos/combinaciones exploradas.
- Tiempo de ejecución por método.
- Confirmación de consistencia entre resultados.
- Estimación de reducción por poda en backtracking.

## 🛠️ Tecnologías utilizadas

- C++17
- LaTeX
- Estructuras de datos básicas (`vector`, arreglos)
- Medición de rendimiento con `chrono`

## 🚀 Requerimientos

- Compilador compatible con C++17 (`g++` recomendado)
- Sistema con terminal para compilación y ejecución
- (Opcional) distribución LaTeX para compilar informes

## 🎓 Aprendizajes clave

### 🚫 Ejercicio 1 (Permutaciones)

- Generar todas las permutaciones puede volverse costoso por crecimiento factorial.
- El orden lexicográfico facilita recorrer de forma sistemática el espacio de soluciones.
- Las restricciones filtran soluciones pero no reducen el costo de generación cuando no hay poda temprana.

### 🎨 Ejercicio 2 (Coloracion)

- Backtracking reduce exploración gracias a poda por conflictos locales.
- Fuerza bruta sirve como referencia de corrección, aunque es menos eficiente.
- La diferencia en nodos explorados crece con `n` y con la densidad del grafo.

## 🔬 Análisis comparativo

| Dimensión | Ejercicio 1: Permutaciones | Ejercicio 2: Coloración |
|---|---|---|
| Tipo de problema | Permutaciones con restricción | Satisfacción de restricciones en grafos |
| Espacio de búsqueda | `n!` | `k^n` |
| Estrategia principal | Enumeración lexicográfica | Backtracking + fuerza bruta |
| Poda temprana | No (en implementación actual) | Sí (backtracking) |
| Validación | Condición local entre posiciones | Restricción de adyacencia |
| Complejidad práctica | Alta para `n` grandes | Muy sensible a `n`, `k` y densidad |

## ⚡️ Conclusiones

- El trabajo evidencia la diferencia práctica entre explorar todo el espacio y podar soluciones inviables de forma temprana.
- Fuerza bruta es útil como baseline de verificación, pero backtracking mejora significativamente el rendimiento en problemas con restricciones.
- La comparación experimental de conteo de nodos y tiempos permite justificar el uso de técnicas más inteligentes de búsqueda.

## 🤖 Uso de IA como apoyo

Durante la realización de este proyecto se utilizó inteligencia artificial como herramienta de apoyo para el aprendizaje. Se empleó como guía para resolver dudas puntuales, aclarar conceptos del curso y comprender con mayor profundidad los problemas planteados. Este acompañamiento facilitó la construcción de una solución mejor fundamentada desde el punto de vista algorítmico, sin reemplazar el análisis y el trabajo propio del equipo.
