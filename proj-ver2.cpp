#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cctype>

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
        	int n;
            cout << "Transaction limit reached!" << endl;
            cout << "To Reset your data press 1: ";
            cin >> n;
            if (n == 1) {
            	void deletealltransactions();
			}
			else {
				cout << "Wrong input. Reset data from the main menu." << endl;
			}
        }
    }

    void addExpense(double amount, string category, string date) {
        if (transactionCount < MAX_TRANSACTIONS) {
            transactions[transactionCount++] = new Expense(amount, category, date);
            totalExpenses += amount;
        } else {
			int n;
            cout << "Transaction limit reached!" << endl;
            cout << "To Reset your data press 1:   ";
            cin >> n;
            if (n == 1) {
            	void deletealltransactions();
			}
			else {
				cout << "Wrong input. Reset data from the main menu." << endl;
			}
        }
    }

    void displayTransactions(){
        cout << "\n--- Transaction History ---\n";
        displayalldata();                                       
    }

    void displaySummary(){                                        
		string cat,date;
    	double savetotalincome=0, savetotalexpense=0, netbill=0;
    	double overallincome=0, overallexpense=0;
    	ifstream fin1("income.txt", ios :: in);
    	ifstream fin2("expense.txt", ios :: in);
		ofstream fout("summary.txt", ios :: out);
		ifstream fin("summary.txt", ios :: in);
    	
    	if (fin1.is_open()){
    		while(fin1 >> cat >> overallincome >> date){
    			savetotalincome+=overallincome;
			}
		}
		
		if (fin2.is_open()){
    		while (fin2 >> cat >> overallexpense >> date){
    			savetotalexpense+=overallexpense;
			}
		}
		netbill= savetotalincome-savetotalexpense;
		if(fout.is_open()){
			fout<< savetotalincome << endl;
			fout<< savetotalexpense << endl;
			fout<< netbill << endl;
		}	
		
		fin1.close();
    	fin2.close();
		fout.close();
		
		
		double x,y,z;
		if(fin.is_open()){
			fin>> x;
			fin>> y;
			fin>> z;
				cout << "\n===YOUR TRANSACTION SUMMARY===\n";
				cout << "Total Income: $" << x << endl;
  			    cout << "Total Expenses: $" << y << endl;
     			cout << "Net Balance: $" << z << endl;
     			
     			cout << endl;
     			cout << endl;
     			cout << endl;
     			
     			if(x>=0){
     				cout << "TOTAL INCOME:    ";
				 for(int i=0;i<=(x/1000);i++){
					cout << "*";}
				}else{
				 	cout << "Balance going in negative!\n";}
				 	
				 	cout <<endl;
				 	
				 	cout << "TOTAL EXPENSES:    ";
     			if(y>=0){
				 for(int i=0;i<=(y/1000);i++){
					cout << "*";}
				}else{
				 	cout << "Balance going in negative!\n";}
				 	
				 	cout <<endl;
				 	
					cout << "NET BALANCE:    ";
				if(z>=0){
				 for(int i=0;i<=(z/1000);i++){
					cout << "*";}
				}else{
				 	cout << "Balance going in negative!\n";}
				 	
				 	cout <<endl;
     				
		}
	
		fin.close();
    	
    }
    
    void saveincome(double amount, string category, string date){  
    	ofstream fout("income.txt", ios :: app);
    	if(fout.is_open()){
    		fout << category << "    " << amount << "    " << date << endl;
    		
    		fout.close();
		}else{
			cout <<"Error opening file or file doesnot exist!" << endl;
		}
	}

	void saveexpense(double amount, string category, string date){      
    	ofstream fout("expense.txt", ios :: app);
    	if(fout.is_open()){
    		fout << category << "    " << amount << "    " << date << endl;
    		
    		fout.close();
		}else{
			cout <<"Error opening file or file doesnot exist!" << endl;
		}
	}		
	
	void savealldata(double amount, string category, string date){    
    	ofstream fout("projectdata.txt", ios :: app);
    	if(fout.is_open()){
    		fout << category << "    " << amount << "    " << date << endl;
    		
    		fout.close();
		}else{
			cout <<"Error opening file or file doesnot exist!" << endl;
		}
	}
	
	void displayalldata(){                                           
		ifstream fin("projectdata.txt", ios :: in);
		string data;
		int i=1;
		if(fin.is_open()){
    		while(getline(fin,data)){
    			cout << i << ".    " << data << endl;
    			i++;
			}
    		fin.close();
		}else{
			cout <<"Error opening file or file doesnot exist!" << endl;
		}	
	}

	void deletealltransactions(){
		int n;
	
    	while(true){
		cout << "Are You Sure You Want To Permenantly Delete All Your Transaction History? \nYes = 1\nNo=0 \nEnter choice:   " << endl;
		cin >> n;	
		if(n==1){
			ofstream fout1("projectdata.txt", ios :: trunc);
			ofstream fout2("income.txt", ios :: trunc);
			ofstream fout3("expense.txt", ios :: trunc);
			ofstream fout4("summary.txt", ios :: trunc);
			
			cout << "All Transactions Deleted! Data Erased..." << endl;
			break;
		}else if(n==0){
			cout << "Operation cancelled. No data was deleted." << endl;
            break;
		}else{
		 cout << "Please enter the correct option!" << endl;
		}
	}
	}
	
	void monthlydisplay(){
		cout <<endl << endl;
		cout << "====== MONTHLY PROJECT DISPLAY ======" << endl;
		string cat,date;
		double amount;
		int f1=0, f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0;
		
		
		cout << "==== JANUARY ====" << endl;
		ifstream fin1("projectdata.txt", ios :: in);
			if(fin1.is_open()){
    		while(fin1 >> cat >> amount >> date){
    			if(date[5] == '0' && date[6] == '1'){
    				f1 =1;
    				cout << cat << "    " << amount << "    " << date << endl;	
				}
					
			}if(f1 == 0){
						cout << "No Transactions In The Month Of January" << endl;
					}
		}
		fin1.close();
		
		cout << "==== FEBRUARY ====" << endl;
		ifstream fin2("projectdata.txt", ios :: in);
			if(fin2.is_open()){
    		while(fin2 >> cat >> amount >> date){
    			if(date[5] == '0' && date[6] == '2'){
    				f2 =1;
    				cout << cat << "    " << amount << "    " << date << endl;	
				}
					
			}if(f2 == 0){
						cout << "No Transactions In The Month Of February" << endl;
					}
		}
		fin2.close();
		
		cout << "==== MARCH ====" << endl;
		ifstream fin3("projectdata.txt", ios :: in);
			if(fin3.is_open()){
    		while(fin3 >> cat >> amount >> date){
    			if(date[5] == '0' && date[6] == '3'){
    				f3 =1;
    				cout << cat << "    " << amount << "    " << date << endl;
				}				
				}if(f3 == 0){
    				cout << "No Transactions In The Month Of March" << endl;	
					}
			
		}
		fin3.close();

		cout << "==== APRIL ====" << endl;
		ifstream fin4("projectdata.txt", ios :: in);
			if(fin4.is_open()){
    		while(fin4 >> cat >> amount >> date){
    			if(date[5] == '0' && date[6] == '4'){
    				f4 =1;
    				cout << cat << "    " << amount << "    " << date << endl;
				}
				}if(f4 == 0){
						cout << "No Transactions In The Month Of April" << endl;
					}
			}
		fin4.close();
		
		cout << "==== MAY ====" << endl;
		ifstream fin5("projectdata.txt", ios :: in);
			if(fin5.is_open()){
    		while(fin5 >> cat >> amount >> date){
    			if(date[5] == '0' && date[6] == '5'){
    				f5 =1;
    				cout << cat << "    " << amount << "    " << date << endl;		
				}
				}if(f5 == 0){
						cout << "No Transactions In The Month Of May" << endl;
					}
		}
		fin5.close();
		
		cout << "==== JUNE ====" << endl;
		ifstream fin6("projectdata.txt", ios :: in);
			if(fin6.is_open()){
    		while(fin6 >> cat >> amount >> date){
    			if(date[5] == '0' && date[6] == '6'){
    				f6 =1;
   					cout << cat << "    " << amount << "    " << date << endl;
				}
				}if(f6 == 0){
						cout << "No Transactions In The Month Of June" << endl;
					}
			}
		fin6.close();
		
		cout << "==== JULY ====" << endl;
		ifstream fin7("projectdata.txt", ios :: in);
			if(fin7.is_open()){
    		while(fin7 >> cat >> amount >> date){
    			if(date[5] == '0' && date[6] == '7'){
    				f7 =1;
    				cout << cat << "    " << amount << "    " << date << endl;
    			}
				}if(f7 == 0){
						cout << "No Transactions In The Month Of July" << endl;
					}
			}
		fin7.close();
		
		cout << "==== AUGUST ====" << endl;
		ifstream fin8("projectdata.txt", ios :: in);
			if(fin8.is_open()){
    		while(fin8 >> cat >> amount >> date){
    			if(date[5] == '0' && date[6] == '8'){
    				f8 =1;
    				cout << cat << "    " << amount << "    " << date << endl;
				}
				}if(f8 == 0){
						cout << "No Transactions In The Month Of August" << endl;
					}
			
		}
		fin8.close();
		
		cout << "==== SEPTEMBER ====" << endl;
		ifstream fin9("projectdata.txt", ios :: in);
			if(fin9.is_open()){
    		while(fin9 >> cat >> amount >> date){
    			if(date[5] == '0' && date[6] == '9'){
    				f9 =1;
    				cout << cat << "    " << amount << "    " << date << endl;	
				}				
				}if(f9 == 0){
						cout << "No Transactions In The Month Of September" << endl;
					}
		}
		fin9.close();
		
		cout << "==== OCTOBER ====" << endl;
		ifstream fin10("projectdata.txt", ios :: in);
			if(fin10.is_open()){
    		while(fin10 >> cat >> amount >> date){
    			if(date[5] == '1' && date[6] == '0'){
    				f10 =1;
    				cout << cat << "    " << amount << "    " << date << endl;	
				}			
				}if(f10 == 0){
						cout << "No Transactions In The Month Of October" << endl;
					}
		}
		fin10.close();
		
		cout << "==== NOVEMBER ====" << endl;
		ifstream fin11("projectdata.txt", ios :: in);
			if(fin11.is_open()){
    		while(fin11 >> cat >> amount >> date){
    			if(date[5] == '1' && date[6] == '1'){
    				f11 =1;
        			cout << cat << "    " << amount << "    " << date << endl;
				}
				}if(f11 == 0){
						cout << "No Transactions In The Month Of November" << endl;
					}
		}
		fin11.close();
		
		cout << "==== DECEMBER ====" << endl;
		ifstream fin12("projectdata.txt", ios :: in);
			if(fin12.is_open()){
    		while(fin12 >> cat >> amount >> date){
    			if(date[5] == '1' && date[6] == '2'){
    				f12 =1;
    				cout << cat << "    " << amount << "    " << date << endl;
				}
				}if(f12 == 0){
						cout << "No Transactions In The Month Of December" << endl;
					}
		}
		fin12.close();
		cout << endl << endl;
	
	}
	
	void search(){
		string cat, date, line;
		double amt;
		int i=0;
		cin.ignore();
		cout << "Enter Date Or Type Of Category To Search The Transaction:  " ;
		getline(cin,line);
		
		for(int j=0; j< line.length(); j++){
            	line[j] = toupper(line[j]);
			}
			
		ifstream fin("projectdata.txt", ios :: in);
		
		while(fin >> cat >> amt >> date){
			if(line == cat || line ==date){
				cout << "\n--- Transaction(s) Found ---\n";
				cout << cat << "    " << amt << "    " << date << endl;	
				i=1;
			}
		}
		if(i==0){
			cout << "No Transaction Found" << endl;
		}
		cout << endl;
	}
	
    void setpass(){
	string l;
	cout << "Set Your Password:   ";
	cin >> l;
	
	ofstream fout("savedpass.txt", ios :: out);
	
	if(fout.is_open()){
		fout << l;	
		fout.close();
	}else{
		cout <<"Error opening file or file doesnot exist!" << endl;
	}
	cout << "\nYour passcode was set please save it somewhere!" << endl;
	}
	
	void password(){
	string code;
	string password;
	int i=0;	
	
	ifstream fin("savedpass.txt", ios :: in);
	if(fin.is_open()){
		getline(fin,code);
	}else{
		cout <<"Error opening file or file doesnot exist!" << endl;
	}
	
	while(i!=3){
		cout << "ENTER YOUR PASSCODE PLEASE:   ";
		cin>> password;
		
	if(password==code){
		cout << "WELCOME!" <<endl;
		break;
		}else{
		cout << "Password is incorrect! Try again.\n";
		i++;
		if(i==3){
		cout << "Trying limit reached!";
		exit(0);
		}
	}
	}
	fin.close();
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
    int i;
		cout << "\n=== PERSONAL FINANCE TRACKER ===\n";
		
			ifstream file1("passcheck.txt", ios :: in);
	
				if(file1 >> i){
					myFinance.password();
				}else{
					ofstream file("passcheck.txt", ios :: out);
					myFinance.setpass();
				if(file.is_open()){
					file << 1 ;
				}
				file.close();
						myFinance.password();
				
			}
			file1.close();
			
        
    do {
        
        cout << "1. Add Income\n";				//done
        cout << "2. Add Expense\n"; 			//done
        cout << "3. View Transactions\n";		//done
        cout << "4. Edit Transactions\n";							//needs format of date checking and alpha capital or small
        cout << "5. Search Transactions\n";		//done
        cout << "6. Monthly Transactions List\n";//done
        cout << "7. Delete Transactions\n";		//done
        cout << "8. Set Transaction Limit\n";							// limit setting for transaction types option no 8
	    cout << "9. View Summary\n";			//done
        cout << "10. Exit\n";					//done
        
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            double amount;
            string category, date;
            cout << "Enter amount: ";
            cin >> amount;
            cout << "Enter category (e.g., Salary, Bonus): ";
            cin >> category;
            for(int i=0; i< category.length(); i++){
            	category[i] = toupper(category[i]);
			}
			
           	while(1){
		   		cout << "Enter date (YYYY-MM-DD): ";
				cin >> date;
				if (date[4] == '-' && date[7] == '-') {
   					     break;
   				 } else {
   					     cout << "Wrong format. Input according to the mentioned criteria please." << endl;
   				 }
		   	} 
            
            myFinance.addIncome(amount, category, date);
            myFinance.saveincome(amount, category, date);
            myFinance.savealldata(amount, category, date);
        }
        else if (choice == 2) {
            double amount;
            string category, date;
            cout << "Enter amount: ";
            cin >> amount;
            
            cout << "Enter category (e.g., Rent, Food, Bills): ";
            cin >> category;
            for(int i=0; i< category.length(); i++){
            	category[i] = toupper(category[i]);
			}
			
            while(1){
		   		cout << "Enter date (YYYY-MM-DD): ";
				cin >> date;
				if (date[4] == '-' && date[7] == '-') {
   					     break;
   				 } else {
   					     cout << "Wrong format. Input according to the mentioned criteria please." << endl;
   				 }
		   	}
		   	
            myFinance.addExpense(amount, category, date);
            myFinance.saveexpense(amount, category, date);
            myFinance.savealldata(amount, category, date);
        }
        else if (choice == 3) {
            myFinance.displayTransactions();
        }
		else if (choice == 4) {
			//edit
		}
		else if (choice == 5) {
			myFinance.search();
		}
		else if (choice == 6) {
			myFinance.monthlydisplay();
		}
		else if (choice == 7) {
			myFinance.deletealltransactions();
		}
		else if (choice == 8) {
            		//limit setting
        }
		else if (choice == 9) {
            myFinance.displaySummary();
        }
    } while (choice != 10);
    
    cout << "Exiting...\n";
    return 0;
}
