CC=g++ `root-config --libs --cflags`

all: analyze plot

analyze: CSCEffFast.C CSCEffFast.h; ${CC} -o $@ $<

plot: PlotCSCEffFast.C; ${CC} -o $@ $<

clean:
	rm -f analyze plot

rootclean:
	rm -f CSCEffFast_C*.* PlotCSCEffFast_C*.*
