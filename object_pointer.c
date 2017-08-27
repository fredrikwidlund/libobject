#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "object_type.h"
#include "object_base.h"
#include "object_pointer.h"

struct object_pointer
{
  object_base  base;
  void        *value;
};

static const struct object_type object_pointer_type =
  {
    .id = OBJECT_TYPE_POINTER,
    .name = "pointer",
    .delete = object_pointer_delete,
    .pack = object_pointer_pack
  };

static struct object_pointer *object_pointer_cast(object *base)
{
  return (struct object_pointer *) base;
}

object *object_pointer(void *value)
{
  object *base;

  base = malloc(sizeof (struct object_pointer));
  object_pointer_construct(base, value);
  object_base_hold(base);

  return base;
}

void object_pointer_delete(object *base)
{
  object_pointer_destruct(base);
  free(base);
}

char *object_pointer_pack(object *base)
{
  int e;
  char *string;

  e = asprintf(&string, "\"%p\"", object_pointer_value(base));
  return e == -1 ? NULL: string;
}

void object_pointer_construct(object *base, void *value)
{
  object_base_construct(base, &object_pointer_type);
  object_pointer_cast(base)->value = value;
}

void object_pointer_destruct(object *base)
{
  object_base_destruct(base);
}

void *object_pointer_value(object *base)
{
  return object_pointer_cast(base)->value;
}

