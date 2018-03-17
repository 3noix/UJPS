Modifications:

- in vjoyinterface.h (commenting the pragma that are generating warnings with mingw32 5.3.0, from Qt 5.7 installation)
	- comment line 276 : #pragma warning( push )
	- comment line 277 : #pragma warning( disable : 4995 )
	- comment line 327 : #pragma region FFB Function prototypes
	- comment line 359 : #pragma endregion
	- comment line 361 : #pragma warning( pop )

- in stdafx.h
	- None

- in public.h
	- None