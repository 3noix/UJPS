#ifndef ABSTRACT_PROFILE
#define ABSTRACT_PROFILE


#include <QObject>
#include <QString>
#include <QColor>


class AbstractProfile : public QObject
{
	Q_OBJECT
	
	public:
		AbstractProfile();
		AbstractProfile(const AbstractProfile &other) = delete;
		AbstractProfile(AbstractProfile &&other) = delete;
		AbstractProfile& operator=(const AbstractProfile &other) = delete;
		AbstractProfile& operator=(AbstractProfile &&other) = delete;
		virtual ~AbstractProfile() = default;
		
		// public functions (called by the window only)
		virtual bool play() = 0;			// executed when clicking "play"
		virtual void run() = 0;				// executed at each time step
		virtual void stop() = 0;			// executed when clicking "stop"
		
		// about time step
		void setTimeStep(int dtms);
		int timeStep() const;
		uint ms2cycles(uint msecs) const;	// to convert msec into a number of cycles
		
		
	signals:
		void message(const QString &str, QColor color);
		
		
	private:
		int m_dtms;
};


Q_DECLARE_INTERFACE(AbstractProfile,"AbstractProfile")


#endif

