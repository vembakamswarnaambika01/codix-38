#include <iostream>
#include <vector>
#include <string>

class Item {
public:
    Item(std::string name, double price) : name(name), price(price) {}

    std::string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

private:
    std::string name;
    double price;
};

class Customer {
public:
    Customer(std::string name) : name(name) {}

    std::string getName() const {
        return name;
    }

private:
    std::string name;
};

class Order {
public:
    Order(Customer customer) : customer(customer) {}

    void addItem(Item item, int quantity) {
        items.push_back(std::make_pair(item, quantity));
    }

    double calculateTotal() const {
        double total = 0;
        for (const auto& item : items) {
            total += item.first.getPrice() * item.second;
        }
        return total;
    }

private:
    Customer customer;
    std::vector<std::pair<Item, int>> items;
};

int main() {
    std::vector<Item> boutiqueItems;
    std::vector<Customer> customers;
    std::vector<Order> orders;

    while (true) {
        std::cout << "Boutique Management System" << std::endl;
        std::cout << "1. Add Item" << std::endl;
        std::cout << "2. Add Customer" << std::endl;
        std::cout << "3. Create Order" << std::endl;
        std::cout << "4. Calculate Total for an Order" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string name;
                double price;
                std::cout << "Enter item name: ";
                std::cin >> name;
                std::cout << "Enter item price: ";
                std::cin >> price;
                Item item(name, price);
                boutiqueItems.push_back(item);
                break;
            }
            case 2: {
                std::string name;
                std::cout << "Enter customer name: ";
                std::cin >> name;
                Customer customer(name);
                customers.push_back(customer);
                break;
            }
            case 3: {
                if (customers.empty() || boutiqueItems.empty()) {
                    std::cout << "You need at least one customer and one item to create an order." << std::endl;
                } else {
                    int customerIndex, itemIndex, quantity;
                    std::cout << "Select a customer by index:" << std::endl;
                    for (size_t i = 0; i < customers.size(); i++) {
                        std::cout << i << ". " << customers[i].getName() << std::endl;
                    }
                    std::cin >> customerIndex;

                    std::cout << "Select an item by index:" << std::endl;
                    for (size_t i = 0; i < boutiqueItems.size(); i++) {
                        std::cout << i << ". " << boutiqueItems[i].getName() << std::endl;
                    }
                    std::cin >> itemIndex;

                    std::cout << "Enter quantity: ";
                    std::cin >> quantity;

                    Order order(customers[customerIndex]);
                    order.addItem(boutiqueItems[itemIndex], quantity);
                    orders.push_back(order);
                }
                break;
            }
            case 4: {
                if (orders.empty()) {
                    std::cout << "No orders to calculate the total for." << std::endl;
                } else {
                    int orderIndex;
                    std::cout << "Select an order by index:" << std::endl;
                    for (size_t i = 0; i < orders.size(); i++) {
                        std::cout << i << ". Customer: " << orders[i].calculateTotal() << std::endl;
                    }
                    std::cin >> orderIndex;
                    double total = orders[orderIndex].calculateTotal();
                    std::cout << "Total for the selected order: $" << total << std::endl;
                }
                break;
            }
            case 5:
                std::cout << "Exiting the program." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }
    }

    return 0;
}
