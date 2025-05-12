#ifndef FINANCE_MANAGER_H
#define FINANCE_MANAGER_H

#include "transaction.h"
#include <vector>
#include <QString>
#include <QList>
#include <memory>

class FinanceManager : public QObject {
    Q_OBJECT

public:
    FinanceManager();
    void addIncome(double amount, const QString& category, const QString& date);
    void addExpense(double amount, const QString& category, const QString& date);
    double getTotalIncome() const { return totalIncome; }
    double getTotalExpenses() const { return totalExpenses; }
    const QList<std::shared_ptr<Transaction>>& getTransactions() const { return transactions; }

private:
    QList<std::shared_ptr<Transaction>> transactions;
    int transactionCount;
    double totalIncome;
    double totalExpenses;
    
    void saveTransaction(const QString& type, double amount, 
                        const QString& category, const QString& date);
};

#endif