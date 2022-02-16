#ifndef WALLET_HPP
#define WALLET_HPP

#include <QGraphicsTextItem>

class Wallet
{
public:
    Wallet(int ammount);
    void Deposit(int ammount);
    bool Withdraw(int ammount);
    int  GetBalance() const;
    void SetNewBalance(int ammount);
private:
    int balance_;
};

#endif // WALLET_HPP
