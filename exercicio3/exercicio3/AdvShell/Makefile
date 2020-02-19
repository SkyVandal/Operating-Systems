# Makefile, versao 1
# Sistemas Operativos, DEI/IST/ULisboa 2018-19

SOURCES = CircuitRouter-AdvShell.c
SOURCES2= CircuitRouter-Client.c
SOURCES+= ../lib/commandlinereader.c ../lib/vector.c
OBJS = $(SOURCES:%.c=%.o)
OBJS2 = $(SOURCES2:%.c=%.o)
CC   = gcc
CFLAGS =-Wall -std=gnu99 -I../
LDFLAGS=-lm
TARGET = CircuitRouter-SimpleShell
TARGET2 = CircuitRouter-Client

all: $(TARGET) $(TARGET2) CircuitRouter-SeqSolver

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS)

$(TARGET2): $(OBJS2)
	$(CC) $(CFLAGS) $^ -o $(TARGET2) $(LDFLAGS)

CircuitRouter-AdvShell.o: CircuitRouter-AdvShell.c CircuitRouter-AdvShell.h ../lib/commandlinereader.h ../lib/vector.h
../lib/commandlinereader.o: ../lib/commandlinereader.c ../lib/commandlinereader.h
../lib/vector.o: ../lib/vector.c ../lib/vector.h ../lib/types.h ../lib/utility.h

$(OBJS):
	$(CC) $(CFLAGS) -c -o $@ $<

CircuitRouter-Client.o: CircuitRouter-Client.c

$(OBJS2):
	$(CC) $(CFLAGS) -c -o $@ $<

CircuitRouter-SeqSolver:
	(cd ../SeqSolver/ && make)

clean:
	@echo Cleaning...
	rm -f $(OBJS) $(TARGET)
	rm -f $(OBJS2) $(TARGET2)
	(cd ../CircuitRouter-SeqSolver/ && make clean)
