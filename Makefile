SUBDIRS := src test

.PHONY: all clean unittest $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	$(MAKE) -C src clean
	$(MAKE) -C test clean

unittest: all
	./out/diskcopy_ut

