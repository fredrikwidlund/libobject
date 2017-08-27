#ifndef OBJECT_TYPE_H_INCLUDED
#define OBJECT_TYPE_H_INCLUDED

typedef struct object_base object;

enum object_type_id
{
  OBJECT_TYPE_UNDEFINED,
  OBJECT_TYPE_INTEGER,
  OBJECT_TYPE_FLOAT,
  OBJECT_TYPE_STRING,
  OBJECT_TYPE_POINTER,
  OBJECT_TYPE_LIST,
  OBJECT_TYPE_MAP
};

struct object_type
{
  int           id;
  const char   *name;
  void        (*delete)(object *);
  char       *(*pack)(object *);
};

int         object_type(object *);
const char *object_type_name(object *);

#endif /* OBJECT_TYPE_H_INCLUDED */
