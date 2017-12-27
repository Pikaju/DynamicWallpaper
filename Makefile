CC = g++
CC_FLAGS =

EXECUTABLE = executable

SOURCE_DIRECTORY = src
OBJECT_DIRECTORY = bin

SOURCES = $(shell find $(SOURCE_DIRECTORY) -name "*.cpp")
OBJECTS = $(SOURCES:$(SOURCE_DIRECTORY)/%.cpp=$(OBJECT_DIRECTORY)/%.o)


$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CC_FLAGS) $(OBJECTS) -o $(EXECUTABLE)

$(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cpp
	mkdir -p "$(@D)"
	$(CC) $(CC_FLAGS) -c $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
	rm -rf $(OBJECT_DIRECTORY)
