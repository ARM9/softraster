#DEBUG	:= 1

CC	:= gcc
AS	:= gcc
LD	:= gcc
GDB	:= gdb
DDD := ddd
LZSS	:= lzss

CFLAGS	:= -Wall -Wextra -pedantic -std=gnu99 -march=native -masm=intel
ASFLAGS	:= -march=native -masm=intel
LDFLAGS := 
LIBS	:= -lmingw32 -lSDL2main -lSDL2 -lm

ifeq (1,$(DEBUG))
  	CFLAGS := $(CFLAGS) -g -Og -DDEBUG
else
  	CFLAGS := $(CFLAGS) -O2 -fomit-frame-pointer
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

export OUTPUT	:= $(shell basename $(CURDIR))
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
	@rm -rf $(OFILES) $(OUTPUT) $(PRECOMPILED)

run: $(OUTPUT)
	./$(OUTPUT)

debug: $(OUTPUT)
	$(DDD) --args $(OUTPUT)

$(OUTPUT): $(PRECOMPILED) $(OFILES)
	$(LD) $(CFLAGS) -o $@ $(OFILES) $(LIBS)

$(PRECOMPILED) : include/precompiled.h
	$(CC) $(CFLAGS) $(INCLUDE) $<

