LOCALCONFIG_FILE := ../mk
include $(LOCALCONFIG_FILE)

SRCS = $(wildcard *.cpp) 
OBJS = $(SRCS:.cpp=.o) 

all:$(OBJS)

%.o: %.cpp
	@$(CPP) $(CPPFLAGS) $(INC_FLAGS) $(LIB_FLAGS) $(DEF_FLAGS) -c $< -o $@
	@$(CP) $@ $(OBJ_DIR)

format:
	@$(PROJ_DIR)/astyle *.cpp $(CODE_FORMAT) >/dev/null
	@$(PROJ_DIR)/astyle *.h   $(CODE_FORMAT) >/dev/null

clean:
	$(RM) $(OBJS)
