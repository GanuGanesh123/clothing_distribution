# Makefile for clothing distribution base code
# Sharlee Climer


CC      = g++
CFLAGS  = -g
TARGET  = clothing
OBJS    = clothing.o

$(TARGET):	$(OBJS)
		$(CC) -o $(TARGET) $(OBJS)

clothing.o:	clothing.cpp clothing.h timer.h
		$(CC) $(CFLAGS) -c clothing.cpp

clean:
		/bin/rm -f *.o $(TARGET)
