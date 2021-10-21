Executables = hello environment errors atexit random
Binaries = hello.o environment.o errors.o atexit.o random.o
CFLAGS = -Wall

all: $(Executables)

$(Executables): % : %.o
				cc $(CFLAGS) $< -o $@

clean:
		rm -f $(Executables) \
				$(Binaries)