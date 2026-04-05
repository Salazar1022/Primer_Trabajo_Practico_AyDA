#include <iostream>
#include <algorithm>
#include <chrono>
using namespace std;

int factorial(int n);
bool next_permutation_test(int* inicio, int* fin);

int main(){

    // Declaración de variables
    int n = 0, total_generadas = 0, total_validas = 0, aux = 0;
    bool valida;

    // Solicitar al usuario el tamaño del arreglo y los elementos del mismo
    cout << "Ingrese el tamaño del arreglo: ";
    cin >> n;
    int A[n];

    // Solcitar al usuario los elementos del arreglo
    for(int i = 0; i < n; i++)
    {
        cout << "Ingrese el elemento " << i + 1 << " del arreglo: ";
        cin >> A[i];
    }
    
    // Ordenar el arreglo para generar las permutaciones en orden lexicográfico
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(A[j] > A[j+1])
            {
                aux = A[j];
                A[j] = A[j+1];
                A[j+1] = aux;
            }
        }
    }    

    auto inicio = chrono::high_resolution_clock::now();

    // Generar todas las permutaciones del arreglo y verificar cuáles cumplen la condición dada
    do 
    {
        total_generadas++;
        valida = true;

        for(int i = 0; i < n - 1; i++)
        {
            if (A[i] > (2*A[i+1]))
            {
                valida = false;
                break;
            }
        } 
        
        if (valida)
        {
            cout << "Permutación válida: ";
            for(int i = 0; i < n; i++)
            {
                cout << A[i] << " ";
            }
            cout << endl;
            
            total_validas++;
        }

    } while (next_permutation_test(A, A + n));

    // *** FIN DEL CRONÓMETRO ***
    auto fin = chrono::high_resolution_clock::now();

    // *** CALCULAR DURACIÓN ***
    chrono::duration<double> duracion = fin - inicio;

    cout << "Total permutaciones posibles: " << factorial(n) << endl;
    cout << "Total permutaciones generadas: " << total_generadas << endl;
    cout << "Total permutaciones validas: " << total_validas << endl;
    cout << duracion.count() << " ns" << endl;

    return 0;
}

// Función para calcular el factorial de un número
int factorial(int n){

    int cont;
    cont = 1;

    for (int i = 1; i < n; i++){
        cont = cont * (i+1);
    }
    return cont;
}

// Función para generar la siguiente permutación en orden lexicográfico
bool next_permutation_test(int* inicio, int* fin) {

    // Calcular el número de elementos del arreglo
    int n = fin - inicio;

    // Si el arreglo tiene 0 o 1 elementos, no hay más permutaciones
    if (n <= 1) return false;

    // Empezar desde el penúltimo elemento y compararlo con el siguiente para encontrar el primer par de elementos que no estén en orden descendente
    int i = n - 2;

    // Primer paso: encontrar el índice más grande i tal que inicio[i] < inicio[i + 1]. Si no existe tal índice, la permutación es la última y no hay más permutaciones.
    while (i >= 0 && inicio[i] >= inicio[i + 1]){
        i--;
    } 

    if (i == -1){
        return false;
    }

    int j = n - 1;

    while (inicio[j] <= inicio[i]){
        j--;
    } 

    int temp = inicio[i];
    inicio[i] = inicio[j];
    inicio[j] = temp;

    int izq = i + 1, der = n - 1;
    while (izq < der) {
        temp = inicio[izq];
        inicio[izq] = inicio[der];
        inicio[der] = temp;
        izq++; der--;
    }

    return true;
}