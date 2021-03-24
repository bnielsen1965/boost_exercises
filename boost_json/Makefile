SRCDIR := src
OBJDIR := obj
BINDIR := bin

# use VPATH with src subdirectories
SRCDIRS := $(shell find $(SRCDIR) -type d)
space :=
space +=
VPATH := $(subst $(space),:,$(addsuffix /, $(SRCDIRS)))

# target application
TARGET = main

# libraries to link to target
TARGET_LIBRARIES = -lboost_json -lboost_container

# boost include and library paths
IBOOST_PATH = ${HOME}/Projects/boost_1_75_0
LBOOST_PATH = ${HOME}/Projects/boost_1_75_0/stage/lib/

INCLUDES := $(addprefix -I, $(SRCDIRS))

# compiler settings
CXX = g++
CXXFLAGS = $(INCLUDES) -I $(IBOOST_PATH) -L $(LBOOST_PATH)

# build array of source files and expected object files
SOURCE_FILES = $(shell find $(SRCDIR)/ -type f -name '*.cpp')
SOURCES = $(SOURCE_FILES)
OBJECTS = $(patsubst %.cpp,%.o,$(notdir $(SOURCES)))


# build all
all: $(TARGET)

# build target by linking object files and providing an rpath for boost libs
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/$@ $(addprefix $(OBJDIR)/,$(OBJECTS)) $(TARGET_LIBRARIES)

# build object files from source
$(OBJECTS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $(OBJDIR)/$@

# clean up
.PHONY: clean
clean:
	rm -f $(BINDIR)/$(TARGET) $(addprefix $(OBJDIR)/,$(OBJECTS))


.PHONY: info
info: ;
	$(info $$SOURCES is [${SOURCES}])
	$(info $$OBJECTS is [${OBJECTS}])
	$(info $$INCLUDES is [${INCLUDES}])
	$(info $$VPATH is [${VPATH}])
