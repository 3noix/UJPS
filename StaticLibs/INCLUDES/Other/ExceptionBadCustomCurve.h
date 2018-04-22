#ifndef EXCEPTION_BAD_CUSTOM_CURVE
#define EXCEPTION_BAD_CUSTOM_CURVE


#include <exception>


class ExceptionBadCustomCurve : public std::exception
{
	public:
		ExceptionBadCustomCurve() = default;
		~ExceptionBadCustomCurve() = default;
		
		const char* what() const noexcept
		{
			return "ExceptionBadCustomCurve";
		};
};


#endif

