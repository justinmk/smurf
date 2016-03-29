# vim: set noet sw=4 ts=4
# ~/neovim/.deps/usr/bin/luajit

DEPS_DIR ?= $(shell pwd)/.deps
DEPS_PREFIX ?= $(DEPS_DIR)/usr
DEPS_BIN ?= $(DEPS_PREFIX)/bin

# Lua-related configuration
LUA_URL ?= http://www.lua.org/ftp/lua-5.1.5.tar.gz
LUAROCKS_URL ?= https://github.com/keplerproject/luarocks/archive/v2.2.0.tar.gz
LUA_TARGET ?= linux
LUA ?= $(DEPS_BIN)/lua
LUAROCKS ?= $(DEPS_BIN)/luarocks
BUSTED ?= $(DEPS_BIN)/busted
MSGPACK ?= $(DEPS_PREFIX)/lib/luarocks/rocks/lua-messagepack
COXPCALL ?= $(DEPS_PREFIX)/lib/luarocks/rocks/coxpcall
LUABIT ?= $(DEPS_PREFIX)/lib/luarocks/rocks/bit32

# Libuv configuration
LIBUV_URL ?= https://github.com/libuv/libuv/archive/v1.7.3.tar.gz
LIBUV ?= $(DEPS_PREFIX)/lib/libuv.a
LIBUV_LINK_FLAGS = $(shell PKG_CONFIG_PATH='$(DEPS_PREFIX)/lib/pkgconfig' pkg-config libuv --libs)

# Compilation
CC ?= gcc
CFLAGS ?= -g -fPIC -Wall -Wextra -Werror -Wconversion -Wextra \
	-Wstrict-prototypes -pedantic
LDFLAGS ?= -shared -fPIC
DEPS_INCLUDE_FLAGS ?= -I$(DEPS_PREFIX)/include

# Misc
# Options used by the 'valgrind' target, which runs the tests under valgrind
VALGRIND_OPTS ?= --log-file=valgrind.log --leak-check=yes --track-origins=yes
# Command that will download a file and pipe it's contents to stdout
FETCH ?= curl -L -o -
# Command that will gunzip/untar a file from stdin to the current directory,
# stripping one directory component
UNTGZ ?= tar xfz - --strip-components=1


all: run

deps: | $(LUABIT) $(LIBUV) $(MSGPACK) $(COXPCALL) $(BUSTED)

build:
	mcs ht.cs

run: | build
	mono ht.exe

test: all
	$(BUSTED) -v '--lpath=./?.lua;' '--cpath=./?.so;' -o gtest test

distclean: clean
	rm -rf $(DEPS_DIR)

$(BUSTED): | $(LUAROCKS)
	$(LUAROCKS) install busted
	$(LUAROCKS) install inspect  # helpful for debugging

$(MSGPACK): $(LUAROCKS)
	$(LUAROCKS) install lua-messagepack

$(COXPCALL): $(LUAROCKS)
	$(LUAROCKS) install coxpcall

$(LUABIT): $(LUAROCKS)
	$(LUAROCKS) install bit32

$(LUAROCKS): $(LUA)
	dir="$(DEPS_DIR)/src/luarocks"; \
	mkdir -p $$dir && cd $$dir && \
	$(FETCH) $(LUAROCKS_URL) | $(UNTGZ) && \
	./configure --prefix=$(DEPS_PREFIX) --force-config \
		--with-lua=$(DEPS_PREFIX) && make bootstrap

$(LUA):
	dir="$(DEPS_DIR)/src/lua"; \
	mkdir -p $$dir && cd $$dir && \
	$(FETCH) $(LUA_URL) | $(UNTGZ) && \
	sed -i -e '/^CFLAGS/s/-O2/-g/' src/Makefile && \
	make $(LUA_TARGET) install INSTALL_TOP=$(DEPS_PREFIX)

$(LIBUV):
	dir="$(DEPS_DIR)/src/libuv"; \
	mkdir -p $$dir && cd $$dir && \
	$(FETCH) $(LIBUV_URL) | $(UNTGZ) && \
	./autogen.sh && ./configure --with-pic --disable-shared \
		--prefix=$(DEPS_PREFIX) && make install

$(DEPS_DIR)/src/libuv:
	mkdir -p $@ && cd $@ && \
	$(FETCH) $(LIBUV_URL) | $(UNTGZ) || rm -rf $@
 
.PHONY: all deps test valgrind clean distclean

