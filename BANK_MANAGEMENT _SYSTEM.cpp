//NAME : EHTASHAM ARIF
//ROLL NO : 23P_0567
//SECTION : BCS_2A

//Header files
#include <iostream>
using namespace std;

// Bank_Account class to represent each bank account../////////
class Bank_Account {
private:
    int acc_no;         // Account number
    string acc_name;    // Account holder's name
    double acc_balance; // Account balance
    static int total_account; // Static variable to keep track of total accounts

public:
    // Default constructor inilized to default values
    Bank_Account() {
        acc_no=0;
        acc_name="N/A";
        acc_balance=0.0;
    }

    // Parameterized constructor
    Bank_Account(int number, string name, double balance)
        : acc_no(number), acc_name(name), acc_balance(balance) {
        inc_total_account();
    }

    // Function to deposit money into the account
    void deposit(double amount) {
        acc_balance += amount;
        cout << "////////////////////////////////\n";
        cout << "Deposit successful! New balance: " << acc_balance << endl;
        cout << "////////////////////////////////\n";
    }

    // Function to withdraw money from the account
    void withdraw(double amount) {
        if (amount < acc_balance) {
            acc_balance -= amount;
            cout << "////////////////////////////////\n";
            cout << "Withdrawal successful! New balance: " << acc_balance << endl;
            cout << "////////////////////////////////\n";
        } else {
            cout << "////////////////////////////////\n";
            cout << "\n\nERROR! INSUFFICIENT BALANCE IN YOUR ACCOUNT\n\n";
            cout << "YOUR ACCOUNT BALANCE IS : " << acc_balance << endl << endl;
            cout << "////////////////////////////////\n";
        }
    }

    // Function to get the current balance of the account
    double get_balance() const {
        return acc_balance;
    }

    // Function to get the account number
    int get_acc_no() const {
        return acc_no;
    }

    // Function to get the account holder's name
    string get_acc_name() const {
        return acc_name;
    }

    // Static function to get the total number of accounts
    static int get_total_account() {
        return total_account;
    }

    // Function to increment the total_accounts
    void inc_total_account() {
        ++total_account;
    }

    // Function to decrement the total_accounts
    void dec_total_account() {
        --total_account;
    }

    // Function to transfer funds from this account to another
    void transfer_funds(Bank_Account& receiver, double amount) {
        if (amount < acc_balance) {
            withdraw(amount);
            receiver.deposit(amount);
            cout << "\n////////////////////////////////\n";
            cout << "Transfer successful!" << endl;
            cout << "Updated balance of sender's account: " << acc_balance << endl;
            cout << "Updated balance of receiver's account: " << receiver.get_balance() << endl;
        } else {
            cout << "////////////////////////////////\n";
            cout << "ERROR! INSUFFICIENT BALANCE IN SENDER'S ACCOUNT" << endl;
            cout << "////////////////////////////////\n";
        }
    }
};

// Initialize static member variable total_account
int Bank_Account::total_account = 0;

// Bank_Manager class to manage multiple bank accounts
class Bank_Manager {
private:
    // Using Dynamic array of pointers to Bank_Account objects
    Bank_Account** account; 

public:
    // Constructor
    Bank_Manager() : account(nullptr) {}

    // Destructor
    ~Bank_Manager() {
        for (int i = 0; i < Bank_Account::get_total_account(); i++) {
            delete account[i];
        }
        delete[] account;
    }

    // Function to create a new bank account dynamically
    void create_bank_account() {
        int acc_no;
        string name;
        double balance;

        //Getting data from the user.
        cout << "ENTER THE ACCOUNT NUMBER : ";
        cin >> acc_no;
        cout << "ENTER ACCOUNT HOLDER'S NAME : ";
        cin >> name;
        cout << "ENTER THE INITIAL BALANCE : ";
        cin >> balance;

        //creating the new pointer object of BAnk Account class and passing data to it.
        Bank_Account* new_account = new Bank_Account(acc_no, name, balance);

        //creating a temporary array dynamicaaly to store data 
        Bank_Account** temp = new Bank_Account*[Bank_Account::get_total_account()];
        for (int i = 0; i < Bank_Account::get_total_account() - 1; i++) {
            temp[i] = account[i];
        }
        //storing the recent data into end of array.
        temp[Bank_Account::get_total_account() - 1] = new_account;

        //deleting the older data 
        delete[] account;

        //giving the adress of the temp to account 
        account = temp;

        cout << "////////////////////////////////\n";
        cout << "ACCOUNT CREATED SUCCESSFULLY!\n";
        cout << "////////////////////////////////\n";
    }

