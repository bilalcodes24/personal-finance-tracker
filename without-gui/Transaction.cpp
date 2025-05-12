#include "../include/Transaction.h"

Transaction::Transaction(double amt, string cat, string dt)
    : amount(amt), category(cat), date(dt) {}

void Transaction::displayTransaction() const {
    cout << date << " | " << category << " | $" << amount << endl;
}

Transaction::~Transaction() {}

double Transaction::getAmount() const { 
    return amount; 
}

string Transaction::getCategory() const { 
    return category; 
}

// Income implementation
Income::Income(double amt, string cat, string dt) 
    : Transaction(amt, cat, dt) {}

void Income::displayTransaction() const {
    cout << "[INCOME] " << date << " | " << category << " | +$" << amount << endl;
}

// Expense implementation
Expense::Expense(double amt, string cat, string dt) 
    : Transaction(amt, cat, dt) {}

void Expense::displayTransaction() const {
    cout << "[EXPENSE] " << date << " | " << category << " | -$" << amount << endl;
}