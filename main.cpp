#include "include.hpp"

std::shared_ptr<Dish> createDish(const std::string& type, const std::string& name, double price) {
    static const std::unordered_map<std::string, std::function<std::shared_ptr<Dish>(const std::string&, double)>> dishMap = {
        {"Fish", [](const std::string& name, double price) { return std::make_shared<Fish>(name, price); }},
        {"Meat", [](const std::string& name, double price) { return std::make_shared<Meat>(name, price); }},
        {"Chicken", [](const std::string& name, double price) { return std::make_shared<Chicken>(name, price); }}
    };

    auto it = dishMap.find(type);
    return (it != dishMap.end()) ? it->second(name, price) : nullptr;
}

template <typename T>
std::shared_ptr<Dish> decorateDish(std::shared_ptr<Dish> dish) {
    return std::make_shared<T>(dish);
}

int main() {
    Menu* menu = Menu::getInstance();
    menu->addDish(createDish("Fish", "Salmon", 12.99));
    menu->addDish(createDish("Meat", "Steak", 15.99));
    menu->addDish(createDish("Chicken", "Grilled Chicken", 10.99));

    menu->display();

    Order order;
    std::shared_ptr<Dish> dish1 = createDish("Fish", "Tuna", 11.99);
    dish1 = decorateDish<Rice>(dish1);
    dish1 = decorateDish<Salad>(dish1);
    order.addDish(dish1);

    std::shared_ptr<Dish> dish2 = createDish("Meat", "Beef", 14.99);
    dish2 = decorateDish<Potato>(dish2);
    order.addDish(dish2);

    std::cout << "Order List" << std::endl;
    for(const auto& x : order) {
        std::cout << x.getName() << " " <<  x.getPrice()<< std::endl;
    }

    double price = order.getTotal();
    std::cout << "Total Order Price: $" << price << std::endl;
    std::cout << "How Will You Pay?\nCard\nCash\n";

   
    std::string paymentMethod;
    std::cin >> paymentMethod;

    Strategy strategy;

    if (paymentMethod == "Card") {
        std::string cardNumber;
        std::cout << "Enter the CardNumber" << std::endl;
        std::cin >> cardNumber;
        
        strategy.setStrategy(std::make_shared<CardPayment>(cardNumber));
    } else if (paymentMethod == "Cash") {
        strategy.setStrategy(std::make_shared<CashPayment>());
    } else {
        std::cout << "Invalid payment method selected." << std::endl;
        return 1;
    }

    strategy.payStrategy(price);
    

    return 0;
}
