#ifndef _MUCUS_ACTION_HANDLER_HPP_
#define _MUCUS_ACTION_HANDLER_HPP_

# include "defs.hpp"
# include "subsystem.hpp"

# include <map>
# include <functional>
# include <memory>

#include "action_target.hpp"

class ActionHandler : public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;

public:    
    ActionHandler();

    void enable();
    void disable();

private:
    std::map<int, action::TouchPtr> m_touches;
	std::vector<int> m_touches_ids;
    cc::EventListenerTouchOneByOne *_event_listener;

	ActionTarget* _active_target;
};

#endif
