#include <iostream>
#include <string>

using namespace std;

const int MAX_TRANSACTIONS = 100;

class Transaction {
protected:
    double amount;
    string category;
    string date;

public:
    Transaction(double amt, string cat, string dt)
        : amount(amt), category(cat), date(dt) {}

    virtual void displayTransaction() const {
        cout << date << " | " << category << " | $" << amount << endl;
    }

    virtual ~Transaction() {}

    double getAmount() const { return amount; }
    string getCategory() const { return category; }
};

class Income : public Transaction {
public:
    Income(double amt, string cat, string dt) : Transaction(amt, cat, dt) {}

    void displayTransaction() const override {
        cout << "[INCOME] " << date << " | " << category << " | +$" << amount << endl;
    }
};

class Expense : public Transaction {
public:
    Expense(double amt, string cat, string dt) : Transaction(amt, cat, dt) {}

    void displayTransaction() const override {
        cout << "[EXPENSE] " << date << " | " << category << " | -$" << amount << endl;
    }
};

class FinanceManager {
private:
    Transaction* transactions[MAX_TRANSACTIONS];
    int transactionCount = 0;
    double totalIncome = 0;
    double totalExpenses = 0;

public:
    void addIncome(double amount, string category, string date) {
        if (transactionCount < MAX_TRANSACTIONS) {
            transactions[transactionCount++] = new Income(amount, category, date);
            totalIncome += amount;
        } else {
            cout << "Transaction limit reached!" << endl;
        }
    }

    void addExpense(double amount, string category, string date) {
        if (transactionCount < MAX_TRANSACTIONS) {
            transactions[transactionCount++] = new Expense(amount, category, date);
            totalExpenses += amount;
        } else {
            cout << "Transaction limit reached!" << endl;
        }
    }

    void displayTransactions() const {
        cout << "\n--- Transaction History ---\n";
        for (int i = 0; i < transactionCount; ++i) {
            transactions[i]->displayTransaction();
        }
        cout << "-----------------------------\n";
    }

    void displaySummary() const {
        cout << "\n--- Financial Summary ---\n";
        cout << "Total Income: $" << totalIncome << endl;
        cout << "Total Expenses: $" << totalExpenses << endl;
        cout << "Net Balance: $" << (totalIncome - totalExpenses) << endl;
        cout << "-----------------------------\n";
    }

    ~FinanceManager() {
        for (int i = 0; i < transactionCount; ++i) {
            delete transactions[i];
        }
    }
};

int main() {
    FinanceManager myFinance;
    int choice;

    do {
        cout << "\n=== Personal Finance Tracker ===\n";
        cout << "1. Add Income\n";
        cout << "2. Add Expense\n";
        cout << "3. View Transactions\n";
        cout << "4. View Summary\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            double amount;
            string category, date;
            cout << "Enter amount: ";
            cin >> amount;
            cout << "Enter category (e.g., Salary, Bonus): ";
            cin >> category;
            cout << "Enter date (YYYY-MM-DD): ";
            cin >> date;
            myFinance.addIncome(amount, category, date);
        }
        else if (choice == 2) {
            double amount;
            string category, date;
            cout << "Enter amount: ";
            cin >> amount;
            cout << "Enter category (e.g., Rent, Food, Bills): ";
            cin >> category;
            cout << "Enter date (YYYY-MM-DD): ";
            cin >> date;
            myFinance.addExpense(amount, category, date);
        }
        else if (choice == 3) {
            myFinance.displayTransactions();
        }
        else if (choice == 4) {
            myFinance.displaySummary();
        }

    } while (choice != 5);

    cout << "Exiting...\n";
    return 0;
}
