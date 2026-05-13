#include "sample_lib.h"
#include "house.h"
#include "map.h"
#include "places.h"
#include "segments.h"
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
  PlaceNode *places = fetch_places(map_name);
  StreetNode *streets = fetch_streets(map_name);

  if (places == NULL) {
    printf("[ERROR] No se pudieron cargar los lugares\n");
    free_houses(houses);
    free_streets(streets);
    return 1;
  }
  if (houses == NULL) {
    printf("[ERROR] No se pudieron cargar las casas\n");
    free_places(places);
    free_streets(streets);
    return 1;
  }
  if (streets == NULL) {
    printf("[ERROR] No se pudieron cargar las calles\n");
    free_houses(houses);
    free_places(places);
    return 1;
  }

  // imprimimos el load y el total de casas
  int total_houses = count_houses(houses);
  int total_places = count_places(places);
  int total_streets = count_streets(streets);
  printf("\nCasas cargadas correctamente para %s, total: %d\n", map_name, total_houses);
  printf("Lugares cargados correctamente para %s, total: %d\n", map_name, total_places);
  printf("Calles cargadas correctamente para %s, total: %d\n", map_name, total_streets);

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
      if (scanf("%d", &street_number) != 1) {
        printf("[ERROR] Numero invalido\n");
        break;
      }
      search_house(houses, street_name, street_number);
      break;
    }
    case 2: {
      printf("Not implemented yet. Come back later. \n");
      break;
    }
    case 3: {
      printf("Enter the name of the place: \n");
      char name_place[256];
      scanf(" %255[^\n]", name_place);
      PlaceNode *found = search_place(places, name_place);
      if (found != NULL) {
        StreetNode *s = closest_segment(streets, found->data.latitude, found->data.longitude);
        if (s != NULL) {
          printf("Closest street: %s\n", s->data.name);
        }
      }
      break;
    }
    default:
      free_houses(houses);
      free_places(places);
      free_streets(streets);
      return 1;
  }

  free_houses(houses);
  free_places(places);
  free_streets(streets);
  return 0;
}