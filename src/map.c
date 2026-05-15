#include "map.h"

#include <stdio.h>
#include <string.h>

FILE *open_map_file(const char *map_name, const char *filename) {
  char file_path[256];
  snprintf(file_path, sizeof(file_path), "maps/%s/%s", map_name, filename);
  FILE *file = fopen(file_path, "r");
  if (file == NULL)
    printf("[ERROR] Fichero no encontrado o ruta incorrecta: %s\n", file_path);
  return file;
}

int ask_from_suggestions(char suggestions[][MAX_SUGGESTION_LEN], int max) {
  int total = 0;
  for (int i = 0; i < max; i++) {
    if (suggestions[i][0] != '\0') {
      printf("  %d. %s\n", i + 1, suggestions[i]);
      total++;
    }
  }
  if (total == 0)
    return -1;

  printf("Enter the number (0 to cancel): ");
  int opcion = 0;
  if (scanf("%d", &opcion) == 1 && opcion >= 1 && opcion <= total)
    return opcion - 1;
  return -1;
}

void print_map_menu(void) {
  printf("Enter a map number:\n 1. xs_1\n 2. xs_2\n 3. md_1\n 4. lg_1\n 5. xl_1\n 6. 2xl_1\n");
}

void print_map_options(void) {
  printf("Where are you? \n 1. address \n 2. coordinate \n 3. place \n");
}

const char *map_name_from_option(int option) {
  switch (option) {
    case 1:
      return "xs_1";
    case 2:
      return "xs_2";
    case 3:
      return "md_1";
    case 4:
      return "lg_1";
    case 5:
      return "xl_1";
    case 6:
      return "2xl_1";
    default:
      return NULL;
  }
}