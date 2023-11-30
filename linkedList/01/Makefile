sources := main.cpp

CC = g++
LD = $(CC)

INCFLAGS =
CFLAGS   = -c $(INCFLAGS)
LDFLAGS  = -o
GDBFLAGS = -g

target  := main
targets := $(target)

# Compile
.cpp.o:
	$(CC) $(CFLAGS) $<

all: $(targets)
main: $(sources:.cpp=.o)
	$(CC) $(LDFLAGS) $@ $(notdir $^)


clean:
	/bin/rm -rf $(target) $(notdir $(sources:.cpp=.o))
# END OF FILE
