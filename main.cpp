#include "bankAccount.h"
#include <vector>
#include <memory>

bankAccount::bankAccount() {
	accountNumber = new std::string("000");
	accountHolderName = "New Account";
	balance = 0.0;
}

bankAccount::bankAccount(std::string accNum, std::string name, double bal) {
	accountNumber = new std::string(accNum);
	accountHolderName = name;
	balance = bal;
}

bankAccount::~bankAccount() {
	delete accountNumber;
}

bankAccount::bankAccount(const bankAccount& other) {
	accountNumber = new std::string(*other.accountNumber);
	accountHolderName = other.accountHolderName;
	balance = other.balance;
}
bankAccount& bankAccount::operator=(const bankAccount& other) {
	if (this != &other) {
		delete accountNumber;
		accountNumber = new std::string(*other.accountNumber);
		accountHolderName = other.accountHolderName;
		balance = other.balance;
	}
	return *this;
}
void bankAccount::withdraw(double amount) {
	if (amount > 0 && amount <= balance) {
		balance -= amount;
	}
	else {
		std::cout << "Insufficient funds or invalid amount." << std::endl;
	}
}

void bankAccount::deposit(double amount) {
	if (amount > 0) balance += amount;
}

bankAccount& bankAccount::operator+=(double amount) {
	deposit(amount);
	return *this;
}

//Adding the CHedking acct
CheckingAccount::CheckingAccount(std::string num, std::string name, double bal, double fee)
	: bankAccount(num, name, bal), transactionFee(fee) {}

void CheckingAccount::withdraw(double amount) {
	std::cout << "Applying transaction fee of $" << transactionFee << "..." << std::endl;
	bankAccount::withdraw(amount + transactionFee);
}

//Adding the Savings acct
SavingsAccount::SavingsAccount(std::string num, std::string name, double bal, double rate)
	: bankAccount(num, name, bal), interestRate(rate) {
}

void SavingsAccount::calculateInterest() {
	double interest = balance * interestRate;
	balance += interest;
	std::cout << "Interest added: $" << interest << std::endl;
}

//*********Static Utilities
void bankAccount::printAccount(const bankAccount& account) {
	std::cout << "\n--- Account Details ---" << std::endl;
	std::cout << "Number: " << *account.accountNumber << std::endl;
	std::cout << "Holder: " << account.accountHolderName << std::endl;
	std::cout << "Balance: $" << account.balance << std::endl;
}


//*****MAIN FUNCTION WITH POLYMORPHIC
int main() {
	
	std::vector<std::unique_ptr<bankAccount>> myAccounts;

	myAccounts.push_back(std::make_unique<CheckingAccount>("CH100", "Sandra's Checking Account", 1000.0, 2.50));
	myAccounts.push_back(std::make_unique<SavingsAccount>("SV200", "Sandra's Savings Account", 5000.0, 0.05));

	std::cout << "--- Testing Polymorphic Withdrawal ---" << std::endl;

	for (const auto& acc : myAccounts) {
		std::cout << "\nAccount: " << acc->getAccountHolderName() << std::endl;
		
		acc->withdraw(100.0);
		std::cout << "New Balance: $" << acc->getBalance() << std::endl;
	}

	SavingsAccount* savings = dynamic_cast<SavingsAccount*>(myAccounts[1].get());
	if (savings) {
		std::cout << "\n--- Calculating Interest for Savings ---" << std::endl;
		savings->calculateInterest();
		std::cout << "Balance after interest: $" << savings->getBalance() << std::endl;
	}

	return 0;
}