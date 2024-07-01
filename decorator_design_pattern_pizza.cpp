/*                                              Decorator design pattern

issue before Decorator design pattern :- class explosation

let's say we have base pizza so we need to maintain different permutation and combination with base pizza and different topping.
managing different class is too complex.

sol:- decorator design pattern
--------------------------------------------------------------------------------------------------------------------
Q-> Why we use decorator design pattern??

Ans:-> The Decorator design pattern is used to dynamically add new functionality or behaviors to objects without 
       altering their structure.
--------------------------------------------------------------------------------------------------------------------
Q-> Why we need and use the Decorator pattern?

Ans->
Open-Closed Principle (OCP): 
    *** The Decorator pattern allows us to extend the behavior of objects without modifying their code. 
    *** This adheres to the OCP, which states that classes should be open for extension but closed for modification.

Single Responsibility Principle (SRP): 
    *** Each decorator class has a single responsibility, which is to add or modify a specific behavior. 
    *** This promotes a cleaner and more maintainable codebase by separating concerns.

Code Reusability: 
    *** Decorators can be combined in various ways to create different combinations of behaviors. 
    *** This promotes code reusability since decorators can be reused across different objects.

Separation of Concerns: 
    *** Decorators encapsulate the functionality they add, keeping it separate from the core functionality of the object. 
    *** This separation makes the code easier to understand, maintain, and extend.

Run-Time Flexibility: 
    *** Decorators can be added or removed dynamically at runtime, allowing for dynamic changes in object behavior. 
    *** This provides flexibility and adaptability to changing requirements without affecting existing code.

Complexity Management: 
    *** Using the Decorator pattern, complex behaviors can be built by composing simpler behaviors. 
    *** This simplifies the design and management of complex systems by breaking them down into smaller, more manageable components.

--------------------------------------------------------------------------------------------------------------------
--->>>      Explanation of code below:---
--------------------------------------------------------------------------------------------------------------------

BasePizza is the abstract base class representing the interface for all pizza types.

Farmhouse, Marghrita, and vegDelight are concrete pizza classes implementing the cost() function to return the cost of each pizza type.

ToppingDecorator is an abstract decorator class that extends BasePizza. It contains a pointer to a 
BasePizza object and forwards calls to its cost() method to the wrapped object.

ExtraCheese and Mushroom are concrete decorator classes that add extra functionality (toppings) to pizzas.
They inherit from ToppingDecorator and override the cost() method to add the cost of the topping to the 
cost of the wrapped pizza.

In the main() function:
We create instances of different pizza configurations and calculate their costs.
We delete dynamically allocated objects to prevent memory leaks.

--------------------------------------------------------------------------------------------------------------------
Steps to create decorator design pattern?
--------------------------------------------------------------------------------------------------------------------

Here's a high-level overview of the steps to implement the Decorator pattern:

Identify the Component Interface: Define an interface (or abstract class) that represents the core functionality of the component. 
This interface should declare the methods that all concrete components and decorators will implement.

Create Concrete Component Classes: Implement one or more concrete classes that conform to the component interface. 
These classes represent the core functionality without any additional decorations.

Create the Decorator Interface: Define an interface (or abstract class) that extends the component interface. 
This interface should declare methods for adding or modifying behavior.

Create Concrete Decorator Classes: Implement concrete decorator classes that extend the decorator interface. 
Each decorator class adds a specific behavior or decoration to the component.

Implement Composition: Each decorator class should contain a reference to the wrapped component (either another decorator or a concrete component). 
This composition allows decorators to chain together and modify behavior recursively.

Override Methods: Override the methods declared in the decorator interface to add or modify behavior. 
Decorator classes can choose to delegate method calls to the wrapped component before or after adding their own behavior.

Client Code:Use the decorator classes to dynamically add or remove behavior from the components. 
Clients can create decorated instances of components and treat them uniformly as if they were instances of the component interface.

Testing and Refinement: Test the implementation to ensure that the decorators correctly modify the behavior of components without breaking existing functionality. 
Refine the design as necessary to meet the requirements.

--------------------------------------------------------------------------------------------------------------------
Real-World Example of Decorator Design Pattern

******** Consider a video streaming platform where users can watch movies and TV shows ********

Each video content may have additional features or options available, such as subtitles, 
language preferences, video quality options, and audio enhancements.

In this scenario, the base component is the video content itself, while the decorators 
represent the various additional features that users can enable or customize.

For example, a user might select the option to enable subtitles, change the language of the audio track, or adjust the video quality settings.

Each of these options acts as a decorator that enhances the viewing experience without altering the underlying video content.

By using the Decorator pattern, the streaming platform can dynamically apply these additional features to the video content 
based on user preferences, providing a customizable viewing experience.

--------------------------------------------------------------------------------------------------------------------
Some points to know:->

Mushroom is a type of ToppingDecorator, indicating an "is-a" relationship with ToppingDecorator.

ToppingDecorator has a "has-a" relationship with BasePizza, as it wraps a BasePizza object.

Mushroom also indirectly has a "has-a" relationship with BasePizza through ToppingDecorator.

*/

