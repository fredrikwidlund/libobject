#ifndef OBJECT_BASE_H_INCLUDED
#define OBJECT_BASE_H_INCLUDED

typedef struct object_base object_base;
struct object_base
{
  const struct object_type *type;
  size_t                    references;
};

void object_base_construct(object_base *, const struct object_type *);
void object_base_destruct(object_base *);
void object_base_hold(object_base *);
void object_base_release(object_base *);

#endif /* OBJECT_BASE_H_INCLUDED */
