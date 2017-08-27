#ifndef OBJECT_STRING_H_INCLUDED
#define OBJECT_STRING_H_INCLUDED

object  *object_string(char *);

void  object_string_delete(object *);
char *object_string_pack(object *);

void  object_string_construct(object *, char *);
void  object_string_destruct(object *);
char *object_string_value(object *);

#endif /* OBJECT_STRING_H_INCLUDED */
