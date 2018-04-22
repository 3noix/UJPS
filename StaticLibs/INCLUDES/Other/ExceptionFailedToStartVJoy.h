#ifndef EXCEPTION_FAILED_TO_START_VJOY
#define EXCEPTION_FAILED_TO_START_VJOY


#include <exception>
#include <string>


class ExceptionFailedToStartVJoy : public std::exception
{
	public:
		ExceptionFailedToStartVJoy(const std::string &text) :
			std::exception{},
			m_text{text}
		{};
		
		~ExceptionFailedToStartVJoy() = default;
		
		const char* what() const noexcept
		{
			return m_text.c_str();
		};
		
		
	private:
		std::string m_text;
};


#endif

