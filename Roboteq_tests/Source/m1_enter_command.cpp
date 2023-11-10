#include <iostream>
#include <stdio.h>
#include <string.h>
#include <chrono>

#include "RoboteqDevice.h"
#include "ErrorCodes.h"
#include "Constants.h"

using namespace std;

// motor relative position command information:
/* Syntax Serial: !G [nn] mm
Syntax Scripting: setcommand(_G, nn, mm)
setcommand(_GO, nn, mm)
Number of Arguments: 2
Argument 1: Channel
Min: 1 Max: Total Number of Motors
Commands Reference200 Advanced Digital Motor Controller User Manual V2.1, December 3, 2020
Argument 2: Value Type: Signed 32-bit
Min: -1000 Max: 1000 */
// show me a simple loop that runs for 3 seconds, and then stops, waiting 500ms between each iteration.

// Simple function, will send motor full left position, then full right, then center.
// Each command is ran continuously for 3 seconds before moving to the next command.
RoboteqDevice connectDevice(string port)
{
    RoboteqDevice device;
    int status = device.Connect(port);

    if (status != RQ_SUCCESS)
    {
        cout << "Error connecting to device: " << status << "." << endl;
        return 1;
    }
    // return reference to device
    return device;
}


int ExecuteInput(string port)
{
    cout << endl
         << "Motor Oscillate:" << endl;
    cout << "------------------------" << endl;
    string response = "";
    RoboteqDevice device;
    int status = device.Connect(port);

    if (status != RQ_SUCCESS)
    {
        cout << "Error connecting to device: " << status << "." << endl;
        return 1;
    }

    // check stdin in loop
    string input;
    int command = 0;

    while (true)
    {
        // check if there is any input
        // check if int after eof
        if (cin.peek() != EOF)        {
            // read input
            cin >> input;
            // check if input is "exit"
            if (input == "exit")
                return 0;
        }
        else
        {
            // verify that input is int
            // if not, break
            try
            {
                command = stoi(input);
                cout << "- New Motor Position: SetCommand(_G, 1, " << command << ")...";
                // todo: call function based on command
            }
            catch (...)
            {
                cout << "Invalid input. Please try again!\n";
            }
        }
        // call motorcommand function
        if ((status = device.SetCommand(_G, 1, -1000)) != RQ_SUCCESS)
            cout << "failed --> " << status << endl;
        else
            cout << "succeeded." << endl;


        // sleep for 100ms
        sleepms(100);
    }
}

int main(int argc, char **argv)
{
#ifdef _WIN32
    // Windows
    string port = "COM1";
#endif

#ifdef __linux__
    // Linux
    string port = "/dev/ttyS4";
#endif

    if (argc > 1)
        port = argv[1];



    return ExecuteInput(port);
}