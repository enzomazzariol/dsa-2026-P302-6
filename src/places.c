#include "places.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

  PlaceNode *head = NULL;
  PlaceNode *tail = NULL;
  char line[256];

  while (fgets(line, sizeof(line), file))
  {
    PlaceNode *new_node = (PlaceNode *)malloc(sizeof(PlaceNode));
    if (new_node == NULL)
    {
      printf("[ERROR] fallo en la asignacion de memoria\n");
      fclose(file);
      free_places(head);
      return NULL;
    }

    char id[37]; 
    char place[PLACE_LENGTH];
    char amenity[PLACE_LENGTH];
    double latitude;
    double longitude;
    int parsed = sscanf(line,
    "%36[^,],%49[^,],%49[^,],%lf,%lf", id, place, amenity, &latitude, &longitude);    
    if (parsed != 5)
    {
      free(new_node);
      continue;
    }

    strcpy(new_node->data.id, id);
    strcpy(new_node->data.place, place);
    strcpy(new_node->data.amenity, amenity);
    new_node->data.latitude = latitude;
    new_node->data.longitude = longitude;
    new_node->next = NULL;

    if (head == NULL)
    {
      head = new_node;
      tail = new_node;
    }
    else
    {
      tail->next = new_node;
      tail = new_node;
    }
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
  printf("[ERROR] Place not found\n");
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