#ifndef _MUCUS_LOOP_HPP_
#define _MUCUS_LOOP_HPP_

# include "defs.hpp"
# include "subsystem.hpp"
# include "logger.hpp"

# include <functional>
# include <memory>
# include <list>

inline void lazyDoNothing() {};

class Loop : public subsystem_t
{
    DEFINE_LOGGER(Loop)

    virtual void start() override;
    virtual void stop() override;

public:
    Loop();
    
    void reload();
    
    void schedule(LazyFunction func, float delay);
    
    void update_world(float dt);
    void update_view(float dt);
    
private:
    float m_reminder;
};

#endif
