all: bin/File_Manager


bin/File_Manager: build/main.o build/FManager.o
	g++ -Wall -g build/main.o build/FManager.o -o bin/File_Manager

build/main.o: src/main.cpp
	g++ -Wall -c -g src/main.cpp -o build/main.o

build/FManager.o: src/FManager.cpp
	g++ -Wall -c -g src/FManager.cpp -o build/FManager.o


clean:
	rm -rf build/*.o bin/FileManager
