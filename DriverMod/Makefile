
DIRS := $(shell find . -maxdepth 1 -type d)
DIRS := $(basename $(patsubst ./%,%,$(DIRS)))
DIRS := $(sort $(DIRS))


SUBDIRS := $(DIRS)

all:$(SUBDIRS)
	@for dir in $(SUBDIRS);do make -C $$dir -s || exit 1;done

f:$(SUBDIRS)
	@for dir in $(SUBDIRS);do make -C $$dir f -s || exit 1;done

clean:
	@for dir in $(SUBDIRS);do make -C $$dir clean -s || exit 1;done
	
