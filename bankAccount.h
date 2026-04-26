#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <iostream>
#include <string> 

// base Class
class bankAccount {
protected:
	std::string* accountNumber;
	std::string accountHolderName;
	double balance;

public: //Default constructor
	bankAccount();
	bankAccount(std::string accNum, std::string name, double bal);

	//Rule of three
	virtual ~bankAccount(); //Virtual destructor
	bankAccount(const bankAccount& other); //to copy constructor
	bankAccount& operator=(const bankAccount& other); //copy assigment operator

	//Virtual withdraw
	virtual void withdraw(double amount);
	void deposit(double amount);

	//Operator overloading
	bankAccount& operator+=(double amount);
	double getBalance() const { return balance; }
	std::string getAccountHolderName() const { return accountHolderName; }

	static void printAccount(const bankAccount& account);
};
//Checking Acct Class 
class CheckingAccount : public bankAccount {
private:
	double transactionFee;

public:
	CheckingAccount(std::string num, std::string name, double bal, double fee);


	void withdraw(double amount) override;
};

//Savings Acct Class
class SavingsAccount : public bankAccount {
private:
	double interestRate;

public:
	SavingsAccount(std::string num, std::string name, double bal, double rate);

	void calculateInterest();
};

#endif

