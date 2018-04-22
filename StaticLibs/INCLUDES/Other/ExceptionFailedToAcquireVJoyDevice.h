#ifndef EXCEPTION_FAILED_TO_ACQUIRE_VJOY_DEVICE
#define EXCEPTION_FAILED_TO_ACQUIRE_VJOY_DEVICE


#include <exception>
#include <string>


class ExceptionFailedToAcquireVJoyDevice : public std::exception
{
	public:
		ExceptionFailedToAcquireVJoyDevice(const std::string &text) :
			std::exception{},
			m_text{text}
		{};
		
		~ExceptionFailedToAcquireVJoyDevice() = default;
		
		const char* what() const noexcept
		{
			return m_text.c_str();
		};
		
		
	private:
		std::string m_text;
};


#endif

