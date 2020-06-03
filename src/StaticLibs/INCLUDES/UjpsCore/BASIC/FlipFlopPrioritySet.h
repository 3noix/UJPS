#ifndef FLIP_FLOP_PRIORITY_SET
#define FLIP_FLOP_PRIORITY_SET


class FlipFlopPrioritySet
{
	public:
		FlipFlopPrioritySet(bool outputInitValue)
		{
			m_prevOutput = outputInitValue;
		};
		
		bool calculate(bool set, bool reset)
		{
			bool output;
			
			if (set) {output = true;}
			else if (reset) {output = false;}
			else {output = m_prevOutput;}
			
			m_prevOutput = output;
			return output;
		};
		
		
	private:
		bool m_prevOutput;
};


#endif

