INCLUDE_PATH = $(HOME)/include
LIB_PATH = $(HOME)/lib
MXLIB_EXLIBS = -lboost_filesystem -lboost_system -lcfitsio 

OPTIMIZE = -O3

CPP = g++

CFLAGS += --std=c99 -D_XOPEN_SOURCE=600  -fPIC
CPPFLAGS += --std=c++0x -D_XOPEN_SOURCE=600 -fPIC

INCLUDE = -I$(INCLUDE_PATH)

.c.o:
	$(CC) $(OPTIMIZE) $(CFLAGS) $(INCLUDE) -c $<

.cpp.o:
	$(CPP) $(OPTIMIZE) $(CPPFLAGS) $(INCLUDE) -c $<

# programs to be made
TARGETS = dlog

all : $(TARGETS)

OBJS = dlog_main.o
HEADS =   dlog.hpp  timeStamp.hpp  basicEntry.hpp basicLogger.hpp

dlog_main.o: $(HEADS)

dlog: $(OBJS) $(HEADS)
	$(CPP) -o dlog $(OBJS) $(OPTIMIZE) $(CPPFLAGS) -L$(LIB_PATH) -lmxlib  $(MXLIB_EXLIBS) 
	
install:
	install dlog $(HOME)/bin
	
.PHONY: clean
clean:
	rm dlog
	rm -f *.o 
	rm -f *~
