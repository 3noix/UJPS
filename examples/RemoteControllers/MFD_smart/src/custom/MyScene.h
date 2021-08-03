#ifndef MY_SCENE
#define MY_SCENE


#include "../default/MfdScene.h"
class MfdSelectableTextItem;
class AbstractMfdPage;


class MyScene : public MfdScene
{
	Q_OBJECT
	
	public:
		explicit MyScene(QObject *parent = nullptr);
		MyScene(const MyScene &other) = delete;
		MyScene(MyScene &&other) = delete;
		MyScene& operator=(const MyScene &other) = delete;
		MyScene& operator=(MyScene &&other) = delete;
		virtual ~MyScene() = default;
		
		bool setCurrentPage(AbstractMfdPage *page);
		
		
	signals:
		void buttonChanged2(uint button, bool bPressed);
		
		
	private slots:
		void slotButtonChanged(uint button, bool bPressed);
		
		
	private:
		bool m_bOneButtonClicked;
		
		AbstractMfdPage *m_currentPage;
		AbstractMfdPage *m_page_PWR;
		AbstractMfdPage *m_page_IFCS;
		AbstractMfdPage *m_page_SYS;
		
		MfdSelectableTextItem *m_textPWR;
		MfdSelectableTextItem *m_textSHLD;
		MfdSelectableTextItem *m_textSCAN;
		MfdSelectableTextItem *m_textIFCS;
		MfdSelectableTextItem *m_textSYS;
};


#endif

