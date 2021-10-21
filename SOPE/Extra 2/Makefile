Executables = p5a p5b p6a
Binaries = p5a.o p5b.o p6a.o
CFLAGS = -Wall

all: $(Executables)

$(Executables): % : %.o
				cc $(CFLAGS) $< -o $@

clean:
		rm -f $(Executables) \
				$(Binaries)