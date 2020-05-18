# If RACK_DIR is not defined when calling the Makefile, default to two directories above
RACK_DIR ?= ../..

# FLAGS will be passed to both the C and C++ compiler
FLAGS +=
CFLAGS +=
CXXFLAGS +=

# Careful about linking to shared libraries, since you can't assume much about the user's environment and library search path.
# Static libraries are fine, but they should be added to this plugin's build system.
LDFLAGS +=

# Add .cpp files to the build
SOURCES += $(wildcard src/*.cpp)

# Add files to the ZIP package when running `make dist`
# The compiled plugin and "plugin.json" are automatically added.
DISTRIBUTABLES += res
DISTRIBUTABLES += $(wildcard LICENSE*)

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk

# Dependencies
DEPS += $(libsamplerate)

$(libsamplerate):
	$(WGET) https://github.com/kfrlib/kfr/archive/4.2.0.tar.gz -o kfr.tar.gz
	cd dep && $(UNTAR) ../kfr.tar.gz
	cd dep/kfr && $(CONFIGURE)
	cd dep/kfr && $(MAKE)
	cd dep/kfr && $(MAKE) install