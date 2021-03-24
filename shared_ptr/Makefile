SRCDIR = src
OBJDIR = obj
BINDIR = bin

# target application
TARGET = main

# libraries to link to target
TARGET_LIBRARIES = -lpthread

# c++ standard to use
CXX_STANDARD = c++17

# boost include and library paths
IBOOST_PATH = ${HOME}/Projects/boost_1_75_0
LBOOST_PATH = ${HOME}/Projects/boost_1_75_0/stage/lib/

# compiler settings
CXX = g++
CXXFLAGS = -std=$(CXX_STANDARD) -I $(IBOOST_PATH) -L $(LBOOST_PATH)

# build array of source files and expected object files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst %.cpp,%.o,$(notdir $(SOURCES)))



# build all
all: $(TARGET)

# build target by linking object files and providing an rpath for boost libs
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/$@ $(addprefix $(OBJDIR)/,$(OBJECTS)) $(TARGET_LIBRARIES)

# build object files from source
$(OBJECTS): %.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $(OBJDIR)/$@

# clean up
.PHONY: clean
clean:
	rm -f $(BINDIR)/$(TARGET) $(addprefix $(OBJDIR)/,$(OBJECTS))
