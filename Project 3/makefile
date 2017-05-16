CXX = g++
CXXFLAGS = -Wall

proj3: DNA.o Sequencer.o driver.cpp
	$(CXX) $(CXXFLAGS) DNA.o Sequencer.o driver.cpp -o proj3

Sequencer.o: DNA.cpp DNA.h Sequencer.cpp Sequencer.h
	$(CXX) $(CXXFLAGS) -c Sequencer.cpp

DNA.o: DNA.cpp DNA.h
	$(CXX) $(CXXFLAGS) -c DNA.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj3

run1:
	./proj3 proj3_9.csv

run2:
	./proj3 proj3_60.csv

run3:
	./proj3 proj3_3000.csv

run4:
	./proj3 proj3_15000.csv
