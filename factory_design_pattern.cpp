/*
when we need to create objects based on some condition like.. if condition 1 will fulfill then i will create obj1
                                                              if condition 2 will fulfill then i will create obj2 and so on..
just to avoide duplication of code

*/

#include <iostream>
using namespace std;

// Abstract base class Shape
class Shape
{
    public:
    
    // Pure virtual function to draw the shape
    virtual void draw() = 0;
    
    // Virtual destructor to ensure proper cleanup
    virtual ~Shape() {}
};

// Concrete class Circle
class Circle : public Shape
{
    public:
    
    // Implementation of the draw() function for Circle
    void draw() override
    {
        cout << "Circle" << endl;
    }
};

// Concrete class Square
class Square : public Shape
{
    public:
    
    // Implementation of the draw() function for Square
    void draw() override
    {
        cout << "Square" << endl;
    }
};

// Concrete class Rectangle
class Rectangle : public Shape
{
    public:
    
    // Implementation of the draw() function for Rectangle
    void draw() override
    {
        cout << "Rectangle" << endl;
    }
};

// *********************** below code will also work **********************

// Shape Factory class
class ShapeFactory
{
    public:
    
    // Method to create shapes based on input string
    Shape* getShape(const string &input)
    {
        if (input == "Circle")
        {
            return new Circle();
        }
        else if (input == "Square")
        {
            return new Square();
        }
        else if (input == "Rectangle")
        {
            return new Rectangle();
        }
        else
        {
            return nullptr;
        }
    }
};

int main()
{
    ShapeFactory factory;

    // Create shapes
    Shape* circle = factory.getShape("Circle");
    Shape* square = factory.getShape("Square");
    Shape* rectangle = factory.getShape("Rectangle");

    // Draw the shapes
    if (circle)
    {
        circle->draw(); // Output: Circle
    }
    
    if (square)
    {
        square->draw(); // Output: Square
    }
    
    if (rectangle)
    {
        rectangle->draw(); // Output: Rectangle
    }

    // Free memory
    delete circle;
    delete square;
    delete rectangle;

    return 0;
}


// *********************** another way to create factory **********************

/*
Shape *createShape(int choice)
{
    switch (choice)
    {
    case 1:
        return new Circle();
    case 2:
        return new Rectangle();
    case 3:
        return new Square();
    default:
        return nullptr;
    }
}

int main()
{
    int choice;
    cout << "Enter your choice (1 - Circle, 2 - Rectangle, 3 - Square): ";
    cin >> choice;

    Shape *shape = createShape(choice);
    
    if (shape)
    {
        shape->draw();
        delete shape; // Free allocated memory
    }
    
    else
    {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
*/
