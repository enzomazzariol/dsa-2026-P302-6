#include <string.h>
#include <stdio.h>
#include "abreviaturas.h"

void abreviaturas(const char *abreviada, char *resultado, int tam) {
    int variable = -1;
    int longitud = strlen(abreviada);

    for(int i = 0; i < longitud; i++){
        if(abreviada[i] == ' '){
            variable = i;
            break;
        }
    }

    if(variable == -1){
        strncpy(resultado, abreviada, tam - 1);
        resultado[tam - 1] = '\0';
        return;
    }

    if(abreviada[0] == 'c' || abreviada[0] == 'C'){
        strncpy(resultado, "carrer ", tam - 1);
    } else if(abreviada[0] == 'p' || abreviada[0] == 'P'){
        strncpy(resultado, "plaça ", tam - 1);
    } else if(abreviada[0] == 'a' || abreviada[0] == 'A'){
        strncpy(resultado, "avinguda ", tam - 1);
    } else if(abreviada[0] == 'r' || abreviada[0] == 'R'){
        strncpy(resultado, "rambla ", tam - 1);
    } else {
        strncpy(resultado, abreviada, tam - 1);
        resultado[tam - 1] = '\0';
        return;
    }

    resultado[tam - 1] = '\0';
    strncat(resultado, abreviada + variable + 1, tam - strlen(resultado) - 1);
}