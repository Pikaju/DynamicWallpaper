CC = g++
CC_FLAGS = -std=c++17 -I$(INCLUDE_DIRECTORY) -O2

EXECUTABLE = executable

SOURCE_DIRECTORY = src
LIBRARY_DIRECTORY = lib
INCLUDE_DIRECTORY = $(LIBRARY_DIRECTORY)/src/
OBJECT_DIRECTORY = bin

SOURCES = $(shell find $(SOURCE_DIRECTORY) -name "*.cpp")
OBJECTS = $(SOURCES:$(SOURCE_DIRECTORY)/%.cpp=$(OBJECT_DIRECTORY)/%.o)


$(EXECUTABLE): $(OBJECTS) $(LIBRARY_DIRECTORY)/bin/FastNoiseSIMD.a
	$(CC) $(CC_FLAGS) $(OBJECTS) $(wildcard $(LIBRARY_DIRECTORY)/bin/*.a) -o $(EXECUTABLE)

$(LIBRARY_DIRECTORY)/bin/%.a:
	$(MAKE) -C $(LIBRARY_DIRECTORY)

$(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cpp
	mkdir -p "$(@D)"
	$(CC) $(CC_FLAGS) -I$(INCLUDE_DIRECTORY) -c $< -o $@


run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean_libraries:
	$(MAKE) clean -C $(LIBRARY_DIRECTORY)

clean_bin:
	rm -rf $(OBJECT_DIRECTORY)

clean: clean_libraries clean_bin
	rm -f $(EXECUTABLE)
