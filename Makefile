# Top-level Makefile

include Makefile.inc

SUBDIRS=src tests
CLEANDIRS=$(SUBDIRS)

# Default recipe
all: subdirs

# Make Semantic Assurances
.PHONY: all clean subdirs $(SUBDIRS) $(CLEANDIRS)
tests: src

# Various phony tagets
subdirs: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

clean: $(CLEANDIRS)
$(CLEANDIRS):
	$(MAKE) -C $@ clean

VPATH=$(ROOTDIR)/tests
test: testing
	$<

debug-test: testing
	gdb $<
	
