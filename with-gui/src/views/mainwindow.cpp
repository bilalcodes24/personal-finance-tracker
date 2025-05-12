#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "transactiondialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , financeManager(new FinanceManager)
{
    ui->setupUi(this);
    setupConnections();
    updateTransactionTable();
    updateSummary();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete financeManager;
}

void MainWindow::setupConnections()
{
    connect(ui->addIncomeButton, &QPushButton::clicked, this, &MainWindow::on_addIncomeButton_clicked);
    connect(ui->addExpenseButton, &QPushButton::clicked, this, &MainWindow::on_addExpenseButton_clicked);
}

void MainWindow::on_addIncomeButton_clicked()
{
    TransactionDialog dialog(true, this);
    if (dialog.exec() == QDialog::Accepted) {
        financeManager->addIncome(dialog.getAmount(), dialog.getCategory(), dialog.getDate());
        updateTransactionTable();
        updateSummary();
    }
}

void MainWindow::on_addExpenseButton_clicked()
{
    TransactionDialog dialog(false, this);
    if (dialog.exec() == QDialog::Accepted) {
        financeManager->addExpense(dialog.getAmount(), dialog.getCategory(), dialog.getDate());
        updateTransactionTable();
        updateSummary();
    }
}

void MainWindow::updateTransactionTable()
{
    // Clear existing items
    ui->transactionsTable->setRowCount(0);
    
    // Add transactions to table
    const auto& transactions = financeManager->getTransactions();
    for (const auto& transaction : transactions) {
        int row = ui->transactionsTable->rowCount();
        ui->transactionsTable->insertRow(row);
        
        ui->transactionsTable->setItem(row, 0, new QTableWidgetItem(transaction->getDate()));
        ui->transactionsTable->setItem(row, 1, new QTableWidgetItem(transaction->getType()));
        ui->transactionsTable->setItem(row, 2, new QTableWidgetItem(transaction->getCategory()));
        ui->transactionsTable->setItem(row, 3, new QTableWidgetItem(QString::number(transaction->getAmount(), 'f', 2)));
    }
}

void MainWindow::updateSummary()
{
    double totalIncome = financeManager->getTotalIncome();
    double totalExpenses = financeManager->getTotalExpenses();
    double balance = totalIncome - totalExpenses;
    
    QString summary = QString("Total Income: $%1\nTotal Expenses: $%2\nBalance: $%3")
        .arg(totalIncome, 0, 'f', 2)
        .arg(totalExpenses, 0, 'f', 2)
        .arg(balance, 0, 'f', 2);
    
    ui->summaryLabel->setText(summary);
}