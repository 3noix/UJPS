#ifndef EXCEPTION_BAD_LAYERS_COMBO
#define EXCEPTION_BAD_LAYERS_COMBO


#include <exception>


class ExceptionBadLayersCombo : public std::exception
{
	public:
		ExceptionBadLayersCombo() = default;
		~ExceptionBadLayersCombo() = default;
		
		const char* what() const noexcept
		{
			return "ExceptionBadLayersCombo";
		};
};


#endif

