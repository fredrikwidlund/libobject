#ifndef OBJECT_FLOAT_H_INCLUDED
#define OBJECT_FLOAT_H_INCLUDED

object  *object_float(double);

void     object_float_delete(object *);
char    *object_float_pack(object *);

void     object_float_construct(object *, double);
void     object_float_destruct(object *);
double   object_float_value(object *);

#endif /* OBJECT_FLOAT_H_INCLUDED */
