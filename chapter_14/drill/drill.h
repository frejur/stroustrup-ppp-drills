#ifndef DRILL_H
#define DRILL_H
#include <iostream>

class B1 {
public:
    void f() {
        std::cout << NAME << "::" << "f()";
    }
    virtual void vf() {
        std::cout << NAME << "::" << "vf()";
    }
private:
    const std::string NAME{ "B1" };
};

class D1 : B1 {
public:
    void vf() {
        std::cout << "D1" << "::" << "f()";
    }
};

#endif // DRILL_H
