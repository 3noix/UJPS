#ifndef EXCEPTION_BAD_MAP_AXIS_2
#define EXCEPTION_BAD_MAP_AXIS_2


#include <exception>


class ExceptionBadMapAxis2 : public std::exception
{
	public:
		ExceptionBadMapAxis2() = default;
		~ExceptionBadMapAxis2() = default;
		
		const char* what() const noexcept
		{
			return "ExceptionBadMapAxis2";
		};
};


#endif

