///@brief ATM fucntionality file
/*
*Function
    1.display (displayWelcome ,banner, ATMMENU)
    2.Authentication (auth_Account,authentication)
    3.delay
    4.hidden password
*file
    "database.h"
    companion file '"database.h"'
    main "ATM_main.cpp"
*library
    fstream to read and wirte in file
 */
#include <string>
#include <fstream>
#include <iostream>
#include <conio.h>
using namespace std;
void displayWELCOME()
{

    system("cls");
    system("color 06");
    cout << "\n***********************************************\n"
         << "\tWELCOME TO THE NALA BANK ATM\n"
         << "***********************************************\n";
}
void banner()
{
    cout << "\n***********************************************\n"
         << "\t    THE NALA BANK ATM \n"
         << "***********************************************\n";
}
void ATMMENU()
{
    system("cls");
    system("color 02");
    cout << "\n***********************************************\n"
         << "\t    THE NALA BANK ATM\n"
         << "***********************************************\n"
         << "\tCHOOSE FROM THE FOLLOWING \n"
         << "***********************************************\n"
         << "\t 1.Check balance.\n"
         << "\t 2.Deposite Money.\n"
         << "\t 3.Withdrawl Money.\n"
         << "\t 4.exit.\n"
         << "***********************************************\n";
}

/// @brief  separate function for account authentication
/// @param givenAccountNo
/// @return
/*
1.open file "database.txt"
2.read each line of file(stored as string in text variable below)
3.match the givenAccountNo and realaccountNo return 1 if true
*/
bool auth_Account(int givenAccountNo)
{
    string text;
    ifstream acc_check("../database.txt");
    bool flag = 0;
    if (acc_check.is_open())
    {
        while (getline(acc_check, text))
        {
            int endfirst = text.find_first_of(' ', 0);
            int realaccountNo = stoi(text.substr(1, endfirst - 1));
            if (givenAccountNo == realaccountNo)
            {
                flag = 1;

                break;
            }
        }
        acc_check.close();
    }
    return flag;
}

/// @brief function for account & password authentication
/// @param givenAccountNo
/// @param givenPassword
/// @return  bool
/*
1.open file "database.txt"
2.read each line of file(stored as string in text variable below)
3.match the givenAccountNo and realaccountNo as well as givenPassword
and realPassword  return 1 if true
*/

bool authentication(int givenAccountNo, string givenPassword)
{ // password as well as account no.
    string text;
    ifstream pass_check("../database.txt");
    bool flag = 0;
    if (pass_check.is_open())
    {
        while (getline(pass_check, text))
        {
            int endfirst = text.find_first_of(' ', 0); // first _ char
            int realaccountNo = stoi(text.substr(1, endfirst - 1));

            int endsecond = text.find_first_of(' ', endfirst + 1); // second
            string realPassword = text.substr(endfirst + 2, endsecond - (endfirst + 2));

            if ((realaccountNo == givenAccountNo) && (realPassword.compare(givenPassword) == 0))
            {

                flag = 1;
                break;
            }
        }
        pass_check.close();
        return flag;
    }

    cout << "file does not open in authentication\n";
    return flag;
}
/// @brief simple delay function
/// @param milisec
void delay(unsigned long long milisec)
{

    for (unsigned long long i = 0; i < milisec * 1000000; i++)
    {
        /// delay
    }
}

/// @brief Password filled using conio.h
/// @param in_pass 
void hiddenPassword(string &in_pass)
{
    char ch;
    cout << "Enter Your Password: ";
    ch = getch();  // does not print any thing in console
    while (ch != 13)
    {
        if (ch != 8)
        {
            in_pass.push_back(ch);
            cout << "*"; // we are deliberately printing *
        }
        else if(ch==8){ //ASCII of backspace 
        in_pass.pop_back();
        cout<<"\b \b";//rub the character behind the cursor.
        }
        ch = getch();
    }
    cout << endl;
    
    
}