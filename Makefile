LIBSRCS := $(wildcard lib/*.d16)
LIBSRCS := $(filter-out lib/brk.d16, $(LIBSRCS))
LIBS = $(patsubst %.d16,%.o,$(LIBSRCS))
LIBCSRCS = $(wildcard lib/*.c)
LIBS += $(patsubst %.c, %.o, $(LIBCSRCS))

SRCS := $(wildcard src/*.d16)
CSRCS := $(wildcard src/*.c)
OBJS = $(patsubst %.d16,%.o,$(SRCS))
OBJS += $(patsubst %.c,%.o,$(CSRCS))

CFLAGS=-Iinclude +/Users/mnolan/vc.config

all: munk
	d16-jit munk
munk: start.o $(OBJS) $(LIBS) lib/brk.o
	d16-ld $^ -o $@
%.o:%.c
	vc $(CFLAGS) -c $< -o $@
%.o:%.d16
	d16 $< -o $@
clean:
	rm -f munk
	rm -f src/*.o
	rm -f lib/*.o
.PHONY: clean all
