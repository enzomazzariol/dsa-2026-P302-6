#include "segments.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

StreetNode *init_street_list() {
  return NULL;
}

void append_street(StreetNode **head, StreetNode **tail, Street data) {
  StreetNode *new_node = (StreetNode *)malloc(sizeof(StreetNode));
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

StreetNode *fetch_streets(const char *map_name)
{
  char file_path[256];
  snprintf(file_path, sizeof(file_path), "maps/%s/streets.txt", map_name);

  FILE *file = fopen(file_path, "r");
  if (file == NULL)
  {
    printf("[ERROR] Fichero no encontrado o ruta incorrecta: %s\n", file_path);
    return NULL;
  }

  StreetNode *head = init_street_list();
  StreetNode *tail = NULL;
  char line[512];

  while (fgets(line, sizeof(line), file))
  {
    Street s;
    int parsed = sscanf(line, "%lld,%lf,%lf,%lld,%lf,%lf,%lf,%99[^\r\n]",
                        &s.from_id, &s.from_latitude, &s.from_longitude,
                        &s.to_id, &s.to_latitude, &s.to_longitude,
                        &s.length, s.name);
    if (parsed != 8)
      continue;

    append_street(&head, &tail, s);
  }

  fclose(file);
  return head;
}

int count_streets(StreetNode *head)
{
  int total = 0;
  StreetNode *current = head;

  while (current != NULL)
  {
    total++;
    current = current->next;
  }

  return total;
}

StreetNode *closest_segment(StreetNode *streets, double latitude, double longitude)
{
  StreetNode *current = streets;
  StreetNode *closest = NULL;
  double min_dist = 99999999.0;

  // recorremos todos los segmentos y nos quedamos con el mas cercano
  while (current != NULL) {
    double from_lat = current->data.from_latitude;
    double from_lon = current->data.from_longitude;
    double to_lat = current->data.to_latitude;
    double to_lon = current->data.to_longitude;

    // vector del segmento (from -> to)
    double dx = to_lon - from_lon;
    double dy = to_lat - from_lat;
    double largo = dx * dx + dy * dy;

    // proyectamos el punto sobre la recta del segmento
    // t indica donde cae la proyeccion: 0 = from, 1 = to
    double t = 0.0;
    if (largo > 0.0) {
      t = ((longitude - from_lon) * dx + (latitude - from_lat) * dy) / largo;
      // si la proyeccion cae fuera del segmento la recortamos al extremo
      if (t < 0.0) t = 0.0;
      if (t > 1.0) t = 1.0;
    }

    // punto del segmento mas cercano al place
    double proj_lon = from_lon + t * dx;
    double proj_lat = from_lat + t * dy;

    // distancia al cuadrado (no hace falta sqrt para comparar)
    double diff_lon = longitude - proj_lon;
    double diff_lat = latitude - proj_lat;
    double dist = diff_lon * diff_lon + diff_lat * diff_lat;

    if (dist < min_dist) {
      min_dist = dist;
      closest = current;
    }

    current = current->next;
  }

  return closest;
}

void free_streets(StreetNode *head)
{
  StreetNode *current = head;
  while (current != NULL)
  {
    StreetNode *next = current->next;
    free(current);
    current = next;
  }
}
