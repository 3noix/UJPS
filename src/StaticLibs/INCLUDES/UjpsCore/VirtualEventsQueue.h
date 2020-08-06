#ifndef VIRTUAL_EVENTS_QUEUE
#define VIRTUAL_EVENTS_QUEUE


#include <vector>
#include "VirtualEvent.h"
class AbstractProfile;


class VirtualEventsQueue
{
	public:
		VirtualEventsQueue(AbstractProfile *p);
		VirtualEventsQueue(const VirtualEventsQueue &other) = delete;
		VirtualEventsQueue(VirtualEventsQueue &&other) = delete;
		VirtualEventsQueue& operator=(const VirtualEventsQueue &other) = delete;
		VirtualEventsQueue& operator=(VirtualEventsQueue &&other) = delete;
		virtual ~VirtualEventsQueue() = default;
		
		void postEvent(const VirtualEvent &event);
		void postEvents(const std::vector<VirtualEvent> &events);
		void processEvents();
		
		static void setInputRepeaterEnabled(bool b);
		static bool isInputRepeaterEnabled();
		
		
	private:
		// for usual events
		std::vector<VirtualEvent> m_events;
		
		// for input repeater
		static bool bInputRepeaterEnabled;
		
		void setInputRepeaterEvent(const VirtualEvent &event);
		void updateInputRepeaterEvent();
		
		AbstractProfile *m_profile;
		int m_inputRepeaterDuration;
		int m_inputRepeaterDtms;
		int m_inputRepeaterDtmsTotal;
		bool m_bUseInputRepeaterEvent;
		float m_inputRepeaterOriginalAxisValue;
		VirtualEvent m_inputRepeaterEvent;
};


#endif

