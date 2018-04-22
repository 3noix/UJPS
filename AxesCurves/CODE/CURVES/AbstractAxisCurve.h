#ifndef ABSTRACT_AXIS_CURVE
#define ABSTRACT_AXIS_CURVE


#include <QObject>
class QWidget;


class AbstractAxisCurve : public QObject
{
	Q_OBJECT
	
	public:
		AbstractAxisCurve() = default;
		AbstractAxisCurve(const AbstractAxisCurve &other) = delete;
		AbstractAxisCurve(AbstractAxisCurve &&other) = delete;
		AbstractAxisCurve& operator=(const AbstractAxisCurve &other) = delete;
		AbstractAxisCurve& operator=(AbstractAxisCurve &&other) = delete;
		virtual ~AbstractAxisCurve() = default;
		
		virtual float run(float in) = 0;
		virtual QWidget* settingsWidget() = 0;
		
		
	signals:
		void curveModified();
};

#endif
