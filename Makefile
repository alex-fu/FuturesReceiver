CXX = g++
INC = -I./include
LIB = -L./lib64 -lthostmduserapi -lthosttraderapi
SRC = src/CTPMdUserSpi.cpp src/CTPTraderSpi.cpp src/testCTPMdUserSpi.cpp src/testCTPTraderSpi.cpp src/test.cpp
BIN = ./bin
CFLAGS = -g -Wall -fPIC -D_DEBUG
TARGET = test

all:$(TARGET)
	cp $(TARGET) $(BIN)
$(TARGET):$(SRC)
	$(CXX) $(CFLAGS) -o $(TARGET) $(INC) $(SRC) $(LIB)
clean:
	rm -f $(BIN)/* *.o $(TARGET)
