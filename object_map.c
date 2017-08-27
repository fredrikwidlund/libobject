#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <dynamic.h>

#include "object_type.h"
#include "object_base.h"
#include "object_map.h"
#include "object.h"

typedef struct object_map_item object_map_item;
struct object_map_item
{
  const char  *key;
  object      *value;
};

struct object_map
{
  object_base  base;
  map          items;
};

static object_map_item object_map_item_empty = {NULL, NULL};

static size_t object_map_item_hash(map *map, void *p)
{
  object_map_item *item = p;

  return hash_string((char *) item->key);
}

static void object_map_item_set(map *map, void *p1, void *p2)
{
  object_map_item *dst = p1, *src = p2;

  *dst = *src;
}

static int object_map_item_equal(map *map, void *p1, void *p2)
{
  object_map_item *item1 = p1, *item2 = p2;

  return item1->key == item2->key || (item1->key && item2->key && strcmp(item1->key, item2->key) == 0);
}

static void object_map_item_release(map *map, void *p)
{
  object_map_item *item = p;

  if (item->value)
    object_release(item->value);
}

static struct object_map *object_map_cast(object *base)
{
  return (struct object_map *) base;
}

static const struct object_type object_map_type =
  {
    .id = OBJECT_TYPE_MAP,
    .name = "map",
    .delete = object_map_delete,
    .pack = object_map_pack
  };

object *object_map(void)
{
  object *base;

  base = malloc(sizeof (struct object_map));
  object_map_construct(base);
  object_base_hold(base);

  return base;
}

void object_map_delete(object *base)
{
  object_map_destruct(base);
  free(base);
}

char *object_map_pack(object *base)
{
  string s;
  size_t i, n;
  char *value;
  map *map;
  object_map_item *item;

  string_construct(&s);
  string_append(&s, "{");
  map = &object_map_cast(base)->items;
  item = map->elements;
  for (i = 0, n = 0; i < map->elements_capacity; i ++)
    if (item[i].key)
      {
        if (n)
          string_append(&s, ",");
        n ++;
        string_append(&s, "\"");
        string_append(&s, (char *) item[i].key);
        string_append(&s, "\":");
        value = object_pack(item[i].value);
        string_append(&s, value);
        free(value);
      }
  string_append(&s, "}");

  return string_data(&s);
}

void object_map_construct(object *base)
{
  object_base_construct(base, &object_map_type);
  map_construct(&object_map_cast(base)->items, sizeof (object_map_item), &object_map_item_empty, object_map_item_set);
}

void object_map_destruct(object *base)
{
  object_base_destruct(base);
  map_destruct(&object_map_cast(base)->items, object_map_item_equal, object_map_item_release);
}

void object_map_set(object *base, const char *key, object *value)
{
  map_insert(&object_map_cast(base)->items, (object_map_item[]){{.key = key, .value = value}},
             object_map_item_hash, object_map_item_equal, object_map_item_set, object_map_item_release);
}

object *object_map_get(object *base, const char *key)
{
  object_map_item *item;

  item = map_at(&object_map_cast(base)->items, (object_map_item[]){{.key = key}},
                object_map_item_hash, object_map_item_equal);
  return item->value;
}
