#ifndef MFD_WIDGET
#define MFD_WIDGET


#include <QGraphicsView>
#include "CUSTOM/MyScene.h"

#include "REMOTE/RemoteJoystickClient.h"
class ConnectionWidget;


class MfdWidget : public QGraphicsView
{
	Q_OBJECT
	
	public:
		explicit MfdWidget(int size = 600, QWidget *parent = nullptr);
		MfdWidget(const MfdWidget &other) = delete;
		MfdWidget(MfdWidget &&other) = delete;
		MfdWidget& operator=(const MfdWidget &other) = delete;
		MfdWidget& operator=(MfdWidget &&other) = delete;
		virtual ~MfdWidget();
		
		void showConnectionWidget();
		
		void setLed1(bool b);
		void setLed2(bool b);
		bool led1() const;
		bool led2() const;
		
		
	private slots:
		void slotButtonChanged(uint button, bool bPressed);
		void slotSetData(const QString &prop, QVariant data);
		
		void slotError(const QString &text);
		void slotSetState(RemoteJoystickClient::State s);
		
		
	private:
		MyScene m_scene;
		ConnectionWidget *m_connectionWidget;
		RemoteJoystickClient m_client;
};


#endif

