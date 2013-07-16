C = /usr/bin/gcc

INCS = -I. -I/usr/include -I/usr/include/allegro
CFLAGS = -Wall

LIBLINK = `allegro-config --libs`

OBJ = shots.o jogo.o main.o matematica.o stars.o asteroids.o nave.o hud.o shield.o menu.o records.o configuration.o explosion.o

all: clean jogo

clean:
	rm -rf *.o

jogo: $(OBJ)
	$(C) $(CFLAGS) -o jogo $(OBJ) $(LIBLINK)

    %.o:%.c
	$(C) $(CFLAGS) $(INCS) -c $+
