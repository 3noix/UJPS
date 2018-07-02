#ifndef VIRTUAL_EVENTS_QUEUE
#define VIRTUAL_EVENTS_QUEUE


#include <QVector>
#include <QTimer>
#include "VirtualEvent.h"
#include "ujpscore-global.h"

class AbstractProfile;

class UJPSCORE_EXPORT VirtualEventsQueue
{
	public:
		VirtualEventsQueue(AbstractProfile &profileRef);
		VirtualEventsQueue(const VirtualEventsQueue &other) = delete;
		VirtualEventsQueue(VirtualEventsQueue &&other) = delete;
		VirtualEventsQueue& operator=(const VirtualEventsQueue &other) = delete;
		VirtualEventsQueue& operator=(VirtualEventsQueue &&other) = delete;
		virtual ~VirtualEventsQueue() = default;
		
		void postEvent(const VirtualEvent &event);
		void postEvents(const QVector<VirtualEvent> &events);
		void processEvents();
		
	private:
		void setMappingRepeaterEvent(const VirtualEvent &event);
		void updateMappingRepeaterEvent();

		AbstractProfile &m_profileRef;

		QVector<VirtualEvent> m_events;

		VirtualEvent m_repeaterEvent;
		float m_repeaterOriginalAxisValue;
		int m_repeaterDtms;
		int m_repeaterDtmsTotal;
};


#endif


