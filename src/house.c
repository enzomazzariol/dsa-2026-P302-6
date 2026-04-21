#include "house.h"
#include "algoritmos.h"
#include "abreviaturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

HouseNode *init_house_list() {
  return NULL;
}

void append_house(HouseNode **head, HouseNode **tail, House data) {
  HouseNode *new_node = (HouseNode *)malloc(sizeof(HouseNode));
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

HouseNode *fetch_houses(const char *map_name)
{
  char file_path[256];
  snprintf(file_path, sizeof(file_path), "maps/%s/houses.txt", map_name);

  FILE *file = fopen(file_path, "r");
  if (file == NULL)
  {
    printf("[ERROR] Fichero no encontrado o ruta incorrecta: %s\n", file_path);
    return NULL;
  }

  HouseNode *head = init_house_list();
  HouseNode *tail = NULL;
  char line[256];

  while (fgets(line, sizeof(line), file))
  {
    House h;
    int parsed = sscanf(line, "%99[^,],%d,%lf,%lf", h.street, &h.number, &h.latitude, &h.longitude);
    if (parsed != 4)
      continue;

    append_house(&head, &tail, h);
  }

  fclose(file);
  return head;
}

void insert_match(Match results[], int *count, HouseNode *node, int dist) {
    if (*count < MAX_RESULTS) {
        results[*count].node = node;
        results[*count].distance = dist;
        (*count)++;
    } else if (dist >= results[*count - 1].distance) {
        return; 
    } else {
        results[*count - 1].node = node;
        results[*count - 1].distance = dist;
    }

    // ordenar (insertion sort pequeño)
    for (int i = *count - 1; i > 0; i--) {
        if (results[i].distance < results[i - 1].distance) {
            Match temp = results[i];
            results[i] = results[i - 1];
            results[i - 1] = temp;
        }
    }
}

void to_lowercase(const char *input, char *output, int size) {
  int i;
  for (i = 0; i < size - 1 && input[i] != '\0'; i++) {
    output[i] = tolower(input[i]);
  }
  output[i] = '\0';
}

void search_house(HouseNode *houses, const char *house_name, int house_number){
  HouseNode *current = houses;
  HouseNode *best_match = NULL;
  int best_distance = 9999;

  char house_name_lower[HOUSE_STREET_LENGTH];
  to_lowercase(house_name, house_name_lower, HOUSE_STREET_LENGTH);

  while (current != NULL){
    int limite = 3;
    if(current->data.number == house_number){

      char street_lower[HOUSE_STREET_LENGTH];
      to_lowercase(current->data.street, street_lower, HOUSE_STREET_LENGTH);

      int len1 = strlen(street_lower);
      int len2 = strlen(house_name_lower);

      // filtro para optimizar levenshtein_distance
      if(abs(len1 - len2) <= limite){
        int distance = levenshtein_distance(street_lower, house_name_lower);
        int distance_abbr = levenshtein_distance(street_lower, abreviaturas(house_name_lower));
        int final_distance = 0;

        if(distance < distance_abbr){
          final_distance = distance;
        } else{
          final_distance = distance_abbr;
        }

        if(final_distance < best_distance){
          best_distance = final_distance;
          best_match = current;
        }

        if(final_distance == 0)
          break;
      }

    }
    current = current->next;
  }
  if (best_match != NULL && best_distance <= 3) {
    printf("House found: %s %d\n", best_match->data.street, best_match->data.number);
    printf("Lat = %.6f, Lon = %.6f\n", best_match->data.latitude, best_match->data.longitude);
  } else {
    printf("[ERROR] House not found\n");
  }
}

int count_houses(HouseNode *head){ 
  int total = 0;
  HouseNode *current = head;

  while (current != NULL)
  {
    total++;
    current = current->next;
  }

  return total;
}

void free_houses(HouseNode *head)
{
  HouseNode *current = head;
  while (current != NULL)
  {
    HouseNode *next = current->next;
    free(current);
    current = next;
  }
}