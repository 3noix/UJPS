#ifndef UJPS_HTTP_SERVER
#define UJPS_HTTP_SERVER


#include <QMap>
#include <QHttpServerResponse>
class QHttpServer;
class RemoteJoystickHttp;


class UjpsHttpServer
{
	public:
		static UjpsHttpServer& instance();
		static QString ethernetLocalIpAddress(bool ipv6 = false);
		
		bool listen();
		RemoteJoystickHttp* registerRemoteGuiHttp(const QString &name, uint id, const QString &dirPath);
		QString url(const QString &name) const;
		void close();
		
		
	private:
		UjpsHttpServer();
		UjpsHttpServer(const UjpsHttpServer &other) = delete;
		UjpsHttpServer(UjpsHttpServer &&other) = delete;
		UjpsHttpServer& operator=(const UjpsHttpServer &other) = delete;
		UjpsHttpServer& operator=(UjpsHttpServer &&other) = delete;
		~UjpsHttpServer();
		
		static UjpsHttpServer m_instance;
		
		struct RemoteData
		{
			QString dirPath;
			RemoteJoystickHttp* remote;
		};
		
		QHttpServerResponse processFile(const QString &name, const QString &fileName);
		QHttpServerResponse processButton(const QString &name, uint button, bool bPressed);
		QHttpServerResponse processAxis(const QString &name, uint axis, float value);
		QHttpServerResponse processPov(const QString &name, uint pov, float value);
		
		QHttpServer *m_httpServer;
		QMap<QString,RemoteData> m_httpRemotes;
};


#endif

