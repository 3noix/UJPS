#ifndef CRENEL_ON_RISING
#define CRENEL_ON_RISING


class CrenelOnRising
{
	public:
		CrenelOnRising(uint nbCycles, bool retriggable)
		{
			m_firstTime = true;
			m_nbCycles = nbCycles;
			m_counter = 0;
			m_retriggable = retriggable;
			m_prevInput = false;
			m_prevOutput = false;
		};
		
		bool operator()(bool input)
		{
			if (!m_firstTime && input && !m_prevInput && (m_retriggable || !m_prevOutput)) // rising
			{
				m_counter = m_nbCycles; // reset counter
			}
			else if (m_counter > 0)
			{
				m_counter--;
			}
			bool output = (m_counter > 0);
			
			m_firstTime = false;
			m_prevInput = input;
			m_prevOutput = output;
			return output;
		};
		
		
	private:
		bool m_firstTime;
		uint m_nbCycles;
		uint m_counter;
		bool m_retriggable;
		bool m_prevInput;
		bool m_prevOutput;
};


#endif

