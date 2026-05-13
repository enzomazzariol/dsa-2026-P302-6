#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// calcular minimo de tres numeros
int minimo(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

int levenshtein_distance(const char *a, const char *b) {
    int m = strlen(a);
    int n = strlen(b);

    int D[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        D[i][0] = i;
    }

    // Inicializar la primera fila
    for (int j = 0; j <= n; j++) {
        D[0][j] = j;
    }

    // Llenar la matriz
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int cost;
            
            // Si los caracteres son iguales, el costo es 0, si no, 1
            if (a[i - 1] == b[j - 1]) {
                cost = 0;
            } else {
                cost = 1;
            }

            // Aplicamos la fórmula del pseudocódigo
            D[i][j] = minimo(
                D[i - 1][j] + 1,      // Deletion (borrado)
                D[i][j - 1] + 1,      // Insertion (inserción)
                D[i - 1][j - 1] + cost // Substitution (sustitución)
            );
        }
    }

    return D[m][n];
}