#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// --- Transaction Class ---
class Transaction {
public:
    string type;
    double amount;
    string date; // Simplified as a string for this example

    Transaction(string t, double amt) : type(t), amount(amt) {
        date = "2026-02-04"; // Current date
    }

    void display() const {
        cout << left << setw(15) << type << " | $" << setw(10) << amount << " | " << date << endl;
    }
};

// --- Account Class ---
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> history;

public:
    Account(int accNum, double initialDeposit) : accountNumber(accNum), balance(initialDeposit) {
        if (initialDeposit > 0) {
            history.push_back(Transaction("Initial Deposit", initialDeposit));
        }
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            history.push_back(Transaction("Deposit", amount));
            cout << "Successfully deposited $" << amount << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
            return false;
        }
        balance -= amount;
        history.push_back(Transaction("Withdrawal", amount));
        cout << "Successfully withdrew $" << amount << endl;
        return true;
    }

    double getBalance() const { return balance; }
    int getAccountNumber() const { return accountNumber; }

    void displayHistory() const {
        cout << "\n--- Transaction History for Acc #" << accountNumber << " ---" << endl;
        for (const auto& t : history) {
            t.display();
        }
        cout << "Current Balance: $" << balance << endl;
    }
};

// --- Customer Class ---
class Customer {
private:
    string name;
    Account* account; // A customer has an account

public:
    Customer(string n, int accNum, double initialBal) {
        name = n;
        account = new Account(accNum, initialBal);
    }

    ~Customer() { delete account; }

    void viewProfile() {
        cout << "\nCustomer: " << name << endl;
        account->displayHistory();
    }

    Account* getAccount() { return account; }
};

// --- System Controller ---
void transferFunds(Customer& sender, Customer& receiver, double amount) {
    cout << "\nInitiating Transfer..." << endl;
    if (sender.getAccount()->withdraw(amount)) {
        receiver.getAccount()->deposit(amount);
        cout << "Transfer of $" << amount << " completed." << endl;
    } else {
        cout << "Transfer failed." << endl;
    }
}

int main() {
    Customer alice("Alice Smith", 1001, 500.0);
    Customer bob("Bob Jones", 1002, 200.0);

    alice.getAccount()->deposit(150.0);
    alice.getAccount()->withdraw(50.0);

    transferFunds(alice, bob, 200.0);

    // 4. Display Results
    alice.viewProfile();
    bob.viewProfile();

    return 0;
}