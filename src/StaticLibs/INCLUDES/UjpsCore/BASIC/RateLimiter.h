#ifndef RATE_LIMITER
#define RATE_LIMITER


class RateLimiter
{
	public:
		RateLimiter(float maxRate, float outputInitValue, int dtms)
		{
			m_prevOutput = outputInitValue;
			m_limUp = maxRate * (0.001f * dtms);
			m_limDown = -m_limUp;
		};
		
		float operator()(float input, bool reset = false)
		{
			if (reset)
			{
				m_prevOutput = input;
				return input;
			}
			
			float output;
			
			if ((input - m_prevOutput) > m_limUp) {output = m_limUp + m_prevOutput;}
			else if ((input - m_prevOutput) < m_limDown) {output = m_limDown + m_prevOutput;}
			else {output = input;}
			
			m_prevOutput = output;
			return output;
		};
		
		
	private:
		float m_prevOutput;
		float m_limUp;
		float m_limDown;
};


#endif

