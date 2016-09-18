#include <iostream>
#include <fstream>
#include <sstream>

template<typename T> struct NoLoggingPolicy {
  static void log_push(T) {};
  static void log_pop(T) {};
};

template<typename T> struct FileLoggingPolicy {
  static void log_push(T val)
  {
    std::ostringstream ss;   
    ss << "pushed " << val << "\n";
    log_message(ss.str());
  };
  static void log_pop(T val)
  {
    std::ostringstream ss;   
    ss << "popped " << val << "\n";
    log_message(ss.str());
  };
  
  private:
  static void log_message(std::string message)
  {
    std::ofstream logfile("log.txt", std::fstream::app);
    if(logfile.is_open())
        {
        logfile << message;
        }
    logfile.close();
  }
};

template <typename T, int N = 100, typename Logging_policy = NoLoggingPolicy<T>  >
class Stack {
    T _rep[N];
    int _top;
public:
    Stack() : _top(0)
    { }
    void push(const T & val)
    {
        Logging_policy::log_push(val);
        _rep[_top++] = val;
    }
    void pop()
    {
        T val = _rep[--_top];
        Logging_policy::log_pop(val);        
    }
    const T & top() const
    {
        return _rep[_top - 1];
    }
    bool empty() const
    {
        return _top == 0;
    }
};


int main()
{
Stack<double, 100, FileLoggingPolicy<double> > s;
s.push(1);
s.push(2.5);
s.pop();
s.push(7);
s.pop();
s.pop();
}
