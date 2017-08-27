#ifndef OBJECT_INTEGER_H_INCLUDED
#define OBJECT_INTEGER_H_INCLUDED

object  *object_integer(int64_t);

void     object_integer_delete(object *);
char    *object_integer_pack(object *);

void     object_integer_construct(object *, int64_t);
void     object_integer_destruct(object *);
int64_t  object_integer_value(object *);

#endif /* OBJECT_INTEGER_H_INCLUDED */
