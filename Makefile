#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = g++
CFLAGS  = -g -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: MessageProcessor

# To create the executable file count we need the object files
# main.o, MessageGetter.o, and Test.o:
#
MessageProcessor:  main.o MessageGetter.o Test.o 
	$(CC) $(CFLAGS) -o MessageProcessor main.o MessageGetter.o Test.o

# To create the object file main.o, we need the source
# files main.c, Structure.h, and MessageGetter.h:
#
main.o:  main.c Structure.h MessageGetter.h Test.h
	$(CC) $(CFLAGS) -c main.c

# To create the object file Test.o, we need the source files
# Test.c and Test.h:
#
Test.o:  Test.c Test.h 
	$(CC) $(CFLAGS) -c Test.c

# To create the object file MessageGetter.o, we need the source files
# MessageGetter.c and MessageGetter.h:
#
MessageGetter.o:  MessageGetter.c MessageGetter.h 
	$(CC) $(CFLAGS) -c MessageGetter.c

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lpthread -lm

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) MessageProcessor *.o *~
