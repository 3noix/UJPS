#ifndef SETTINGS_DIALOG
#define SETTINGS_DIALOG


#include <QDialog>
class AbstractSettingsWidget;
class QGridLayout;
class QTabWidget;
class QPushButton;
class QCloseEvent;


class SettingsDialog : public QDialog
{
	Q_OBJECT
	
	public:
		explicit SettingsDialog(QWidget *parent = nullptr);
		SettingsDialog(const SettingsDialog &other) = delete;
		SettingsDialog(SettingsDialog &&other) = delete;
		SettingsDialog& operator=(const SettingsDialog &other) = delete;
		SettingsDialog& operator=(SettingsDialog &&other) = delete;
		~SettingsDialog() = default;
		
		void addSettingsWidget(AbstractSettingsWidget *w);
		
		
	private slots:
		void slotBoutonOk();
		void slotBoutonCancel();
		
		
	protected:
		virtual void closeEvent(QCloseEvent *event) override;
		virtual void keyPressEvent(QKeyEvent *event) override;
		
		
	private:
		void setupWidget();
		
		QGridLayout *layout;
		QTabWidget *tabs;
		QList<AbstractSettingsWidget*> settingsWidgets;
		QPushButton *boutonOk, *boutonCancel;
};


#endif





