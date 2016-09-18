#include <iostream>

template <typename T>
class Register
{
private:
	T total;
public:
	Register()
	{
	total = (T)0;
	}

    void put(T value)
	{
		total += value;
	}

	void reset()
	{
		total = (T)0;
	}

	T get()
	{
		return total;
	}

};
