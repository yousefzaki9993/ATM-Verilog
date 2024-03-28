#include <iostream>
// new test 
#include <string>
using namespace std;

int account_sn;		//current account serial number

const int numberOfAccounts = 4;
int accounts[numberOfAccounts][3] =
{		{50602, 8030, 5000},
		{28764, 1215, 8000},
		{12825, 1234, 7500},
		{34345, 3333, 3000},
};

int *account_num, *pin, *balance;

//functions

void idle();
void home();
bool validate_acc(int acc);
bool validate_pin(int pin);
int  find_account(int acc);
bool proceed(char response);
void withdraw();
void allow_withdraw(int n);
void confirm();
void print();
void deposit();
void transfer();
void allow_transfer(int n);
void show_balance();
void change_pin();
void another_transaction();
void eject_card();


	int main() {
		idle();
		return 0;
	}

	void idle(){
		int account_num_input, pin_input, chances = 3;
		cout<<"---------------------------------------------\n";
		cout<<"\nWelcome to the ATM.\nPlease insert your card." << endl;
		cin >> account_num_input;
		if(validate_acc(account_num_input)) {
			cout << "Enter the pin number: ";
			
			while(chances != 0) {
				cin >> pin_input;
				if(validate_pin(pin_input)) {
					account_num = &accounts[account_sn][0];
					pin = &accounts[account_sn][1];
					balance = &accounts[account_sn][2];
					home();
					break;
				} else {
					chances--;
					cout << "Invalid pin. " << chances << " tries left\n"; 
				}
			}
			
			eject_card(); 	//incorrect pin
		} else {
			cout << "\nSomething went wrong\n";
			eject_card(); 	//invalid account
		}
	}

	bool validate_acc(int acc) {
		for(int i = 0; i < numberOfAccounts; i++)
			if (acc == accounts[i][0]) {
				account_sn = i;
				return true;
			}
		return false;
	}

	bool validate_pin(int pin) {
		if(pin == accounts[account_sn][1])
			return true;
		else 
			return false;
	}

	int find_account(int acc) { 		// returns account index if found, else returns -1
		for(int i = 0; i < numberOfAccounts; i++)
			if (acc == accounts[i][0])
				return i;
		return -1;
	}

	bool proceed(char response) {
		while(true) {
			if(response == 'y' || response == 'Y')
				return true;
			else 
				return false;
		}
	}

	void home() {
		int option;
		cout << "\n\t--- Main Menu ---\n" << endl;
		cout << "Choose a transaction:" << endl;
		cout << "\t1. Check balance" << "\n\t2. Withdraw" << "\n\t3. Deposit"
			 << "\n\t4. Transfer"    << "\n\t5. Change Pin" << endl;
		cin >> option;
	
		switch(option) {
			case 0:
				eject_card();
				break;
			case 1:
				show_balance();
				break;
			case 2: 
				withdraw();
				break;
			case 3: 
				deposit();
				break;
			case 4:
				transfer();
				break;
			case 5:
				change_pin();
				break;
			default:
				cout << "Invalid input.\nPlease choose from 0 to 5: ";
				home();						////////////
		}
	}

	void another_transaction(){
		cout<<"Do you want to make another transaction? (y/n)"<<endl;
		char cont;
		cin >> cont;
		if(proceed(cont))
			home();
		else
			eject_card();
	}

	void change_pin() {
		int new_pin;
		cout << "Enter the new pin: ";
		cin >> new_pin;
		*pin = new_pin;
		another_transaction();
	}

	void withdraw(){
		int withdraw_amount;
		cout << "Enter amount to withdrawn: " << endl;
		cin >> withdraw_amount;
		allow_withdraw(withdraw_amount);
	}

	void allow_withdraw(int withdraw_amount) {
		if(withdraw_amount <= *balance) {
			*balance -= withdraw_amount;
			cout << "Dispensing " << "$"<< withdraw_amount << endl;
			confirm();
		} else {
			cout << "Insufficent funds.. Ejecting card" << endl;
			eject_card();
		}
	}

	void confirm() {
		cout << "Do you want to print a receipt? (y/n)" << endl;
		char take_receipt;
		cin >> take_receipt;
		if (proceed(take_receipt))
			print();
		else
			another_transaction();
	}

	void print() {
		cout << "Your account balance is:	 $" << *balance << endl;
		another_transaction();
	}

	void deposit() {
		int deposit_amount;
		cout << "Enter an amount to deposit: ";
		cin >> deposit_amount;
		
		*balance += deposit_amount;
		cout << "$" << deposit_amount << " was deposited successfully.\n";
		confirm();
	}

	void transfer() {
		int count = 3, acc, account_num_input;
		cout << "Enter the account you want to transfer to: ";
		while(count != 0) {
			cin >> account_num_input;
			if(account_num_input == *account_num){
			cout << "\nInvalid input. you can't transfer for your account\n";
			eject_card();
			}
			acc = find_account(account_num_input);
			if(acc == -1) {
				count--;
				cout << "Incorrect account. " << count << " tries left\t";
			} else {
				cout << "Account Verified\n";
				break;
			}
		}
		if(count == 0)
			eject_card();
		else
			allow_transfer(acc);
	}

	void allow_transfer(int loc) {
		int amount_transfer;
		cout << "Enter amount to transfer: ";
		cin >> amount_transfer;
		if(amount_transfer <= *balance) {
			*balance -= amount_transfer;
			accounts[loc][2] += amount_transfer;
			cout << "$" << amount_transfer << " has been transfered and deducted from your account" << endl;
			confirm();
		} else {
			cout << "Insuffient funds." << endl;
			eject_card();
		}
	}
		
	void show_balance() {
		cout << "Your account balance is $" << *balance << endl;
		confirm();
	}

	void eject_card() {
		cout << "\nThank you for being our client\n\tSee you soon\n";
		account_num = pin = balance = NULL; 
		cout<<"\nCard Ejected\n\n";
		idle();
	}
