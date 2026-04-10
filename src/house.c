#include "house.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

  HouseNode *head = NULL;
  HouseNode *tail = NULL;
  char line[256];

  while (fgets(line, sizeof(line), file))
  {
    HouseNode *new_node = (HouseNode *)malloc(sizeof(HouseNode));
    if (new_node == NULL)
    {
      printf("[ERROR] fallo en la asignacion de memoria\n");
      fclose(file);
      free_houses(head);
      return NULL;
    }

    char street[HOUSE_STREET_LENGTH];
    int number;
    double lat;
    double lon;
    int parsed = sscanf(line, "%99[^,],%d,%lf,%lf", street, &number, &lat, &lon);
    if (parsed != 4)
    {
      free(new_node);
      continue;
    }

    strcpy(new_node->data.street, street);
    new_node->data.number = number;
    new_node->data.latitude = lat;
    new_node->data.longitude = lon;
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

void search_house(HouseNode *houses, const char *house_name, int house_number)
{
  HouseNode *current = houses;
  char input_lower[100] = house_name;
  

  for(int i = 0; i < 100; i++){
    towlower(input_lower[i]);
    towlower(current->data.street[i])
  }

  while (current != NULL)
  {
    char current_lower[100];
    
    if (strcmp(current_lower, input_lower) == 0 &&
        current->data.number == house_number)
    {
      printf("House found: lat=%.6f lon=%.6f\n",
             current->data.latitude,
             current->data.longitude);
      return;
    }
    current = current->next;
  }

  printf("[ERROR] House not found\n");
}

int count_houses(HouseNode *head)
{
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