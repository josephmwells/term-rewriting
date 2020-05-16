
all:
	g++ test_display.cpp -o display
	g++ test_basic.cpp -o basic
	g++ test_polinomial.cpp -o polinomial
	g++ test_boolean.cpp -o boolean

basic:
	g++ test_basic.cpp -o basic

mac-all:
	clang++ -std=c++17 test_display.cpp -o display
	clang++ -std=c++17 test_basic.cpp -o basic 
	clang++ -std=c++17 test_polinomial.cpp -o polinomial 
	clang++ -std=c++17 test_boolean.cpp -o boolean 
