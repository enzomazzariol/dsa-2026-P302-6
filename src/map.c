#include "map.h"

#include <stdio.h>

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