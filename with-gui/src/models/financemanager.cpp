#include "financemanager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

FinanceManager::FinanceManager() : transactionCount(0), totalIncome(0), totalExpenses(0) 
{
    // Load saved transactions here if needed
}

void FinanceManager::addIncome(double amount, const QString& category, const QString& date)
{
    transactions.append(std::make_shared<Transaction>(amount, category, date, "Income"));
    totalIncome += amount;
    transactionCount++;
    saveTransaction("Income", amount, category, date);
}

void FinanceManager::addExpense(double amount, const QString& category, const QString& date)
{
    transactions.append(std::make_shared<Transaction>(amount, category, date, "Expense"));
    totalExpenses += amount;
    transactionCount++;
    saveTransaction("Expense", amount, category, date);
}

void FinanceManager::saveTransaction(const QString& type, double amount, 
                                   const QString& category, const QString& date)
{
    QFile file(type.toLower() + ".txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << date << "," << category << "," << amount << Qt::endl;
        file.close();
    }
}

FinanceManager::~FinanceManager() {
    for (int i = 0; i < transactionCount; i++) {
        delete transactions[i];
    }
}