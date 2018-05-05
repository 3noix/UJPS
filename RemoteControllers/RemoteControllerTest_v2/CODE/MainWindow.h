#ifndef MAIN_WINDOW
#define MAIN_WINDOW


#include <QWidget>
class QGridLayout;
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSlider;
class QGroupBox;

#include "RemoteJoystickClient.h"


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
		void slotConnect();
		void slotDisconnect();
		
		void slotSetData(const QString &prop, QVariant data);
		void slotSetState(AbstractRemoteJoystickClient::State s);
		void slotError(QString str);
		
		void slotSliderValueChanged(int value);
		void slotButton1Pressed();
		void slotButton2Pressed();
		void slotButton1Released();
		void slotButton2Released();
		
		
	private:
		void setupWidget();
		static QStringList findClassicalHosts();
		
		RemoteJoystickClient m_client;
		
		QGridLayout *m_mainLayout;
		QComboBox *m_hostCombo;
		QLineEdit *m_portLineEdit;
		QLabel *m_hostLabel, *m_portLabel, *m_statusLabel;
		QPushButton *m_connectButton, *m_sendDataButton, *m_disconnectButton;
		
		QGroupBox *m_box;
		QGridLayout *m_layout2;
		QSlider *m_slider;
		QPushButton *m_button1, *m_button2, *m_button3;
};

#endif

