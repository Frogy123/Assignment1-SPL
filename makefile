all: main

#tool invocations
#Executable "main" depends on the files main.o and Auxiliary.o.
main: bin/main.o bin/Auxiliary.o
	@echo 'Building target: main'
	@echo 'Invoking: GCC C++ Linker'
	g++ -o bin/main bin/main.o bin/Auxiliary.o
	@echo 'Finished building target: main'
	@echo ' '

#Depends on the source and header files
bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp

#Depends on the source and header files
bin/Auxiliary.o: src/Auxiliary.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Auxiliary.o src/Auxiliary.cpp
	
#clean the build directory
clean:
	rm -f bin/*