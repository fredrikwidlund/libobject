#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <sys/stat.h>


#include "object_type.h"
#include "object_base.h"
#include "object_integer.h"
#include "object_float.h"
#include "object_string.h"
#include "object_pointer.h"
#include "object_list.h"
#include "object_map.h"
#include "object.h"

#include "mp4_atom.h"

ssize_t load(char *path, void **data)
{
  struct stat st;
  int e, fd;
  ssize_t n;

  e = stat(path, &st);
  if (e == -1)
    return -1;

  st.st_size;
  *data = malloc(st.st_size);
  if (!*data)
    return -1;

  fd = open(path, O_RDONLY);
  if (fd == -1)
    {
      free(*data);
      return -1;
    }

  n = read(fd, *data, st.st_size);
  (void) close(fd);
  if (n != st.st_size)
    {
      free(*data);
      return -1;
    }

  return n;
}

int main()
{
  mp4_atom *a;
  void *data;
  ssize_t n;

  n = load(argv[1], &data);
  if (n == -1)
    err(1, "load");

  a = mp4_atom_new(NULL);
  e = mp4_atom_unpack(a, data, n);
  if (e == -1)
    err(1, "mp4_atom_unpack");
  mp4_atom_print(a, stdout);
  mp4_atom_release(atom);

  free(data);
}

/*
int main(int argc, char **argv)
{
  bytes bytes;
  void *data;
  size_t size;
  object *atom;

  load(argv[1], &data, &size);
  if (!data)
    err(1, "load");

  bytes_construct(&bytes, data, size);
  atom = mp4_atom_new(NULL);
  mp4_atom_unpack(atom, &bytes);

  printf("%s\n", string);

  object_release(atom);
  free(string);
  free(data);
  }*/

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
