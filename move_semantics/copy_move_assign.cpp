#include <iostream>
#include <cstring>

inline void print_cout(const char *in)
{
    std::cout << in << std::endl;
}

class String
{
private:
    char *m_data;
    size_t m_size;

public:
    String(const char *in)
    {
        print_cout("Create!");
        m_size = std::strlen(in);
        m_data = new char[m_size + 1];
        memcpy(m_data, in, m_size);
        m_data[m_size + 1] = 0;
    }
    ~String()
    {
        print_cout("Destroy!");
        if (m_data)
        {
            delete[] m_data;
        }
    }
    String(const String &other)
    {
        print_cout("Copy!");
        m_size = other.m_size;
        m_data = new char[m_size + 1];
        memcpy(m_data, other.m_data, m_size + 1);
    }
    String(String &&other)
    {
        print_cout("Move!");
        m_size = other.m_size;
        m_data = other.m_data;

        other.m_size = 0;
        other.m_data = nullptr;
    }

    String &operator=(String &&other)
    {
        print_cout("Assign!");

        if (this != &other)
        {
            if (m_data)
            {
                delete[] m_data;
            }

            m_size = other.m_size;
            m_data = other.m_data;

            other.m_size = 0;
            other.m_data = nullptr;
        }
        return *this;
    }

    void Print()
    {
        for (int i = 0; i < m_size; i++)
        {
            std::cout << m_data[i];
        }
        std::cout << std::endl;
    }
};

class Foo
{
private:
    String m_name;

public:
    // This can avoid move but in this example show move semantics.
    // Foo(const char *name) : m_name(name) {}

    Foo(const String &name) : m_name(name) {}
    Foo(String &&name) : m_name(std::move(name)) {}

    ~Foo() {}

    void PrintName()
    {
        std::cout << "Foo: ";
        m_name.Print();
    }
};

int main()
{
    // Create String, then move to Foo.m_name
    Foo a("pluanant");
    a.PrintName();
    print_cout("");

    // Create
    String nickname("plu");
    nickname.Print();
    print_cout("");

    // Copy, nickname still working.
    Foo b(nickname);
    nickname.Print();
    b.PrintName();
    print_cout("");

    // Move, nick name should be empty.
    Foo c(std::move(nickname));
    nickname.Print();
    c.PrintName();
    print_cout("");

    // Create new name var
    String name = String("Anant");
    String var_a = name;

    // Move, since var_b is new variable
    String var_b = std::move(name);

    // Assign, since var_c is created variable
    String var_c("var_c");
    var_c = std::move(var_b);
    
    name.Print();
    var_a.Print();
    var_b.Print();
    var_c.Print();
    print_cout("");

    return 0;
}