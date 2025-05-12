#include "FinanceManager.h"
#include <iostream>
#include <fstream>

int main() {
    FinanceManager myFinance;
    int choice;
    
    cout << "\n=== PERSONAL FINANCE TRACKER ===\n";
    
    ifstream file1("passcheck.txt");
    int i;
    
    if(file1 >> i) {
        myFinance.password();
    } else {
        ofstream file("passcheck.txt");
        myFinance.setpass();
        if(file.is_open()) {
            file << 1;
        }
        file.close();
        myFinance.password();
    }
    file1.close();

    do {
        cout << "\n1. Add Income\n";
        cout << "2. Add Expense\n";
        cout << "3. View Transactions\n";
        cout << "4. View Summary\n";
        cout << "5. View Monthly Report\n";
        cout << "6. Search Transactions\n";
        cout << "7. Edit Transaction\n";
        cout << "8. Set Budget Limit\n";
        cout << "9. Delete All Transactions\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                double amount;
                string category, date;
                cout << "\nEnter income details:\n";
                cout << "Amount: $";
                cin >> amount;
                cout << "Category: ";
                cin >> category;
                cout << "Date (YYYY-MM-DD): ";
                cin >> date;
                myFinance.addIncome(amount, category, date);
                break;
            }
            case 2: {
                double amount;
                string category, date;
                cout << "\nEnter expense details:\n";
                cout << "Amount: $";
                cin >> amount;
                cout << "Category: ";
                cin >> category;
                cout << "Date (YYYY-MM-DD): ";
                cin >> date;
                myFinance.addExpense(amount, category, date);
                break;
            }
            case 3:
                myFinance.displayTransactions();
                break;
            case 4:
                myFinance.displaySummary();
                break;
            case 5:
                myFinance.monthlydisplay();
                break;
            case 6:
                myFinance.search();
                break;
            case 7:
                myFinance.edittransaction();
                break;
            case 8:
                myFinance.setLimit();
                break;
            case 9: {
                char confirm;
                cout << "Are you sure you want to delete all transactions? (y/n): ";
                cin >> confirm;
                if(confirm == 'y' || confirm == 'Y') {
                    myFinance.deletealltransactions();
                }
                break;
            }
            case 10:
                cout << "Thank you for using Personal Finance Tracker!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 10);
    
    cout << "Exiting...\n";
    return 0;
}
