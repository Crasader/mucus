#ifndef __mucus__level_manager__
#define __mucus__level_manager__

# include "subsystem.hpp"
# include "primitives.hpp"

# include "logger.hpp"

# include "defs.hpp"

class LevelLoader : public subsystem_t
{
    DEFINE_LOGGER(LevelLoader);
    
    virtual void start() override;
    virtual void stop() override;
    
public:
    LevelLoader();
    
    void loadLevel(const char *level_name);
};

#endif

