CFLAGS = -std=c99 -pedantic -Wall -Wextra
CPPFLAGS = -std=c++11 -pedantic -Wall

all: lib tail tail2 wordcount

lib: htab_memory.c htab_hash.c htab_iterators.c htab_getset.c
	gcc $(CFLAGS) -c htab_memory.c htab_hash.c htab_iterators.c htab_getset.c
	ar rcs libhtab.a htab*.o

tail: tail.c
	gcc $(CFLAGS) -o tail tail.c

tail2: tail2.cc
	g++ $(CPPFLAGS) -o tail2 tail2.cc

wordcount: wordcount.c libhtab.a htab.h htab_structures.h io.c
	gcc $(CFLAGS) -o wordcount wordcount.c libhtab.a io.c
	
wordcount_dynamic: wordcount.c htab_memory.c htab_hash.c htab_iterators.c htab_getset.c io.c
	gcc $(CFLAGS) -o libhtab.so -shared -fPIC htab_memory.c htab_hash.c htab_iterators.c htab_getset.c
	export LD_LIBRARY_PATH="."
	gcc $(CFLAGS) -o wordcount_dynamic -lhtab -L. wordcount.c io.c

run: