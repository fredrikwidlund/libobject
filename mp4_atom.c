
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


void mp4_atom_print(mp4_atom *a, FILE *stream)
{
  char *string;

  string = object_pack(atom);
  (void) fputs(string, stream);
  free(string);
}
