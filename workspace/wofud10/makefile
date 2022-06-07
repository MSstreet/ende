CC = gcc
TARGET = haxShared
OBJ = haxShared libhaxshared.so

txtShared : libhaxshared.so
	        $(CC) -o $(TARGET) -g hax_test.c -L./ -lhaxshared

libhaxshared.so: main.o
	        $(CC) -shared -o libhaxshared.so main.o

main.o :
	        $(CC) -g -fPIC -c main.c

test:
	        LD_LIBRARY_PATH=${PWD} ./$(TARGET)

debug:
	        LD_LIBRARY_PATH=${PWD} cgdb ./${TARGET}

leak:
	        LD_LIBRARY_PATH=${PWD} valgrind --leak-check=full --error-limit=no ./${TARGET}

clean:
	        rm -f ${OBJ}
		rm -f *.o
