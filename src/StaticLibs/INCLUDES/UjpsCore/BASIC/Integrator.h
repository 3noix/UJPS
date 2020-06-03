#ifndef INTEGRATOR
#define INTEGRATOR


class Integrator
{
	public:
		Integrator(float initialOutput, float min, float max, int dtms)
		{
			m_firstTime = true;
			m_prevInput = 0.0f;
			m_prevOutput = initialOutput;
			m_min = (min < max ? min : max);
			m_max = (min < max ? max : min);
			m_dt = 0.001f * dtms;
		};
		
		float calculate(float input, bool bReset = false, float initValue = 0.0f)
		{
			if (bReset)
			{
				if (initValue < m_min) {initValue = m_min;}
				if (initValue > m_max) {initValue = m_max;}
				m_prevInput = input;
				m_prevOutput = initValue;
				m_firstTime = false;
				return initValue;
			}
			else if (m_firstTime)
			{
				m_prevInput = input;
				m_firstTime = false;
			}
			
			float output = m_prevOutput + 0.5*(input+m_prevInput)*m_dt;
			if (output < m_min) {output = m_min;}
			if (output > m_max) {output = m_max;}
			
			m_prevInput = input;
			m_prevOutput = output;
			return output;
		};
		
		
	private:
		bool m_firstTime;
		float m_prevInput;
		float m_prevOutput;
		float m_min;
		float m_max;
		float m_dt;
};


#endif

