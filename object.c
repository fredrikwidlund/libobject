#include <stdlib.h>
#include <stdint.h>

#include "object_type.h"
#include "object_base.h"
#include "object.h"

void object_hold(object *object)
{
  object_base_hold(object);
}

void object_release(object *object)
{
  object_base_release(object);
}

char *object_pack(object *object)
{
  return object->type->pack(object);
}
