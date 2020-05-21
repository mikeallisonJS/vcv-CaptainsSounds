# If RACK_DIR is not defined when calling the Makefile, default to two directories above
RACK_DIR ?= ../..

# FLAGS will be passed to both the C and C++ compiler
FLAGS += -Idep/include
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

libfftw := dep/lib/libfftw3.a
OBJECTS += $(libfftw)

# Dependencies
DEPS += $(libfftw)

$(libfftw):
	cd dep && $(WGET) http://www.fftw.org/fftw-3.3.8.tar.gz
	cd dep && $(UNTAR) ./fftw-3.3.8.tar.gz
	cd dep/fftw-3.3.8 && $(CONFIGURE)
	cd dep/fftw-3.3.8 && $(MAKE)
	cd dep/fftw-3.3.8 && $(MAKE) install

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk
