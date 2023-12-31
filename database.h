/// @brief Database Management
/*
*Function
    1.parseDatabaseInATM
    2.check balance
    3.updatae database
*file
    "database.h"
    companion file ATM.h
    main file "ATM_main.cpp"
*library
    fstream to read and wirte in file
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<string> parseData;

/// @brief parseData from the "database.txt" using fstream
void parseDatabaseInATM()
{
    string text;

    ifstream data;
    data.open("../database.txt");

    if (data.is_open())
    {
        while (getline(data, text))
        {

            // cout<<text<<endl;
            //  each data set aquired
            /*             int endfirst = text.find_first_of(' ', 0); // first _ char
                        int accountNo = stoi(text.substr(1, endfirst - 1));

                        int endsecond = text.find_first_of(' ', endfirst + 1); // second
                        string pass = text.substr(endfirst + 2, endsecond - (endfirst + 2));

                        int endthird = text.find_first_of('\n', endsecond + 1); // third

                        double balance = stod(text.substr(endsecond + 2, endthird - 1));
             */
            // push the strinng in parseData vector to rewrite the database.txt
            parseData.push_back(text);
        }

        data.close();
    }
}

/// @brief directly checking balance from database.txt using brute force
/*
1.find the accountNo
    by finding first _ (/whitespace char in each of the line)
2.comparing the realaccountNo and givenAccountNo
3.find B in that line(containg accountNo)
4.substring the whole string to the balance string
5.return stod (string to decimal)convert the string to double
*/
/// @param givenAccountNo

double checkBalance(int givenAccountNo)
{
    ifstream balance_check("../database.txt");
    if (balance_check.is_open())
    {
        string text;
        while (getline(balance_check, text))
        {
            int endfirst = text.find_first_of(' ', 0);
            int realaccountNo = stoi(text.substr(1, endfirst - 1));
            if (realaccountNo == givenAccountNo)
            {
                int B = text.find_first_of('B', 0);
                return stod(text.substr(B + 1, text.length() - B)); // return balance
            }
        }
        balance_check.close();
    }
    else
    {
        cout << "file doesnot open in check balance\n";
    }
    return 0.0;
}
/// @brief updating database for withdraw and deposite
/*  BRUTE FORCE -less efficient(DRAW BACK )
    saving the whole file in a string vector
    then rewriting the whole file with replaced string 
*/
/// @param givenAccountNo
/// @param givenPassword
/// @param newBalance
void updateDatabase(int givenAccountNo, string givenPassword, int newBalance)
{

    // making replacement string
    string newEntry = "A" + to_string(givenAccountNo) + " P" + givenPassword + " B" + to_string(newBalance);

    // opening file for in and out
    fstream file("../database.txt", ios::in | ios::out);
    if (file.is_open())
    {
        string text;
        int index = 0;
        // vector fill and index find for accountNo
        while (getline(file, text))
        {
            // parseData.push_back(text);
            int endfirst = text.find_first_of(' ', 0);
            int realaccountNo = stoi(text.substr(1, endfirst - 1));

            if (givenAccountNo == realaccountNo)
            {
                break;
            }

            index++;
        }
        // filling parseData vector ;
        parseDatabaseInATM();
        // parseData vector update at index]
        parseData[index] = newEntry;

        // streampos pos = file.tellp();
        file.seekp(0, ios::beg);

        // write the wile file
        int size = parseData.size();
        for (int i = 0; i < size; i++)
        {
            file << parseData[i] << "\n";
        }

        // clear vector of database
        parseData.clear();

        file.close();
    }
}
