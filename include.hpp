#ifndef Restaurant_Ordering_System 
#define Restaurant_Ordering_System 


#include <iostream>
#include <vector>
#include <string>

class Dish {
private:
    std::string m_name;
    double m_price;
public:
    Dish(std::string name, double price);
    std::string getName() const;
    double getPrice() const;
};

class Menu {
private:
    std::vector<Dish> m_menu;

public:
    void addDish(const Dish& dish);
    void display() const;
};

class Order {
private:
    std::vector<Dish> m_order;  
public:
    class iterator {
        private:
            std::vector<Dish>::iterator current;
        public:
            iterator() : current(nullptr) {}
            iterator(std::vector<Dish>::iterator ptr) : current(ptr) {}   
                
            const  Dish& operator*() const { return *current;}
            Dish& operator*()  { return *current;}

            iterator& operator++() { current++; return *this;}
            iterator& operator--() { current--; return *this;}
        
            iterator operator++(int) { iterator tmp(*this); current++; return tmp; }
            iterator operator--(int) { iterator tmp(*this);current--; return tmp; }
        
            bool operator==(const iterator& other) const{return other.current == current;}
            bool operator!=(const iterator& other) const{return other.current != current;}
    };
        
    class const_iterator {
        private:
        std::vector<Dish>::const_iterator current;
    public:
        const_iterator() : current(nullptr) {}
        const_iterator(std::vector<Dish>::const_iterator ptr) : current(ptr) {}   
            
        const  Dish& operator*() const { return *current;}

        const_iterator& operator++() { current++; return *this;}
        const_iterator& operator--() { current--; return *this;}
    
        const_iterator operator++(int) { const_iterator tmp(*this); current++; return tmp; }
        const_iterator operator--(int) { const_iterator tmp(*this);current--; return tmp; }
    
        bool operator==(const const_iterator& other) const{return other.current == current;}
        bool operator!=(const const_iterator& other) const{return other.current != current;}
    };


    void addDish(const Dish& dish);
    void getTotal() const;
    
    iterator begin() noexcept;
    iterator end() noexcept;

    const_iterator cbegin() noexcept;
    const_iterator cend() noexcept;
};



#include "impl.cpp"

#endif // Restaurant_Ordering_System 