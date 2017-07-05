a.out: gate.o wire.o task.o adder.o \
	main.o flip_flop.o store.o
	gcc -o a.out gate.o wire.o task.o \
		adder.o flip_flop.o store.o main.o
gate.o: gate.c gate.h wire.h
	gcc -c gate.c
wire.o: wire.c wire.h gate.h
	gcc -c wire.c
task.o: task.c task.h gate.h wire.h
	gcc -c task.c
adder.o: adder.c task.h gate.h wire.h
	gcc -c adder.c
flip_flop.o: flip_flop.c flip_flop.h
	gcc -c flip_flop.c
store.o: store.c store.h wire.h gate.h \
	flip_flop.h adder.h
	gcc -c store.c
main.o: main.c core.h
	gcc -c main.c
clean:
	rm -rf a.out* *.o
