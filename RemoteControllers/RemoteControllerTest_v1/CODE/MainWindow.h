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

#include <QDataStream>
#include <QAbstractSocket>
class QTcpSocket;
class QNetworkSession;


class MainWindow : public QWidget
{
	Q_OBJECT
	
	public:
		enum class State
		{
			Init,
			NotConnected,
			Connecting,
			Connected,
			Error
		};
		
		explicit MainWindow(QWidget *parent = nullptr);
		MainWindow(const MainWindow &other) = delete;
		MainWindow(MainWindow &&other) = delete;
		MainWindow& operator=(const MainWindow &other) = delete;
		MainWindow& operator=(MainWindow &&other) = delete;
		virtual ~MainWindow() = default;
		
		void setState(State s);
		
		
	private slots:
		void slotSessionOpened();
		void slotConnect();
		void slotConnected();
		void slotReceiveData();
		void slotDisconnect();
		void slotDisconnected();
		void slotError(QAbstractSocket::SocketError socketError);
		
		void slotSliderValueChanged(int value);
		void slotButton1Pressed();
		void slotButton2Pressed();
		void slotButton1Released();
		void slotButton2Released();
		
		
	private:
		void setupWidget();
		
		QGridLayout *m_mainLayout;
		QComboBox *m_hostCombo;
		QLineEdit *m_portLineEdit;
		QLabel *m_hostLabel, *m_portLabel, *m_statusLabel;
		QPushButton *m_connectButton, *m_sendDataButton, *m_disconnectButton;
		
		QGroupBox *m_box;
		QGridLayout *m_layout2;
		QSlider *m_slider;
		QPushButton *m_button1, *m_button2, *m_button3;
		
		QTcpSocket *m_tcpSocket;
		QNetworkSession *m_networkSession;
};

#endif

