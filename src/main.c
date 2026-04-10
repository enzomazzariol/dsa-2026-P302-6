#include "sample_lib.h"
#include "house.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void createaleak() {
  char *foo = malloc(20 * sizeof(char));
  printf("Allocated leaking string: %s", foo);
}

// void compare_house_name(*char );

int main(void) {
  printf("*****************\nWelcome to DSA!\n*****************\n");

  // how to import and call a function
  printf("Factorial of 4 is %d\n", fact(4));

  // uncomment and run "make v" to see how valgrind detects memory leaks
  // createaleak();

  int user_map = 0;
  print_map_menu();
  scanf("%d", &user_map);
  printf("Has elegido el mapa: %d", user_map);

  const char *map_name = map_name_from_option(user_map);
  if (map_name == NULL) {
    printf("\n[ERROR] Mapa invalido\n");
    return 1;
  }

  HouseNode *houses = fetch_houses(map_name);
  if (houses == NULL) {
    printf("[ERROR] No se pudieron cargar las casas\n");
    return 1;
  }

  // imprimimos el load y el total de casas
  int total_houses = count_houses(houses);
  printf("\nCasas cargadas correctamente para %s, total: %d\n", map_name, total_houses);

  int opcion_user = 0;
  print_map_options();
  scanf("%d", &opcion_user);

  switch (opcion_user) {
    case 1: {
      printf("Enter a street name: \n");
      char street_name[256];
      scanf(" %255[^\n]", street_name);
      
      printf("Enter a street number: \n");
      int street_number;
      scanf("%d", &street_number);
      search_house(houses, street_name, street_number);
      break;
    }
    case 2:
      printf("Not implemented yet. Come back later. \n");
      break;
    case 3:
      printf("Not implemented yet. Come back later. \n");
      break;
    default:
      printf("[ERROR] Operación inválida\n");
      return 1;
  }

  free_houses(houses);
  return 0;
}