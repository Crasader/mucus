#include "action_handler.hpp"

#include "master.hpp"

#include "view.hpp"
#include "player.hpp"

#include "physics.hpp"
#include "objects/base_object.hpp"
#include "objects/player/body.hpp"
#include "objects/ball.hpp"

static const size_t TOUCH_AURACY = 10; //pixels

void ActionHandler::start()
{
    enable();
	_active_target = &(master_t::subsystem<Player>());
}

void ActionHandler::stop()
{
    disable();
}

ActionHandler::ActionHandler()
	: _active_target(0)
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

        action::TouchPtr touch = std::make_shared<action::Touch>();
        touch->begin = location;
        touch->from = location;

        m_touches[id] = touch;
        m_touches_ids.push_back(id);

        // determine touch type and init touch handlers
        if (m_touches.size() == 1)
        {
        }
        else if (m_touches.size() == 2)
        {
            if(_active_target)
            {
                if( _active_target->multi_touch_type() == ActionTarget::SHARING )
                {
                    _active_target->onTwoTouchBegin( m_touches[m_touches_ids[0]], m_touches[m_touches_ids[1]] );
                }
            }
        }

        return true;
    };

    _event_listener->onTouchMoved = [&](cc::Touch* pTouch, cc::Event* pEvent) {
        action::TouchPtr &touch = m_touches[pTouch->getID()];

        touch->to = invert_y_coord(pTouch->getLocationInView());

        if( _active_target )
        {
            if( m_touches.size() == 2 && _active_target->multi_touch_type() == ActionTarget::SHARING)
            {
                _active_target->onTwoTouchContinue( m_touches[m_touches_ids[0]], m_touches[m_touches_ids[1]]);
            }
            else
            {
                if( touch->type == action::Touch::TARGET )
                {
                    pr::Vec2 begin( touch->begin.x, touch->begin.y );
                    pr::Vec2 end( touch->to.x, touch->to.y );
                    if( pr::distance(begin, end) > TOUCH_AURACY )
                    {
                        touch->type = action::Touch::MOVE;
                        _active_target->onMoveTouchBegin( touch );
                    }
                }

                if( touch->type == action::Touch::MOVE )
                {
                    _active_target->onMoveTouchContinue( touch );
                }

            }
        }

        touch->from = touch->to;
    };

    _event_listener->onTouchEnded = [&](cc::Touch* pTouch, cc::Event* pEvent) {
        int id = pTouch->getID();

        if( _active_target )
        {

            action::TouchPtr &touch = m_touches[id];

            touch->end = invert_y_coord(pTouch->getLocationInView());

            if( m_touches.size() == 2 && _active_target->multi_touch_type() == ActionTarget::SHARING)
            {
                _active_target->onTwoTouchEnd( m_touches[m_touches_ids[0]], m_touches[m_touches_ids[1]]);
            }
            else
            {
                switch( touch->type )
                {
                case action::Touch::TARGET:
                    {
                        _active_target->onTargetTouch( touch );
                        break;
                    }
                case action::Touch::MOVE:
                    {
                        _active_target->onMoveTouchEnd( touch );
                        break;
                    }
                default:
                    {
                        assert( false && "Unknown touch type!" );
                    }
                }
            }

        }

        m_touches.erase(id);
        auto delete_it = std::find( m_touches_ids.begin(), m_touches_ids.end(), id );
        m_touches_ids.erase( delete_it );
    };

    cc::Director::sharedDirector()->getEventDispatcher()->addEventListenerWithFixedPriority(_event_listener, 0);
}
void ActionHandler::disable()
{
    cc::Director::sharedDirector()->getEventDispatcher()->removeEventListener(_event_listener);
}
