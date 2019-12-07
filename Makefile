CFLAGS+=-O3
ged: main.o
	cc ${CFLAGS} -o main main.o `pkg-config --libs gtk+-2.0`
ged.o: main.c
	cc ${CFLAGS} -c main.c `pkg-config --cflags gtk+-2.0`
clean:
	rm -f main.o main *~
