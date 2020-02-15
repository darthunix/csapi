EXTENSION = csapi
MODULES = csapi
DATA = csapi--0.1.sql

OBJS = src/csapi.o src/hooks.o

ifdef USE_PGXS
override PG_CPPFLAGS += -I$(CURDIR)/src/include
else
override PG_CPPFLAGS += -I$(top_srcdir)/$(subdir)/src/include
endif


MODULE_big = csapi
PG_CPPFLAGS = -g -O2

PG_CONFIG = /Users/darthunix/git/builds/postgres/bin/pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)