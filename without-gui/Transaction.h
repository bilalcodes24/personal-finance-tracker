#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>

using namespace std;

class Transaction {
protected:
    double amount;
    string category;
    string date;

public:
    Transaction(double amt, string cat, string dt);
    virtual void displayTransaction() const;
    virtual ~Transaction();
    double getAmount() const;
    string getCategory() const;
};

class Income : public Transaction {
public:
    Income(double amt, string cat, string dt);
    void displayTransaction() const override;
};

class Expense : public Transaction {
public:
    Expense(double amt, string cat, string dt);
    void displayTransaction() const override;
};

#endif