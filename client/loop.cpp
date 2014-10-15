#include "loop.hpp"

#include "master.hpp"

#include "object_manager.hpp"

#include "physics.hpp"
#include "view.hpp"
#include "effect_manager.hpp"

static const float DEFAULT_WORLD_TICK_TIME = 1.f/60.f;
static const float DEFAULT_VIEW_TICK_TIME = 1.f/33.f;
static const float BOOST_GAME_SPEED = 1.4f;

using namespace std::placeholders;

Loop::Loop()
    : m_reminder(0)
{
}

void Loop::start()
{
    cc::Director::sharedDirector()->getScheduler()->schedule(std::bind(&Loop::update_world, this, _1), this, DEFAULT_WORLD_TICK_TIME, 0, 0.f, false, "update_world");
    cc::Director::sharedDirector()->getScheduler()->schedule(std::bind(&Loop::update_view, this, _1), this, DEFAULT_VIEW_TICK_TIME, 0, 0.f, false, "update_view");
}

void Loop::stop()
{
    cc::Director::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
    m_reminder = 0;
}

void Loop::reload()
{
    stop();
    start();
}

void Loop::schedule(LazyFunction func, float delay)
{
    cc::Director::sharedDirector()->getScheduler()->schedule([=](float){func();}, this, 0.f, 1, delay, false, "schedule_once");
}

void Loop::update_world(float delta)
{
	delta *= BOOST_GAME_SPEED; // speed up game time

    float corrected_delta = delta + m_reminder; // add reminder from previous tick

    while (corrected_delta > DEFAULT_WORLD_TICK_TIME) {
        master_t::subsystem<Physics>().step(DEFAULT_WORLD_TICK_TIME);
        corrected_delta -= DEFAULT_WORLD_TICK_TIME;
    }

    m_reminder = corrected_delta; // new reminder
    delta -= m_reminder; // set delta to time passed in physics

    master_t::subsystem<View>().manageCameraPositionAndScale(delta); // manage dynamic scale

    master_t::subsystem<ObjectManager>().update_dynamic_objects_state(delta);
    master_t::subsystem<ObjectManager>().collect_garbage_objects();
}

void Loop::update_view(float dt)
{
    master_t::subsystem<ObjectManager>().update_objects(dt);
    master_t::subsystem<EffectManager>().update_effects(dt);
}
