#include <stdlib.h>

#include "hittable_list.h"

void hittable_list_init(hittable_list *list)
{
    list->objects = NULL;
    list->count = 0;
    list->capacity = 0;
}

void hittable_list_clear(hittable_list *list)
{
    free(list->objects);

    list->objects = NULL;
    list->count = 0;
    list->capacity = 0;
}

void hittable_list_add(hittable_list *list, hittable *object)
{
    if(list->count == list->capacity)
    {
        int new_capacity = (list->capacity == 0) ? 4 : list->capacity * 2;

        hittable **new_objects = realloc(list->objects, new_capacity * sizeof(hittable *));

        if(new_objects == NULL)
        {
            return;
        }

        list->objects = new_objects;
        list->capacity = new_capacity;
    }

    list->objects[list->count] = object;
    list->count++;
}

bool hittable_list_hit(const hittable_list *list, ray r, double t_min, double t_max, hit_record *rec)
{
    hit_record temp_rec;

    bool hit_anything = false;
    double closest_so_far = t_max;

    for(int i=0; i<list->count; i++)
    {
        if(list->objects[i]->hit(list->objects[i], r, t_min, closest_so_far, &temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;

            *rec = temp_rec;
        }
    }

    return hit_anything;
}