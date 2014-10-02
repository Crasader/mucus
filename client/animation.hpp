//
//  animation.hpp
//  mucus
//
//  Created by inkooboo on 8/24/12.
//
//

#ifndef __mucus__animation__
#define __mucus__animation__

# include "defs.hpp"

# include <loop.hpp>

# include <json/value.h>

# include <string>
# include <map>
# include <functional>

class Animation
{
    typedef std::map<std::string, cc::ActionInterval *> AnimationsMap;
public:
    Animation(const char *name);
    ~Animation();

    cc::Sprite *sprite();
    
    void animate(const std::string &name, LazyFunction on_animation_loop_end);
    
private:
    Json::Value m_descr;
    cc::Sprite *m_sprite;
    cc::Action *m_cur_action;
    
    AnimationsMap m_animations;
};

#endif /* defined(__mucus__animation__) */
