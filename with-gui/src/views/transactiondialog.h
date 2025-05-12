#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class TransactionDialog;
}

class TransactionDialog : public QDialog {
    Q_OBJECT

public:
    explicit TransactionDialog(bool isIncome = true, QWidget *parent = nullptr);
    ~TransactionDialog();

    QString getCategory() const;
    double getAmount() const;
    QString getDate() const;

private slots:
    void on_saveButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::TransactionDialog *ui;
    bool isIncomeTransaction;
};

#endif // TRANSACTIONDIALOG_H