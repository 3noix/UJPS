#ifndef PULSE_ON_RISING
#define PULSE_ON_RISING


class PulseOnRising
{
	public:
		PulseOnRising(bool inputInitValue = false)
		{
			m_prevInput = inputInitValue;
		};
		
		bool operator()(bool input)
		{
			bool output = (input && !m_prevInput);
			m_prevInput = input;
			return output;
		};
		
		
	private:
		bool m_prevInput;
};


#endif

