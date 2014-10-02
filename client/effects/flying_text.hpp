//
//  flying_text.hpp
//  mucus
//
// Created by inkooboo on 9/4/12.
//
//

#ifndef __mucus__flying_text_effect__
#define __mucus__flying_text_effect__

# include "defs.hpp"
# include "primitives.hpp"

# include "effect_base.hpp"

# include <memory>

namespace effects 
{

    struct FlyingText : public EffectBase
    {
        static std::weak_ptr<FlyingText> create(const pr::Vec2 &position, cc::CCNode *parent, const char *text, size_t size, const cc::ccColor3B &color, float duration);
        
        virtual void update(float dt) override;
        virtual cc::CCNode * node() override;

    private:
        cc::CCLabelTTF *m_label;
        pr::Vec2 m_position;
    };
}

#endif /* defined(__mucus__flying_text_effect__) */
