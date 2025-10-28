#include "smart_ptr.h"

struct User {
    std::string name;
    int age;
    
    User(std::string n, int a) : name(n), age(a) {}
};



int main(){
    auto ptr = sp::make_unique<User>(std::string("sv"), 1);
    std::cout << ptr->name << std::endl;
    
    // Example with custom deleter
    auto deleter = [](User* p) { 
        std::cout << "custom deleter called" << std::endl; 
        delete p; 
    };
    auto ptr2 = sp::UniquePointer<User>(new User("je", 3), deleter);

    auto sh_ptr = sp::SharedPointer<User>(new User("bb", 3), deleter);

    return 0;
}