#include <iostream>
using namespace std;

// Interface class for all types of pizza
class BasePizza
{
    public:
    
    // Virtual function to calculate the cost of the pizza
    virtual int cost() = 0;
};

// Concrete pizza class representing Farmhouse pizza
class Farmhouse : public BasePizza
{
    public:
    
    // Cost of Farmhouse pizza
    int cost() override
    {
        return 200;
    }
};

// Concrete pizza class representing Marghrita pizza
class Marghrita : public BasePizza
{
    public:
    
    // Cost of Marghrita pizza
    int cost() override
    {
        return 150;
    }
};

// Concrete pizza class representing vegDelight pizza
class vegDelight : public BasePizza
{
    public:
    
    // Cost of vegDelight pizza
    int cost() override
    {
        return 180;
    }
};

// Abstract decorator class extending BasePizza
// It has-a relation with BasePizza
class ToppingDecorator : public BasePizza
{
    protected:
    
    // Pointer to the base pizza
    BasePizza *basepizza; 

    public:
    
    // Constructor
    ToppingDecorator(BasePizza *pizza) : basepizza(pizza) {}

    // Override cost() method to delegate to the wrapped pizza
    int cost() override
    {
        return basepizza->cost();
    }
};

// Concrete decorator class adding extra cheese topping
// It is-a ToppingDecorator and has-a BasePizza
class ExtraCheese : public ToppingDecorator
{
    public:
    
    // Constructor
    ExtraCheese(BasePizza *pizza) : ToppingDecorator(pizza) {}

    // Override cost() method to add cost of extra cheese
    int cost() override
    {
        return basepizza->cost() + 10;
    }
};

// Concrete decorator class adding mushroom topping
// It is-a ToppingDecorator and has-a BasePizza
class Mushroom : public ToppingDecorator
{
    public:
    
    // Constructor
    Mushroom(BasePizza *pizza) : ToppingDecorator(pizza) {}

    // Override cost() method to add cost of mushroom
    int cost() override
    {
        return basepizza->cost() + 15;
    }
};

// Concrete decorator class adding onion topping
// It is-a ToppingDecorator and has-a BasePizza
class Onion : public ToppingDecorator
{
    public:
    
    // Constructor
    Onion(BasePizza *pizza) : ToppingDecorator(pizza) {}

    // Override cost() method to add cost of onion
    int cost() override
    {
        // this will also work as ToppingDecorator Constructor contain basepizza
        // return ToppingDecorator::cost() + 20;
        return basepizza->cost() + 20;
    }
};

int main()
{
    // Create a Marghrita pizza with Extra Cheese
    BasePizza *pizza1 = new ExtraCheese(new Marghrita());
    cout << endl<<"Cost of Marghrita pizza with Extra Cheese: " << pizza1->cost() << endl;
    
    // Create a Marghrita pizza with Extra Cheese and Mushroom
    BasePizza *pizza2 = new Mushroom(new ExtraCheese(new Marghrita()));
    cout <<endl<<"Cost of Marghrita pizza with Extra Cheese and Mushroom: " << pizza2->cost() << endl;
    
    // Create a vegDelight pizza with Extra Cheese, Mushroom and Onion
    BasePizza *pizza3 = new Onion(new Mushroom(new ExtraCheese(new vegDelight())));
    cout <<endl<< "Cost of vegDelight pizza with Extra Cheese, Mushroom, and Onion: " << pizza3->cost() << endl<<endl;;

    // Clean up dynamically allocated objects to prevent memory leaks
    delete pizza1;
    delete pizza2;
    delete pizza3;

    return 0;
}
