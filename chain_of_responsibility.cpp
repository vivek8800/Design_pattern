/*
    *********************************** Chain of Responsibility*************************************
    
    ---> when any sender sends request and he doesn't care who one will going to fullfil my request.
    
    Note:- Apply where in use case, just send request and whic reciever fulfill request, we don't know. 
    
    Application: ATM
                 Vending Machine
                 Design Logger( asked in Amazon)
                 
                                       ______________________________________________________________
    sender/ client------request-----> | (reciever obj1) ---->(reciever obj2)---->(reciever obj3)    |
                                      |                                                 |           |
                                      |                                                 |           |
                                      |                                                 V           |
                                      |                                             (reciever objn) |
                                      |______________________________________________________________
                                      
    when client send request then this request will go first with obj1. if obj1 will not able to fulfill the request then it will forward to second 
    obj2 and so no untill fullfil the request. if request is not able to fullfil then system should send some error message(not able to fullfil request).
    
*/


#include <iostream>
using namespace std;

class LogProcessor 
{
    public:

    // Static constants representing log levels
    static const int INFO;
    static const int DEBUG;
    static const int ERROR;
    
    // Pointer to the next logger processor
    LogProcessor* nextLoggerProcessor;

    // Constructor
    LogProcessor(LogProcessor* loggerProcessor):nextLoggerProcessor(loggerProcessor){}

    // Virtual method for logging
    virtual void log(int logLevel, string message)
    {
        // If there's a next logger processor, delegate the logging to it
        if(nextLoggerProcessor != nullptr) 
        {
            nextLoggerProcessor->log(logLevel, message);
        }
    }
};

// Definition of static constants
const int LogProcessor::INFO = 1;
const int LogProcessor::DEBUG = 2;
const int LogProcessor::ERROR = 3;

// Derived class for logging INFO level messages
class InfoLogProcessor : public LogProcessor
{   
    public:
    
    // Constructor
    InfoLogProcessor(LogProcessor* nextLoggerProcessor) : LogProcessor(nextLoggerProcessor){}

    // Overridden log method for INFO level messages
    void log(int logLevel, string message) override
    {
        if (logLevel == INFO)
        {
            cout<<"INFO: "<<message<<endl;
        } 
        else 
        {
            // If not INFO level, delegate logging to the next logger processor
            LogProcessor::log(logLevel, message);
        }
    }
};

// Derived class for logging ERROR level messages
class ErrorLogProcessor : public LogProcessor
{  
public:
    // Constructor
    ErrorLogProcessor(LogProcessor* nextLoggerProcessor) : LogProcessor(nextLoggerProcessor){}

    // Overridden log method for ERROR level messages
    void log(int logLevel, string message) override 
    {
        if (logLevel == ERROR)
        {
            cout<<"ERROR: "<< message<<endl;
        } 
        else
        {
            // If not ERROR level, delegate logging to the next logger processor
            LogProcessor::log(logLevel, message);
        }
    }
};

// Derived class for logging DEBUG level messages
class DebugLogProcessor : public LogProcessor
{   
public:
    // Constructor
    DebugLogProcessor(LogProcessor* nextLoggerProcessor) : LogProcessor(nextLoggerProcessor) {}

    // Overridden log method for DEBUG level messages
    void log(int logLevel, string message) override
    {
        if (logLevel == DEBUG)
        {
            cout<<"DEBUG: "<<message<<endl;
        } 
        else 
        {
            // If not DEBUG level, delegate logging to the next logger processor
            LogProcessor::log(logLevel, message);
        }
    }
};

int main()
{
    // Creating an instance of the log chain with INFO -> DEBUG -> ERROR order
    LogProcessor* logObject = new InfoLogProcessor(new DebugLogProcessor(new ErrorLogProcessor(nullptr)));
    
    // Logging different messages with different log levels
    logObject->log(LogProcessor::ERROR, "exception happens");
    
    logObject->log(LogProcessor::DEBUG, "need to debug this");
    
    logObject->log(LogProcessor::INFO, "just for information");
    
    // Clean up dynamic memory
    delete logObject;

    return 0;
}