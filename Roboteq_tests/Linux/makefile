CC=g++


all: sample.o m1_oscillate.o RoboteqDevice.o

sample.o: RoboteqDevice.o
	$(CC) RoboteqDevice.o ../Source/sample.cpp -o sample.o
	$(CC) RoboteqDevice.o ../Source/m1_oscillate.cpp -o m1_oscillate.o

RoboteqDevice.o: 
	$(CC) -c ../Source/RoboteqDevice.cpp

clean:
	rm *.o
