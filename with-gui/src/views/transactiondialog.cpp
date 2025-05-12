#include "transactiondialog.h"
#include "ui_transactiondialog.h"
#include <QMessageBox>

TransactionDialog::TransactionDialog(bool isIncome, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TransactionDialog)
    , isIncomeTransaction(isIncome)
{
    ui->setupUi(this);
    setWindowTitle(isIncome ? "Add Income" : "Add Expense");
    ui->dateEdit->setDate(QDate::currentDate());

    connect(ui->saveButton, &QPushButton::clicked, this, &TransactionDialog::on_saveButton_clicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &TransactionDialog::on_cancelButton_clicked);
}

TransactionDialog::~TransactionDialog()
{
    delete ui;
}

QString TransactionDialog::getCategory() const
{
    return ui->categoryLineEdit->text();
}

double TransactionDialog::getAmount() const
{
    return ui->amountSpinBox->value();
}

QString TransactionDialog::getDate() const
{
    return ui->dateEdit->date().toString("yyyy-MM-dd");
}

void TransactionDialog::on_saveButton_clicked()
{
    if (ui->categoryLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please enter a category.");
        return;
    }
    if (ui->amountSpinBox->value() <= 0) {
        QMessageBox::warning(this, "Validation Error", "Amount must be greater than 0.");
        return;
    }
    accept();
}

void TransactionDialog::on_cancelButton_clicked()
{
    reject();
}