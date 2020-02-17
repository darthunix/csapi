EXTENSION = pg_vx
MODULES = pg_vx
DATA = pg_vx--0.1.sql

OBJS = src/pg_vx.o src/hooks.o src/cscan.o

ifdef USE_PGXS
override PG_CPPFLAGS += -I$(CURDIR)/src/include
else
override PG_CPPFLAGS += -I$(top_srcdir)/$(subdir)/src/include
endif


MODULE_big = pg_vx
PG_CPPFLAGS = -g -O2

PG_CONFIG = /Users/darthunix/git/builds/postgres/bin/pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)