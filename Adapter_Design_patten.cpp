/*
****************************** Adapter design Pattern ********************************

    Adapter is a bridge between expected interface and exixting interface
     ____________                                           ___________
    | expected  |                                          | existing |
    | interface |<---------- (Bridge->Adapter)<----------> |interface |
    ------------                                           -----------
    
    real world Scenario:-
    
    ---> Power adapter and Socket
    
    let's say power adapter is of round shape and socket is of square shape.
    Now client wants to use that socket but directly can't use due to incompatiable
    So we require Adapter.
    Adapter knows what client wants and also know how to talk with existing interface also.

*/

#include <iostream>
using namespace std;

// Adaptee: Class representing weight in pounds (Existing interface)
class WeightInPounds
{
    double pounds;

    public:
    WeightInPounds(double pounds) : pounds(pounds) {}

    double getPounds() const 
    {
        return pounds;
    }

};

// Target: Interface for weight in kilograms
class WeightInKilograms
{
    public:
    
    virtual double getKilograms() const = 0;
    virtual ~WeightInKilograms() {}
};

// Adapter: Adapts WeightInPounds to WeightInKilograms
class WeightAdapter : public WeightInKilograms
{
    WeightInPounds weight;
    
    public:
    
    // constructor
    WeightAdapter(const WeightInPounds& weight) : weight(weight) {}

    double getKilograms() const override 
    {
        // Convert pounds to kilograms
        return weight.getPounds() * 0.453592;
    }

};

// Client code
void printWeight(WeightInKilograms& weight)
{
    cout<<"Weight in kilograms: "<<weight.getKilograms()<<" kg\n";
}

int main()
{
    // Create weight in pounds
    WeightInPounds weightInPounds(80.0);

    // Create adapter to convert pounds to kilograms
    WeightAdapter adapter(weightInPounds);

    // Display weight in kilograms
    printWeight(adapter);

    return 0;
}