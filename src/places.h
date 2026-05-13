#ifndef PLACES_H
#define PLACES_H
#define PLACE_LENGTH 50

typedef struct Place {
  char id[37];
  char place[PLACE_LENGTH];
  char amenity[PLACE_LENGTH];
  double latitude;
  double longitude;
} Place;

typedef struct PlaceNode {
  Place data;
  struct PlaceNode *next;
} PlaceNode;

PlaceNode *init_place_list();
void append_place(PlaceNode **head, PlaceNode **tail, Place data);
int count_places(PlaceNode *head);
PlaceNode* fetch_places(const char *map_name);
PlaceNode *search_place(PlaceNode *places, const char *name);
void free_places(PlaceNode *head);

#endif
