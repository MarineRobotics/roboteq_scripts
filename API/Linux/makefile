CC=g++


all: sample.o

sample.o: RoboteqDevice.o
	$(CC) RoboteqDevice.o ../Source/sample.cpp -o sample.o

RoboteqDevice.o: 
	$(CC) -c ../Source/RoboteqDevice.cpp

clean:
	rm *.o
