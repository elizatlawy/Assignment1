#All Targets
all : splflix

splflix : bin/Session.o bin/Watchable.o bin/Action.o bin/User.o bin/Main.o
	g++ -o bin/splflix  bin/Session.o bin/Watchable.o bin/Action.o bin/User.o bin/Main.o

bin/Session.o : src/Session.cpp include/Session.h
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Session.o src/Session.cpp
	
bin/Action.o : src/Action.cpp include/Action.h
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Action.o src/Action.cpp
	
bin/Watchable.o : include/Watchable.h src/Watchable.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Watchable.o src/Watchable.cpp
	
bin/User.o : include/User.h src/User.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/User.o src/User.cpp
	
bin/Main.o : src/Main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Main.o src/Main.cpp

clean: 
	rm -f bin/*
