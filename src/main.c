#include "sample_lib.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#define HOUSE_STREET_LENGHT 100

void createaleak() {
  char *foo = malloc(20 * sizeof(char));
  printf("Allocated leaking string: %s", foo);
}

struct House {
  char street[HOUSE_STREET_LENGHT];
  int number;
  double latitude;
  double longitude;
};

struct HouseNodo{
  struct House data;
  struct HouseNodo *next;
};

struct HouseNodo* fetch_houses(FILE *file){
  file = fopen("xs_1", "r");
  if(file == NULL){
    printf("[ERROR] File does not exist or incorrect path");
  }

  // Inicializamos variables para la lista de casas
  struct HouseNodo *head = NULL;
  struct HouseNodo *tail = NULL;
  char line[256];
  
  while(fgets(line, sizeof(line), file)){
    struct House newHouse;
    struct HouseNodo *new_nodo = NULL;

    // espacio en memoria para cada casa
    new_nodo = (struct HouseNodo *)malloc(sizeof(struct HouseNodo));

    if(!new_nodo){
      printf("[ERROR] Memory allocation failed\n");
      return;
    }

    // leemos data del archivo house.txt
    char street[HOUSE_STREET_LENGHT];
    int number;
    double lat;
    double lon;
    sscanf(line, "%[^,],%d,%lf,%lf", street, &number, &lat, &lon);

    strcpy(newHouse.street, street);
    newHouse.number = number;
    newHouse.latitude = lat;
    newHouse.longitude = lon;

    // guardamos en la lista enlazada
    new_nodo->data = newHouse;
    new_nodo->next = NULL;

    if(head == NULL){
      head = new_nodo;
      tail = new_nodo;
    } else{
      tail->next = new_nodo;
      tail = new_nodo;
    };
  }

  return head;
  fclose(file);
}

void search_house(char *house_name){
  
}

int main() {
  printf("*****************\nWelcome to DSA!\n*****************\n");

  // how to import and call a function
  printf("Factorial of 4 is %d\n", fact(4));

  // uncomment and run "make v" to see how valgrind detects memory leaks
  // createaleak();

  int user_map = 0;
  printf("Enter a map number: \n 1. xs_1 \n 2. xs_2 \n 3. md_1 \n 4. md_1 \n 5. lg_1 \n 6. xl_1 \n 7. 2xl_1 \n");
  scanf("%d", &user_map);
  printf("Has elegido el mapa: %d", user_map);

  return 0;
}