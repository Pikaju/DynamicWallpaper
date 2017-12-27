CC = g++
CC_FLAGS = -std=c++11


SOURCE_DIRECTORY = src
OBJECT_DIRECTORY = bin

FASTNOISE_SIMD_SOURCES = $(shell find $(SOURCE_DIRECTORY)/FastNoiseSIMD -name "*.cpp")
FASTNOISE_SIMD_OBJECTS = $(FASTNOISE_SIMD_SOURCES:$(SOURCE_DIRECTORY)/%.cpp=$(OBJECT_DIRECTORY)/%.o)

STB_SOURCES = $(shell find $(SOURCE_DIRECTORY)/stb -name "*.cpp")
STB_OBJECTS = $(STB_SOURCES:$(SOURCE_DIRECTORY)/%.cpp=$(OBJECT_DIRECTORY)/%.o)


all: $(OBJECT_DIRECTORY)/FastNoiseSIMD.a $(OBJECT_DIRECTORY)/stb_image_write.a

$(OBJECT_DIRECTORY)/FastNoiseSIMD.a: $(FASTNOISE_SIMD_OBJECTS)
	mkdir -p "$(@D)"
	ar crf $@ $(FASTNOISE_SIMD_OBJECTS)

$(OBJECT_DIRECTORY)/stb_image_write.a: $(STB_OBJECTS)
	mkdir -p "$(@D)"
	ar crf $@ $(STB_OBJECTS)


# Special flags from the FastNoiseSIMD GitHub site

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
	rm -rf $(OBJECT_DIRECTORY)
