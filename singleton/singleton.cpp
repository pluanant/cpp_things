#include <iostream>
#include <thread>
#include <mutex>

class Singleton
{
private:
    int m_counter;
    std::mutex m_counter_mutex;

    Singleton() : m_counter(1) {}
    ~Singleton() {}

public:
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

    static Singleton &get_instance()
    {
        // Static local variable initialization is thread safe.
        // Unless disable via compiler flag.

        static Singleton instance;
        return instance;
    }

    void print()
    {
        std::scoped_lock lock(m_counter_mutex);

        // if not lock can get repeat val
        int tmp = m_counter;
        std::cout << "Hi: " << tmp << "\n";
        m_counter++;
    }
};

void print_thread()
{
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Singleton &singleton = Singleton::get_instance();
    for (int i = 1; i <= 10; i++)
    {
        singleton.print();
    }
}

int main()
{
    // Singleton &instance = Singleton::get_instance();
    // instance.print();
    // instance.print();

    // Inaccessible constructor
    // Singleton val;

    // Deleted copy operator
    // Singleton val = Singleton::get_instance();
    // Singleton* val_ptr = Singleton::get_instance();
    // Singleton val_copy = instance;

    // Deleted assign operator
    // instance = nullptr;

    // Thread testing
    std::thread t1(print_thread);
    std::thread t2(print_thread);
    std::thread t3(print_thread);

    t1.join();
    t2.join();
    t3.join();

    std::cout << std::flush;

    return 0;
}