#ifndef VIGEM_SETTINGS_WIDGET
#define VIGEM_SETTINGS_WIDGET


#include "AbstractSettingsWidget.h"
#include "../VigemPidWhiteLister.h"
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QCheckBox;


class VigemSettingsWidget : public AbstractSettingsWidget
{
	Q_OBJECT
	
	public:
		explicit VigemSettingsWidget(QWidget *parent = nullptr);
		VigemSettingsWidget(const VigemSettingsWidget &s) = delete;
		VigemSettingsWidget(VigemSettingsWidget &&s) = delete;
		VigemSettingsWidget& operator=(const VigemSettingsWidget &s) = delete;
		VigemSettingsWidget& operator=(VigemSettingsWidget &&s) = delete;
		virtual ~VigemSettingsWidget();
		
		virtual QString tabName() const override;
		virtual void buttonOkClicked() override;
		virtual void buttonCancelClicked() override;
		
		
	private slots:
		void slotStartAutoWhiteLister();
		
		
	private:
		void addStatusWidgets();
		void addVigemConfPageWidgets();
		void addStartAutoWhiteListerWidgets();
		void addWhiteListWidgets();
		
		QVBoxLayout *layout1;
		
		// ViGEm status
		QHBoxLayout *layoutStatus;
		QLabel *label1;
		QLabel *label2;
		
		// open ViGEm configuration page
		QHBoxLayout *layoutVigemConfPage;
		QLabel *labelVigemConfPage;
		
		// start auto white lister
		QHBoxLayout *layoutStartAutoWhiteLister;
		QLabel *labelStartAutoWhiteLister;
		
		// white list
		QHBoxLayout *layoutWhiteList;
		QCheckBox *boxWhiteList;
		VigemPidWhiteLister m_vigemInterface;
};


#endif





