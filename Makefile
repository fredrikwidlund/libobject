PROG    = object
CFLAGS  = -g -Wall -O3 -std=gnu11 -flto -fuse-linker-plugin
LDADD   = -ldynamic
OBJS    = main.o bytes.o object_type.o object_base.o
OBJS   += object_integer.o
OBJS   += object_float.o
OBJS   += object_string.o
OBJS   += object_pointer.o
OBJS   += object_list.o
OBJS   += object_map.o
OBJS   += object.o

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDADD)

clean:
	rm -f $(PROG) $(OBJS)
