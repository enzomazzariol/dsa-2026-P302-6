#ifndef HOUSE_H
#define HOUSE_H

#define HOUSE_STREET_LENGTH 100

typedef struct House {
  char street[HOUSE_STREET_LENGTH];
  int number;
  double latitude;
  double longitude;
} House;

typedef struct HouseNodo {
  House data;
  struct HouseNodo *next;
} HouseNode;

HouseNode *fetch_houses(const char *map_name);
void search_house(HouseNode *houses, const char *house_name, int house_number);
int count_houses(HouseNode *head);
void print_first_houses(HouseNode *head, int limit);
void free_houses(HouseNode *head);

#endif