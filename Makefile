CC = g++  # Compile with g++
CFLAGS = -Wall -O2 `pkg-config --cflags opencv4`  # Include OpenCV flags at compile time
LDFLAGS = `pkg-config --libs opencv4` -lsndfile  # Link OpenCV and libsndfile library

TARGET = LSB  # object is LSB

# Source files
SRCS = main.cpp common.cpp msg_lsbto_picture.cpp text_lsbto_picture.cpp pic_lsbto_picture.cpp audio_lsbto_picture.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)  # Default target is TARGET

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)  # Link object files

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@  # Compile individual source files to object files

clean:
	rm -f $(TARGET) $(OBJS)  # Clean target and object files
