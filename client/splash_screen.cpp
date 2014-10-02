#include "splash_screen.hpp"
#include "master.hpp"
#include "resource_utils.hpp"

void SplashScreen::start()
{
    m_layer = cc::CCLayer::create();

    cc::CCSprite *logo = cc::CCSprite::create(res::picture("logo1").c_str());

    m_layer->addChild(logo);

    cc::CCSize size = cc::CCDirector::sharedDirector()->getWinSize();

    logo->setPosition(cc::Point(size.width/2, size.height/2));

    m_scene->addChild(m_layer);
}

void SplashScreen::stop()
{
    m_scene->removeChild(m_layer, true);
}

SplashScreen::SplashScreen()
{
    m_scene = cc::CCScene::create();
}

SplashScreen::~SplashScreen()
{
}

cc::CCScene * SplashScreen::scene()
{
    return m_scene;
}
