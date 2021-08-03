#ifndef MEMORIZATION
#define MEMORIZATION


template <typename T>
class Memorization
{
	public:
		Memorization(T outputInitValue)
		{
			m_prevOutput = outputInitValue;
		};
		
		T operator()(T input, bool memCond)
		{
			T output = (memCond ? m_prevOutput : input);
			m_prevOutput = output;
			return output;
		};
		
		
	private:
		T m_prevOutput;
};


#endif

