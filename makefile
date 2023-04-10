all: clean simulador monitor

monitor: Monitor.o 
	gcc -o monitor Monitor.o -lpthread

simulador: Simulador.o
	gcc -o simulador Simulador.o -lpthread

clean:
	rm -f *.o *~ simulador monitor