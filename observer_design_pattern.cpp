#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Declaration of Subject interface
class Subject;

// Observer interface
class Observer 
{
    public:
    
    // Pure virtual function to update the observer with the item name
    virtual void update(const string& itemName) = 0;
};

// Subject interface
class Subject
{
    public:
    
    // Pure virtual function to attach an observer
    virtual void attach(Observer* observer) = 0;
    
    // Pure virtual function to detach an observer
    virtual void detach(Observer* observer) = 0; 
    
    // Pure virtual function to notify observers about an update
    virtual void notify(const string& itemName) = 0;
};

// Concrete Subject: AmazonItem
class AmazonItem : public Subject 
{
    private:
    
    // Name of the Amazon item
    string itemName; 
    
    // Stock status of the item
    bool inStock; 
    
    // List of observers
    vector<Observer*> observers; 

    public:
    
    // Constructor to initialize item name and stock status
    AmazonItem(const string& name) : itemName(name), inStock(true) {} 

    // Attach an observer to the list
    void attach(Observer* observer) override
    {
        observers.push_back(observer);
    }

    // Detach an observer from the list
    void detach(Observer* observer) override
    {
        for (auto it = observers.begin(); it != observers.end(); ++it)
        {
            if (*it == observer) 
            {
                observers.erase(it);
                break;
            }
        }
    }

    // Notify all observers about the stock status change
    void notify(const string& itemName) override
    {
        for (auto observer : observers)
        {
            observer->update(itemName);
        }
    }

    // Set the stock status and notify observers if the item goes out of stock
    void setStockStatus(bool status)
    {
        if (inStock != status)
        {
            inStock = status;
            if (!inStock) 
            {
                notify(itemName);
            }
        }
    }
};

// Concrete Observer: User
class User : public Observer
{
    private:
    // Username of the observer
    string username; 

    public:
    // Constructor to initialize username
    User(const string& name) : username(name) {} 

    // Update the user with the item name when the item goes out of stock
    void update(const string& itemName) override
    {
        cout << "Dear " << username << ", " << itemName << " is out of stock on Amazon." << endl;
    }
};

int main()
{
    // Create an Amazon item
    AmazonItem item("Smartphone");

    // Create users (observers)
    User user1("Alice");
    User user2("Bob");

    // Attach users to the item
    item.attach(&user1);
    item.attach(&user2);

    // Simulate item going out of stock
    item.setStockStatus(false);

    // Detach a user
    item.detach(&user2);

    // Simulate item coming back in stock
    item.setStockStatus(true);

    return 0;
}