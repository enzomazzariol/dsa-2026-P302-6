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

void search_house(HouseNode *houses, const char *house_name, int house_number) {
    HouseNode *current = houses;

    while (current != NULL) {
        const char *abbr = abreviaturas(house_name);

        if (current->data.number == house_number && (strcasecmp(current->data.street, house_name) == 0 || strcasecmp(current->data.street, abbr) == 0)) {
            printf("House found: Latitud = %.6f, Longitud = %.6f\n", current->data.latitude, current->data.longitude);
            return;
        }
        current = current->next;
    }

    int street_found = 0;
    current = houses;

    while (current != NULL) {
        const char *abbr = abreviaturas(house_name);

        if (strcasecmp(current->data.street, house_name) == 0 || strcasecmp(current->data.street, abbr) == 0) {
            street_found = 1;
            break;
        }
        current = current->next;
    }

    if (street_found) {
        printf("No se ha encontrado el número proporcionado. ");
        printf("Números disponibles en esta calle: ");

        current = houses;
        while (current != NULL) {
            const char *abbr = abreviaturas(house_name);

            if (strcasecmp(current->data.street, house_name) == 0 || strcasecmp(current->data.street, abbr) == 0) {
                printf("%d ", current->data.number);
            }
            current = current->next;
        }

        printf("\nEnter the correct house number: \n");
        int new_number;
        if (scanf("%d", &new_number) == 1) {
            search_house(houses, house_name, new_number);
        } else {
            printf("[ERROR] Numero invalido\n");
        }
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