#ifndef INTERPOLATION_1D
#define INTERPOLATION_1D


const float EPSILON_INTERP = 1e-10;
class Interpolation1D
{
	public:
		Interpolation1D(const std::vector<float> xbp, const std::vector<float> ybp)
		{
			// the x breakpoints (xbp) must be sorted by increasing order!
			m_xbp = xbp;
			m_ybp = ybp;
		};
		
		float operator()(float input)
		{
			if (m_xbp.size() != m_ybp.size()) {return 9999.0f;}
			int indexLast = m_xbp.size() - 1;
	
			// if the input is smaller than the first element
			if (input <= m_xbp[0])
			{
				return m_ybp[0];
			}
			// if the input is greater than the last element
			else if (input >= m_xbp[indexLast])
			{
				return m_ybp[indexLast];
			}
			else
			{
				int max = indexLast;
				int min = 0;
				int current = 0;
				
				do
				{
					// new current index = (min+max)/2
					current = (min + max) >> 1;
					
					if (input < m_xbp[current]) {max = current;}
					else {min = current;}
				} while (max != (min+1));
				
				float denom = m_xbp[min+1] - m_xbp[min];
				if (fabs(denom) < EPSILON_INTERP) {denom = EPSILON_INTERP;}
				float output = m_ybp[min] + (input - m_xbp[min]) * (m_ybp[min+1] - m_ybp[min]) / denom;
				return output;
			}
		};
		
		
	private:
		std::vector<float> m_xbp;
		std::vector<float> m_ybp;
};


#endif

