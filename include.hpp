#ifndef RESTAURANT_ORDERING_SYSTEM
#define RESTAURANT_ORDERING_SYSTEM

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <functional>

class Dish
{
public:
    virtual std::string getName() const = 0;
    virtual double getPrice() const = 0;
    virtual ~Dish() = default;
};

class Fish : public Dish
{
private:
    std::string m_name;
    double m_price;

public:
    Fish(std::string name, double price);
    double getPrice() const override;
    std::string getName() const override;
};

class Meat : public Dish
{
private:
    std::string m_name;
    double m_price;

public:
    Meat(std::string name, double price);
    double getPrice() const override;
    std::string getName() const override;
};

class Chicken : public Dish
{
private:
    std::string m_name;
    double m_price;

public:
    Chicken(std::string name, double price);
    double getPrice() const override;
    std::string getName() const override;
};

class Decorator : public Dish
{
protected:
    std::shared_ptr<Dish> dish;

public:
    explicit Decorator(std::shared_ptr<Dish> dish_);
};

class Rice : public Decorator
{
public:
    explicit Rice(std::shared_ptr<Dish> dish_);
    double getPrice() const override;
    std::string getName() const override;
};

class Potato : public Decorator
{
public:
    explicit Potato(std::shared_ptr<Dish> dish_);
    double getPrice() const override;
    std::string getName() const override;
};

class Salad : public Decorator
{
public:
    explicit Salad(std::shared_ptr<Dish> dish_);
    double getPrice() const override;
    std::string getName() const override;
};

class Menu
{
private:
    std::vector<std::shared_ptr<Dish>> m_menu;
    static Menu *sign_;

public:
    static Menu *getInstance();
    void addDish(std::shared_ptr<Dish> dish);
    void display() const;
};

class Order
{
private:
    std::vector<std::shared_ptr<Dish>> m_order;

public:
    class iterator
    {
    private:
        std::vector<std::shared_ptr<Dish>>::iterator current;

    public:
        iterator() : current(nullptr) {}
        iterator(std::vector<std::shared_ptr<Dish>>::iterator ptr) : current(ptr) {}

        const Dish &operator*() const { return **current; }
        Dish &operator*() { return **current; }

        iterator &operator++()
        {
            ++current;
            return *this;
        }
        iterator &operator--()
        {
            --current;
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp(*this);
            ++current;
            return tmp;
        }
        iterator operator--(int)
        {
            iterator tmp(*this);
            --current;
            return tmp;
        }

        bool operator==(const iterator &other) const { return other.current == current; }
        bool operator!=(const iterator &other) const { return other.current != current; }
    };

    class const_iterator
    {
    private:
        std::vector<std::shared_ptr<Dish>>::const_iterator current;

    public:
        const_iterator() : current(nullptr) {}
        const_iterator(std::vector<std::shared_ptr<Dish>>::const_iterator ptr) : current(ptr) {}

        const Dish &operator*() const { return **current; }

        const_iterator &operator++()
        {
            ++current;
            return *this;
        }
        const_iterator &operator--()
        {
            --current;
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp(*this);
            ++current;
            return tmp;
        }
        const_iterator operator--(int)
        {
            const_iterator tmp(*this);
            --current;
            return tmp;
        }

        bool operator==(const const_iterator &other) const { return other.current == current; }
        bool operator!=(const const_iterator &other) const { return other.current != current; }
    };

    void addDish(std::shared_ptr<Dish> dish);
    double getTotal() const;

    iterator begin() { return iterator(m_order.begin()); }
    iterator end() { return iterator(m_order.end()); }
    const_iterator begin() const { return const_iterator(m_order.begin()); }
    const_iterator end() const { return const_iterator(m_order.end()); }
};

class Payment
{
public:
    virtual ~Payment() = default;
    virtual void pay(double) const = 0;
};

class CardPayment : public Payment
{
private:
    std::string cardNumber_;

public:
    CardPayment(const std::string cartNumber);
    void pay(double amount) const override;
};

class CashPayment : public Payment
{
public:
    void pay(double amount) const override;
};

class Strategy
{
private:
    std::shared_ptr<Payment> payment;

public:
    void setStrategy(const std::shared_ptr<Payment> &set);
    void payStrategy(double amount) const;
};

#include "impl.cpp"

#endif // RESTAURANT_ORDERING_SYSTEM