#ifndef _MUCUS_PLAYER_HPP_
#define _MUCUS_PLAYER_HPP_

#include "defs.hpp"
#include "subsystem.hpp"

#include "primitives.hpp"

#include <memory>

class Player : public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;

public:
    Player();

    void reload();    
};

#endif
