//
//  arek_view.hpp
//  mucus
//
//  Created by inkooboo on 11/22/12.
//
//

#ifndef mucus_arek_view_hpp
#define mucus_arek_view_hpp

#include "defs.hpp"
#include "master.hpp"
#include "resource_utils.hpp"
#include "view.hpp"
#include "game_logic.hpp"
#include "main_menu.hpp"
#include "player.hpp"
#include "objects/player/body.hpp"
#include "effects/flying_text.hpp"


struct MucusView : public cc::Object, public View
{
    virtual void start() override
    {
        View::start();
        
        using namespace cocos2d;
        
        cc::MenuItemImage *pClose = cc::MenuItemImage::create(
                                                                  res::picture("CloseNormal").c_str(),
                                                                  res::picture("CloseSelected").c_str(),
                                                                  this,
                                                                  menu_selector(MucusView::menuExit) );
        
        pClose->setPosition( ccp(m_size.width - 27, m_size.height - 28) );
        
        cc::MenuItemImage *pReload = cc::MenuItemImage::create(
                                                                   res::picture("shesterenka").c_str(),
                                                                   res::picture("shesterenka_p").c_str(),
                                                                   this,
                                                                   menu_selector(MucusView::menuTest) );
        
        pReload->setPosition( ccp(m_size.width - 27, 28) );
       
        cc:Vector<MenuItem *> items;
        items.pushBack(pClose);
        items.pushBack(pReload); 
        createGameLayerMenu(items);
    }
    
    void menuExit(cc::Object*)
    {
        master_t::subsystem<GameLogic>().loadScene(master_t::subsystem<MainMenu>().scene());
    }
    
    void menuTest(cc::Object*)
    {
        /// test sound fx. Remove it.
#ifndef NO_SOUND
        master_t::subsystem<cd::SimpleAudioEngine>().playEffect(res::sound_effect("046").c_str());
#endif
        ///
        
        /// test effects. Remove it.
        pr::Vec2 world_size = master_t::subsystem<Physics>().worldSize();
        world_size *= .5f;
        
        effects::FlyingText::create(world_size, m_game_layer, "Test Text", 14, cc::ccc3(190, 255, 190), 5.f);
        ///
        
    }
    
    virtual void manageCameraPositionAndScale(float t) override
    {
        Player &player = master_t::subsystem<Player>();
        
        if (player.isAvatarCreated())
        {
            pr::Vec2 body_postion = player.getBody()->getPosition();
            
            m_cur_positon = body_postion;
        }
        
        validateScale();
        validatePosition();
    }
    
};

#endif
