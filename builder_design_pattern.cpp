/*
********************************* Builder Design Pattern *****************************

   1. It is a creational design Pattern
   2. It is a step by step objects creation Pattern
   
 ******* To approach the problem of implementing the Builder design pattern, you can follow these steps:

1.  Define the Product Class (Student):
        --> Define the class representing the complex object to be constructed (Student in this case).
        --> Determine the attributes of the class and provide appropriate member variables and methods.
        
2.  Define the Abstract Builder Class (StudentBuilder):
        --> Create an abstract class (StudentBuilder) with methods to set the attributes of the product.
        --> Include abstract methods for setting optional attributes (like subjects) to be implemented by concrete builders.
        
3.  Implement Concrete Builder Classes (EngineeringStudentBuilder and MBAStudentBuilder):
        --> Create concrete builder classes that inherit from the abstract builder.
        --> Implement methods to set the attributes of the product based on the specific requirements of each product variation.
        --> Implement methods to set optional attributes.
        
4.  Implement the Director Class:
        --> Create a director class (Director) responsible for directing the construction process.
        --> Provide methods in the director class to specify the steps required to construct different variations of the product.
        --> Use a builder object to construct the product based on the specified steps.
        
5.  Use Client Code (main function):
        --> In the client code (main function), create instances of concrete builder classes (e.g., EngineeringStudentBuilder, MBAStudentBuilder).
        --> Create an instance of the director class and pass a builder object to it.
        --> Use the director object to construct the product, resulting in a complex object with predefined attributes.
*/

// ------------------------------------------------------------------------------------------

/*
// problem faced before using builder design pattern

#include<iostream>
using namespace std;

class Student
{
    public:
    
    // data member
    int roll_no;            // mendatory
    int age;                // optional
    string name;            // optional
    string father_name;     // optional
    string mother_name;     // optional
    list<string> subject;   // optional
    string mobile_no;       // optional
    
    // can have more optional field
    
    // Then constructor will look like this:--->
    // issue:- big constructor parameter list due to multiple optional parameter
    
    Student(int roll_no, int age, string name, string father_name, string mother_name, list<string> subject, string mobile_no)
    {
        this->roll_no = roll_no;
        this-> age = age;
        this-> name = name;
        this-> father_name = father_name;
        this-> mother_name = mother_name;
        this-> subject = subject;
        this-> mobile_no = mobile_no;
    }
    
    //**************** constructor can also be look like ********************
    
    Student(int roll_no, int age)
    {
        this->roll_no = roll_no;
        this-> age = age;
    }
    
    Student(int roll_no, int age, string name)
    {
        this->roll_no = roll_no;
        this-> age = age;
        this-> name = name;
    }
    
    Student(int roll_no, string father_name, string mother_name)
    {
        this->roll_no = roll_no;
        this-> father_name = father_name;
        this-> mother_name = mother_name;
    }
    // issue :- no of constructor is more
    // and here below constructor is different but will give compilation error because of function parameter signature (int, string, string)
    
    Student(int roll_no, string father_name, string subject)
    {
        this->roll_no = roll_no;
        this-> father_name = father_name;
        this-> subject = subject;
    }
    
    // to overcome this issue when lot of optional things is there, builder design pattern comes into the picture
};

*/

// #############################################------------ solution: --------------##########################################

#include <iostream>
#include <vector>
using namespace std;

// Forward declaration of Student class
class Student;

// Abstract StudentBuilder class
class StudentBuilder 
{
    public:
    
    // Member variables to hold student details
    int rollNumber;                     // mendatory
    int age;                            // optional
    string name;                        // ooptional
    string fatherName;                  // optional
    string motherName;                  // optional
    vector<string> subjects;            // optional
    
    // Abstract method for setting subjects (to be implemented by subclasses)
    virtual StudentBuilder& setSubjects() = 0;

    // Abstract build method to create a Student object (to be implemented by subclasses)
    virtual Student build() = 0;
    
    // Setters for common attributes and return type is builder itself
    StudentBuilder& setRollNumber(int rollNumber)
    {
        this->rollNumber = rollNumber;
        return *this;
    }

    StudentBuilder& setAge(int age) 
    {
        this->age = age;
        return *this;
    }

    StudentBuilder& setName(const string& name) 
    {
        this->name = name;
        return *this;
    }

    StudentBuilder& setFatherName(const string& fatherName)
    {
        this->fatherName = fatherName;
        return *this;
    }

