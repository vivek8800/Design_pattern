/*
******************************************* Singleton Design Pattern *************************************************

The Singleton design pattern is a creational design pattern that ensures a class has only one instance and provides a global point of access to that instance. 
It is one of the design patterns  often used when we need to control access to resources such as database connections or logging instances, 
or when we want to maintain a single shared state throughout the application.

********** Key characteristics of the Singleton pattern:- ***********

Private Constructor: The Singleton class typically has a private constructor to prevent direct instantiation of the class from outside.

Static Instance: It contains a static member variable that holds the single instance of the class.

Static Method: It provides a static method that controls access to the single instance. 
This method either creates a new instance if it doesn't exist or returns the existing instance.

Global Access Point: The Singleton class provides a global point of access to the single instance, allowing other classes to access its functionality without creating a new instance.


The Singleton pattern is commonly used in scenarios where there should be exactly one instance of a class available globally, such as:

    --> Managing access to shared resources like database connections, file system, or network connections.
    --> Implementing logging mechanisms.
    --> Creating configuration management objects.
    --> Managing thread pools or thread-safe resources.

Explanation:-

    *** The code defines a Singleton class with a private constructor and a private data member.
    
    *** It also contains a static pointer instance of type Singleton to hold the single instance of the class.
    
    *** A static method createInstance() is provided to create or retrieve the instance of the Singleton class. 
        It checks if the instance is already created, and if not, it creates a new instance and returns it. 
        This method ensures that only one instance of the class exists throughout the program execution.
    
    *** The setdata() method sets the value of the data member.
    
    *** The showdata() method displays the value of the data member.
    
    *** In the main() function, two instances of the Singleton class are created using the createInstance() method.
    
    *** The data members of both instances are set using the setdata() method, and their values are displayed 
        using the showdata() method.
        
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
What are some best practices for using the Singleton design pattern?**
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

There are several best practices for using the Singleton design pattern, including:

Use the Singleton pattern sparingly:
The Singleton pattern should only be used when it is absolutely necessary. Overusing the Singleton pattern can lead to increased complexity and reduced flexibility.

Make the constructor private:
The constructor for the Singleton class should be made private to prevent clients from creating multiple instances of the class.

Provide a public static method to get the instance of the class:
A public static method should be provided to get the instance of the Singleton class. This method should check to see if the instance has already been created, and if not, it should create the instance and return it.

Use lazy initialization:
The Singleton class should use lazy initialization to create the instance of the class. This means that the instance is not created until it is first needed, which can help to improve performance.

Make the Singleton class thread-safe:
If the Singleton class will be used in a multithreaded environment, it is important to make it thread-safe. 
This can be done by using synchronization primitives, such as locks or mutexes.

issue before thread-safe

let's say two thread T1 and T2 simultaneously call the function and checked instance == nullptr.
then let's say one thread T1 created 1st instance but as condition is true for thread T2 as well so
thread T2 will also create new instance, so for Singleton class two instance will create, which violates Singleton.

Sol:--

Approach 1: Use mutex (lock/unlock)

problem : performance issue
    let's say you have more than 10 thread so lock-unlock will be time consuming
    
Approach 2: Eager instantiation

Approach 3: 

static Singleton* createInstance()
    {
        if(instance == NULL) 
        {
            // mutex lock
            if(instance == NULL) 
            {
                instance = new Singleton(); 
            }
            // unlock
        }
        
        return instance; 
    }

*/

#include<iostream>
using namespace std;

// Singleton class definition
class Singleton
{
    // Static pointer to hold the instance of Singleton class
    static Singleton* instance;
    
    // Data member to hold some value
    int data; 
    
    // Private constructors to prevent instantiation from outside
    // Default constructor
    Singleton(){} 
    
    // Constructor with parameter
    Singleton(int data) 
    {
        this->data=data;
    }
    
    public:
    
    // Static method so that you can call through the name of class as object can't be create
    // Static method to create or get the instance of Singleton class
    static Singleton* createInstance()
    {
        // Check if instance is not already created
        if(instance == NULL) 
        {
            // Create new instance if not exists
            instance = new Singleton(); 
            cout << "Instance created for the first time" << endl;
        }
        
        // Return the instance
        return instance; 
    }

    // Method to set the data value
    void setdata(int data)
    {
        this->data = data;
    }
    
    // Method to display the data value
    void showdata()
    {
        cout << data << " ";
    }
};

// Initializing static member of Singleton class
Singleton* Singleton::instance = NULL;

int main()
{
    // Creating instance of Singleton class
    Singleton *obj1 = Singleton::createInstance();
    
    // Setting data value to 23
    obj1->setdata(23); 
    
    // Displaying data value
    obj1->showdata(); 
    
    // Creating another instance of Singleton class
    Singleton *obj2 = Singleton::createInstance();
    
    cout << endl;
    
    // Setting data value to 93
    obj2->setdata(93); 
    
    // Displaying data value
    obj2->showdata(); 
    
    cout<<endl;
    
    // Displaying data value
    obj1->showdata(); 
    
    // both obj1 and obj2 have same data value
    
    return 0;
}