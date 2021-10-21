Executables = 5 ssignal 13_1 13_2 13_3 13_4
Binaries = 5.o ssignal.o 13_1.o 13_2.o 13_3.o 13_4.o
CFLAGS = -Wall
LIBS = -lpthread

all: $(Executables)

$(Executables): % : %.o
				cc $(CFLAGS) $< -o $@

sthread: sthread.o
	gcc -o sthread sthread.o $(LIBS)

10: 10.o
	gcc -o 10 10.o $(LIBS)

clean: 
		rm -f $(Executables) \
				$(Binaries)
		rm -f sthread *.o