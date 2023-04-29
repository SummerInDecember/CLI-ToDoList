#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string version = "1.0.0";

void toDoList(vector<string> goals, vector<bool> doneOrNot, int amountOfGoals){


    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";

    string doneOrDonent;
    
    for(int i = 0; i < amountOfGoals; i++){
         if(doneOrNot[i] == true){
            doneOrDonent = "done";
         }
         else{
            doneOrDonent = "not done";
         }
        cout << "[++]Goal nº " << i + 1 << ": " << goals[i] << "(" << doneOrDonent << ")" << endl;
    }
    


    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";

}

int getFirstGoalNumber(){
    int amountOfGoals;
    ofstream hasItBeenRunnedCookie("hasItBeenRunnedCookie.txt");
    ofstream amountOfGoalsCookie("amountOfGoalsCookie.txt");

    do{
        cout << "[++]How many goals do you have: ";
        cin >> amountOfGoals;
        if(amountOfGoals < 100000 && amountOfGoals > 0){
            amountOfGoalsCookie << amountOfGoals << endl;
            amountOfGoalsCookie.close();
            hasItBeenRunnedCookie << "true" << endl;
            return amountOfGoals;
            break;
        }
        else if(amountOfGoals > 100000 || amountOfGoals < 0 || amountOfGoals == 0){
            cout << "[««»»]That is not a valdi option, the amount must be bigger that 0 and smaller than 100000\n";
            continue;
        }
        else{
            cout << "[««~~»»]I don't even know how you manage to mess up so much a simple task\n";
            cout << "[««~~»»]You don't deserve to use this program\n";
            cout << "[««~~»»]ABORTING";
            abort();
        }
    }while(1 == 1);
}


void setGoals(vector<string>& goals, vector<bool>& doneOrNot){
        ofstream goalsCookie("GoalsCookie.txt");
        ofstream doneOrNotCookie("doneOrNotCookie.txt");

        int amountOfGoals;
        ifstream amontGoal("amountOfGoalsCookie.txt");
        amontGoal >> amountOfGoals;

        for(int i = 0; i < amountOfGoals; i++){
            string goal;
            cout << "What is your goal nº " << i + 1 << "?: ";
            cin.clear();
            getline(cin >> ws, goal);
            goals.push_back(goal);
            goalsCookie << goal << endl;
            doneOrNot.push_back(false);
            doneOrNotCookie << "false" << endl;
        }

        doneOrNotCookie.close();
        goalsCookie.close();

        toDoList(goals, doneOrNot, amountOfGoals);
}

vector<bool> haveIDoneIt(bool optionChosen, vector<string>& goals, vector<bool>& doneOrNot, int amountOfGoals){
       optionChosen = false;
       do{

            char isAnythingDone;
            cout << "Have you done any of your goals?:(y/n) ";
            cin >> isAnythingDone;



            int goalNumber;

            if(isAnythingDone == 'y' || isAnythingDone == 'Y'){
                cout << "Enter the number of the goal you want to do: ";
                cin >> goalNumber;

                int boolGoalNumber = goalNumber - 1;
                doneOrNot[boolGoalNumber] = true;

                toDoList(goals, doneOrNot, amountOfGoals);

                remove("doneOrNotCookie.txt");

                ofstream doneOrNotCookie("doneOrNotCookie.txt");
                for (int i = 0; i < amountOfGoals; i++) {
                    if(i == boolGoalNumber || doneOrNot[i] == true){
                        doneOrNotCookie << "true" << endl;
                        doneOrNot[i] = true;
                    }
                    else{
                        doneOrNotCookie << "false" << endl;
                    }
                
                }
                doneOrNotCookie.close();

                optionChosen = true;

                

            }
            else if(isAnythingDone == 'n' || isAnythingDone == 'N'){
                cout << "OK\n";
                optionChosen = true;

            } 
            else{
                cout << "That is not a valid option\n";
                optionChosen = false;
            }
        }while(optionChosen == false);

        return doneOrNot;

}

void options(){
    cout << "[++]-d/--doanother     == It does another goal to your choice.\n";
    cout << "[++]-c/--createanother == It creates another goal to your choice.\n";
    cout << "[++]-a/--abort         == It closes the program.\n";
    cout << "[++]-o/--options       == It shows you the options\n";
    cout << "[++]-v/--version       == It shows you the version";
}


int main(int argc, char *argv[]){

    ifstream checkIfItWasRunned("hasItBeenRunnedCookie.txt");

    // get the goals, amount of goals and check if the goal was done or not
    // in the case that the cookie files already exist
    string lineOfGoals;
    string lineOfDones;

    ifstream amountie("amountOfGoalsCookie.txt");
    ifstream golies("GoalsCookie.txt");
    ifstream donies("doneOrNotCookie.txt");

    int amountieOfGoals;
    vector<string> goalie;
    vector<bool> donieOrNot;

    while (getline (golies, lineOfGoals)){
        goalie.push_back(lineOfGoals);
    }

    while (getline (donies, lineOfDones)){
        if(lineOfDones == "true"){
            donieOrNot.push_back(true);
        }
        else{
            donieOrNot.push_back(false);
        }
    }

    amountie >> amountieOfGoals;

    amountie.close();
    donies.close();
    golies.close();

    int amountOfGoals;
    bool optionChosen;

    if(!checkIfItWasRunned){
        amountOfGoals = getFirstGoalNumber();

        // sets some important variables and calls some

        vector<string> goals;
        vector<bool> doneOrNot;

        bool optionChosen;

        setGoals(goals, doneOrNot);


        haveIDoneIt(optionChosen, goals, doneOrNot, amountOfGoals);
        }
    else{
        char willAddAnother;
        string optionChoice;

        toDoList(goalie, donieOrNot, amountieOfGoals);

        do{ 
            cout << "[**]Choose an option(use -o to see the options): ";
            cin >> optionChoice;

            if(optionChoice == "-o" || optionChoice == "--options"){
                options();
            }
            else if(optionChoice == "-d" || optionChoice == "--doanother"){
                haveIDoneIt(optionChosen, goalie, donieOrNot, amountieOfGoals);
            }
            else if(optionChoice == "-a" || optionChoice == "--abort"){
                cout << "\n[««»»]Closing the program!\n\n";
                break;
            }
            else if(optionChoice == "-v" || optionChoice == "--version"){
                cout << version << endl;
            }
            else if(optionChoice == "-c" || optionChoice == "--createanother"){
                amountieOfGoals++;
                string secondGoal;
                cout << "What is the goal you want to add?: ";
                getline(cin >> ws, secondGoal);
                goalie.push_back(secondGoal);
                ofstream secondTimeGoal;
                secondTimeGoal.open("GoalsCookie.txt", ios_base::app);
                secondTimeGoal << secondGoal << endl;
                secondTimeGoal.close();
                donieOrNot.push_back(false);
                ofstream secondTimeDonie;
                secondTimeDonie.open("doneOrNotCookie.txt", ios_base::app);
                secondTimeDonie << "false" << endl;
                secondTimeDonie.close();

                //Updates the number in the file amountOfGoalsCookie.txt
                remove("amountOfGoalsCookie.txt");

                ofstream amountieCookie("amountOfGoalsCookie.txt");
                amountieCookie << amountieOfGoals;

                amountieCookie.close();

                toDoList(goalie, donieOrNot, amountieOfGoals);

            }
            else{
                cout << "[««»»]That is not a valid option\n";
            }

        }while(1 == 1);

    }

    checkIfItWasRunned.close();

    return 0;
}
