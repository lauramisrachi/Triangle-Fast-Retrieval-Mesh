PROGS = main-Maillage
OBJS = Maillage.o
CXXFLAGS = -Wall -std=c++11 -g 

all: $(PROGS)
	
main-Maillage: main-Maillage.o $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS) $(LIBS) 
	
clean: 
		-rm -f $(PROGS) *.o .dSYM 