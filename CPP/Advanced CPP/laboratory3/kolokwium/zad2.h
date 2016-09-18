template <typename T, typename U >
class PositiveStackAdapter
{
	U stack;
public:
	T pop()
	{
		return stack.pop();
	}

	bool empty()
	{
		return stack.empty();
	}
	
	T& top()
	{
		return stack.top();
	}

	void push(T x)
	{
		if(x > 0)
			stack.push(x);
	}
};
