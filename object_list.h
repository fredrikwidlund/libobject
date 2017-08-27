#ifndef OBJECT_LIST_H_INCLUDED
#define OBJECT_LIST_H_INCLUDED

object  *object_list(void);
void     object_list_delete(object *);
char    *object_list_pack(object *);
void     object_list_construct(object *);
void     object_list_destruct(object *);
void     object_list_append(object *, object *);
size_t   object_list_size(object *);
object  *object_list_get(object *, size_t);

#endif /* OBJECT_LIST_H_INCLUDED */
