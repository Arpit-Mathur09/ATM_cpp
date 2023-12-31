///@brief ATM using fstream 
/*    DRAWBACk 
1. less efficient 
2. NO GUI
*/
#include <iostream>
#include "database.h" //file handling
#include "ATM.h"

using namespace std;

int main()
{
here:
    displayWELCOME();
    int in_accNo; // input accountNo
    cout << "Enter your Account number: ";
    cin >> in_accNo;
//checking the INPUT ACCOUNT NO.
    try
    {
        if (!auth_Account(in_accNo))
        {
            throw('A');
        }
    }
    catch (char A)
    {
        std::cerr << "ERROR: Authentication ERROR(Account Not Registered)" << '\n';
        delay(4000);
        goto here;
    }

//loop
    while (1)
    {
        ATMMENU(); // ATM menu display

        string in_pass; // input password
        cout << endl;

        //Menu
        int choice; // input choice
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;
        
        switch (choice)
        {
        // check balance
        case 1:
                hiddenPassword(in_pass);
        
            try
            {
                if (authentication(in_accNo, in_pass))
                {
                    system("color");
                    cout << "Your current balance is: " << checkBalance(in_accNo) << endl;
                    delay(5000);
                }
                else

                    throw('A'); // A- Authentication error
            }
            catch (char A)
            {
                system("color 04");
                std::cerr << "ERROR: AUTHENtICATION ERROR(Invalid Password)" << '\n';
                delay(4000);
                goto here;
            }
            break;

        // deposite Money
        case 2:
                hiddenPassword(in_pass);

            try
            {
                if (authentication(in_accNo, in_pass))
                {
                    // check balance from databse
                    double bal = checkBalance(in_accNo);
                    double deposite = 0;
                    cout << "Enter the amount to deposite: ";
                    cin >> deposite;
                    cout << endl;
                    deposite += bal;
                    updateDatabase(in_accNo, in_pass, deposite);
                    // updated bal;
                    system("cls");
                    banner();
                    cout << "\v\v\t\t SUCCESS\n";
                    system("color 27");
                    cout << "\tYour current balance is: " << checkBalance(in_accNo) << endl;
                    delay(5000);
                }
                else
                {
                    throw('A');
                }
            }
            catch (char A)
            {
                system("color 04");
                std::cerr << "ERROR : AUTHENTICATION ERROR(Invalid password)" << '\n';
                delay(4000);
                goto here;
            }

            break;
            // withdraw Money
        case 3:
                hiddenPassword(in_pass);

            try
            {
                if (authentication(in_accNo, in_pass))
                {
                    // chekc balance from datbase
                    double balance = checkBalance(in_accNo);
                    double withdraw;
                tryagain:
                    cout << "Enter the amount to withdraw: ";
                    cin >> withdraw;
                    try
                    {
                        try
                        {
                            if (withdraw <= 0)
                            {
                                throw('I');
                            }
                        }
                        catch (char I)
                        {
                            system("color 04");
                            std::cerr << "ERROR: INVALID INPUT TRY AGAIN" << '\n';
                            system("color");
                            delay(4000);
                            goto tryagain;
                        }

                        if (withdraw > balance)
                        {
                            throw('W');
                        }
                        else
                        {
                            cout << endl;
                            balance -= withdraw;
                            updateDatabase(in_accNo, in_pass, balance);
                            cout << "Your current balance is: " << checkBalance(in_accNo) << endl;
                            delay(5000);
                        }
                    }
                    catch (char W)
                    {
                        system("color 04");
                        std::cerr << "ERROR: INSUFFICIENT BALANCE" << '\n';
                        delay(4000);
                    }
                }
                else
                    throw('A');
            }
            catch (char A)
            {
                system("color 04");
                std::cerr << "ERROR: AUTHENTICATION (Invalid Password)" << '\n';
                goto here;
            }

            break;

        default:

            goto here;
        }
    }
}