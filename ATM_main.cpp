///@brief ATM using fstream 

#include <iostream>
#include "database.h" //file handling
#include "ATM.h"

int main()
{
here:
    displayWELCOME();
    int in_accNo; // input accountNo
    std::cout << "Enter your Account number: ";
    std::cin >> in_accNo;
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

        std::string in_pass; // input password
        std::cout << std::endl;

        //Menu
        int choice; // input choice
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << std::endl;
        
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
                    std::cout << "Your current balance is: " << checkBalance(in_accNo) << std::endl;
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
                    std::cout << "Enter the amount to deposite: ";
                    std::cin >> deposite;
                    std::cout << std::endl;
                    deposite += bal;
                    updateDatabase(in_accNo, in_pass, deposite);
                    // updated bal;
                    system("cls");
                    banner();
                    std::cout << "\v\v\t\t SUCCESS\n";
                    system("color 27");
                    std::cout << "\tYour current balance is: " << checkBalance(in_accNo) << std::endl;
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
                    std::cout << "Enter the amount to withdraw: ";
                    std::cin >> withdraw;
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
                            std::cout << std::endl;
                            balance -= withdraw;
                            updateDatabase(in_accNo, in_pass, balance);
                            std::cout << "Your current balance is: " << checkBalance(in_accNo) << std::endl;
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