BASE_NAME := rush-hour
TARGET_DIR = .
TARGET := $(TARGET_DIR)/$(BASE_NAME) 
TARGET_ARCHIVE := $(BASE_NAME).tar.gz
MAIN_SRC_FILES := $(wildcard *.cpp)
MAIN_OBJ_FILES := $(patsubst %.cpp,%.o,$(MAIN_SRC_FILES))
ENGINE_BASE_NAME := engine
ENGINE_DIR := ../$(ENGINE_BASE_NAME)
ENGINE_LIB_NAME := $(ENGINE_BASE_NAME)
ENGINE_LIB_FILENAME := lib$(ENGINE_LIB_NAME).so
ENGINE_LIB_PATH := ../engine/$(ENGINE_LIB_FILENAME)
DEPENDENCIES_DIR := dependencies

CXX = g++
CXX_FLAGS = -std=c++11 -O2
CXX_FLAGS += -I$(ENGINE_DIR)
LDFLAGS = -L$(ENGINE_DIR) -Wl,-rpath=./$(ENGINE_BASE_NAME) -l$(ENGINE_LIB_NAME)
TAR_GZ = tar zcvf

package: $(TARGET_ARCHIVE)
	@echo "all done!"

$(TARGET_ARCHIVE): $(TARGET)
	# package your distribution tar gz archive here with the necessary distribution artifacts
	$(TAR_GZ) $(TARGET_ARCHIVE) $(TARGET) $(ENGINE_LIB_PATH)
	@echo "$(TARGET) package done!"

$(TARGET): $(MAIN_OBJ_FILES) $(ENGINE_LIB_FILENAME)
	# build your client here
	$(CXX) $(CXX_FLAGS) -o $(TARGET) $(MAIN_OBJ_FILES) $(LDFLAGS)
	@echo "$(TARGET) compile done!"

%.o: %.cpp
	# compile your sources here
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

$(ENGINE_LIB_FILENAME):
	# Build the engine library
	$(MAKE) -C $(ENGINE_DIR)

clean:
	@rm -f $(TARGET_ARCHIVE)
	@rm -f $(TARGET)
	@rm -f $(MAIN_OBJ_FILES)
	$(MAKE) -C $(ENGINE_DIR) clean

.PHONY: clean package debug

