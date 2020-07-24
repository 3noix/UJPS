#ifndef FLIP_FLOP
#define FLIP_FLOP


class FlipFlop
{
	public:
		FlipFlop(bool prioToSet, bool outputInitValue)
		{
			m_prioToSet = prioToSet;
			m_prevOutput = outputInitValue;
		};
		
		bool operator()(bool set, bool reset)
		{
			bool output = m_prevOutput;
			
			if (m_prioToSet)
			{
				if (set) {output = true;}
				else if (reset) {output = false;}
			}
			else
			{
				if (reset) {output = false;}
				else if (set) {output = true;}
			}
			
			m_prevOutput = output;
			return output;
		};
		
		
	private:
		bool m_prioToSet;
		bool m_prevOutput;
};


#endif

