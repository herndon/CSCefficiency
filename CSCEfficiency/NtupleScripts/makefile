CC=g++
FLAGS=`root-config --libs --cflags`

all: analyze plot

analyze: CSCEffFast.C CSCEffFast.h; ${CC} -o $@ $< ${FLAGS}

plot: PlotCSCEffFast.C; ${CC} -o $@ $< ${FLAGS}

clean:
	rm -f analyze plot

rootclean:
	rm -f CSCEffFast_C*.* PlotCSCEffFast_C*.*
