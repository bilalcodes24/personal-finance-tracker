#include "transaction.h"
#include <iostream>

Transaction::Transaction(double amt, const QString& cat, const QString& dt, const QString& typ)
    : amount(amt)
    , category(cat)
    , date(dt)
    , type(typ)
{
}

void Transaction::displayTransaction() const {
    std::cout << date << " | " << category << " | $" << amount << std::endl;
}

Transaction::~Transaction() {}

double Transaction::getAmount() const { 
    return amount; 
}

std::string Transaction::getCategory() const { 
    return category; 
}

// Income implementation
Income::Income(double amt, const std::string& cat, const std::string& dt) 
    : Transaction(amt, cat, dt) {}

void Income::displayTransaction() const {
    std::cout << "[INCOME] " << date << " | " << category << " | +$" << amount << std::endl;
}

// Expense implementation
Expense::Expense(double amt, const std::string& cat, const std::string& dt) 
    : Transaction(amt, cat, dt) {}

void Expense::displayTransaction() const {
    std::cout << "[EXPENSE] " << date << " | " << category << " | -$" << amount << std::endl;
}