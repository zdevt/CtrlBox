
LOCALCONFIG_FILE := ./mk
include $(LOCALCONFIG_FILE)

TESTIP ?= "172.16.129.252"

PROJ_EXCLUDE_DIRS := Common Objs

DIRS    := $(shell find . -maxdepth 1 -type d)
DIRS    := $(basename $(patsubst ./%,%,$(DIRS)))
DIRS    := $(filter-out $(PROJ_EXCLUDE_DIRS),$(DIRS))
DIRS    := $(sort $(DIRS))
SUBDIRS := $(DIRS)

DST     := MAINAPP 

all: f
	@for dir in $(SUBDIRS);do make -C $$dir -j8 -s || exit 1;done
	@$(AR) -rsc -o liball.a ./Objs/*.o
	@$(RANLIB) liball.a
	@$(CPP) Main.cpp -L. -lall $(CPPFLAGS) $(INC_FLAGS) $(LIB_FLAGS) $(DEF_FLAGS) -o $(DST)
#@$(CPP) Main.cpp $(OBJ_DIR)/*.o $(CPPFLAGS) $(INC_FLAGS) $(LIB_FLAGS) $(DEF_FLAGS) -o $(DST)
	@\cp $(DST) ../rootfs/app/
	@md5sum $(DST) >../rootfs/app/cksum
	@\cp $(DST) ../rootfs_min/app/
	@md5sum $(DST) >../rootfs_min/app/cksum
	@../GenUpgFile/gen MAINAPP 0x1 0x1 $(VER) MAINAPP.hs

dynamic:
	@for dir in $(SUBDIRS);do make -C $$dir -j8 -s || exit 1;done
	@$(CPP) -shared -fPIC -o liball.so ./Objs/*.o
	@$(CPP) Main.cpp $(CPPFLAGS) $(INC_FLAGS) $(LIB_FLAGS) $(DEF_FLAGS) -o $(DST) -Wl,-rpath . -L. -lall

test: all
	@../Test/upgrade MAINAPP.hs 192.168.0.103 17004

test1: all 
	@../Test/upgrade MAINAPP.hs $(TESTIP) 17004

f:
	@for dir in $(SUBDIRS);do make -C $$dir format -s > /dev/null || exit 1;done
	@./astyle *.cpp      $(CODE_FORMAT) > /dev/null
	@./astyle Common/*.h $(CODE_FORMAT) > /dev/null

t: f
	@find . -name "*.h" -o -name "*.c" -o -name "*.cc" -o -name "*.cpp" > cscope.files
	@cscope -Rbkq -i cscope.files
	@ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .

def:
	@echo $(AUTHOR)
	@echo $(AUTHORIP)
	@echo $(LOGINTIME)
	@echo $(MK_TIME)
	@echo $(VER)

clean:
	@for dir in $(SUBDIRS);do make -C $$dir clean -s || exit 1;done
	@rm -f $(DST) Objs/*.o core.* DebugBin/DebugAdmin
	@rm -f cscope* tags *.hs *.so *.a core

