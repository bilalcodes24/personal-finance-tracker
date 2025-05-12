#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "../models/financemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addIncomeButton_clicked();
    void on_addExpenseButton_clicked();
    void updateTransactionTable();
    void updateSummary();

private:
    Ui::MainWindow *ui;
    FinanceManager *financeManager;
    void setupConnections();
};

#endif