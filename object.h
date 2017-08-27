#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

void  object_hold(object *);
void  object_release(object *);
char *object_pack(object *);

#endif /* OBJECT_H_INCLUDED */
