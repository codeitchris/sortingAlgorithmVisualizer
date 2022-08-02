default:
	clang++ -std=c++11 -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -lraylib -lm -lpthread -ldl -lm -lpthread -ldl main.cpp -o main