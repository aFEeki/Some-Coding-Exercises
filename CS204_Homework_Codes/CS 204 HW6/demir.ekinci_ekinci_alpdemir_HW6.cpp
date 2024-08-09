//Alp Demir Ekinci 31935
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <mutex>
#include <iomanip>
#include <thread>
#include <random>
using namespace std;
int target;
bool status = true;
bool hostflag = true;
int winnerid = -1;
vector<int> points;
mutex playermutex;
mutex printmutex;
int random_number(const int & min, const int & max) //rng function taken from lab code
{
    static mt19937 generator(time(0));
    uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}
void print_time() //prints time, taken from lab codes
{
    time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
    struct tm *ptm = new struct tm;
    localtime_s(ptm, &tt);
    cout << put_time(ptm,"%X");
}
void gaymer(int ID, int min, int max, chrono::system_clock::time_point start_time) //gamer thread function.
{
    this_thread::sleep_until(start_time); //sleeps all of the players until 3 seconds after the run time.
    while (hostflag) //iterates until reaching the last round
    {
        playermutex.lock();
        if (status == false) //status is used to check if the round has ended or not or is it available to be started
        {
            playermutex.unlock();
        }
        else
        {
            int guess = random_number(min, max);
            if (guess == target) //if the guess is correct
            {
                printmutex.lock();
                cout << "Player with id " << ID << " guessed " << guess << " correctly at: ";
                print_time();
                cout << endl;
                status = false;
                winnerid = ID;
                printmutex.unlock();
            }
            else //if the guess is not correct
            {
                printmutex.lock();
                cout << "Player with id " << ID << " guessed " << guess << " incorrectly at: ";
                print_time();
                cout << endl;
                printmutex.unlock();
            }
            playermutex.unlock();
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}
void host(int min, int max, int roundnum, chrono::system_clock::time_point start_time) //host thread function
{
    printmutex.lock(); //prints the 1st print outs
    cout << "---------------------------------------------------" << endl;
    cout << "Game started at: ";
    print_time();
    cout << endl;
    cout << "Round 1 will start 3 seconds later" << endl;
    target = random_number(min, max);
    cout << "Target is " << target << endl;
    printmutex.unlock();
    this_thread::sleep_until(start_time); //sleeps for 3 seconds
    for (int i = 2; i <= roundnum + 1; i++) //iterates for each round
    {
        if (status == false)
        {
            if (i == roundnum + 1) //if all of the rounds have ended
            {
                printmutex.lock();
                points[winnerid]++;
                hostflag = false;
                cout << "---------------------------------------------------" << endl;
                cout << "Game is over!" << endl;
                cout << "Leaderboard:" << endl;
                for (int i = 0; i < points.size(); i++)
                {
                    cout << "Player " << i << " has won " << points[i] << " times" << endl;
                }
                printmutex.unlock();
            }
            else //if there are still rounds to go through
            {
                printmutex.lock();
                points[winnerid]++;
                winnerid = -1;
                status = true;
                cout << "---------------------------------------------------" << endl;
                cout << "Round " << i << " started at: ";
                print_time();
                cout << endl;
                target = random_number(min, max);
                cout << "Target is " << target << endl;
                printmutex.unlock();
            }
        }
        else
        {
            i--;
        }
    }
}
int main()
{
    int playernum = 0; //all of the inputs required
    int roundnum = 0;
    int lowerbound = 0;
    int upperbound = 0;
    cout << "Please enter number of players" << endl;
    cin >> playernum;
    while (playernum < 1) //input checks
    {
        cout << "Number of players cannot be lower than 1!" << endl;
        cout << "Please enter number of players" << endl;
        cin >> playernum;
    }
    cout << "Please enter number of rounds" << endl;
    cin >> roundnum;
    while (roundnum < 1)
    {
        cout << "Number of rounds cannot be lower than 1!" << endl;
        cout << "Please enter number of rounds" << endl;
        cin >> roundnum;
    }
    cout << "Please enter the randomization range" << endl;
    cin >> lowerbound >> upperbound;
    while (lowerbound >= upperbound && lowerbound < 1)
    {
        cout << "Lower bound has to be smaller than or equal to higher bound" << endl;
        cout << "Please enter the randomization range" << endl;
        cin >> lowerbound >> upperbound;
    }
    chrono::system_clock::time_point start_time = chrono::system_clock::now() + chrono::seconds(3); //adds 3 seconds to the current time and sets it to the start time of the threads
    thread hostthread (host, lowerbound, upperbound, roundnum, start_time); //host thread declaration
    vector<thread> threads; //vector made of threads to store all the player threads
    for (int i = 0; i < playernum; i++) //declaration of gaymer threads
    {
        points.push_back(0);
        threads.push_back(thread(gaymer, i, lowerbound, upperbound, start_time));
    }
    for (int i = 0; i < threads.size(); i++) //join the gamer threads
    {
        threads[i].join();
    }
    hostthread.join(); //join the host thread
}
