Executables = bin-text dirfiles 5 8
Binaries = bin-text.o dirfiles.o 5.o 8.o
CFLAGS = -Wall

all: $(Executables)

$(Executables): % : %.o
				cc $(CFLAGS) $< -o $@

clean: 
		rm -f $(Executables) \
				$(Binaries)