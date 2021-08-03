#ifndef EXCEPTION_FAILED_TO_CONNECT
#define EXCEPTION_FAILED_TO_CONNECT


#include <exception>
#include <string>


class ExceptionFailedToConnect : public std::exception
{
	public:
		ExceptionFailedToConnect(const std::string &text) :
			std::exception{},
			m_text{text}
		{};
		
		~ExceptionFailedToConnect() = default;
		
		const char* what() const noexcept
		{
			return m_text.c_str();
		};
		
		
	private:
		std::string m_text;
};


#endif

