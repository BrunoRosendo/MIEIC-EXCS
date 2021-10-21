Executables = 1 3 sexec count count_ok bbcount bbcount2 bbcount3
Binaries = 1.o 3.o sexec.o count.o count_ok.o bbcount.o bbcount2.o bbcount3.o
CFLAGS = -Wall
LIBS = -lpthread

all: $(Executables)

$(Executables): % : %.o
				cc $(CFLAGS) $< -o $@ $(LIBS)

clean: 
		rm -f $(Executables) \
				$(Binaries)