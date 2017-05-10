CFLAGS =  -I../include -DSIM_WITHOUT_QT_AT_ALL -Wall -fPIC -static

OS = $(shell uname -s)
ifeq ($(OS), Linux)
    CFLAGS += -D__linux -DLIN_VREP
else
    CFLAGS += -D__APPLE__ -DMAC_VREP
endif

all: 
    @rm -f bin/*.*
    @rm -f *.o 
    g++ $(CFLAGS) -c main.cpp -o main.o
    g++ $(CFLAGS) -c ../common/v_repLib.cpp -o v_repLib.o
    @mkdir -p bin
    g++ v_repLib.o main.o -o bin/vrep -lpthread -ldl -llua5.1
