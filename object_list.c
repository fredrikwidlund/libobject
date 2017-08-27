#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <dynamic.h>

#include "object_type.h"
#include "object_base.h"
#include "object_list.h"
#include "object.h"

struct object_list
{
  object_base base;
  vector      items;
};

static const struct object_type object_list_type =
  {
    .id = OBJECT_TYPE_LIST,
    .name = "list",
    .delete = object_list_delete,
    .pack = object_list_pack
  };

static struct object_list *object_list_cast(object *base)
{
  return (struct object_list *) base;
}

object *object_list(void)
{
  object *base;

  base = malloc(sizeof (struct object_list));
  object_list_construct(base);
  object_base_hold(base);

  return base;
}

void object_list_delete(object *base)
{
  object_list_destruct(base);
  free(base);
}

char *object_list_pack(object *base)
{
  string s;
  size_t i;
  char *item;

  string_construct(&s);
  string_append(&s, "[");
  for (i = 0; i < object_list_size(base); i ++)
    {
      item = object_pack(object_list_get(base, i));
      string_append(&s, item);
      if (i < object_list_size(base) - 1)
        string_append(&s, ",");
      free(item);
    }
  string_append(&s, "]");

  return string_data(&s);
}

void object_list_construct(object *base)
{
  object_base_construct(base, &object_list_type);
  vector_construct(&object_list_cast(base)->items, sizeof (object *));
}

void object_list_destruct(object *base)
{
  size_t i;

  for (i = 0; i < object_list_size(base); i ++)
    object_release(object_list_get(base, i));

  object_base_destruct(base);
  vector_destruct(&object_list_cast(base)->items);
}

void object_list_append(object *base, object *item)
{
  vector_push_back(&object_list_cast(base)->items, &item);
}

size_t object_list_size(object *base)
{
  return vector_size(&object_list_cast(base)->items);
}

object *object_list_get(object *base, size_t index)
{
  object **items = vector_data(&object_list_cast(base)->items);

  return items[index];
}

