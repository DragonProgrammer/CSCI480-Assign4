Process.o .d/Process.d : Process.cpp Process.hpp
Process.bin: Process.o Process.o
	$(CXX) $(CXXFLAGS) $(LIBARYFLAGS) -o $@ $^
