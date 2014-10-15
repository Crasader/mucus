#ifndef _MUCUS_ACTION_HANDLER_HPP_
#define _MUCUS_ACTION_HANDLER_HPP_

# include "defs.hpp"
# include "subsystem.hpp"

# include <map>
# include <functional>
# include <memory>

class ActionHandler : public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;

public:    
    ActionHandler();

    void enable();
    void disable();

private:
	struct Touch
	{
		Touch() : type(TARGET) { }

		cc::CCPoint begin;
		cc::CCPoint from;
		cc::CCPoint to;
		cc::CCPoint end;

		enum Type
		{
			TARGET,
			MOVE
		} type;
	};

    std::map<int, Touch> m_touches;
	std::vector<int> m_touches_ids;
    cc::EventListenerTouchOneByOne *_event_listener;
};

#endif
