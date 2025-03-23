#include "include.hpp"


int main () {
    Menu menu;
    Dish pizza("Pizza", 10);
    Dish salad("Salad", 5);
    Dish soda("Soda", 2);

    menu.addDish(pizza);
    menu.addDish(salad);
    menu.addDish(soda);

    menu.display();

    Order order;
    order.addDish(salad);
    order.addDish(soda);
    
    std::cout << "Order Dishes" << std::endl;
    for(auto x : order) {
        std::cout << x.getName() << " $" << x.getPrice() << std::endl;
    }

    order.getTotal();
}