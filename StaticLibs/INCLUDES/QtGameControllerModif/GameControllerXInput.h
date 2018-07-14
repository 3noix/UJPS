#ifndef GAME_CONTROLLER_XINPUT
#define GAME_CONTROLLER_XINPUT


#include "GameController.h"
#include <windows.h>
#include <XInput.h>
#include <QVector>


class GameControllerXInput : public GameController
{
	Q_OBJECT
	
	public:
		explicit GameControllerXInput(uint id, QObject *parent = nullptr);
		GameControllerXInput(const GameControllerXInput &other) = delete;
		GameControllerXInput(GameControllerXInput &&other) = delete;
		GameControllerXInput& operator=(const GameControllerXInput &other) = delete;
		GameControllerXInput& operator=(GameControllerXInput &&other) = delete;
		virtual ~GameControllerXInput() = default;
		
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
		static float byteToFloat(BYTE b);
		static float shortToFloat(SHORT s);
		
		uint m_id;
		bool m_bFirstRead;
		bool m_connected;
		XINPUT_STATE m_state;
		QVector<WORD> m_buttonsMapping;
};

#endif

