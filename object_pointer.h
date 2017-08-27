#ifndef OBJECT_POINTER_H_INCLUDED
#define OBJECT_POINTER_H_INCLUDED

object  *object_pointer(void *);
void     object_pointer_delete(object *);
char    *object_pointer_pack(object *);

void     object_pointer_construct(object *, void *);
void     object_pointer_destruct(object *);
void    *object_pointer_value(object *);

#endif /* OBJECT_POINTER_H_INCLUDED */
