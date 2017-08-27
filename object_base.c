#include <stdlib.h>

#include "object_type.h"
#include "object_base.h"

void object_base_construct(object_base *base, const struct object_type *type)
{
  base->type = type;
  base->references = 0;
}

void object_base_destruct(object_base *base)
{
  (void) base;
}

void object_base_hold(object_base *base)
{
  base->references ++;
}

void object_base_release(object_base *base)
{
  if (!base->references)
    return;

  base->references --;
  if (!base->references)
    base->type->delete(base);
}
