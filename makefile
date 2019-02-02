#
# Main makefile
#

CC      := g++
CFLAGS  := -std=c++17 -MMD -MP -Wall
LD      := g++
LDFLAGS :=

TARGET  := code
LIB     :=

SRCDIR  := src
SRCEXT  := cpp
OUTDIR  := out
OUTEXT  := o
INCDIR  := inc
INCEXT  := d
BINDIR  := bin

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT) ! -wholename src/cpp-base64/test.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%,$(OUTDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OUTEXT)))

all: $(BINDIR)/$(TARGET) docu

docu:
	$(MAKE) -C doc all

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) $^ $(LIB) -o $@

$(OUTDIR)/%.$(OUTEXT): $(SRCDIR)/%.$(SRCEXT)
	@dirname $@ | xargs mkdir -p
	$(CC) $(CFLAGS) -I ./$(SRCDIR) -I ./$(INCDIR) -c $< -o $@

clean:
	rm -r $(OUTDIR)/* $(BINDIR)/$(TARGET)

-include $(OBJECTS:%.$(OUTEXT)=%.$(INCEXT))
