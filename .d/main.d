main.o .d/main.d : main.cpp Process.hpp
main.bin: main.o Process.o
	$(CXX) $(CXXFLAGS) $(LIBARYFLAGS) -o $@ $^
