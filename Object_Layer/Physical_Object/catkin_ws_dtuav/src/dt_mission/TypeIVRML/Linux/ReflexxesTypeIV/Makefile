# Makefile
# 
# Reflexxes GmbH
# Sandknoell 7
# D-24805 Hamdorf
# GERMANY
#
# http://www.reflexxes.com
#
# Author : Torsten Kroeger, <info@reflexxes.com>
# Date   : November 2011
#
#

include ../Makefile.global

export

# ********************************************************************************
# ********************************************************************************
# LINUX
# ********************************************************************************
# ********************************************************************************

ifeq ($(TARGET_OS),__LINUX__)

include ../TargetDependencies.global

export


# ---------- Objects ----------

ReflexxesAPI_SRCS         := $(shell find $(SRC_DIR)/ReflexxesAPI -name '*.cpp')
TypeIVRMLMath_SRCS        := $(shell find $(SRC_DIR)/TypeIVRMLMath -name '*.cpp')
TypeIVRMLPosition_SRCS    := $(shell find $(SRC_DIR)/TypeIVRMLPosition -name '*.cpp')
TypeIVRMLVelocity_SRCS    := $(shell find $(SRC_DIR)/TypeIVRMLVelocity -name '*.cpp')

ReflexxesAPI_OBJS         := $(patsubst $(SRC_DIR)/ReflexxesAPI/%.cpp, $(OBJ_DIR)/%.$(OBJECT_FILE_EXT), $(ReflexxesAPI_SRCS))
TypeIVRMLMath_OBJS        := $(patsubst $(SRC_DIR)/TypeIVRMLMath/%.cpp, $(OBJ_DIR)/%.$(OBJECT_FILE_EXT), $(TypeIVRMLMath_SRCS))
TypeIVRMLPosition_OBJS    := $(patsubst $(SRC_DIR)/TypeIVRMLPosition/%.cpp, $(OBJ_DIR)/%.$(OBJECT_FILE_EXT), $(TypeIVRMLPosition_SRCS))
TypeIVRMLVelocity_OBJS    := $(patsubst $(SRC_DIR)/TypeIVRMLVelocity/%.cpp, $(OBJ_DIR)/%.$(OBJECT_FILE_EXT), $(TypeIVRMLVelocity_SRCS))



$(OBJ_DIR)/%.$(OBJECT_FILE_EXT): $(SRC_DIR)/TypeIVRMLMath/%.cpp
	mkdir -p $(OBJ_DIR)
	@echo $(LINE1)
	$(CC) $< -o $@
	
$(OBJ_DIR)/%.$(OBJECT_FILE_EXT): $(SRC_DIR)/ReflexxesAPI/%.cpp
	mkdir -p $(OBJ_DIR)
	@echo $(LINE1)
	$(CC) $< -o $@
	
$(OBJ_DIR)/%.$(OBJECT_FILE_EXT): $(SRC_DIR)/TypeIVRMLPosition/%.cpp
	mkdir -p $(OBJ_DIR)
	@echo $(LINE1)
	$(CC) $< -o $@
	
$(OBJ_DIR)/%.$(OBJECT_FILE_EXT): $(SRC_DIR)/TypeIVRMLVelocity/%.cpp
	mkdir -p $(OBJ_DIR)
	@echo $(LINE1)
	$(CC) $< -o $@	


# -------- OutputFiles --------

$(LIB_DIR)/libReflexxesTypeIV.$(LIB_FILE_EXT): $(TypeIVRMLMath_OBJS) $(ReflexxesAPI_OBJS) $(TypeIVRMLPosition_OBJS) $(TypeIVRMLVelocity_OBJS)
	mkdir -p $(LIB_DIR)
	@echo $(LINE1)
	$(AR) $@ $^

# ****************************************************************
# Entry point for 'do_all'
# ****************************************************************

do_all: $(LIB_DIR)/libReflexxesTypeIV.$(LIB_FILE_EXT)
	@echo Built directory contents
	@echo $(LINE1)
	@echo Operating system: $(TARGET_OS) [$(VARIANT)]
	

# ****************************************************************
# Entry point for 'do_clean'
# ****************************************************************

do_clean:
	@echo $(LINE1)
	@echo Operating system: $(TARGET_OS) [$(VARIANT)]
	rm -f $(TypeIVRMLMath_OBJS) $(ReflexxesAPI_OBJS) $(TypeIVRMLPosition_OBJS) $(TypeIVRMLVelocity_OBJS)
	rm -f $(LIB_DIR)/libReflexxesTypeIV.$(LIB_FILE_EXT)

include ../ExternalTargets.global

endif

	
