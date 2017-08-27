#ifndef OBJECT_MAP_H_INCLUDED
#define OBJECT_MAP_H_INCLUDED

object *object_map(void);
void    object_map_delete(object *);
char   *object_map_pack(object *);
void    object_map_construct(object *);
void    object_map_destruct(object *);
void    object_map_set(object *, const char *, object *);
object *object_map_get(object *, const char *);

#endif /* OBJECT_MAP_H_INCLUDED */
