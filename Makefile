CXX=g++

output: utility.o index.o loadingScreen.o
	$(CXX) utility.o index.o loadingScreen.o -o KCVisualizer

utility.o: sources/utility.cpp headers/utility.h
	$(CXX) -c sources/utility.cpp headers/utility.h

index.o: index.cpp
	$(CXX) -c index.cpp

loadingScreen.o: sources/loadingScreen.cpp headers/loadingScreen.h
	$(CXX) -c sources/loadingScreen.cpp headers/loadingScreen.h

clean:
	del *.o KCVisualizer.exe