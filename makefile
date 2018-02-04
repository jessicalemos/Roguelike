CFLAGS= -ansi -Wall -O2
OBJS=$(patsubst %.c, %.o, $(wildcard *.c))
EXEC=mec

instalar: $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)
	sudo cp $(EXEC) /usr/lib/cgi-bin
	sudo cp rato.png /var/www/html/
	sudo cp gato.png /var/www/html/
	sudo cp queijo.png /var/www/html/
	sudo cp ratoeira.png /var/www/html/
	sudo cp blood.png /var/www/html/
	sudo cp gameover.png /var/www/html/
	sudo cp go.png /var/www/html/
	sudo cp pathfinding.png /var/www/html/
	sudo cp pocao.png /var/www/html/
	sudo cp faca.png /var/www/html/
	sudo cp bomb.png /var/www/html/
	sudo cp auto.png /var/www/html/
	sudo cp rato_transparente.png /var/www/html/
	sudo cp	help_button.png /var/www/html/
	sudo cp	gato_ataque.png /var/www/html/
	sudo cp	go_button.png /var/www/html/
	sudo cp	novo.png /var/www/html/
	sudo cp	bonus1.png /var/www/html/
	sudo cp	bonus2.png /var/www/html/
	sudo cp	bonus3.png /var/www/html/
	sudo cp	score.png /var/www/html/

limpar:
	rm $(EXEC) *.o

