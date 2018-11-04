#ifndef MFD_SCENE
#define MFD_SCENE


#include <QGraphicsScene>
class MfdBezelSegmentH;
class MfdBezelSegmentV;
class MfdBezelCorner1;
class MfdBezelCorner2;
class MfdScreen;


class MfdScene : public QGraphicsScene
{
	Q_OBJECT
	
	public:
		explicit MfdScene(QObject *parent = nullptr);
		MfdScene(const MfdScene &other) = delete;
		MfdScene(MfdScene &&other) = delete;
		MfdScene& operator=(const MfdScene &other) = delete;
		MfdScene& operator=(MfdScene &&other) = delete;
		virtual ~MfdScene() = default;
		
		void setLed1(bool b);
		void setLed2(bool b);
		bool led1() const;
		bool led2() const;
		
		
	signals:
		void buttonChanged(uint button, bool bPressed);
		
		
	private:
		MfdBezelSegmentH *m_up;
		MfdBezelSegmentH *m_down;
		MfdBezelSegmentV *m_left;
		MfdBezelSegmentV *m_right;
		
		MfdBezelCorner1 *m_upLeft;
		MfdBezelCorner1 *m_upRight;
		MfdBezelCorner2 *m_downLeft;
		MfdBezelCorner2 *m_downRight;
		
		MfdScreen *m_screen;
};


#endif

