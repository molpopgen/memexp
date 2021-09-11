CXXFLAGS=-O3 -g
CFLAGS=-O3 -g
LDFLAGS=-lgsl -lgslcblas

all: memexp memexpc

memexp: memexp.o
	$(CXX) $(CXXFLAGS) -o memexp memexp.o $(LDFLAGS)

memexp.o: memexp.cc
	$(CXX) $(CXXFLAGS) -c memexp.cc

memexpc: memexpc.o
	$(CC) $(CFLAGS) -o memexpc memexpc.o $(LDFLAGS) -lm

memexpc.o: memexpc.c
	$(CC) $(CFLAGS) -c memexpc.c

clean:
	rm -f *.o

