#ifndef GENERAL_SETTINGS_WIDGET
#define GENERAL_SETTINGS_WIDGET


#include "AbstractSettingsWidget.h"
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QRadioButton;
class QButtonGroup;
class QLineEdit;


class GeneralSettingsWidget : public AbstractSettingsWidget
{
	Q_OBJECT
	
	public:
		explicit GeneralSettingsWidget(QWidget *parent = nullptr);
		GeneralSettingsWidget(const GeneralSettingsWidget &s) = delete;
		GeneralSettingsWidget(GeneralSettingsWidget &&s) = delete;
		GeneralSettingsWidget& operator=(const GeneralSettingsWidget &s) = delete;
		GeneralSettingsWidget& operator=(GeneralSettingsWidget &&s) = delete;
		virtual ~GeneralSettingsWidget();
		
		virtual QString tabName() const override;
		virtual void buttonOkClicked() override;
		virtual void buttonCancelClicked() override;
		
		
	private:
		void addDefaultDirWidgets();
		
		QVBoxLayout *layout1;
		QHBoxLayout *layout2;
		
		// default directory
		QLabel *labelDefDir;
		QRadioButton *radioDefDirPrevious, *radioDefDirFixed;
		QButtonGroup *radioDefDirGroup;
		QLineEdit *lineDefDir;
};


#endif





