#ifndef SEGMENTS_H
#define SEGMENTS_H

#define STREET_NAME_LENGTH 100

typedef struct Street {
  long long from_id;
  double from_latitude;
  double from_longitude;
  long long to_id;
  double to_latitude;
  double to_longitude;
  double length;
  char name[STREET_NAME_LENGTH];
} Street;

typedef struct StreetNode {
  Street data;
  struct StreetNode *next;
} StreetNode;

StreetNode *init_street_list();
void append_street(StreetNode **head, StreetNode **tail, Street data);
StreetNode *fetch_streets(const char *map_name);
int count_streets(StreetNode *head);
StreetNode *closest_segment(StreetNode *streets, double latitude, double longitude);
void free_streets(StreetNode *head);

#endif
