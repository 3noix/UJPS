#ifndef ABSTRACT_SETTINGS_WIDGET
#define ABSTRACT_SETTINGS_WIDGET

#include <QWidget>


class AbstractSettingsWidget : public QWidget
{
	Q_OBJECT
	
	public:
		explicit AbstractSettingsWidget(QWidget *parent = nullptr) : QWidget(parent) {};
		AbstractSettingsWidget(const AbstractSettingsWidget &other) = delete;
		AbstractSettingsWidget(AbstractSettingsWidget &&other) = delete;
		AbstractSettingsWidget& operator=(const AbstractSettingsWidget &other) = delete;
		AbstractSettingsWidget& operator=(AbstractSettingsWidget &&other) = delete;
		virtual ~AbstractSettingsWidget() = default;
		
		virtual QString tabName() const = 0;
		virtual void buttonOkClicked() = 0;
		virtual void buttonCancelClicked() = 0;
};


#endif





