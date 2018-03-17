#ifndef VJOY_SETTINGS_WIDGET
#define VJOY_SETTINGS_WIDGET

#include "AbstractSettingsWidget.h"
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QPushButton;


class VJoySettingsWidget : public AbstractSettingsWidget
{
	Q_OBJECT
	
	public:
		explicit VJoySettingsWidget(QWidget *parent = nullptr);
		VJoySettingsWidget(const VJoySettingsWidget &s) = delete;
		VJoySettingsWidget(VJoySettingsWidget &&s) = delete;
		VJoySettingsWidget& operator=(const VJoySettingsWidget &s) = delete;
		VJoySettingsWidget& operator=(VJoySettingsWidget &&s) = delete;
		virtual ~VJoySettingsWidget() = default;
		
		virtual QString tabName() const override;
		virtual void buttonOkClicked() override;
		virtual void buttonCancelClicked() override;
		
		
	private slots:
		void slotBrowseButtonClicked();
		
		
	private:
		QVBoxLayout *layout1;
		QHBoxLayout *layout2;
		QLabel *label;
		QLineEdit *line;
		QPushButton *button;
};


#endif





