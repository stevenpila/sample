CC=g++
CFLAGS=-c -Wall
LDFLAGS= \
	-L/usr/lib/

LDLIBS= \
	-lmysqlcppconn

SOURCE_PATH=../src

SOURCES= \
	$(SOURCE_PATH)/main.cpp
OBJECTS=$(SOURCES:.cpp=.o)

TARGET=sample

all: $(SOURCES) $(TARGET)
	echo -n "\nsuccessfully created $(TARGET)\n\n"

run:
	./$(TARGET)

clean:
	rm -rf $(SOURCE_PATH)/*.o $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) $(LDLIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
