/*
 * Ejercicio 2: Coloracion de Grafos con k Colores
 * Algoritmos: Backtracking y Fuerza Bruta
 * Materia: Analisis y Diseno de Algoritmos - EAFIT
 *
 * Compilar: g++ -O2 -std=gnu++17 -o solucion main.cpp
 * Ejecutar: ./solucion
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <string>

using namespace std;
using namespace std::chrono;

// ─────────────────────────────────────────────
//  Variables globales
// ─────────────────────────────────────────────
int n, k;
vector<vector<int>> adj;
vector<int> color;
vector<int> primera_sol;
bool primera_guardada = false;

long long total_bt = 0;
long long total_fb = 0;
long long nodos_bt = 0;
long long nodos_fb = 0;

// ─────────────────────────────────────────────
//  Formateo de tiempo: elige la unidad adecuada
//  segun la magnitud para que nunca salga 0.0000
// ─────────────────────────────────────────────
string formato_tiempo(double nanoseconds) {
    if (nanoseconds < 1000.0) {
        // Mostrar en nanosegundos
        ostringstream oss;
        oss << fixed << setprecision(2) << nanoseconds << " ns";
        return oss.str();
    } else if (nanoseconds < 1000000.0) {
        // Mostrar en microsegundos
        ostringstream oss;
        oss << fixed << setprecision(4) << nanoseconds / 1000.0 << " us";
        return oss.str();
    } else if (nanoseconds < 1000000000.0) {
        // Mostrar en milisegundos
        ostringstream oss;
        oss << fixed << setprecision(4) << nanoseconds / 1000000.0 << " ms";
        return oss.str();
    } else {
        // Mostrar en segundos
        ostringstream oss;
        oss << fixed << setprecision(4) << nanoseconds / 1000000000.0 << " s";
        return oss.str();
    }
}

// ─────────────────────────────────────────────
//  Lectura del grafo
// ─────────────────────────────────────────────
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
    cout << "Ingrese los " << n * n << " valores fila por fila:" << endl;
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << "  Fila " << i << " (vecinos del vertice " << i << "): ";
        for (int j = 0; j < n; j++)
            cin >> adj[i][j];
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

// ─────────────────────────────────────────────
//  Imprime una asignacion de colores
// ─────────────────────────────────────────────
void imprimir_solucion(const vector<int>& sol) {
    for (int v = 0; v < n; v++)
        cout << "    vertice " << v << "  ->  color " << sol[v] << endl;
}

// ─────────────────────────────────────────────
//  BACKTRACKING
// ─────────────────────────────────────────────
bool es_seguro(int v, int c) {
    for (int u = 0; u < n; u++)
        if (adj[v][u] && color[u] == c)
            return false;
    return true;
}

void bt(int v) {
    nodos_bt++;
    if (v == n) {
        total_bt++;
        if (!primera_guardada) {
            primera_sol = color;
            primera_guardada = true;
        }
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

// ─────────────────────────────────────────────
//  FUERZA BRUTA
// ─────────────────────────────────────────────
bool verificar_coloracion(const vector<int>& col) {
    for (int u = 0; u < n; u++)
        for (int v = u + 1; v < n; v++)
            if (adj[u][v] && col[u] == col[v])
                return false;
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

// ─────────────────────────────────────────────
//  Programa principal
// ─────────────────────────────────────────────
int main() {
    leer_grafo();

    // ═══════════════════════════════════════
    //  BACKTRACKING — medicion en nanosegundos
    // ═══════════════════════════════════════
    primera_guardada = false;
    total_bt = 0;
    nodos_bt = 0;
    fill(color.begin(), color.end(), 0);

    cout << endl;
    cout << "Ejecutando Backtracking..." << endl;

    auto t0 = high_resolution_clock::now();
    bt(0);
    auto t1 = high_resolution_clock::now();
    double ns_bt = duration_cast<nanoseconds>(t1 - t0).count();

    cout << endl;
    cout << "=============================================" << endl;
    cout << "           RESULTADO: BACKTRACKING" << endl;
    cout << "=============================================" << endl;

    if (total_bt == 0) {
        cout << "  No existe una " << k << "-coloracion valida para este grafo." << endl;
    } else {
        cout << "  Coloraciones validas encontradas : " << total_bt << endl;
        cout << "  Primera solucion:" << endl;
        imprimir_solucion(primera_sol);
    }
    cout << "  Nodos explorados    : " << nodos_bt << endl;
    cout << "  Tiempo de ejecucion : " << formato_tiempo(ns_bt) << endl;

    // ═══════════════════════════════════════
    //  FUERZA BRUTA — medicion en nanosegundos
    // ═══════════════════════════════════════
    total_fb = 0;
    nodos_fb = 0;

    cout << endl;
    cout << "Ejecutando Fuerza Bruta..." << endl;

    auto t2 = high_resolution_clock::now();
    fuerza_bruta();
    auto t3 = high_resolution_clock::now();
    double ns_fb = duration_cast<nanoseconds>(t3 - t2).count();

    cout << endl;
    cout << "=============================================" << endl;
    cout << "           RESULTADO: FUERZA BRUTA" << endl;
    cout << "=============================================" << endl;
    cout << "  Combinaciones totales generadas  : " << nodos_fb
         << "  (" << k << "^" << n << ")" << endl;
    cout << "  Coloraciones validas encontradas : " << total_fb << endl;
    cout << "  Tiempo de ejecucion : " << formato_tiempo(ns_fb) << endl;

    // ═══════════════════════════════════════
    //  VERIFICACION CRUZADA
    // ═══════════════════════════════════════
    cout << endl;
    cout << "=============================================" << endl;
    cout << "            VERIFICACION CRUZADA" << endl;
    cout << "=============================================" << endl;
    if (total_bt == total_fb)
        cout << "  OK  Ambos enfoques coinciden: " << total_bt
             << " coloraciones validas." << endl;
    else {
        cout << "  ERROR  Discrepancia detectada!" << endl;
        cout << "  Backtracking : " << total_bt
             << "  |  Fuerza Bruta : " << total_fb << endl;
    }

    // ═══════════════════════════════════════
    //  COMPARACION DE EFICIENCIA
    // ═══════════════════════════════════════
    cout << endl;
    cout << "=============================================" << endl;
    cout << "         COMPARACION DE EFICIENCIA" << endl;
    cout << "=============================================" << endl;
    cout << "  Metodo          Nodos explorados   Tiempo" << endl;
    cout << "  Backtracking    " << setw(16) << nodos_bt
         << "   " << formato_tiempo(ns_bt) << endl;
    cout << "  Fuerza Bruta    " << setw(16) << nodos_fb
         << "   " << formato_tiempo(ns_fb) << endl;

    if (nodos_fb > 0) {
        double reduccion = (1.0 - (double)nodos_bt / (double)nodos_fb) * 100.0;
        cout << endl;
        if (reduccion > 0.0) {
            cout << fixed << setprecision(2);
            cout << "  La poda del backtracking elimino el " << reduccion
                 << "% de los nodos." << endl;
        } else {
            cout << "  El backtracking no logro reducir nodos en este caso." << endl;
            cout << "  (grafo sin aristas: sin conflictos, sin poda posible)" << endl;
        }
    }

    cout << endl;
    return 0;
}
