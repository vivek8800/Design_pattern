#include<iostream>
using namespace std;

class gameSetting
{
    static gameSetting* instance;
    int brightness;
    int width;
    int height;

    // Constructor
    gameSetting():width(786), height(1200), brightness(75){}

    public:
    static gameSetting* getInstance()
    {
        if(instance==NULL)
        {
            instance= new gameSetting();
            return instance;
        }
    }

    void setWidth(int width)
    {
        this->width=width;
    }

    void setHeight(int height)
    {
        this->height=height;
    }

    void setBrightness(int brightness)
    {
        this->brightness=brightness;
    }

    int getWidth()
    {
        return this->width;
    }

    int getHeight()
    {
        return this->height;
    }

    int getBrightness()
    {
        return this->brightness;
    }

    void displaySetting()
    {
        cout<<"Brightness: "<<brightness<<endl;
        cout<<"Height: "<<height<<endl;
        cout<<"Width: "<<width<<endl;
    }
};

gameSetting* gameSetting::instance=NULL;

int main()
{
    gameSetting *setting = gameSetting::getInstance();
    setting->displaySetting();
    setting->setBrightness(400);
    setting->setWidth(500);

    setting->displaySetting();

    return 0;
}