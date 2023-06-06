CXX=g++

output: utility.o userInterface.o index.o loadingScreen.o mainMenuScreen.o exitScreen.o
	$(CXX) utility.o userInterface.o index.o loadingScreen.o mainMenuScreen.o exitScreen.o -o KCVisualizer

utility.o: sources/utility.cpp 
	$(CXX) -c sources/utility.cpp 

userInterface.o: sources/userInterface.cpp
	$(CXX) -c sources/userInterface.cpp

index.o: index.cpp
	$(CXX) -c index.cpp

loadingScreen.o: sources/loadingScreen.cpp 
	$(CXX) -c sources/loadingScreen.cpp 

mainMenuScreen.o: sources/mainMenuScreen.cpp 
	$(CXX) -c sources/mainMenuScreen.cpp 

exitScreen.o: sources/exitScreen.cpp
	$(CXX) -c sources/exitScreen.cpp

clean:
	del *.o KCVisualizer.exe