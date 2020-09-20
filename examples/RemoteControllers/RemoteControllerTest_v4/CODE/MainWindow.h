#ifndef MAIN_WINDOW
#define MAIN_WINDOW


#include <QWidget>
class QVBoxLayout;
class QGridLayout;
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSlider;
class QGroupBox;

#include "RemoteJoystickClient.h"
class ConnectionWidget;


class MainWindow : public QWidget
{
	Q_OBJECT
	
	public:
		explicit MainWindow(QWidget *parent = nullptr);
		MainWindow(const MainWindow &other) = delete;
		MainWindow(MainWindow &&other) = delete;
		MainWindow& operator=(const MainWindow &other) = delete;
		MainWindow& operator=(MainWindow &&other) = delete;
		virtual ~MainWindow() = default;
		
		
	private slots:
		void slotSetData(const QString &data);
		void slotSetState(RemoteJoystickClient::State s);
		
		void slotSliderValueChanged(int value);
		void slotButton1Pressed();
		void slotButton2Pressed();
		void slotButton1Released();
		void slotButton2Released();
		
		
	private:
		void setupWidget();
		
		ConnectionWidget *m_connectionWidget;
		RemoteJoystickClient m_client;
		
		QVBoxLayout *m_mainLayout;
		QGroupBox *m_box;
		QGridLayout *m_layout2;
		QSlider *m_slider;
		QPushButton *m_button1, *m_button2, *m_button3;
		
		float povValue;
};


#endif

