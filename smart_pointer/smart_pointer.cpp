#include <iostream>
#include <memory>

inline void print_cout(const char *in)
{
    std::cout << in << std::endl;
}

class Foo
{
private:
    std::string m_name;

public:
    Foo() { print_cout("Created!"); }
    Foo(const std::string &name) : m_name(name) { print_cout("Created!"); }
    ~Foo() { print_cout("Destroyed!"); }

    void PrintName()
    {
        std::cout << "Foo: " << m_name << std::endl;
    }

    std::string GetName()
    {
        return m_name;
    }
};

int main()
{
    {
        // Stack allocation
        Foo a("Well");
        a.PrintName();
    }
    print_cout("");

    {
        // Heap allocation
        Foo *a = new Foo("it");
        a->PrintName();

        if (a)
            delete a;
    }
    print_cout("");

    {
        // Heap allocation with unique pointer
        std::unique_ptr<Foo> foo_ptr = std::make_unique<Foo>("dose");
        foo_ptr->PrintName();
    }
    print_cout("");

    std::weak_ptr<Foo> weak_foo;
    {
        // Heap allocation with shared pointer
        std::shared_ptr<Foo> foo_;
        {
            std::shared_ptr<Foo> foo_ptr = std::make_shared<Foo>("not");
            foo_ = foo_ptr;
            weak_foo = foo_ptr;
        }
        print_cout(weak_foo.expired() ? "Weak: expired!" : "Weak: alive!");
        foo_->PrintName();
    }
    print_cout(weak_foo.expired() ? "Weak: expired!" : "Weak: alive!");
    print_cout("");

    return 0;
}