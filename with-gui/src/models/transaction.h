#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>

class Transaction {
public:
    Transaction(double amt, const QString& cat, const QString& dt, const QString& typ);
    virtual ~Transaction() = default;

    double getAmount() const { return amount; }
    QString getCategory() const { return category; }
    QString getDate() const { return date; }
    QString getType() const { return type; }

protected:
    double amount;
    QString category;
    QString date;
    QString type;
};

#endif