#ifndef FINANCE_MANAGER_H
#define FINANCE_MANAGER_H

#include "Transaction.h"
#include <string>

using namespace std;

const int MAX_TRANSACTIONS = 100;

class FinanceManager {
private:
    Transaction* transactions[MAX_TRANSACTIONS];
    int transactionCount;
    double totalIncome;
    double totalExpenses;

public:
    FinanceManager();
    ~FinanceManager();
    
    void addIncome(double amount, string category, string date);
    void addExpense(double amount, string category, string date);
    void displayTransactions();
    void displaySummary();
    void saveincome(double amount, string category, string date);
    void saveexpense(double amount, string category, string date);
    void savealldata(double amount, string category, string date);
    void displayalldata();
    void deletealltransactions();
    void monthlydisplay();
    void search();
    void edittransaction();
    void setLimit();
    bool checkLimitExceeded(const string& category, double newAmount);
    void setpass();
    void password();
};

#endif