#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <err.h>

#include "object_type.h"
#include "object_base.h"
#include "object_integer.h"
#include "object_float.h"
#include "object_string.h"
#include "object_pointer.h"
#include "object_list.h"
#include "object_map.h"
#include "object.h"

int main()
{
}

/*
int main()
{
  object *list, *map;
  char *string;

  list = object_list();
  object_list_append(list, object_integer(1));
  object_list_append(list, object_integer(2));
  object_list_append(list, object_integer(3));
  object_list_append(list, object_integer(5));
  object_list_append(list, object_integer(7));
  object_list_append(list, object_float(3.14));
  object_list_append(list, object_string("... and so on ..."));

  map = object_map();
  object_map_set(map, "primes", list);
  object_map_set(map, "test", object_string("foo"));
  object_map_set(map, "key", object_pointer(map));;

  string = object_pack(map);
  printf("%s\n", string);
  free(string);

  object_release(map);
}
*/
