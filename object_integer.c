#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "object_type.h"
#include "object_base.h"
#include "object_integer.h"

struct object_integer
{
  object_base base;
  int64_t     value;
};

static const struct object_type object_integer_type =
  {
    .id = OBJECT_TYPE_INTEGER,
    .name = "integer",
    .delete = object_integer_delete,
    .pack = object_integer_pack
  };

static struct object_integer *object_integer_cast(object *base)
{
  return (struct object_integer *) base;
}

object *object_integer(int64_t value)
{
  object *base;

  base = malloc(sizeof (struct object_integer));
  object_integer_construct(base, value);
  object_base_hold(base);

  return base;
}

void object_integer_delete(object *base)
{
  object_integer_destruct(base);
  free(base);
}

char *object_integer_pack(object *base)
{
  int e;
  char *string;

  e = asprintf(&string, "%ld", object_integer_value(base));
  return e == -1 ? NULL: string;
}

void object_integer_construct(object *base, int64_t value)
{
  object_base_construct(base, &object_integer_type);
  object_integer_cast(base)->value = value;
}

void object_integer_destruct(object *base)
{
  object_base_destruct(base);
}

int64_t object_integer_value(object *base)
{
  return object_integer_cast(base)->value;
}

