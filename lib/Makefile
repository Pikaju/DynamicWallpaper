CC = g++
CC_FLAGS = -std=c++11

LIBRARY = $(OBJECT_DIRECTORY)/FastNoiseSIMD.a

SOURCE_DIRECTORY = src
OBJECT_DIRECTORY = bin

SOURCES = $(shell find $(SOURCE_DIRECTORY) -name "*.cpp")
OBJECTS = $(SOURCES:$(SOURCE_DIRECTORY)/%.cpp=$(OBJECT_DIRECTORY)/%.o)


$(LIBRARY): $(OBJECTS)
	mkdir -p "$(@D)"
	ar crf $(LIBRARY) $(OBJECTS)

# Special flags from the GitHub site

$(OBJECT_DIRECTORY)/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_sse2.o: $(SOURCE_DIRECTORY)/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_sse2.cpp
	mkdir -p "$(@D)"
	$(CC) $(CC_FLAGS) -msse2 -c $(SOURCE_DIRECTORY)/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_sse2.cpp -o $(OBJECT_DIRECTORY)/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_sse2.o

$(OBJECT_DIRECTORY)/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_sse41.o: $(SOURCE_DIRECTORY)/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_sse41.cpp
	mkdir -p "$(@D)"
	$(CC) $(CC_FLAGS) -msse4.1 -c $(SOURCE_DIRECTORY)/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_sse41.cpp -o $(OBJECT_DIRECTORY)/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_sse41.o

$(OBJECT_DIRECTORY)/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_avx2.o: $(SOURCE_DIRECTORY)/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_avx2.cpp
	mkdir -p "$(@D)"
	$(CC) $(CC_FLAGS) -march=core-avx2 -c $(SOURCE_DIRECTORY)/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_avx2.cpp -o $(OBJECT_DIRECTORY)/FastNoiseSIMD/FastNoiseSIMD/FastNoiseSIMD_avx2.o



$(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cpp
	mkdir -p "$(@D)"
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -f $(LIBRARY)
	rm -rf $(OBJECT_DIRECTORY)
