#ifndef FLIP_FLOP_PRIORITY_RESET
#define FLIP_FLOP_PRIORITY_RESET


class FlipFlopPriorityReset
{
	public:
		FlipFlopPriorityReset(bool outputInitValue)
		{
			m_prevOutput = outputInitValue;
		};
		
		bool calculate(bool set, bool reset)
		{
			bool output;
			
			if (reset) {output = false;}
			else if (set) {output = true;}
			else {output = m_prevOutput;}
			
			m_prevOutput = output;
			return output;
		};
		
		
	private:
		bool m_prevOutput;
};


#endif

