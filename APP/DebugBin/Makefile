
LOCALCONFIG_FILE := ../mk
include $(LOCALCONFIG_FILE)

EXEC:=DebugAdmin

all:
	@$(CPP) *.cpp -o $(EXEC) -s
	@\cp DebugAdmin ../../rootfs/bin
	@\cp DebugAdmin ../../rootfs_min/bin

format:
	@$(PROJ_DIR)/astyle *.cpp $(CODE_FORMAT) >/dev/null
	@$(PROJ_DIR)/astyle *.h   $(CODE_FORMAT) >/dev/null

clean:
	@rm -f $(EXEC)

