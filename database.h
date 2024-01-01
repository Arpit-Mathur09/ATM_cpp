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

std::vector<std::string> parseData;

/// @brief parseData from the "database.txt" using fstream
void parseDatabaseInATM()
{
    std::string text;

    std::fstream data;
    data.open("../database.txt");

    if (data.is_open())
    {
        while (std::getline(data, text))
        {

            // cout<<text<<endl;
            //  each data set aquired
            /*             int endfirst = text.find_first_of(' ', 0); // first _ char
                        int accountNo = stoi(text.substr(1, endfirst - 1));

                        int endsecond = text.find_first_of(' ', endfirst + 1); // second
                        std::string pass = text.substr(endfirst + 2, endsecond - (endfirst + 2));

                        int endthird = text.find_first_of('\n', endsecond + 1); // third

                        double balance = stod(text.substr(endsecond + 2, endthird - 1));
             */
            // push the strinng in parseData std::vector to rewrite the database.txt
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
4.substd::string the whole std::string to the balance std::string
5.return stod (std::string to decimal)convert the std::string to double
*/
/// @param givenAccountNo

double checkBalance(int givenAccountNo)
{
    std::fstream balance_check("../database.txt");
    if (balance_check.is_open())
    {
        std::string text;
        while (std::getline(balance_check, text))
        {
            int endfirst = text.find_first_of(' ', 0);
            int realaccountNo = std::stoi(text.substr(1, endfirst - 1));
            if (realaccountNo == givenAccountNo)
            {
                int B = text.find_first_of('B', 0);
                return std::stod(text.substr(B + 1, text.length() - B)); // return balance
            }
        }
        balance_check.close();
    }
    else
    {
        std::cout << "file doesnot open in check balance\n";
    }
    return 0.0;
}
/// @brief updating database for withdraw and deposite
/*  BRUTE FORCE -less efficient(DRAW BACK )
    saving the whole file in a std::string std::vector
    then rewriting the whole file with replaced std::string 
*/
/// @param givenAccountNo
/// @param givenPassword
/// @param newBalance
void updateDatabase(int givenAccountNo, std::string givenPassword, int newBalance)
{

    // making replacement std::string
    std::string newEntry = "A" + std::to_string(givenAccountNo) + " P" + givenPassword + " B" + std::to_string(newBalance);

    // opening file for in and out
    std::fstream file("../database.txt", std::ios::in | std::ios::out);
    if (file.is_open())
    {
        std::string text;
        int index = 0;
        // std::vector fill and index find for accountNo
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
        // filling parseData std::vector ;
        parseDatabaseInATM();
        // parseData std::vector update at index]
        parseData[index] = newEntry;

        // streampos pos = file.tellp();
        file.seekp(0, std::ios::beg);

        // write the wile file
        int size = parseData.size();
        for (int i = 0; i < size; i++)
        {
            file << parseData[i] << "\n";
        }

        // clear std::vector of database
        parseData.clear();

        file.close();
    }
}
