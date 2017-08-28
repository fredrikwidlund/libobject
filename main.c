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

#include "bytes.h"

size_t bytes_offset(bytes *b1, bytes *b2)
{
  return b2->base - b1->base;
}

typedef object mp4_atom;

void mp4_atom_container_unpack(mp4_atom *, bytes *);

mp4_atom *mp4_atom_new(char *type)
{
  mp4_atom *atom;

  atom = object_map();
  object_map_set(atom, "type", object_string(type ? type : "root"));

  return atom;
}

void mp4_atom_unpack(mp4_atom *atom, bytes *b)
{
  char *type;

  type = object_string_value(object_map_get(atom, "type"));
  if (strcmp(type, "root") == 0)
    mp4_atom_container_unpack(atom, b);
  if (strcmp(type, "moov") == 0)
    mp4_atom_container_unpack(atom, b);
  if (strcmp(type, "trak") == 0)
    mp4_atom_container_unpack(atom, b);

}

void mp4_atom_container_unpack(mp4_atom *atom, bytes *b)
{
  bytes saved;
  object *items;
  mp4_atom *item;
  size_t size;
  char type[4];

  items = object_map_get(atom, "items");
  if (!items)
    {
      items = object_list();
      object_map_set(atom, "items", items);
    }

  while (bytes_valid(b) && bytes_size(b))
    {
      saved = *b;
      size = bytes_pop32(b);
      bytes_pop(b, (uint8_t *) type, sizeof type);
      if (size == 0)
        size = bytes_size(b) - 8;
      else if (size == 1)
        size = bytes_pop64(b) - 16;

      bytes_copy(&child_bytes, b);
      bytes_truncate(&child_bytes, size);
      child = mp4_atom_new(type);
      mp4_atom_unpack(child, &child_bytes);
      object_list_append(children, children);

      bytes_pop(b, NULL, size);
    }
}


void load(char *path, void **data, size_t *size)
{
  struct stat st;
  int e, fd;
  ssize_t n;

  e = stat(path, &st);
  if (e == -1)
    return;

  *size = st.st_size;
  *data = malloc(*size);
  if (!*data)
    return;

  fd = open(path, O_RDONLY);
  if (fd == -1)
    {
      free(*data);
      *data = NULL;
      return;
    }

  n = read(fd, *data, *size);
  (void) close(fd);
  if (n != *size)
    {
      free(*data);
      *data = NULL;
    }
}

int main(int argc, char **argv)
{
  bytes bytes;
  void *data;
  size_t size;
  object *atom;
  char *string;

  load(argv[1], &data, &size);
  if (!data)
    err(1, "load");

  bytes_construct(&bytes, data, size);
  atom = mp4_atom_new(NULL);
  mp4_atom_unpack(atom, &bytes);
  string = object_pack(atom);

  printf("%s\n", string);

  object_release(atom);
  free(string);
  free(data);
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
