#ifndef GAME_CONTROLLER_EVENTS
#define GAME_CONTROLLER_EVENTS


using uint = unsigned int;


class GameControllerAxisEvent
{
	public:
		GameControllerAxisEvent(uint controllerId, uint axis, float value);
		uint controllerId() const;
		uint axis() const;
		float value() const;
		
		
	private:
		uint m_id;
		uint m_axis;
		float m_value;
};


class GameControllerButtonEvent
{
	public:
		GameControllerButtonEvent(uint controllerId, uint button, bool pressed);
		uint controllerId() const;
		uint button() const;
		bool pressed() const;
		
		
	private:
		uint m_id;
		uint m_button;
		bool m_pressed;
};


class GameControllerPovEvent
{
	public:
		GameControllerPovEvent(uint controllerId, uint pov, float angle);
		uint controllerId() const;
		uint pov() const;
		float angle() const;
		
		
	private:
		uint m_id;
		uint m_pov;
		float m_angle;
};


#endif
