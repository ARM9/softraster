DEBUG	:= 1

CC	:= gcc
AS	:= gcc
LD	:= gcc
GDB	:= gdb
DDD := ddd
PROF	:= gprof
LZSS	:= lzss

CFLAGS	:= -Wall -Wextra -pedantic -std=gnu99 -march=native -masm=intel
ASFLAGS	:= -march=native -masm=intel
LDFLAGS := 

ifeq (1,$(DEBUG))
  	CFLAGS	:= $(CFLAGS) -g -Og -DDEBUG
else
  	CFLAGS := $(CFLAGS) -O2 -pg
#-fomit-frame-pointer 
	LDFLAGS := $(LDFLAGS) -pg
#-s
endif

ifeq ($(OS),Windows_NT)
	LIBS	:= -lmingw32 -lSDL2main -lSDL2 -lm
	export OUTPUT	:= $(shell basename $(CURDIR)).exe
else
	LIBS	:= -lSDL2main -lSDL2 -lm
	export OUTPUT	:= $(shell basename $(CURDIR))
endif

SOURCES		:= src gfx
INCLUDES	:= include
DATA		:= data gfx
GFX			:= gfx

CFILES		:= $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
SFILES		:= $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:= $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.bin)))
OFILES		:= $(CFILES:%.c=build/%.o) $(SFILES:%.s=build/%.o)
PRECOMPILED	:= include/precompiled.h.gch

export VPATH	:= $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
export INCLUDE	:= $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir))
#--------------------------------------
build/%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

build/%.o : %.s
	$(AS) $(ASFLAGS) $(INCLUDE) -c $< -o $@
#--------------------------------------
.PHONY: clean run

all: build $(OUTPUT)

build:
	@mkdir -p $@

clean:
	@echo cleaning
	@rm -rf $(OFILES) $(OUTPUT) $(PRECOMPILED)

run: all
	./$(OUTPUT)

debug: all
	$(GDB) $(OUTPUT)
#	$(DDD) --args $(OUTPUT)

prof: all
	$(PROF) -b $(OUTPUT) > profile.txt

$(OUTPUT): $(PRECOMPILED) $(OFILES)
	@echo linking $@
	$(LD) $(CFLAGS) $(LDFLAGS) -o $@ $(OFILES) $(LIBS)

$(PRECOMPILED) : include/precompiled.h
	$(CC) $(CFLAGS) $(INCLUDE) $<

