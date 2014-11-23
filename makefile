#DEBUG	:= 1

CC	:= gcc
AS	:= as
LD	:= gcc
GDB	:= gdb
DDD := ddd

CFLAGS	:= -Wall -Wextra -pedantic -std=gnu99 -march=native
ASFLAGS	:= 
LDFLAGS := 
LIBS	:= -lmingw32 -lSDL2main -lSDL2 -lm

ifeq (1,$(DEBUG))
  	CFLAGS := $(CFLAGS) -g -O0 -DDEBUG
else
  	CFLAGS := $(CFLAGS) -O2 -fomit-frame-pointer
endif

SOURCES		:= src
INCLUDES	:= include

CFILES	:= $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
SFILES	:= $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
OFILES	:= $(CFILES:.c=.o) $(SFILES:.s=.o)
PRECOMPILED	:= include/precompiled.h.gch

export VPATH	:= $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
export INCLUDE	:= $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir))

export OUTPUT	:= $(shell basename $(CURDIR))
#--------------------------------------
%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

%.o : %.s
	$(AS) $(ASFLAGS) $(INCLUDE) -o $@ $<
#--------------------------------------
.PHONY: clean run

all: $(OUTPUT)

clean:
	@rm -rf $(OFILES) $(OUTPUT) $(PRECOMPILED)

run: $(OUTPUT)
	./$(OUTPUT)

debug: $(OUTPUT)
	$(DDD) --args $(OUTPUT)

$(OUTPUT): $(PRECOMPILED) $(OFILES)
	$(LD) $(CFLAGS) -o $@ $(OFILES) $(LIBS)

$(PRECOMPILED) : include/precompiled.h
	$(CC) $(CFLAGS) $(INCLUDE) $<

