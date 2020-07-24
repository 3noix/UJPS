#ifndef TEMPORIZATION
#define TEMPORIZATION


struct TempoOutput
{
	bool shortPress;
	bool longPress;
};


class Tempo
{
	public:
		Tempo(uint nbCycles)
		{
			m_nbCycles = nbCycles;
			m_prevInput = false;
			m_counter = 0;
		};
		
		TempoOutput operator()(bool input)
		{
			TempoOutput output;
			if (input)
			{
				++m_counter; // increment cycles m_counter
				if (m_counter == m_nbCycles) // long press of nbCycles detected
				{
					output.shortPress = false;
					output.longPress = true;
				}
				else
				{
					output.shortPress = false;
					output.longPress = false;
				}
				if (m_counter > m_nbCycles + 1) {m_counter = m_nbCycles + 1;}
			}
			else if (!input && m_prevInput && m_counter < m_nbCycles) // release after short press detected (less than nbCycles)
			{
				output.shortPress = true;
				output.longPress = false;
				m_counter = 0;
			}
			else // input stable at false or falling after more than nbCycles
			{
				output.shortPress = false;
				output.longPress = false;
				m_counter = 0;
			}
			
			m_prevInput = input;
			return output;
		};
		
		
	private:
		uint m_nbCycles;
		bool m_prevInput;
		uint m_counter;
};


#endif

