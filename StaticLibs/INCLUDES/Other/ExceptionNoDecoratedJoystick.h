#ifndef EXCEPTION_NO_DECORATED_JOYSTICK
#define EXCEPTION_NO_DECORATED_JOYSTICK


#include <exception>


class ExceptionNoDecoratedJoystick : public std::exception
{
	public:
		ExceptionNoDecoratedJoystick() = default;
		~ExceptionNoDecoratedJoystick() = default;
		
		const char* what() const noexcept
		{
			return "ExceptionNoDecoratedJoystick";
		};
};


#endif

