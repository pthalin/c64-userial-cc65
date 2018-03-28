SOURCES = main.c userial.c
ASOURCES = 
CC65_TARGET = c64
NAME = example
PROGRAM = $(NAME).prg
DISK = $(NAME).d64
C1541 = c1541
CC      = cl65
CFLAGS  = -t $(CC65_TARGET) -O -g -I../..
LDFLAGS = -t $(CC65_TARGET) -m $(PROGRAM).map -Ln $(PROGRAM).lbl -I../..

.PHONY: all clean assets
all: assets $(PROGRAM)

ifneq ($(MAKECMDGOALS),clean)
-include $(SOURCES:.c=.d)
endif

%.o: %.s
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(PROGRAM): $(SOURCES:.c=.o) $(ASOURCES:.s=.o)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(ASOURCES:.s=.o) $(SOURCES:.c=.o) $(SOURCES:.c=.d) $(PROGRAM) $(PROGRAM).map $(PROGRAM).lbl $(DISK)

run: all
	x64 $(PROGRAM)


.PHONY: disk
disk:   $(DISK)

$(DISK): all
	$(C1541) -format $(NAME),AA d64 $@
	$(C1541) -attach $@ -write $(PROGRAM)
