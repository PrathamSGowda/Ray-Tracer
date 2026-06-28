#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <stdbool.h>

#include "hittable.h"

typedef struct
{
    hittable **objects;

    int count;
    int capacity;

} hittable_list;

void hittable_list_init(hittable_list *list);

void hittable_list_clear(hittable_list *list);

void hittable_list_add(hittable_list *list, hittable *object);

bool hittable_list_hit(const hittable_list *list, ray r, double t_min, double t_max, hit_record *rec);

#endif