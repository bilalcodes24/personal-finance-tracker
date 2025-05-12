# Personal Finance Tracker Qt Application

This project is a simple GUI application for managing personal finances using the Qt framework. It allows users to track their income and expenses, view transaction history, and manage budget limits.

## Project Structure

```
finance-tracker-qt
├── src
│   ├── main.cpp                # Entry point of the application
│   ├── models
│   │   ├── transaction.h       # Defines the Transaction class
│   │   ├── transaction.cpp     # Implements the Transaction class methods
│   │   ├── financemanager.h    # Defines the FinanceManager class
│   │   └── financemanager.cpp  # Implements the FinanceManager class methods
│   ├── views
│   │   ├── mainwindow.h        # Defines the MainWindow class
│   │   ├── mainwindow.cpp      # Implements the MainWindow class methods
│   │   ├── mainwindow.ui       # Qt Designer file for the main window
│   │   ├── transactiondialog.h  # Defines the TransactionDialog class
│   │   ├── transactiondialog.cpp# Implements the TransactionDialog class methods
│   │   └── transactiondialog.ui # Qt Designer file for the transaction dialog
│   └── resources
│       └── icons.qrc          # Resource file for icons and images
├── data
│   ├── income.txt              # Stores income transaction data
│   ├── expense.txt             # Stores expense transaction data
│   ├── projectdata.txt         # Stores all transaction data
│   └── budget.txt              # Stores budget limit data
├── CMakeLists.txt              # CMake configuration file
├── .gitignore                  # Git ignore file
└── README.md                   # Project documentation
```

## Building the Application

1. Ensure you have CMake and Qt installed on your system.
2. Clone the repository or download the project files.
3. Open a terminal and navigate to the project directory.
4. Create a build directory:
   ```
   mkdir build
   cd build
   ```
5. Run CMake to configure the project:
   ```
   cmake ..
   ```
6. Build the project:
   ```
   make
   ```
7. Run the application:
   ```
   ./finance-tracker-qt
   ```

## Features

- Add income and expenses
- View transaction history
- Display financial summaries
- Set budget limits
- Edit and delete transactions

## License

This project is licensed under the MIT License. See the LICENSE file for more details.