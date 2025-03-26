#include "include.hpp"

Menu *Menu::sign_ = nullptr;

Fish::Fish(std::string name, double price) : m_name(std::move(name)), m_price(price) {}
std::string Fish::getName() const { return m_name; }
double Fish::getPrice() const { return m_price; }

Meat::Meat(std::string name, double price) : m_name(std::move(name)), m_price(price) {}
std::string Meat::getName() const { return m_name; }
double Meat::getPrice() const { return m_price; }

Chicken::Chicken(std::string name, double price) : m_name(std::move(name)), m_price(price) {}
std::string Chicken::getName() const { return m_name; }
double Chicken::getPrice() const { return m_price; }

Decorator::Decorator(std::shared_ptr<Dish> dish_) : dish(std::move(dish_)) {}

Rice::Rice(std::shared_ptr<Dish> dish_) : Decorator(std::move(dish_)) {}
std::string Rice::getName() const { return dish->getName() + " with Rice"; }
double Rice::getPrice() const { return dish->getPrice() + 2.0; }

Potato::Potato(std::shared_ptr<Dish> dish_) : Decorator(std::move(dish_)) {}
std::string Potato::getName() const { return dish->getName() + " with Potato"; }
double Potato::getPrice() const { return dish->getPrice() + 5.0; }

Salad::Salad(std::shared_ptr<Dish> dish_) : Decorator(std::move(dish_)) {}
std::string Salad::getName() const { return dish->getName() + " with Salad"; }
double Salad::getPrice() const { return dish->getPrice() + 4.0; }

void Menu::addDish(std::shared_ptr<Dish> dish) { m_menu.push_back(std::move(dish)); }
Menu *Menu::getInstance()
{
    if (!sign_)
        sign_ = new Menu();
    return sign_;
}
void Menu::display() const
{
    std::cout << "Menu" << std::endl;
    for (const auto &dish : m_menu)
    {
        std::cout << dish->getName() << " - $" << dish->getPrice() << std::endl;
    }
}

void Order::addDish(std::shared_ptr<Dish> dish) { m_order.push_back(std::move(dish)); }
double Order::getTotal() const
{
    double sum = 0;
    for (const auto &dish : m_order)
    {
        sum += dish->getPrice();
    }
    return sum;
}

CardPayment::CardPayment(const std::string cardNumber) : cardNumber_(cardNumber) {}

void CardPayment::pay(double amount) const
{
    std::cout << "The people with " << cardNumber_ << " will pay " << amount << std::endl;
}

void CashPayment::pay(double amount) const
{
    std::cout << "The people with Cash will pay " << amount << std::endl;
}

void Strategy::payStrategy(double amount) const
{
    if (payment)
    {
        payment->pay(amount);
    }
    else
    {
        std::cout << "Set Payment Strategy" << std::endl;
    }
}

void Strategy::setStrategy(const std::shared_ptr<Payment> &set)
{
    payment = set;
}