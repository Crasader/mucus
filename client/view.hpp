#ifndef _MUCUS_VIEW_HPP_
#define _MUCUS_VIEW_HPP_

# include "defs.hpp"
# include "subsystem.hpp"
# include "primitives.hpp"

class View : public subsystem_t
{
protected:
    virtual void start() override;
    virtual void stop() override;
    
public:
    View();
    ~View();

    cc::Scene * scene();

    void reload(cc::Size bg_size, pr::Vec2 world_size);
    
    float pixelScale() const;
    cc::Point toScreenCoordinates(pr::Vec2 world_coord) const;
    pr::Vec2 toWorldCoordinates(cc::Point screen_coord) const;
    float worldToPixel(float world_size) const;
    float pixelToScreen(float pixel_size) const;
    float screenToPixel(float screen_size) const;
    float pixelToWorld(float pixel_size) const;
    cc::CCLayer * gameLayer();
    
    void moveViewBy(float dx, float dy);
    void moveViewToPosition(const pr::Vec2 &position);
    
    void manageCameraPositionAndScale(float t);
    
    pr::Vec2 currentCameraPosition() const;

    void addSprite(cc::Node *sprite, int z_order = 0);
    void removeSprite(cc::Node *sprite);
    void drawSpriteHelper(cc::Node *sprite, pr::Vec2 position, float angle);

protected:
    void createGameLayerMenu(const cc::Vector<cc::MenuItem *> &items);

    void validateScale();
    void validatePosition();
    
    cc::Scene *m_scene;
    cc::Layer *m_game_layer;
    
    cc::Size m_size;
    
    float m_view_scale;
    float m_min_view_scale;
    float m_max_view_scale;
    float m_default_view_scale;
    float m_world_scale;
    
    pr::Vec2 m_half_screen_in_world_size;
    pr::Vec2 m_cur_positon;
};

#endif
