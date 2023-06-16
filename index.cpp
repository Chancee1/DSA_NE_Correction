#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

void addLocation(const string &location)
{
    ofstream file("location.csv", ios::app);
    if (file.is_open())
    {
        file << location << endl;
        file.close();
        cout << location << " was successfully added in location.csv";
    }
    else
    {
        cout << "Error adding " << location << " to location.csv";
    }
}

void deleteLocation(const string &location)
{
    ifstream file("location.csv");
    vector<string> locations;
    string line;
    if (!file.is_open())
    {
        cout << "Unable to open file" << endl;
        return;
    }
    while (getline(file, line))
    {
        if (line != location)
        {
            locations.push_back(line);
        }
        file.close();
    }
    ofstream outFile("location.csv");
    if (!outFile.is_open())
    {
        cout << "Unable to open file" << endl;
        return;
    }
    for (const auto &loc : locations)
    {
        outFile << loc << endl;
    }

    outFile.close();
    cout << "Successfully deleted" << location << "From location.csv" << endl;
}

void listAllLocations()
{
    ifstream file("location.csv");
    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }
    vector<string> locations;
    string line;
    cout << "Here is a list of all locations previously added" << endl;
    while (getline(file, line))
    {
        cout << line << endl;
    }
    return;
}

void  listAllDiseases(){
    ifstream file("diseases.csv");
    vector<string> diseases;
    string line;
    string word;

    cout<< "Found diseases" <<endl;

    while(getline(file, line)){

        istringstream iss(line);
        iss >> word;
        iss >> word;
        cout<< word <<endl;
    }

}

void findLocationOfDisease(const string &disease){
    ifstream file("diseases.csv");
    vector<string> diseases;
    string line;
    string firstword;
    string secondword;


    while(getline(file, line)){
        istringstream iss(line);
        iss >> firstword;
        iss >> secondword;
        if(secondword == disease){
            cout<< firstword <<endl;
        }
    }
}

void totalCases(const string &disease){
    ifstream file("diseases.csv");
    vector<string> diseases;
    string line;
    string word;
    int count;

    while(getline(file, line)){
        istringstream iss(line);
        iss >> word;
        iss >> word;
        if( word == disease){
            iss >> word;
            count += stoi(word);
        }
    }

    cout<< "Total Cases of "<<disease << " are: "<< count << endl;
}


void  totalCasesInLocation(const string &location, const string &disease){
    ifstream file("diseases.csv");
    vector<string> diseases;
    string line;
    string word;
    int count;

    while(getline(file, line)){
        istringstream iss(line);
        iss >> word;
        if( word == location){
            iss >> word;
        }
        if( word == disease){
            iss >> word;
            count += stoi(word);
        }
    }
     cout<< "Total Cases of "<<disease << " in "<<location<< " are "<< count<<endl;
}

void recordDisease(const string &location, const string &disease, const string &cases)
{
    ofstream file("diseases.csv", ios::app);
    if (!file.is_open())
    {
        return;
    }

    vector<string> locations;
    ifstream inFile("location.csv");
    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }
    string line;
    while (getline(inFile, line))
    {
        locations.push_back(line);
    }

    for (const auto &loc : locations)
    {
        if (loc == location)
        {
            file << location << " " << disease << " " << cases <<endl;
            cout<<"Successfully Recorded Disease";
            file.close();
            return;
        }
    }
    cout<<"Location Not Found. Failed to record disease";
    file.close();

    return;
}

void help(){
    cout << "==================================================================" << endl;
    cout << "*                    H E L P  M E N U                            *" << endl;
    cout << "==================================================================" << endl;
    cout << "add <Location>                          : Add a new location" << endl;
    cout << "delete <Location>                       : Delete an existing location" << endl;
    cout << "record <Location> <disease> <cases>     : Record a disease and its cases            " << endl;
    cout << "list locations                          : List all existing locations            " << endl;
    cout << "list diseases                           : List existing Diseases in locations          " << endl;
    cout << "where <disease>                         : Find where the disease exists           " << endl;
    cout << "cases <location> <disease>              : Find cases of a disease in location          " << endl;
    cout << "cases <disease>                         : Find total cases of a given disease    " << endl;
    cout << "help                                    : Prints user manual    " << endl;
    cout << "exit                                    : Exit the program  " << endl;

}

void processCommands()
{
    while (true)
    {
        cout << endl;
        cout << "Console > ";
        string command;
        getline(cin, command);

        for (char &c : command)
        {
            c = tolower(c);
        }

        istringstream iss(command);
        vector<string> words;
        string word;

        while (iss >> word)
        {
            words.push_back(word);
        }

        if (!words.empty())
        {
            const string &firstword = words[0];
            if (firstword == "add")
            {
                if (words.size() > 1)
                {
                    const string &secondWord = words[1];
                    addLocation(secondWord);
                }
                else
                {
                    cout << "Please provide a valid location name!" << endl;
                }
            }
            else if (firstword == "delete")
            {
                if (words.size() > 1)
                {
                    const string &secondWord = words[1];
                    deleteLocation(secondWord);
                }
                else
                {
                    cout << "Please provide a valid location name!" << endl;
                }
            }
            else if (firstword == "list")
            {
                if (words.size() > 1)
                {
                    const string &secondWord = words[1];
                    if (secondWord == "locations")
                    {
                        listAllLocations();
                    }
                    else if(secondWord == "diseases")
                    {
                        listAllDiseases();
                    }
                }
                else
                {
                    cout << "Please specify what to list!" << endl;
                }
            }
            else if (firstword == "record")
            {
                if (words.size() > 3)
                {
                    const string &location = words[1];
                    const string &diseases = words[2];
                    const string &cases = words[3];
                    recordDisease(location, diseases, cases);
                }
                else
                {
                    cout << "Please provide a valid command!" << endl;
                }
            }
            else if (firstword == "help")
            {
                help();
            }
            else if (firstword == "where")
            {
                const string &disease = words[1];
                findLocationOfDisease(disease);
            }
            else if (firstword == "cases")
            {
                if(words.size() <= 2){
                const string &disease = words[1];
                totalCases(disease);
                }else{
                    const string &location = words[1];
                    const string &disease = words[2];
                  totalCasesInLocation(location, disease);
                }
            }
            else if (firstword == "exit")
            {
                break;
            }
            else
            {
                cout << "Invalid command. type help to see the list of all available commands." << endl;
            }
        }
    }
}

int main()
{
    cout << "\t============================================================" << endl;
    cout << "\t*                                                           *" << endl;
    cout << "\t*        Welcome to Disease Cases Reporting System          *" << endl;
    cout << "\t*           *                                               *" << endl;
    cout << "\t*    It is developed by Chance Ineza Jost  as Practical     *" << endl;
    cout << "\t*              Evaluation for the end of Year3              *" << endl;
    cout << "\t*                                                           *" << endl;
    cout << "\t============================================================" << endl;
    cout << "\tStarting Time: Thu Apr 05 23:59:08 CAT 2022                 " << endl;
    cout << "\tNeed Help? type help, and then press Enter key              " << endl;

    processCommands();

    return 0;
}