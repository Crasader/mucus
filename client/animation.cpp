#include "animation.hpp"
#include "resource_utils.hpp"

#include "master.hpp"
#include <json/json.h>

cc::Sprite * Animation::sprite()
{
    return m_sprite;
}


Animation::Animation(const char *name)
    : m_sprite(0)
    , m_cur_action(0)
{
    std::string base_path = res::animation_base_path(name);

    std::string description_str = res::load_file_content(base_path + name + ".json");
    Json::Reader parser;
    parser.parse(description_str, m_descr);

    auto action_names = m_descr.getMemberNames();
    for (auto it = action_names.begin(); it != action_names.end(); ++it)
    {
        std::string cur_name = *it;
        const Json::Value &cur = m_descr[cur_name];
        assert(cur.isObject());

        float interval = cur["interval"].asFloat();

        const Json::Value &frames = cur["frames"];
        assert(frames.isArray());

        cc::Vector<cc::SpriteFrame *> anim_frames;
        for (unsigned int i = 0; i < frames.size(); ++i) {
            std::string frame = frames[i].asString();

            std::string frame_path = res::animation_frame((base_path + frame).c_str());

            cc::Texture2D *texture = cc::TextureCache::sharedTextureCache()->addImage(frame_path.c_str());

            cc::SpriteFrame *sprite_frame = cc::SpriteFrame::createWithTexture(texture, cc::Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));

            if (!m_sprite)
                m_sprite = cc::Sprite::createWithSpriteFrame(sprite_frame);

            anim_frames.pushBack(sprite_frame);
        }

        cc::Animation *animation = cc::Animation::createWithSpriteFrames(anim_frames, interval);
        cc::ActionInterval *action = cc::Animate::create(animation);
        action->retain();

        m_animations[cur_name] = action;
    }

}

Animation::~Animation()
{
    for (auto &anim : m_animations)
        anim.second->release();
}

void Animation::animate(const std::string &name, LazyFunction on_animation_loop_end)
{
    auto animation_iter = m_animations.find(name);
    if (animation_iter == m_animations.end())
        return;

    auto &action = animation_iter->second;

    if (m_cur_action)
        m_sprite->stopAction(m_cur_action);

    m_cur_action = cc::RepeatForever::create(action);
    m_sprite->runAction(m_cur_action);

    float delay = m_descr[name]["interval"].asFloat() * m_descr[name]["frames"].size();

    master_t::subsystem<Loop>().schedule(on_animation_loop_end, delay);
}

