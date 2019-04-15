VPATH := src

udp : src/main.o
	$(CXX) -o $@ $^

src/main.o : src/main.cpp
	$(CXX) -o $@ -c $^

clean :
	@rm udp src/main.o

