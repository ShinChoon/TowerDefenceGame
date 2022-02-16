#include "wallet.hpp"

#include <QFont>

/**
 * @brief Construct a new Wallet:: Wallet object
 * 
 * @param balance Player balance 
 */
Wallet::Wallet(int balance): balance_(balance)
{}

/**
 * @brief Deposit money to player wallet
 * 
 * @param ammount 
 */
void Wallet::Deposit(int ammount)
{
    balance_+=ammount;
}


/**
 * @brief Withdraw money from player wallet
 * @param ammount
 * @return None
 */
bool Wallet::Withdraw(int ammount)
{
    if(balance_ >= ammount)
    {
        balance_-=ammount;
        return true;
    }

    return false;
}

/**
 * @brief Get balance
 * @param ammount Player Wallet
 * @return None
 */
int Wallet::GetBalance() const
{
    return balance_;
}

/**
 * @brief Set New Balance for player
 * @param   ammount   Player Wallet
 * @return  None
 */
void Wallet::SetNewBalance(int ammount)
{
    qDebug() << "Set New Balance: " << ammount;
    balance_ = ammount;
}

