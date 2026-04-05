/*
 * Ejercicio 2: Coloracion de Grafos con k Colores
 * Algoritmos: Backtracking y Fuerza Bruta
 *
 * Compilar: g++ -O2 -std=gnu++17 -o solucion main.cpp
 * Ejecutar: ./solucion
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>
#include <functional>

using namespace std;
using namespace std::chrono;

// Repeticiones para promediar tiempos en grafos muy pequeños.
// 100000 garantiza precision
static const int REPS = 100000;


//  Variables globales del grafo activo
int n, k;
vector<vector<int>> adj;
vector<int> color;
vector<int> primera_sol;
bool primera_guardada = false;

long long total_bt = 0;
long long total_fb = 0;
long long nodos_bt  = 0;
long long nodos_fb  = 0;

//  Formateo de tiempo — unidad fija: microsegundos (us)
string formato_tiempo(double nanoseconds) {
    ostringstream oss;
    oss << fixed << setprecision(4) << nanoseconds / 1000.0 << " us";
    return oss.str();
}


//  Mide el tiempo promedio de una funcion, repitiendo REPS veces para mayor precision
double medir_ns(function<void()> fn, int reps = REPS) {
    auto t0 = high_resolution_clock::now();
    for (int i = 0; i < reps; i++) fn();
    auto t1 = high_resolution_clock::now();
    return (double)duration_cast<nanoseconds>(t1 - t0).count() / reps;
}


//  Lectura del grafo desde consola
void leer_grafo() {
    cout << "=============================================" << endl;
    cout << "   COLORACION DE GRAFOS CON k COLORES" << endl;
    cout << "=============================================" << endl;
    cout << endl;

    cout << "Numero de vertices del grafo (n): ";
    cin >> n;
    cout << "Numero de colores disponibles  (k): ";
    cin >> k;

    adj.assign(n, vector<int>(n, 0));
    color.assign(n, 0);

    cout << endl;
    cout << "Ingrese la matriz de adyacencia " << n << "x" << n << "." << endl;
    cout << "Use 1 si hay arista entre dos vertices, 0 si no la hay." << endl;
    cout << "Ingrese los " << n * n << " valores fila por fila:" << endl << endl;

    for (int i = 0; i < n; i++) {
        cout << "  Fila " << i << " (vecinos del vertice " << i << "): ";
        for (int j = 0; j < n; j++) cin >> adj[i][j];
    }

    cout << endl;
    cout << "Grafo ingresado (" << n << " vertices, k=" << k << " colores):" << endl;
    cout << "  Aristas detectadas: ";
    bool hay = false;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (adj[i][j]) { cout << i << "-" << j << "  "; hay = true; }
    if (!hay) cout << "(sin aristas)";
    cout << endl;
}

//  Imprime una asignacion de colores
void imprimir_solucion(const vector<int>& sol) {
    for (int v = 0; v < n; v++)
        cout << "    vertice " << v << "  ->  color " << sol[v] << endl;
}

//  BACKTRACKING
bool es_seguro(int v, int c) {
    for (int u = 0; u < n; u++)
        if (adj[v][u] && color[u] == c) return false;
    return true;
}

void bt(int v) {
    nodos_bt++;
    if (v == n) {
        total_bt++;
        if (!primera_guardada) { primera_sol = color; primera_guardada = true; }
        return;
    }
    for (int c = 1; c <= k; c++) {
        if (es_seguro(v, c)) {
            color[v] = c;
            bt(v + 1);
            color[v] = 0;
        }
    }
}

void reset_bt() {
    primera_guardada = false;
    total_bt = 0;
    nodos_bt = 0;
    fill(color.begin(), color.end(), 0);
}

//  FUERZA BRUTA
bool verificar_coloracion(const vector<int>& col) {
    for (int u = 0; u < n; u++)
        for (int v = u + 1; v < n; v++)
            if (adj[u][v] && col[u] == col[v]) return false;
    return true;
}

void fuerza_bruta() {
    long long total_comb = 1;
    for (int i = 0; i < n; i++) total_comb *= k;
    vector<int> col(n);
    for (long long mask = 0; mask < total_comb; mask++) {
        nodos_fb++;
        long long tmp = mask;
        for (int v = 0; v < n; v++) { col[v] = tmp % k + 1; tmp /= k; }
        if (verificar_coloracion(col)) total_fb++;
    }
}

void reset_fb() {
    total_fb = 0;
    nodos_fb = 0;
}

//  Ejecuta y muestra resultados para el grafo
//  activo (adj, n, k ya cargados)
void ejecutar_y_mostrar(const string& nombre_grafo) {

    cout << endl;
    cout << "--------------------------------------------" << endl;
    cout << "  CASO: " << nombre_grafo << endl;
    cout << "--------------------------------------------" << endl;

    // BACKTRACKING
    // Primera pasada real (para contar + guardar primera solucion)
    reset_bt();
    bt(0);
    long long bt_soluciones = total_bt;
    long long bt_nodos      = nodos_bt;
    vector<int> bt_primera  = primera_sol;

    // Pasada de medicion (REPS veces, solo tiempo)
    double ns_bt = medir_ns([&]() {
        reset_bt();
        bt(0);
    });

    cout << endl;
    cout << "=============================================" << endl;
    cout << "           RESULTADO: BACKTRACKING" << endl;
    cout << "=============================================" << endl;

    if (bt_soluciones == 0) {
        cout << "  No existe una " << k << "-coloracion valida para este grafo." << endl;
    } else {
        cout << "  Coloraciones validas encontradas : " << bt_soluciones << endl;
        cout << "  Primera solucion:" << endl;
        imprimir_solucion(bt_primera);
    }
    cout << "  Nodos explorados    : " << bt_nodos << endl;
    cout << "  Tiempo de ejecucion : " << formato_tiempo(ns_bt)
         << "  (promedio de " << REPS << " repeticiones)" << endl;

    // FUERZA BRUTA
    // Primera pasada real
    reset_fb();
    fuerza_bruta();
    long long fb_soluciones = total_fb;
    long long fb_nodos      = nodos_fb;

    // Pasada de medicion
    double ns_fb = medir_ns([&]() {
        reset_fb();
        fuerza_bruta();
    });

    cout << endl;
    cout << "=============================================" << endl;
    cout << "           RESULTADO: FUERZA BRUTA" << endl;
    cout << "=============================================" << endl;
    cout << "  Combinaciones totales generadas  : " << fb_nodos
         << "  (" << k << "^" << n << ")" << endl;
    cout << "  Coloraciones validas encontradas : " << fb_soluciones << endl;
    cout << "  Tiempo de ejecucion : " << formato_tiempo(ns_fb)
         << "  (promedio de " << REPS << " repeticiones)" << endl;

    // VERIFICACION CRUZADA
    cout << endl;
    cout << "=============================================" << endl;
    cout << "            VERIFICACION CRUZADA" << endl;
    cout << "=============================================" << endl;
    if (bt_soluciones == fb_soluciones)
        cout << "  OK  Ambos enfoques coinciden: " << bt_soluciones
             << " coloraciones validas." << endl;
    else {
        cout << "  ERROR  Discrepancia detectada!" << endl;
        cout << "  Backtracking : " << bt_soluciones
             << "  |  Fuerza Bruta : " << fb_soluciones << endl;
    }

    //COMPARACION DE EFICIENCIA
    cout << endl;
    cout << "=============================================" << endl;
    cout << "         COMPARACION DE EFICIENCIA" << endl;
    cout << "=============================================" << endl;
    cout << "  Metodo            Nodos explorados   Tiempo [us]" << endl;
    cout << "  Backtracking      " << setw(16) << bt_nodos
         << "   " << formato_tiempo(ns_bt) << endl;
    cout << "  Fuerza Bruta      " << setw(16) << fb_nodos
         << "   " << formato_tiempo(ns_fb) << endl;

    if (fb_nodos > 0) {
        double reduccion = (1.0 - (double)bt_nodos / (double)fb_nodos) * 100.0;
        cout << endl;
        // Usar ostringstream para no contaminar el estado de cout
        ostringstream msg;
        if (reduccion > 0.0) {
            msg << fixed << setprecision(2)
                << "  La poda del backtracking elimino el " << reduccion
                << "% de los nodos.";
        } else {
            msg << "  El backtracking no logro reducir nodos en este caso.\n"
                << "  (grafo sin aristas: sin conflictos, sin poda posible)";
        }
        cout << msg.str() << endl;
    }
}

//  Carga un grafo predefinido (para benchmarks)
void cargar_grafo(int vertices, int colores,
                  const vector<pair<int,int>>& aristas) {
    n = vertices;
    k = colores;
    adj.assign(n, vector<int>(n, 0));
    color.assign(n, 0);
    for (auto& e : aristas) {
        adj[e.first][e.second] = 1;
        adj[e.second][e.first] = 1;
    }
}

//  MENU PRINCIPAL
int main() {

    cout << "=============================================" << endl;
    cout << "   COLORACION DE GRAFOS CON k COLORES" << endl;
    cout << "=============================================" << endl;
    cout << endl;
    cout << "Seleccione modo:" << endl;
    cout << "  1) Ingresar grafo manualmente" << endl;
    cout << "  2) Ejecutar benchmarks predefinidos (tabla comparativa)" << endl;
    cout << "Opcion: ";

    int opcion;
    cin >> opcion;

    if (opcion == 1) {
        // Modo interactivo
        leer_grafo();
        ejecutar_y_mostrar("Grafo ingresado manualmente");

    } else {
        // ── Benchmarks predefinidos ───────────────
        // Grafo 1: Ciclo C4, k=3 ──────────────
        cargar_grafo(4, 3, {{0,1},{1,2},{2,3},{3,0}});
        cout << endl << "  Grafo 1: Ciclo C4 (n=4, k=3)" << endl;
        cout << "  Aristas: 0-1, 1-2, 2-3, 3-0" << endl;
        ejecutar_y_mostrar("Ciclo C4  |  n=4, k=3");

        // ── Grafo 2: Completo K4, k=4 ────────────
        cargar_grafo(4, 4, {{0,1},{0,2},{0,3},{1,2},{1,3},{2,3}});
        cout << endl << "  Grafo 2: Completo K4 (n=4, k=4)" << endl;
        cout << "  Aristas: todos los pares posibles" << endl;
        ejecutar_y_mostrar("Completo K4  |  n=4, k=4");

        // ── Grafo 3: Ciclo C7 con cuerdas, k=3 ───
        // Grafo de 7 vertices: ciclo + cuerdas internas -> mas denso
        cargar_grafo(7, 3, {
            {0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,0},  // ciclo C7
            {0,2},{1,3},{2,4},{3,5},{4,6}                // cuerdas
        });
        cout << endl << "  Grafo 3: C7 + cuerdas (n=7, k=3)" << endl;
        cout << "  Ciclo de 7 vertices con cuerdas adicionales" << endl;
        ejecutar_y_mostrar("C7+cuerdas  |  n=7, k=3");

        // ── Grafo 4: Bipartito K2,3, k=2 ─────────
        cargar_grafo(5, 2, {{0,2},{0,3},{0,4},{1,2},{1,3},{1,4}});
        cout << endl << "  Grafo 4: Bipartito K2,3 (n=5, k=2)" << endl;
        cout << "  Vertices {0,1} conectados con {2,3,4}" << endl;
        ejecutar_y_mostrar("Bipartito K2,3  |  n=5, k=2");

    }

    cout << endl;
    return 0;
}
