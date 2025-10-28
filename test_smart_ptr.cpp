#include <catch2/catch_all.hpp>
#include <functional>
#include "smart_ptr.h"


using namespace std;

// User struct for testing
struct User {
    std::string name;
    int age;
    
    User(std::string n, int a) : name(n), age(a) {}
};

// ==========================================================
// TESTS FOR UNIQUEPOINTER
// ==========================================================

TEST_CASE("Unique ptr: ctor") {
    auto p = sp::make_unique<User>("svetlin", 46);
    REQUIRE(p->age == 46);
};

TEST_CASE("Unique ptr: move") {
    auto p = sp::make_unique<User>("svetlin", 46);
    auto p2 = move(p);
    REQUIRE(p2->age == 46);
    REQUIRE(p2->name == "svetlin");
    REQUIRE(p.get() == nullptr);
};

TEST_CASE("Shared ptr: copy assignment") {
    auto p = sp::make_shared<User>("svetlin", 46);
    sp::SharedPointer<User> p2;
    p2 = p;
    REQUIRE(p->age == 46);
    REQUIRE(p->name == "svetlin");
    REQUIRE(p2->age == 46);
    REQUIRE(p2->name == "svetlin");
};

// More extensive tests
TEST_CASE("Unique ptr: default constructor") {
    sp::UniquePointer<User> p;
    REQUIRE(p.get() == nullptr);
};

TEST_CASE("Unique ptr: custom deleter") {
    bool deleted = false;
    auto deleter = [&deleted](User* ptr) { 
        deleted = true;
        delete ptr; 
    };
    {
        sp::UniquePointer<User, std::function<void(User*)>> p(new User("test", 20), deleter);
        REQUIRE(p->name == "test");
    }
    REQUIRE(deleted);
};

TEST_CASE("Unique ptr: operator* and operator->") {
    auto p = sp::make_unique<User>("john", 30);
    REQUIRE((*p).name == "john");
    REQUIRE(p->age == 30);
};

TEST_CASE("Shared ptr: construction") {
    auto p = sp::make_shared<User>("alice", 25);
    REQUIRE(p->name == "alice");
    REQUIRE(p->age == 25);
};

TEST_CASE("Shared ptr: multiple copies") {
    auto p1 = sp::make_shared<User>("bob", 40);
    auto p2 = p1;
    auto p3 = p2;
    auto p4 = p1;
    
    REQUIRE(p1->name == "bob");
    REQUIRE(p2->name == "bob");
    REQUIRE(p3->name == "bob");
    REQUIRE(p4->name == "bob");
    REQUIRE(p1->age == p2->age);
};

TEST_CASE("Shared ptr: independent pointers") {
    auto p1 = sp::make_shared<User>("charlie", 35);
    auto p2 = sp::make_shared<User>("david", 28);
    
    REQUIRE(p1->name == "charlie");
    REQUIRE(p2->name == "david");
    REQUIRE(p1->age == 35);
    REQUIRE(p2->age == 28);
};

TEST_CASE("Shared ptr: reassignment") {
    auto p1 = sp::make_shared<User>("eve", 32);
    auto p2 = p1;
    auto p3 = sp::make_shared<User>("frank", 45);
    
    p2 = p3;  // Now p2 should point to frank
    REQUIRE(p2->name == "frank");
    REQUIRE(p3->name == "frank");
    REQUIRE(p1->name == "eve");  // p1 still points to eve
};

TEST_CASE("Shared ptr: operator* and operator->") {
    auto p = sp::make_shared<User>("grace", 29);
    REQUIRE((*p).name == "grace");
    REQUIRE(p->age == 29);
};

TEST_CASE("Shared ptr: modification through reference") {
    auto p1 = sp::make_shared<User>("henry", 50);
    auto p2 = p1;
    
    (*p1).age = 51;
    REQUIRE(p1->age == 51);
    REQUIRE(p2->age == 51);  // Should reflect in p2 as well
};

TEST_CASE("Unique ptr: null after move") {
    auto p1 = sp::make_unique<User>("irene", 33);
    REQUIRE(p1.get() != nullptr);
    
    auto p2 = std::move(p1);
    REQUIRE(p1.get() == nullptr);
    REQUIRE(p2->name == "irene");
};

TEST_CASE("Shared ptr: multiple copies of same object") {
    auto p1 = sp::make_shared<User>("jack", 27);
    auto p2 = p1;
    auto p3 = p1;
    
    REQUIRE(p1->name == "jack");
    REQUIRE(p2->name == "jack");
    REQUIRE(p3->name == "jack");
    REQUIRE(p1->age == 27);
    REQUIRE(p2->age == 27);
    REQUIRE(p3->age == 27);
};

TEST_CASE("Multiple unique pointers") {
    auto p1 = sp::make_unique<User>("alice", 25);
    auto p2 = sp::make_unique<User>("bob", 30);
    
    REQUIRE(p1->name == "alice");
    REQUIRE(p2->name == "bob");
};