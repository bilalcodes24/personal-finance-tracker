#include "../include/FinanceManager.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

FinanceManager::FinanceManager() : transactionCount(0), totalIncome(0), totalExpenses(0) {}

FinanceManager::~FinanceManager() {
    for(int i = 0; i < transactionCount; i++) {
        delete transactions[i];
    }
}

void FinanceManager::addIncome(double amount, string category, string date) {
    if(transactionCount < MAX_TRANSACTIONS) {
        transactions[transactionCount++] = new Income(amount, category, date);
        totalIncome += amount;
        saveincome(amount, category, date);
        savealldata(amount, category, date);
    } else {
        int n;
        cout << "Transaction limit reached!" << endl;
        cout << "To reset your data press 1: ";
        cin >> n;
        if(n == 1) {
            deletealltransactions();
        }
    }
}

void FinanceManager::addExpense(double amount, string category, string date) {
    if(transactionCount < MAX_TRANSACTIONS) {
        if(checkLimitExceeded(category, amount)) {
            cout << "Warning: Budget limit exceeded for category: " << category << endl;
        }
        transactions[transactionCount++] = new Expense(amount, category, date);
        totalExpenses += amount;
        saveexpense(amount, category, date);
        savealldata(amount, category, date);
    } else {
        int n;
        cout << "Transaction limit reached!" << endl;
        cout << "To reset your data press 1: ";
        cin >> n;
        if(n == 1) {
            deletealltransactions();
        }
    }
}

void FinanceManager::displayTransactions() {
    cout << "\n--- TRANSACTION HISTORY ---\n";
    displayalldata();
}

void FinanceManager::displaySummary() {
    string cat, date;
    double savetotalincome = 0, savetotalexpense = 0, netbill = 0;
    
    ifstream fin1("../data/income.txt");
    if(fin1.is_open()) {
        double amount;
        while(fin1 >> cat >> amount >> date) {
            savetotalincome += amount;
        }
    }
    
    ifstream fin2("../data/expense.txt");
    if(fin2.is_open()) {
        double amount;
        while(fin2 >> cat >> amount >> date) {
            savetotalexpense += amount;
        }
    }
    
    netbill = savetotalincome - savetotalexpense;
    
    ofstream fout("../data/summary.txt");
    if(fout.is_open()) {
        fout << savetotalincome << endl;
        fout << savetotalexpense << endl;
        fout << netbill << endl;
    }
    
    cout << "\n=== FINANCIAL SUMMARY ===\n";
    cout << "Total Income: $" << savetotalincome << endl;
    cout << "Total Expenses: $" << savetotalexpense << endl;
    cout << "Net Balance: $" << netbill << endl;
    
    fin1.close();
    fin2.close();
    fout.close();
}

void FinanceManager::saveincome(double amount, string category, string date) {
    ofstream fout("../data/income.txt", ios::app);
    if(fout.is_open()) {
        fout << category << " " << amount << " " << date << endl;
    }
    fout.close();
}

void FinanceManager::saveexpense(double amount, string category, string date) {
    ofstream fout("../data/expense.txt", ios::app);
    if(fout.is_open()) {
        fout << category << " " << amount << " " << date << endl;
    }
    fout.close();
}

void FinanceManager::savealldata(double amount, string category, string date) {
    ofstream fout("../data/projectdata.txt", ios::app);
    if(fout.is_open()) {
        fout << category << " " << amount << " " << date << endl;
    }
    fout.close();
}

void FinanceManager::displayalldata() {
    ifstream fin("../data/projectdata.txt");
    string cat, date;
    double amount;
    int i = 1;
    
    if(fin.is_open()) {
        cout << "\nNo.\tCategory\tAmount\t\tDate\n";
        cout << "----------------------------------------\n";
        while(fin >> cat >> amount >> date) {
            cout << i++ << ".\t" << cat << "\t\t$" << amount << "\t\t" << date << endl;
        }
    } else {
        cout << "No transactions found.\n";
    }
    fin.close();
}

void FinanceManager::deletealltransactions() {
    ofstream fout1("../data/income.txt", ios::trunc);
    ofstream fout2("../data/expense.txt", ios::trunc);
    ofstream fout3("../data/projectdata.txt", ios::trunc);
    ofstream fout4("../data/summary.txt", ios::trunc);
    
    fout1.close();
    fout2.close();
    fout3.close();
    fout4.close();
    
    cout << "All transactions have been deleted.\n";
    
    for(int i = 0; i < transactionCount; i++) {
        delete transactions[i];
    }
    transactionCount = 0;
    totalIncome = 0;
    totalExpenses = 0;
}

