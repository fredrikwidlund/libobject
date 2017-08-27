#include <stdlib.h>
#include <stdint.h>

#include "object_type.h"
#include "object_base.h"

int object_type(object *object)
{
  return object->type->id;
}

const char *object_type_name(object *object)
{
  return object->type->name;
}
