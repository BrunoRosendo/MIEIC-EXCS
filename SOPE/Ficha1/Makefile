Executables = hello atexit cmd_and_vars open read thousands copy_open copy_fopen files
Binaries = hello.o atexit.o cmd_and_vars.o open.o read.o thousands.o copy_open.o copy_fopen.o files.o
CFLAGS = -Wall

all: $(Executables)

$(Executables): % : %.o
				cc $(CFLAGS) $< -o $@

clean: 
		rm -f $(Executables) \
				$(Binaries)