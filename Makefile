PREFIX ?= /usr/local
MODULE = sys/networking
LUAFILE  = init.lua
CFILE = internal.c
HEADERS  =

CFLAGS  += -Wall -Wextra
LDFLAGS += -dynamiclib -undefined dynamic_lookup

OFILE  := $(CFILE:c=o)
SOFILE := $(CFILE:c=so)

all: $(SOFILE)

install: install-library install-lua

build-cli:
	$(CC) main.c -o netspeed

install-cli:
	install $(PREFIX)/bin

$(SOFILE): $(OFILE) $(HEADERS)
	$(CC) $(OFILE) $(CFLAGS) $(LDFLAGS) -o $@

install-library: $(SOFILE)
	mkdir -p $(PREFIX)/lib/lua/5.2/mjolnir/_asm/$(MODULE)
	install -m 0644 $(SOFILE) $(PREFIX)/lib/lua/5.2/mjolnir/_asm/$(MODULE)

install-lua: $(LUAFILE)
	mkdir -p $(PREFIX)/share/lua/5.2/mjolnir/_asm/$(MODULE)
	install -m 0644 $(LUAFILE) $(PREFIX)/share/lua/5.2/mjolnir/_asm/$(MODULE)

uninstall:
	rm -fr $(PREFIX)/lib/lua/5.2/mjolnir/_asm/$(MODULE)/$(SOFILE)
	rm -fr $(PREFIX)/share/lua/5.2/mjolnir/_asm/$(MODULE)/$(LUAFILE)

clean:
	rm -rf $(OFILE) $(SOFILE)

.PHONY: all clean
