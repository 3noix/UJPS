#ifndef PULSE_ON_FALLING
#define PULSE_ON_FALLING


class PulseOnFalling
{
	public:
		PulseOnFalling(bool inputInitValue = false)
		{
			m_prevInput = inputInitValue;
		};
		
		bool calculate(bool input)
		{
			bool output = (!input && m_prevInput);
			m_prevInput = input;
			return output;
		};
		
		
	private:
		bool m_prevInput;
};


#endif

