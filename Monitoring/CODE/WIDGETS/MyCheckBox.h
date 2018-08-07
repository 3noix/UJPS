#ifndef MY_CHECK_BOX
#define MY_CHECK_BOX


#include <QCheckBox>


class MyCheckBox : public QCheckBox
{
	Q_OBJECT
	
	public:
		MyCheckBox(uint axis, QWidget *parent = nullptr);
		MyCheckBox(const MyCheckBox &other) = delete;
		MyCheckBox(MyCheckBox &&other) = delete;
		MyCheckBox& operator=(const MyCheckBox &other) = delete;
		MyCheckBox& operator=(MyCheckBox &&other) = delete;
		virtual ~MyCheckBox() = default;
		
		
	private slots:
		void slotTheSlot(int checkState);
		
		
	signals:
		void axisDisplayChanged(uint axis, bool bDisplay);
		
		
	private:
		uint m_axis;
};


#endif

