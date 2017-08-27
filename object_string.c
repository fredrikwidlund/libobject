#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "object_type.h"
#include "object_base.h"
#include "object_string.h"

struct object_string
{
  object_base  base;
  char        *value;
};

static const struct object_type object_string_type =
  {
    .id = OBJECT_TYPE_STRING,
    .name = "string",
    .delete = object_string_delete,
    .pack = object_string_pack
  };

static struct object_string *object_string_cast(object *base)
{
  return (struct object_string *) base;
}

object *object_string(char *value)
{
  object *base;

  base = malloc(sizeof (struct object_string));
  object_string_construct(base, value);
  object_base_hold(base);

  return base;
}

void object_string_delete(object *base)
{
  object_string_destruct(base);
  free(base);
}

char *object_string_pack(object *base)
{
  int e;
  char *string;

  e = asprintf(&string, "\"%s\"", object_string_value(base));
  return e == -1 ? NULL: string;
}

void object_string_construct(object *base, char *value)
{
  object_base_construct(base, &object_string_type);
  object_string_cast(base)->value = strdup(value);
}

void object_string_destruct(object *base)
{
  object_base_destruct(base);
  free(object_string_cast(base)->value);
  object_string_cast(base)->value = NULL;
}

char *object_string_value(object *base)
{
  return object_string_cast(base)->value;
}