    StudentBuilder& setMotherName(const string& motherName) 
    {
        this->motherName = motherName;
        return *this;
    }

};

// Concrete implementation of StudentBuilder for Engineering students
class EngineeringStudentBuilder : public StudentBuilder 
{
    public:
    
    // Implementation of setSubjects for Engineering students
    StudentBuilder& setSubjects() override
    {
        subjects = {"DSA", "OS", "Computer Architecture, AI"};
        return *this;
    }

    // Build method for EngineeringStudent --> will give final result after calling build method
    Student build() override;
};

// Concrete implementation of StudentBuilder for MBA students
class MBAStudentBuilder : public StudentBuilder 
{
    public:
    
    // Implementation of setSubjects for MBA students 
    StudentBuilder& setSubjects() override
    {
        subjects = {"Micro Economics", "Business Studies", "Operations Management"};
        return *this;
    }

    // Build method for MBAStudent --> will give final result after calling build method
    Student build() override;
};

// Student class
class Student 
{
    public:
    
    // Member variables to hold student details
    // issue ?:- code duplicate
    int rollNumber;                 // mendatory
    int age;                        // optional
    string name;                    // optional
    string fatherName;              // optional
    string motherName;              // optional
    vector<std::string> subjects;   // optional
    
    // Default constructor
    Student() = default;

    // Constructor taking a StudentBuilder object
    Student(const StudentBuilder& builder)
        : rollNumber(builder.rollNumber),
          age(builder.age),
          name(builder.name),
          fatherName(builder.fatherName),
          motherName(builder.motherName),
          subjects(builder.subjects) {}

    // Method to print the Student object
    string toString() const
    {
        return "Roll Number: " + to_string(rollNumber) + "\n" +
               "Age: " + to_string(age) + "\n" +
               "Name: " + name + "\n" +
               "Father's Name: " + fatherName + "\n" +
               "Mother's Name: " + motherName + "\n" +
               "Subjects: " + subjects[0] + ", " + subjects[1] + ", " + subjects[2];
    }
};

// Build method for EngineeringStudent
Student EngineeringStudentBuilder::build() 
{
    return Student(*this);
}

// Build method for MBAStudent
Student MBAStudentBuilder::build()
{
    return Student(*this);
}

// Director class
class Director 
{
    private:
    
    // director class can have EngineeringStudentBuilder or MBAStudentBuilder 
    // based on this it will construct Student
    StudentBuilder* studentBuilder;
    
    // Private methods to create specific types of students
    // step by step call to setter method then call build method
    Student createEngineeringStudent()
    {
        return studentBuilder->setRollNumber(1)
                              .setAge(22)
                              .setName("Rohan")
                              .setSubjects()
                              .build();
    }
    
    // step by step call to setter method then call build method
    Student createMBAStudent()
    {
        return studentBuilder->setRollNumber(2)
                              .setAge(24)
                              .setName("Mayuri")
                              .setFatherName("MyFatherName2")
                              .setMotherName("MyMotherName2")
                              .setSubjects()
                              .build();
    }

    public:
    
    // Constructor
    Director(StudentBuilder* studentBuilder) : studentBuilder(studentBuilder) {}

    // Method to create a Student using the specified builder
    Student createStudent()
    {
         // Check if the builder is an instance of EngineeringStudentBuilder
        if (dynamic_cast<EngineeringStudentBuilder*>(studentBuilder))
        {
            return createEngineeringStudent();
        }
    
        // Check if the builder is an instance of MBAStudentBuilder
        else if (dynamic_cast<MBAStudentBuilder*>(studentBuilder))
        {
            return createMBAStudent();
        }
        
        // Return default behaviour, if the builder is neither an EngineeringStudentBuilder nor an MBAStudentBuilder
        return Student(*studentBuilder); // Default behavior
    }

};

int main()
{
    // Create instances of Director with EngineeringStudentBuilder and MBAStudentBuilder
    Director* directorObj1 = new Director(new EngineeringStudentBuilder());
    Director* directorObj2 = new Director(new MBAStudentBuilder());

    // Create students using the respective directors
    Student engineerStudent = directorObj1->createStudent();
    Student mbaStudent = directorObj2->createStudent();

    // Print the Student details
    cout << "Engineering Student:\n" << engineerStudent.toString() << endl;
    cout << "\nMBA Student:\n" << mbaStudent.toString() << endl;

    // Free memory allocated for the directors
    delete directorObj1;
    delete directorObj2;

    return 0;
}