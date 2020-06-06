# If RACK_DIR is not defined when calling the Makefile, default to two directories above
RACK_DIR ?= ../..

moogFilters := dep/MoogLadders-master/src

# FLAGS will be passed to both the C and C++ compiler
FLAGS += -I$(moogFilters)
CFLAGS +=
CXXFLAGS =  -std=c++17

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
	cd dep && $(WGET) https://github.com/captainssounds/MoogLadders/archive/master.zip
	cd dep && $(UNZIP) ./master.zip

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk
