CPP = g++
BIN = read_write
OBJ = obj/main.o obj/User.o obj/Message.o obj/Logic.o obj/File.o
LINKOBJ = $(OBJ)
CXXFLAGS = -std=gnu++17 -Wall -Wextra


all: $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

obj/main.o: src/main.cpp
	$(CPP) -c src/main.cpp -o obj/main.o $(CXXFLAGS)

obj/User.o: src/User.cpp
	$(CPP) -c src/User.cpp -o obj/User.o $(CXXFLAGS)

obj/Message.o: src/Message.cpp
	$(CPP) -c src/Message.cpp -o obj/Message.o $(CXXFLAGS)

obj/Logic.o: src/Logic.cpp
	$(CPP) -c src/Logic.cpp -o obj/Logic.o $(CXXFLAGS)

obj/File.o: src/File.cpp
	$(CPP) -c src/File.cpp -o obj/File.o $(CXXFLAGS)

clean:
	rm obj/*.o