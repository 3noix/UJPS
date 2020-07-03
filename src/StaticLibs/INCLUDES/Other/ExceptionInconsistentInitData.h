#ifndef EXCEPTION_INCONSISTENT_INIT_DATA
#define EXCEPTION_INCONSISTENT_INIT_DATA


#include <exception>
#include <string>


class ExceptionInconsistentInitData : public std::exception
{
	public:
		ExceptionInconsistentInitData(const std::string &text) :
			std::exception{},
			m_text{text}
		{};
		
		~ExceptionInconsistentInitData() = default;
		
		const char* what() const noexcept
		{
			return m_text.c_str();
		};
		
		
	private:
		std::string m_text;
};


#endif

