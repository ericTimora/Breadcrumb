SRC=main3E.C filter.C image.C sink.C source.C PNMreader.C PNMwriter.C filters.C 
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o proj3E

.C.o: $<
	g++ -I. -c $<

run:
	./proj3E input.pnm output.pnm

clean:
	rm *.o

png:
	pnmtopng < output.pnm > output.png
