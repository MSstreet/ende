SharedCode : main.c libmysharedCode.so
	gcc -o SharedCode main.c -L./ -lmysharedCode

libmysharedCode.so : endetest.o
	gcc -shared -o libmysharedCode.so endetest.o

endetest.o : endetest.h endetest.c
	gcc -fPIC -c endetest.c

test : 
	LD_LIBRARY_PATH=${PWD} ./SharedCode



clean :
	rm -f *.o
	rm -f $(TARGET)
