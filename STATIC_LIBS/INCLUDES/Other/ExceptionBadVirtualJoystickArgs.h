#ifndef EXCEPTION_BAD_VIRTUAL_JOYSTICK_ARGS
#define EXCEPTION_BAD_VIRTUAL_JOYSTICK_ARGS


#include <exception>


class ExceptionBadVirtualJoystickArgs : public std::exception
{
	public:
		ExceptionBadVirtualJoystickArgs() = default;
		~ExceptionBadVirtualJoystickArgs() = default;
		
		const char* what() const noexcept
		{
			return "ExceptionBadVirtualJoystickArgs: id must be <=16, and # of buttons <= 128";
		};
};


#endif

