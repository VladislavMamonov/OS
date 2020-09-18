all: bin/File_Manager


bin/File_Manager: build/main.o build/FileManager.o
	g++ -Wall -g build/main.o build/FileManager.o -o bin/File_Manager

build/main.o: src/main.cpp
	g++ -Wall -c -g src/main.cpp -o build/main.o

build/FileManager.o: src/FileManager.cpp
	g++ -Wall -c -g src/FileManager.cpp -o build/FileManager.o


clean:
	rm -rf build/*.o bin/FileManager