void FinanceManager::monthlydisplay() {
    cout << endl << endl;
    cout << "\n--- MONTHLY PROJECT DISPLAY ---" << endl;
    string cat, date;
    double amount;
    int f1=0, f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0;
    
    cout << "==== JANUARY ====" << endl;
    ifstream fin1("../data/projectdata.txt");
    if(fin1.is_open()) {
        while(fin1 >> cat >> amount >> date) {
            if(date[5] == '0' && date[6] == '1') {
                f1 = 1;
                cout << cat << "    " << amount << "    " << date << endl;
            }
        }
        if(f1 == 0) {
            cout << "No Transactions In The Month Of January" << endl;
        }
    }
    fin1.close();
    
    // Similar blocks for other months (February through December)
    // ... (implement for remaining months following the same pattern)
}

void FinanceManager::search() {
    string searchDate;
    cout << "Enter date to search (YYYY-MM-DD): ";
    cin >> searchDate;
    
    ifstream fin("../data/projectdata.txt");
    string cat, date;
    double amount;
    bool found = false;
    
    if(fin.is_open()) {
        cout << "\nTransactions on " << searchDate << ":\n";
        cout << "----------------------------------------\n";
        while(fin >> cat >> amount >> date) {
            if(date == searchDate) {
                cout << cat << "\t$" << amount << "\t" << date << endl;
                found = true;
            }
        }
        if(!found) {
            cout << "No transactions found on this date.\n";
        }
    }
    fin.close();
}

void FinanceManager::edittransaction() {
    displayalldata();
    
    int lineNumber;
    cout << "\nEnter the transaction number to edit: ";
    cin >> lineNumber;
    
    string cat, date, newCat, newDate;
    double amount, newAmount;
    
    ifstream fin("../data/projectdata.txt");
    ofstream temp("../data/temp.txt");
    
    int currentLine = 1;
    while(fin >> cat >> amount >> date) {
        if(currentLine == lineNumber) {
            cout << "Enter new category: ";
            cin >> newCat;
            cout << "Enter new amount: ";
            cin >> newAmount;
            cout << "Enter new date (YYYY-MM-DD): ";
            cin >> newDate;
            
            temp << newCat << " " << newAmount << " " << newDate << endl;
        } else {
            temp << cat << " " << amount << " " << date << endl;
        }
        currentLine++;
    }
    
    fin.close();
    temp.close();
    
    remove("../data/projectdata.txt");
    rename("../data/temp.txt", "../data/projectdata.txt");
    
    cout << "Transaction updated successfully.\n";
}

void FinanceManager::setLimit() {
    string category;
    double limit;
    
    cout << "Enter category for budget limit: ";
    cin >> category;
    cout << "Enter budget limit amount: $";
    cin >> limit;
    
    ofstream fout("../data/budget.txt", ios::app);
    if(fout.is_open()) {
        fout << category << " " << limit << endl;
        cout << "Budget limit set successfully.\n";
    }
    fout.close();
}

bool FinanceManager::checkLimitExceeded(const string& category, double newAmount) {
    ifstream fin("../data/budget.txt");
    string cat;
    double limit;
    
    while(fin >> cat >> limit) {
        if(cat == category) {
            ifstream exp("../data/expense.txt");
            string expCat, date;
            double amount, total = 0;
            
            while(exp >> expCat >> amount >> date) {
                if(expCat == category) {
                    total += amount;
                }
            }
            
            if(total + newAmount > limit) {
                return true;
            }
            exp.close();
        }
    }
    fin.close();
    return false;
}

void FinanceManager::setpass() {
    string pass;
    cout << "Set your password: ";
    cin >> pass;
    
    ofstream fout("../data/savedpass.txt");
    if(fout.is_open()) {
        fout << pass;
        cout << "Password set successfully.\n";
    }
    fout.close();
}

void FinanceManager::password() {
    string pass, savedpass;
    cout << "Enter password: ";
    cin >> pass;
    
    ifstream fin("../data/savedpass.txt");
    if(fin >> savedpass) {
        if(pass == savedpass) {
            cout << "Access granted.\n";
        } else {
            cout << "Incorrect password. Exiting...\n";
            exit(0);
        }
    }
    fin.close();
}