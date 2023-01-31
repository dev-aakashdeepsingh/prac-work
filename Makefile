all: prac

CXXFLAGS=-march=native -std=c++17 -Wall -Wno-ignored-attributes -ggdb -O3
LDFLAGS=-ggdb
LDLIBS=-lbsd -lboost_system -lboost_context -lboost_chrono -lboost_thread -lpthread

# Enable this to have all communication logged to stdout
# CXXFLAGS += -DVERBOSE_COMMS

BIN=prac
SRCS=prac.cpp mpcio.cpp preproc.cpp online.cpp mpcops.cpp rdpf.cpp \
    cdpf.cpp duoram.cpp cell.cpp
OBJS=$(SRCS:.cpp=.o)
ASMS=$(SRCS:.cpp=.s)

$(BIN): $(OBJS)
	g++ $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.s: %.cpp
	g++ $(CXXFLAGS) -S -o $@ $^

# Remove the files created by the preprocessing phase
reset:
	-rm -f *.p[012].t*

clean: reset
	-rm -f $(BIN) $(OBJS) $(ASMS)

depend:
	makedepend -Y -- $(CXXFLAGS) -- $(SRCS)

# DO NOT DELETE THIS LINE -- make depend depends on it.

prac.o: mpcio.hpp types.hpp bitutils.hpp corotypes.hpp mpcio.tcc preproc.hpp
prac.o: options.hpp online.hpp
mpcio.o: mpcio.hpp types.hpp bitutils.hpp corotypes.hpp mpcio.tcc rdpf.hpp
mpcio.o: coroutine.hpp dpf.hpp prg.hpp aes.hpp rdpf.tcc mpcops.hpp mpcops.tcc
mpcio.o: cdpf.hpp cdpf.tcc
preproc.o: types.hpp bitutils.hpp coroutine.hpp corotypes.hpp mpcio.hpp
preproc.o: mpcio.tcc preproc.hpp options.hpp rdpf.hpp dpf.hpp prg.hpp aes.hpp
preproc.o: rdpf.tcc mpcops.hpp mpcops.tcc cdpf.hpp cdpf.tcc
online.o: online.hpp mpcio.hpp types.hpp bitutils.hpp corotypes.hpp mpcio.tcc
online.o: options.hpp mpcops.hpp coroutine.hpp mpcops.tcc rdpf.hpp dpf.hpp
online.o: prg.hpp aes.hpp rdpf.tcc duoram.hpp duoram.tcc cdpf.hpp cdpf.tcc
online.o: cell.hpp
mpcops.o: mpcops.hpp types.hpp bitutils.hpp mpcio.hpp corotypes.hpp mpcio.tcc
mpcops.o: coroutine.hpp mpcops.tcc
rdpf.o: rdpf.hpp mpcio.hpp types.hpp bitutils.hpp corotypes.hpp mpcio.tcc
rdpf.o: coroutine.hpp dpf.hpp prg.hpp aes.hpp rdpf.tcc mpcops.hpp mpcops.tcc
cdpf.o: bitutils.hpp cdpf.hpp mpcio.hpp types.hpp corotypes.hpp mpcio.tcc
cdpf.o: coroutine.hpp dpf.hpp prg.hpp aes.hpp cdpf.tcc
duoram.o: duoram.hpp types.hpp bitutils.hpp mpcio.hpp corotypes.hpp mpcio.tcc
duoram.o: coroutine.hpp duoram.tcc mpcops.hpp mpcops.tcc cdpf.hpp dpf.hpp
duoram.o: prg.hpp aes.hpp cdpf.tcc rdpf.hpp rdpf.tcc
cell.o: types.hpp bitutils.hpp duoram.hpp mpcio.hpp corotypes.hpp mpcio.tcc
cell.o: coroutine.hpp duoram.tcc mpcops.hpp mpcops.tcc cdpf.hpp dpf.hpp
cell.o: prg.hpp aes.hpp cdpf.tcc rdpf.hpp rdpf.tcc cell.hpp options.hpp
