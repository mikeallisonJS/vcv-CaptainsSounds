# Resolve RACK_DIR if not provided
ifndef RACK_DIR
  # Prefer Rack-SDK in project root if present
  ifneq (,$(wildcard Rack-SDK/plugin.mk))
    RACK_DIR := Rack-SDK
  else
    # Fallback to two directories above (typical when building inside Rack/plugins)
    RACK_DIR := ../..
  endif
endif

# Validate SDK matches host platform
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  EXPECTED_RACK_LIB := $(RACK_DIR)/libRack.dylib
else
  EXPECTED_RACK_LIB := $(RACK_DIR)/libRack.so
endif

ifeq (,$(wildcard $(EXPECTED_RACK_LIB)))
  $(error Rack SDK at '$(abspath $(RACK_DIR))' does not contain '$(notdir $(EXPECTED_RACK_LIB))' (host: $(UNAME_S)). Point RACK_DIR to the correct platform SDK.)
endif

moogFilters := dep/MoogLadders-master/src

# FLAGS will be passed to both the C and C++ compiler
FLAGS += -I$(moogFilters)
CFLAGS +=
CXXFLAGS += -std=c++17

# Careful about linking to shared libraries, since you can't assume much about the user's environment and library search path.
# Static libraries are fine, but they should be added to this plugin's build system.
LDFLAGS +=

# Add .cpp files to the build
SOURCES += $(wildcard src/*.cpp)

# Add files to the ZIP package when running `make dist`
# The compiled plugin and "plugin.json" are automatically added.
DISTRIBUTABLES += res/*.svg res/**/*.svg res/fonts/nunito/Nunito-Bold.ttf
DISTRIBUTABLES += $(wildcard LICENSE*)

OBJECTS +=

# Dependencies
DEPS += $(moogFilters)

$(moogFilters):
	cd dep && $(WGET) https://github.com/mikeallisonJS/MoogLadders/archive/master.zip
	cd dep && $(UNZIP) ./master.zip

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk
