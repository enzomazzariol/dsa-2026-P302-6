#include <string.h>
#include <stdio.h>
#include "abreviaturas.h"

const char* abreviaturas(const char* abreviada){
    static char final_abreviada[100];  // ← solución rápida y segura

    int variable = -1;
    int longitud = strlen(abreviada);

    for(int i = 0; i < longitud; i++){
        if(abreviada[i] == ' '){
            variable = i;
            break;
        }
    }

    if(variable == -1){
        return abreviada;
    }

    if(abreviada[0] == 'c' || abreviada[0] == 'C'){
        strcpy(final_abreviada, "carrer ");
    } else if(abreviada[0] == 'p' || abreviada[0] == 'P'){
        strcpy(final_abreviada, "plaça ");
    } else if(abreviada[0] == 'a' || abreviada[0] == 'A'){
        strcpy(final_abreviada, "avinguda ");
    } else if(abreviada[0] == 'r' || abreviada[0] == 'R'){
        strcpy(final_abreviada, "rambla ");
    } else {
        return abreviada;
    }

    strcat(final_abreviada, abreviada + variable + 1);

    return final_abreviada;
}