    // Function to delete a bank account
    void delete_bank_account() {
        int acc_no;
        cout << "ENTER ACCOUNT NUMBER TO DELETE : ";
        cin >> acc_no;

        //getting the total bank accounts created.
        int total_acc = Bank_Account::get_total_account();

        //count varible for checking that account is found or not.
        int count = -1;

        for (int i = 0; i < total_acc; i++) {
            if (account[i]->get_acc_no() == acc_no) {
                count = i;
                break;
            }
        }

        if (count != -1) {
            //creating a temporay array of new size,  1 size smaller than the origional size.
            Bank_Account** temp = new Bank_Account*[total_acc - 1];
            int j = 0;
            for (int i = 0; i < total_acc; i++) {
                if (i != count) {
                    //copying the data except the data we want to be deleted 
                    temp[j++] = account[i];
                }
            }
            //clearing the data from older array.
            delete[] account;
            //assingning the address of temp to account.
            account = temp;

            //creating the object of Bank_account class and calling the function 
            //to decrement the total accounts because one account is deleted.
            Bank_Account c;
            c.dec_total_account();
            cout << "////////////////////////////////\n";
            cout << "ACCOUNT DELETED SUCCESSFULLY!\n";
            cout << "////////////////////////////////\n";
        } else {
            cout << "////////////////////////////////\n";
            cout << "ACCOUNT NOT FOUND!\n";
            cout << "////////////////////////////////\n";
        }
    }

    // Function to deposit money into a specific account
    void deposit_money(int acc_no, double amount) {
        for (int i = 0; i < Bank_Account::get_total_account(); i++) {
            //if the account no is found then
            if (account[i]->get_acc_no() == acc_no) {
                //calling the deposit function of BAnk Account class and passing the
                //Argument to it.
                account[i]->deposit(amount);
                return;
            }
        }
        cout << "////////////////////////////////\n";
        cout << "Account not found!" << endl;
        cout << "////////////////////////////////\n";
    }

    // Function to withdraw money from a specific account
    void withdraw_money(int acc_no, double amount) {
        for (int i = 0; i < Bank_Account::get_total_account(); i++) {
            //if the account no is found then
            if (account[i]->get_acc_no() == acc_no) {
                //calling the withdraw function of BAnk Account class and passing the
                //Argument to it.
                account[i]->withdraw(amount);
                return;
            }
        }
        cout << "////////////////////////////////\n";
        cout << "Account not found!" << endl;
        cout << "////////////////////////////////\n";
    }

    // Function to find a bank account by account number and return a pointer to it
    Bank_Account* find_bank_account_by_number(int acc_no) {
        for (int i = 0; i < Bank_Account::get_total_account(); i++) {
            //if the account no is found then
            if (account[i]->get_acc_no() == acc_no) {
                return account[i];
            }
        }
        //returning pointer
        return nullptr;
    }

    // Function to display all account details
    void display_account_details() {
        for (int i = 0; i < Bank_Account::get_total_account(); i++) {
            cout<<"Account : "<<i+1;
            cout << "\n\t\t==> Account Number: " << account[i]->get_acc_no() << endl;
            cout << "\t\t==> Account Holder: " << account[i]->get_acc_name() << endl;
            cout << "\t\t==> Balance: " << account[i]->get_balance() << endl;
        }
    }

    //function for the balance inquiry 
    void balance_inquiry(int acc_no)
    {
         for (int i = 0; i < Bank_Account::get_total_account(); i++) {
            //if the account no is found then
            if (account[i]->get_acc_no() == acc_no) {
                cout << "Account Found: " << endl;
                cout << "Account Holder: " << account[i]->get_acc_name() << endl;
                cout << "YOUR BALANCE IS :: " << account[i]->get_balance() << endl;
                return;
            }
        }
        cout << "////////////////////////////////\n";
        cout << "Account not found!" << endl;
        cout << "////////////////////////////////\n";
    }

    // Function to transfer funds from one account to another
    void transfer_funds(int sender_acc_no, int receiver_acc_no, double amount) {
        Bank_Account* sender_account;
        Bank_Account* receiver_account;

        int counter1=-1;
        int counter2=-1;


        // Find sender's account
        for (int i = 0; i < Bank_Account::get_total_account(); i++) {
            //if the account no is found then
            if (account[i]->get_acc_no() == sender_acc_no) {
                //assingning address
                sender_account = account[i];
                ++counter1;
                break;
            }
        }

        // Find receiver's account
        for (int i = 0; i < Bank_Account::get_total_account(); i++) {
            //if the account no is found then
            if (account[i]->get_acc_no() == receiver_acc_no) {
                //assingning address
                receiver_account = account[i];
                ++counter2;
                break;
            }
        }

        // If sender's or receiver's account is not found, exit
        if ((counter1==-1) || (counter2==-1)) {
            cout << "////////////////////////////////\n";
            cout << "Sender's or receiver's account not found!" << endl;
            cout << "////////////////////////////////\n";
            return;
        }

        // Check if sender has enough balance
        if (sender_account->get_balance() >= amount) {
            // Perform the transfer
            //calling the withdraw and deposit function of the Bank Account 
            //passing the argument to withdraw and deposit function
            sender_account->withdraw(amount);
            receiver_account->deposit(amount);
            cout << "////////////////////////////////\n";
            cout << "Transfer successful!" << endl;
            cout << "Updated balance of sender's account: " << sender_account->get_balance() << endl;
            cout << "Updated balance of receiver's account: " << receiver_account->get_balance() << endl;
            cout << "////////////////////////////////\n";
        } else {
            cout << "////////////////////////////////\n";
            cout << "ERROR! INSUFFICIENT BALANCE IN SENDER'S ACCOUNT" << endl;
            cout << "////////////////////////////////\n";
        }
    }

