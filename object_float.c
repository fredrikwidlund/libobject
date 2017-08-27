#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "object_type.h"
#include "object_base.h"
#include "object_float.h"

struct object_float
{
  object_base base;
  double      value;
};

static const struct object_type object_float_type =
  {
    .id = OBJECT_TYPE_FLOAT,
    .name = "float",
    .delete = object_float_delete,
    .pack = object_float_pack
  };

static struct object_float *object_float_cast(object *base)
{
  return (struct object_float *) base;
}

object *object_float(double value)
{
  object *base;

  base = malloc(sizeof (struct object_float));
  object_float_construct(base, value);
  object_base_hold(base);

  return base;
}

void object_float_delete(object *base)
{
  object_float_destruct(base);
  free(base);
}

char *object_float_pack(object *base)
{
  int e;
  char *string;

  e = asprintf(&string, "%f", object_float_value(base));
  return e == -1 ? NULL: string;
}

void object_float_construct(object *base, double value)
{
  object_base_construct(base, &object_float_type);
  object_float_cast(base)->value = value;
}

void object_float_destruct(object *base)
{
  object_base_destruct(base);
}

double object_float_value(object *base)
{
  return object_float_cast(base)->value;
}

