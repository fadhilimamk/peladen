all: 
	g++ -o bin/peladen src/peladen.cpp -levent
	./bin/peladen
make:
	g++ -o bin/peladen src/peladen.cpp -levent
clean:
	rm bin/peladen