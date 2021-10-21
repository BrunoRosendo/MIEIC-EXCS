Executables = 4 noeco password upper upper2
Binaries = 4.o noeco.o password.o upper.o upper2.o
CFLAGS = -Wall

all: $(Executables)

$(Executables): % : %.o
				cc $(CFLAGS) $< -o $@

clean: 
		rm -f $(Executables) \
				$(Binaries)