#include "places.h"
#include "algoritmos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_SUGERENCIAS 5

PlaceNode *init_place_list() {
  return NULL;
}

void append_place(PlaceNode **head, PlaceNode **tail, Place data) {
  PlaceNode *new_node = (PlaceNode *)malloc(sizeof(PlaceNode));
  if (new_node == NULL) {
    printf("[ERROR] fallo en la asignacion de memoria\n");
    return;
  }

  new_node->data = data;
  new_node->next = NULL;

  if (*head == NULL) {
    *head = new_node;
    *tail = new_node;
  } else {
    (*tail)->next = new_node;
    *tail = new_node;
  }
}

PlaceNode *fetch_places(const char *map_name)
{
  char file_path[256];
  snprintf(file_path, sizeof(file_path), "maps/%s/places.txt", map_name);

  FILE *file = fopen(file_path, "r");
  if (file == NULL)
  {
    printf("[ERROR] Fichero no encontrado o ruta incorrecta: %s\n", file_path);
    return NULL;
  }

  PlaceNode *head = init_place_list();
  PlaceNode *tail = NULL;
  char line[256];

  while (fgets(line, sizeof(line), file))
  {
    Place p;
    int parsed = sscanf(line, "%36[^,],%49[^,],%49[^,],%lf,%lf",
                        p.id, p.place, p.amenity, &p.latitude, &p.longitude);
    if (parsed != 5)
      continue;

    append_place(&head, &tail, p);
  }

  fclose(file);
  return head;
}

void search_place(PlaceNode *places, const char *place_name)
{
  PlaceNode *current = places;
  while (current != NULL){
    if(strcasecmp(current->data.place, place_name) == 0){
      printf("Place found: Latitud = %.6f, Longitud = %.6f\n", current->data.latitude, current->data.longitude);
      return;
    }
    current = current->next;
  }
  char sugeridas[MAX_SUGERENCIAS][50];
  int distancias[MAX_SUGERENCIAS];

  for (int i=0; i< MAX_SUGERENCIAS; i++){
    sugeridas[i][0] = '\0';
    distancias[i] = 9999;
  }
  
  current = places;
    while (current != NULL) {
    const char *nombre = current->data.place;
    int dist = levenshtein_distance(place_name, nombre);

    // Evitamos duplicados
    int ya_esta = 0;
    for (int i = 0; i < MAX_SUGERENCIAS; i++) {
      if (strcasecmp(sugeridas[i], nombre) == 0) {
        ya_esta = 1;
        break;
      }
    }
    if (ya_esta) {
      current = current->next;
      continue;
    }
    // Insertion sort parcial: mantenemos el top N por distancia
    for (int i = 0; i < MAX_SUGERENCIAS; i++) {
      if (dist < distancias[i]) {
        for (int j = MAX_SUGERENCIAS - 1; j > i; j--) {
          distancias[j] = distancias[j - 1];
          strncpy(sugeridas[j], sugeridas[j - 1], 49);
          sugeridas[j][49] = '\0';
        }
        distancias[i] = dist;
        strncpy(sugeridas[i], nombre, 49);
        sugeridas[i][49] = '\0';
        break;
      }
    }
    
    current = current->next;
  }

  printf("[ERROR] Place not found. Similar places:\n");
  int total = 0;
  for (int i = 0; i < MAX_SUGERENCIAS; i++) {
    if (sugeridas[i][0] != '\0') {
      printf("  %d. %s\n", i + 1, sugeridas[i]);
      total++;
    }
  }

    // El usuario elige una sugerencia y reintentamos
  if (total > 0) {
    printf("Enter the number of the place (0 to cancel): ");
    int opcion = 0;
    if (scanf("%d", &opcion) == 1 && opcion >= 1 && opcion <= total) {
      search_place(places, sugeridas[opcion - 1]);
    }
  }
}


  

int count_places(PlaceNode *head)
{
  int total = 0;
  PlaceNode *current = head;

  while (current != NULL)
  {
    total++;
    current = current->next;
  }

  return total;
}

void free_places(PlaceNode *head)
{
  PlaceNode *current = head;
  while (current != NULL)
  {
    PlaceNode *next = current->next;
    free(current);
    current = next;
  }
}
