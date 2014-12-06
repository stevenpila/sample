CC=g++
CFLAGS=-c -Wall
LDFLAGS= \
	-L/usr/lib/

LDLIBS= \
	-lmysqlcppconn \
	-lboost_system

SOURCE_PATH=../src

INCLUDES= \
	-I/home/nekkapajigar/Documents/Programming/git/sample/src/include
SOURCES= \
	$(SOURCE_PATH)/main.cpp \
	$(SOURCE_PATH)/Database.cpp \
	$(SOURCE_PATH)/Logger.cpp
OBJECTS=$(SOURCES:.cpp=.o)

TARGET=sample

all: clean build

build: $(SOURCES) $(TARGET)
	@echo -n "\nsuccessfully created $(TARGET)\n\n"
run:
	@echo -n "\nrunning $(TARGET)...\n\n"
	@./$(TARGET)

clean:
	rm -rf $(SOURCE_PATH)/*.o $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) $(LDLIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@
