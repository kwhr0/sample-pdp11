PROGRAM = mandelbrot
DASM = pdp11dasm

all:
	rm -f a.out mapfile
	ack -ansi -O $(PROGRAM).c
	$(DASM) a.out
#	less a.out.das

clean:
	rm -f a.out* *.o mapfile
