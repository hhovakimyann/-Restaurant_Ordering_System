#include "include.hpp"


Dish::Dish(std::string name,double price) : m_name(name), m_price(price) {}
std::string Dish::getName() const { 
    return m_name;
}
double Dish::getPrice() const {
    return m_price;
}


void Menu::addDish(const Dish& dish) {
    m_menu.push_back(dish);
}
void Menu::display() const {
    std::cout << "Menu"<< std::endl;

    for(int i = 0; i < m_menu.size(); i++) {
        std::cout << m_menu[i].getName() << " - " << " $" << m_menu[i].getPrice() << std::endl;
    }
}


void Order::addDish(const Dish& dish) {
    m_order.push_back(dish);
}

void Order::getTotal() const {
    double sum = 0;
    for(int i = 0 ; i < m_order.size(); i++) {
        sum += m_order[i].getPrice();
    }

    std::cout << "The total price of dishes is " << sum << std::endl;
}



typename Order::iterator Order::begin() noexcept {
    return iterator(m_order.begin());
}




typename Order::iterator Order::end() noexcept {
    return iterator(m_order.end());
}
