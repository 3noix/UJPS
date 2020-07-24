#ifndef DELAY
#define DELAY


#include <list>


template <typename T>
class Delay
{
	public:
		Delay(uint nbCycles)
		{
			m_nbCycles = nbCycles;
		};
		
		T operator()(T input)
		{
			m_buffer.push_back(input);
			T output = m_buffer.front();
			if (m_buffer.size() > m_nbCycles) {m_buffer.pop_front();}
			return output;
		};
		
		
	private:
		uint m_nbCycles;
		std::list<T> m_buffer;
};


#endif

