#ifndef CONNECTION_WIDGET
#define CONNECTION_WIDGET


#include <QWidget>
class QHBoxLayout;
class QLabel;
class QComboBox;
class QLineEdit;
class QPushButton;


class ConnectionWidget : public QWidget
{
	Q_OBJECT
	
	public:
		explicit ConnectionWidget(QWidget *parent = nullptr);
		ConnectionWidget(const ConnectionWidget &other) = delete;
		ConnectionWidget(ConnectionWidget &&other) = delete;
		ConnectionWidget& operator=(const ConnectionWidget &other) = delete;
		ConnectionWidget& operator=(ConnectionWidget &&other) = delete;
		virtual ~ConnectionWidget() = default;
		
		void setConnecting();
		void setConnected();
		void setDisconnected();
		
		
	signals:
		void connectionRequest(const QString &hostName, quint16 port);
		
		
	public slots:
		void slotError(QString str);
		
		
	private slots:
		void slotConnect();
		
		
	private:
		void setupWidget();
		static QStringList findClassicalHosts();
		
		QHBoxLayout *m_layout;
		QLabel *m_hostLabel, *m_portLabel;
		QComboBox *m_hostCombo;
		QLineEdit *m_portLineEdit;
		QPushButton *m_connectButton;
};


#endif

