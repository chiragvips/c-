#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>
using namespace std;

class Account {
    int accountNumber;
    char name[50];
    int balance;
public:
    void createAccount(); // function to get data from user
    void showAccount() const; // function to show data on screen
    void modify(); // function to add new data
    void deposit(int); // function to accept amount and add to balance
    void withdraw(int); // function to accept amount and subtract from balance
    void report() const; // function to show data in tabular format
    int retAccountNumber() const; // function to return account number
    int retBalance() const; // function to return balance amount
    char* retName(); // function to return name of account holder
};

void Account::createAccount() {
    cout << "Enter the Account Number: ";
    cin >> accountNumber;
    cout << "Enter the Name of the Account Holder: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Enter The Initial amount(>=500 for Saving and >=1000 for Current): ";
    cin >> balance;
    cout << "\n\n\nAccount Created..";
}

void Account::showAccount() const {
    cout << "\nAccount Number: " << accountNumber;
    cout << "\nAccount Holder Name: " << name;
    cout << "\nBalance: " << balance;
}

void Account::modify() {
    cout << "\nAccount Number: " << accountNumber;
    cout << "\nModify Account Holder Name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nModify Balance amount: ";
    cin >> balance;
}

void Account::deposit(int amount) {
    balance += amount;
}

void Account::withdraw(int amount) {
    balance -= amount;
}

void Account::report() const {
    cout << accountNumber << setw(10) << " " << name << setw(20) << balance << endl;
}

int Account::retAccountNumber() const {
    return accountNumber;
}

int Account::retBalance() const {
    return balance;
}

char* Account::retName() {
    return name;
}

// function declarations
void writeAccount();
void displayAccount(int);
void modifyAccount(int);
void deleteAccount(int);
void displayAll();
void depositWithdraw(int, int);

int main() {
    char ch;
    int num;
    do {
        system("cls");
        cout << "\n\n\t\t\tBANK MANAGEMENT SYSTEM";
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. NEW ACCOUNT";
        cout << "\n\n\t02. DEPOSIT AMOUNT";
        cout << "\n\n\t03. WITHDRAW AMOUNT";
        cout << "\n\n\t04. BALANCE ENQUIRY";
        cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
        cout << "\n\n\t06. CLOSE AN ACCOUNT";
        cout << "\n\n\t07. MODIFY AN ACCOUNT";
        cout << "\n\n\t08. EXIT";
        cout << "\n\n\tSelect Your Option (1-8): ";
        cin >> ch;
        system("cls");
        switch (ch) {
        case '1':
            writeAccount();
            break;
        case '2':
            cout << "\n\n\tEnter The account No.: "; cin >> num;
            depositWithdraw(num, 1);
            break;
        case '3':
            cout << "\n\n\tEnter The account No.: "; cin >> num;
            depositWithdraw(num, 2);
            break;
        case '4':
            cout << "\n\n\tEnter The account No.: "; cin >> num;
            displayAccount(num);
            break;
        case '5':
            displayAll();
            break;
        case '6':
            cout << "\n\n\tEnter The account No.: "; cin >> num;
            deleteAccount(num);
            break;
        case '7':
            cout << "\n\n\tEnter The account No.: "; cin >> num;
            modifyAccount(num);
            break;
        case '8':
            cout << "\n\n\tThanks for using bank management system";
            break;
        default: cout << "\a"; // alert sound
        }
        cin.ignore();
        cin.get();
    } while (ch != '8');
    return 0;
}

// function to write in file
void writeAccount() {
    Account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.createAccount();
    outFile.write(reinterpret_cast<char *> (&ac), sizeof(Account));
    outFile.close();
}

// function to read specific record from file
void displayAccount(int n) {
    Account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened !! Press any Key...";
        return;
    }
    cout << "\nBALANCE DETAILS\n";

    while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account))) {
        if (ac.retAccountNumber() == n) {
            ac.showAccount();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\nAccount number does not exist";
}

// function to modify record of file
void modifyAccount(int n) {
    bool found = false;
    Account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be opened !! Press any Key...";
        return;
    }

    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char *> (&ac), sizeof(Account));
        if (ac.retAccountNumber() == n) {
            ac.showAccount();
            cout << "\n\nEnter The New Details of account" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(Account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}

// function to delete record of file
void deleteAccount(int n) {
    Account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account))) {
        if (ac.retAccountNumber() != n) {
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(Account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\n\tRecord Deleted ..";
}

// function to display all accounts deposit list
void displayAll() {
    Account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened !! Press any Key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME           Balance\n";
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account))) {
        ac.report();
    }
    inFile.close();
}

// function to deposit and withdraw amounts
void depositWithdraw(int n, int option) {
    int amt;
    bool found = false;
    Account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be opened !! Press any Key...";
        return;
    }

    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char *> (&ac), sizeof(Account));
        if (ac.retAccountNumber() == n) {
            ac.showAccount();
            if (option == 1) {
                cout << "\n\n\tTO DEPOSIT AMOUNT";
                cout << "\n\nEnter The amount to be deposited: ";
                cin >> amt;
                ac.deposit(amt);
            }
            else if (option == 2) {
                cout << "\n\n\tTO WITHDRAW AMOUNT";
                cout << "\n\nEnter The amount to be withdrawn: ";
                cin >> amt;
                int bal = ac.retBalance() - amt;
                if (bal < 0)
                    cout << "Insufficient balance";
                else
                    ac.withdraw(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}

