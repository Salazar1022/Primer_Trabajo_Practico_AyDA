Algoritmo pseudocodigo_permutaciones
	
	Definir n, i, j, total_generadas, total_validas, cont, A Como Entero;
	Definir valida Como Logico;
	
	total_generadas = 0;
    total_validas = 0;
    cont = 1;
	n = 0;
	
    Imprimir "Por favor Ingrese de que tamaño desea el arreglo:";
    Leer n;
    Dimension A[n];
	
    Imprimir "Por favor Ingrese cada uno de los enteros:";
    Para i = 0 hasta n - 1 Hacer
        Imprimir "Ingrese el número en la posición ", i + 1, ":";
        Leer A[i];
    FinPara
	
    // Ordenar el arreglo de forma ascendente
    Para i = 0 hasta n - 2 Hacer
        Para j = 0 hasta n - i - 2 Hacer
            Si A[j] > A[j+1] Entonces
                aux    <- A[j];
                A[j]   <- A[j+1];
                A[j+1] <- aux;
            FinSi
        FinPara
    FinPara
		
    // Factorial n!
    Para i = 1 hasta n - 1 Hacer
        cont = cont * (i+1);
    FinPara
	
    Repetir
		valida = verdadero;
        total_generadas = total_generadas + 1;
        Para i = 0 hasta n-2 Hacer
            Si A[i] > (2 * A[i+1]) Entonces
                valida = Falso;
                i = n;
            FinSi
        FinPara
		
        Si valida Entonces
            Para i = 0 hasta n-1 Hacer
                Imprimir Sin Saltar A[i], " ";
            FinPara
            Imprimir "";
            total_validas = total_validas + 1;
        FinSi
		
    Hasta Que next_permutation(A, n) = Falso
	
    Imprimir "Total permutaciones posibles:  ", cont;
    Imprimir "Total permutaciones generadas: ", total_generadas;
    Imprimir "Total permutaciones validas:   ", total_validas;
	
FinAlgoritmo

Funcion valida = next_permutation(A, n)
	
	Definir valida como logico;
    Definir i, j, temp, izq, der, continuar Como Entero;
    continuar = 1;
	
    Si n <= 1 Entonces
        valida = Falso;
        continuar = 0;
    FinSi
	
    Si continuar = 1 Entonces
        i = n - 2;
        Mientras i >= 0 Y A[i] >= A[i+1] Hacer
            i = i - 1;
        FinMientras
		
        Si i = -1 Entonces
            valida = Falso;
            continuar = 0;
        FinSi
    FinSi
	
    Si continuar = 1 Entonces
        j = n - 1;
        Mientras A[j] <= A[i] Hacer
            j = j - 1;
        FinMientras
		
        temp = A[i];
        A[i] = A[j];
        A[j] = temp;
        izq = i + 1;
        der = n - 1;
		
        Mientras izq < der Hacer
            temp = A[izq];
            A[izq] = A[der];
            A[der] = temp;
            izq = izq + 1;
            der = der - 1;
        FinMientras
		
        valida = Verdadero;
		
    FinSi
FinFuncion