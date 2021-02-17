SANFLAGS += -fsanitize=address
CXXFLAGS += -Wall -g -std=c++14 -pedantic $(SANFLAGS)
LDFLAGS += $(SANFLAGS)
main:	main.o Memory.o Instruction.o HelperFunctions.o Pipeline.o RegisterFile.o FetchUnit.o IQueue.o Execute.o Stats.o
	$(CXX) -o $@ $^ $(LDFLAGS)
.phony: clean
clean:
	$(RM) main *.o