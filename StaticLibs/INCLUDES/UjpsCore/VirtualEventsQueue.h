#ifndef VIRTUAL_EVENTS_QUEUE
#define VIRTUAL_EVENTS_QUEUE


#include <QVector>
#include "VirtualEvent.h"

class VirtualEventsQueue
{
	public:
		VirtualEventsQueue() = default;
		VirtualEventsQueue(const VirtualEventsQueue &other) = delete;
		VirtualEventsQueue(VirtualEventsQueue &&other) = delete;
		VirtualEventsQueue& operator=(const VirtualEventsQueue &other) = delete;
		VirtualEventsQueue& operator=(VirtualEventsQueue &&other) = delete;
		virtual ~VirtualEventsQueue() = default;
		
		void postEvent(const VirtualEvent &event);
		void postEvents(const QVector<VirtualEvent> &events);
		void processEvents();
		
		
	private:
		QVector<VirtualEvent> m_events;
};


#endif


