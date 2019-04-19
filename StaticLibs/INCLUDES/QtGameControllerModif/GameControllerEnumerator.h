#ifndef GAME_CONTROLLER_ENUMERATOR
#define GAME_CONTROLLER_ENUMERATOR


#include <QVector>
class GameController;
class QObject;


class GameControllerEnumerator
{
	public:
		GameControllerEnumerator() = default;
		GameControllerEnumerator(const GameControllerEnumerator &other) = delete;
		GameControllerEnumerator(GameControllerEnumerator &&other) = delete;
		GameControllerEnumerator& operator=(const GameControllerEnumerator &other) = delete;
		GameControllerEnumerator& operator=(GameControllerEnumerator &&other) = delete;
		~GameControllerEnumerator() = default;
		
		// return all controllers at a time
		static QVector<GameController*> enumerateControllers(QObject *parent = nullptr);
		
		
	private:
		static const uint NB_JOYSTICKS_MAX_DIRECTINPUT = 16;
		static const uint NB_JOYSTICKS_MAX_XINPUT = 4;
		
		static const bool bUseXInput = true;
};


#endif

