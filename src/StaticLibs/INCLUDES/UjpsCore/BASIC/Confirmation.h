#ifndef CONFIRMATION
#define CONFIRMATION


class Confirmation
{
	public:
		Confirmation(uint nbCycles, bool atTrue)
		{
			m_nbCycles = nbCycles;
			m_counter = 0;
			m_atTrue = atTrue;
			m_prevInput = !m_atTrue;
		};
		
		bool calculate(bool input)
		{
			bool b1 = (input && m_prevInput && m_atTrue);
			bool b2 = (!input && !m_prevInput && !m_atTrue);
			if (b1 || b2) {m_counter++;}
			else {m_counter = 0;}
			
			bool output;
			if (m_nbCycles == 0)
			{
				output = input;
			}
			else if (m_counter > m_nbCycles-1)
			{
				m_counter = m_nbCycles-1;
				output = m_atTrue;
			}
			else
			{
				output = !m_atTrue;
			}
			
			m_prevInput = input;
			return output;
		};
		
		
	private:
		uint m_nbCycles;
		uint m_counter;
		bool m_atTrue;
		bool m_prevInput;
};


#endif

