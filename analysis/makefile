CC      = gcc -std=c11 -g
LFLAGS  =
CFLAGS  = -pipe \
	  -ggdb3 -Wstrict-overflow=5 -fstack-protector-all \
    -W -Wall -Wextra \
	  -Wbad-function-cast \
	  -Wcast-align \
	  -Wcast-qual \
	  -Wconversion \
	  -Wfloat-equal \
	  -Wformat-y2k \
	  -Winit-self \
	  -Winline \
	  -Winvalid-pch \
	  -Wmissing-declarations \
	  -Wmissing-field-initializers \
	  -Wmissing-format-attribute \
	  -Wmissing-include-dirs \
	  -Wmissing-noreturn \
	  -Wmissing-prototypes \
	  -Wnested-externs \
	  -Wnormalized=nfc \
	  -Wold-style-definition \
	  -Woverlength-strings \
	  -Wpacked \
	  -Wpadded \
	  -Wpointer-arith \
	  -Wredundant-decls \
	  -Wshadow \
	  -Wsign-compare \
	  -Wstack-protector \
	  -Wstrict-aliasing=2 \
	  -Wstrict-prototypes \
	  -Wundef \
	  -Wunsafe-loop-optimizations \
	  -Wvolatile-register-var \
	  -Wwrite-strings

#------------------------------------------------------------------------------
PROG = analysis
OBJS = functions.o \
       $(PROG).o
#------------------------------------------------------------------------------
.PHONY : all clean
#------------------------------------------------------------------------------
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

all: $(PROG)

$(PROG):  $(PROG).o

$(PROG): $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)
#------------------------------------------------------------------------------
clean :
	@echo "Limpando ...."
	@rm -f *~ *.bak *.tmp

purge:   clean
	@echo "Faxina ...."
	@rm -f *.o core a.out
	@rm -f $(PROG)
