#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER


#include <QObject>
#include <QString>
#include "GameControllerEvents.h"


class GameController : public QObject
{
	Q_OBJECT
	
	public:
		explicit GameController(QObject *parent = nullptr) : QObject{parent} {};
		GameController(const GameController &other) = delete;
		GameController(GameController &&other) = delete;
		GameController& operator=(const GameController &other) = delete;
		GameController& operator=(GameController &&other) = delete;
		virtual ~GameController() = default;
		
		virtual QString description() = 0;
		virtual QString hardwareId() = 0;
		virtual uint id() = 0;
		virtual bool isValid() = 0;
		
		virtual uint axesCount() = 0;
		virtual uint buttonsCount() = 0;
		virtual uint povsCount() = 0;
		
		virtual float axisValue(uint axis) = 0;
		virtual bool buttonValue(uint button) = 0;
		virtual float povValue(uint pov) = 0;
		
		
	public slots:
		virtual void readGameController() = 0;
		
		
	signals:
		void gameControllerAxisEvent(GameControllerAxisEvent event);
		void gameControllerButtonEvent(GameControllerButtonEvent event);
		void gameControllerPovEvent(GameControllerPovEvent event);
};


#endif

