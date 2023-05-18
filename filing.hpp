#include<iostream>
#include<fstream>
using namespace std;
int filing(int s) {
    //reading high score from file
    int high = 0;
    fstream scoring("scoring.txt", ios::in);
    if (!scoring)
    {
        cout << "File doesn't exist.";
    }
    else
    {
        scoring >> high;
        scoring.close();
    }

    // updating high score if necessary
    if (s > high)
    {
        high = s;
        // writing new high score to file
        scoring.open("scoring.txt", ios::out);
        if (!scoring)
        {
            cout << "Error while creating the file";
        }
        else
        {
            scoring << high;
            scoring.close();
        }
        //cout << endl << high << "high";
        return high;
    }
    else 
    {
        return high;
    }
}