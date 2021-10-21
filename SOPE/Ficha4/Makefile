Executables = 4 7 8 9 10 10_2 6
Binaries = 4.o 7.o 7.o 9.o 10.o 10_2.o 6.o
CFLAGS = -Wall -fno-stack-protector
LIBS = -lpthread

all: $(Executables)

$(Executables): % : %.o
				cc $(CFLAGS) $< -o $@

clean: 
		rm -f $(Executables) \
				$(Binaries)