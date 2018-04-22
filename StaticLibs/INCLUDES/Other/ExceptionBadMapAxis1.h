#ifndef EXCEPTION_BAD_MAP_AXIS_1
#define EXCEPTION_BAD_MAP_AXIS_1


#include <exception>


class ExceptionBadMapAxis1 : public std::exception
{
	public:
		ExceptionBadMapAxis1() = default;
		~ExceptionBadMapAxis1() = default;
		
		const char* what() const noexcept
		{
			return "ExceptionBadMapAxis1";
		};
};


#endif

