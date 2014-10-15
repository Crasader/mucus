#include "action_handler.hpp"

#include "master.hpp"

#include "view.hpp"
#include "player.hpp"

#include "physics.hpp"
#include "objects/base_object.hpp"
#include "objects/ball.hpp"

static const size_t TOUCH_AURACY = 10; //pixels

void ActionHandler::start()
{
    enable();
}

void ActionHandler::stop()
{
    disable();
}

ActionHandler::ActionHandler()
{
}

cc::Point invert_y_coord(cc::Point pos)
{
    pos.y = cc::Director::sharedDirector()->getWinSize().height - pos.y;
    return pos;
}

void ActionHandler::enable()
{
    _event_listener = cc::EventListenerTouchOneByOne::create();

    _event_listener->onTouchBegan = [&](cc::Touch* pTouch, cc::Event* pEvent) {
        cc::Point location = invert_y_coord(pTouch->getLocationInView());
        int id = pTouch->getID();

        Touch touch;
        touch.begin = location;
        touch.from = location;

        m_touches[id] = touch;
        m_touches_ids.push_back(id);

        // TODO
        // determine touch type and init touch handlers
        if (m_touches.size() == 1)
        {
        }
        else if (m_touches.size() == 2)
        {
        }

        return true;
    };

    _event_listener->onTouchMoved = [&](cc::Touch* pTouch, cc::Event* pEvent) {
        Touch &touch = m_touches[pTouch->getID()];

        touch.to = invert_y_coord(pTouch->getLocationInView());

        // TODO

        touch.from = touch.to;
    };

    _event_listener->onTouchEnded = [&](cc::Touch* pTouch, cc::Event* pEvent) {
        int id = pTouch->getID();

        // TODO

        m_touches.erase(id);
        auto delete_it = std::find(m_touches_ids.begin(), m_touches_ids.end(), id);
        m_touches_ids.erase(delete_it);
    };

    cc::Director::sharedDirector()->getEventDispatcher()->addEventListenerWithFixedPriority(_event_listener, 1);
}
void ActionHandler::disable()
{
    cc::Director::sharedDirector()->getEventDispatcher()->removeEventListener(_event_listener);
}
