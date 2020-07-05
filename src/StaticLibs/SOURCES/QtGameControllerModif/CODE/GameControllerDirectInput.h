#ifndef GAME_CONTROLLER_DIRECTINPUT
#define GAME_CONTROLLER_DIRECTINPUT


#include "GameController.h"
#include <QVector>
#include <windows.h>
#define DIRECTINPUT_VERSION 0x0800
#include "dinput.h"
#include "dinputd.h"
struct DI_ENUM_CONTEXT
{
	DIJOYCONFIG* pPreferredJoyCfg;
	bool bPreferredJoyCfgValid;
};
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
BOOL CALLBACK EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext);


class GameControllerDirectInput : public GameController
{
	Q_OBJECT
	
	friend BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
	friend BOOL CALLBACK EnumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext);
	
	public:
		explicit GameControllerDirectInput(uint id, QObject *parent = nullptr);
		GameControllerDirectInput(const GameControllerDirectInput &other) = delete;
		GameControllerDirectInput(GameControllerDirectInput &&other) = delete;
		GameControllerDirectInput& operator=(const GameControllerDirectInput &other) = delete;
		GameControllerDirectInput& operator=(GameControllerDirectInput &&other) = delete;
		virtual ~GameControllerDirectInput() = default;
		
		virtual QString description() override final;
		virtual QString hardwareId() override final;
		virtual uint id() override final;
		virtual bool isValid() override final;
		
		virtual uint axesCount() override final;
		virtual uint buttonsCount() override final;
		virtual uint povsCount() override final;
		
		virtual float axisValue(uint axis) override final;
		virtual bool buttonValue(uint button) override final;
		virtual float povValue(uint pov) override final;
		
		
	public slots:
		virtual void readGameController() override final;
		
		
	private:
		static QString hexaString(DWORD value);
		
		QString m_description;
		QString m_hardwareId;
		
		uint m_id;
		bool m_valid;
		uint m_nbAxes;
		uint m_nbButtons;
		uint m_nbPovs;
		
		QVector<float> m_axesValues;
		QVector<bool> m_buttonsValues;
		QVector<float> m_povsValues;
		
		LPDIRECTINPUTDEVICE8 m_pJoystick;
		uint m_enumCounter;
		QVector<GUID> m_DIaxisGIIDs;
		bool m_bFirstRead;
};


#endif

