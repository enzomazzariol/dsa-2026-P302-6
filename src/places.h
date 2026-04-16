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
  struct PlaceNodo *next;
} PlaceNode;

int count_places(const char* filename);

int load_places(const char* filename);

Place* search_place(const char* name, Place* places, int num_places);


#endif