    //function to calculate the total bank balance 
    double total_bank_balance()
    {
        int total_acc=Bank_Account::get_total_account();
        int total=0;
        for(int i = 0; i < total_acc ; i++)
        {
            //adding all the balance
            total=total+ account[i]->get_balance();
        }
        return total;
    }
    
};

int main() {
     cout << "\n\n//////////////////////__WELCOME TO BANK MANAGEMENT__////////////////////\n\n";
    //creating the object of the Bank_manager class
    Bank_Manager b;
    int choice;
    do {
        cout << "\n///////////////////////////////____MENU____///////////////////////////////\n";
        cout << "\n 1) CREATE A NEW ACCOUNT " << endl;
        cout << " 2) DELETE AN ACCOUNT " << endl;
        cout << " 3) FIND THE ACCOUNT DETAILS" << endl;
        cout << " 4) DISPLAY ALL ACCOUNT DETAILS" << endl;
        cout << " 5) DEPOSIT AMOUNT " << endl;
        cout << " 6) WITHDRAW AMOUNT " << endl;
        cout << " 7) BALANCE INQUIRY "<<endl;
        cout << " 8) TRANSFER FUNDS "<<endl;
        cout << " 9) TOTAL BALANCE IN BANK "<<endl;
        cout << " 10) EXIT THE PROGRAM \n" << endl;
        cout << "////////////////////////////////\n";
        cout << "ENTER YOUR CHOICE : ";
        cin >> choice;
        cout << "////////////////////////////////\n";

    //using switch statement
        switch (choice) {
            case 1: {
                //calling function
                b.create_bank_account();
                break;
            }
            case 2: {
                //calling function
                b.delete_bank_account();
                break;
            }
            case 3: {
                int acc_no;
                cout << "Enter account number to find: ";
                cin >> acc_no;
                //creating a pointer object to find the account
                Bank_Account* found_account = b.find_bank_account_by_number(acc_no);
                //if account will be found then it will contains its address therefore..
                if (found_account != nullptr) {
                    cout << "Account Found: " << endl;
                    cout << "Account Number: " << found_account->get_acc_no() << endl;
                    cout << "Account Holder: " << found_account->get_acc_name() << endl;
                    cout << "Balance: " << found_account->get_balance() << endl;
                } else {
                    cout << "////////////////////////////////\n";
                    cout << "Account not found!" << endl;
                    cout << "////////////////////////////////\n";
                }
                break;
            }
            case 4: {
                //calling function
                b.display_account_details();
                break;
            }
            case 5: {
                int acc_no;
                double amount;
                cout << "Enter account number to deposit into: ";
                cin >> acc_no;
                cout << "Enter amount to deposit: ";
                cin >> amount;
                //calling function
                b.deposit_money(acc_no, amount);
                break;
            }
            case 6: {
                int acc_no;
                double amount;
                cout << "Enter account number to withdraw from: ";
                cin >> acc_no;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                //calling function
                b.withdraw_money(acc_no, amount);
                break;
            }
            case 7:
            {
                int acc_no;
                cout<<"ENTER THE ACCOUNT NO : ";
                cin>>acc_no;
                //calling function
                b.balance_inquiry(acc_no);
                break;
            }
            case 8:
            {
                int sender_acc_no, receiver_acc_no;
                double amount;
                cout << "Enter sender's account number: ";
                cin >> sender_acc_no;
                cout << "Enter receiver's account number: ";
                cin >> receiver_acc_no;
                cout << "Enter amount to transfer: ";
                cin >> amount;
                //calling function
                b.transfer_funds(sender_acc_no, receiver_acc_no, amount);
                break;
            }
            case 9:
            {
                //for total balance in the bank.
                cout<<"\n\nTHE TOTAL BALANCE IN BANK IS : "<<b.total_bank_balance()<<endl<<endl;
                break;
            }
            case 10: {
                cout << "\n\nEXITING PROGRAM....\n\n";
                break;
            }
            default: {
                cout << "////////////////////////////////\n";
                cout << "\nERROR! \nPLEASE INPUT CORRECT CHOICE \n\n";
                cout << "////////////////////////////////\n";
            }
        }
    } while (choice != 10);

    cout << "\n\n//////////////////////______PROGRAM ENDED_______////////////////////\n\n";

    return 0;
}
