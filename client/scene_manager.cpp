#include "scene_manager.hpp"

#include "view.hpp"
#include "level_loader.hpp"
#include "loop.hpp"

const static float TRANSITION_TIME = .5f;

void SceneManager::start()
{
    loadScene(master_t::subsystem<View>().scene());
    master_t::subsystem<LevelLoader>().loadLevel("test_level");
}

void SceneManager::stop()
{
}

SceneManager::SceneManager()
{
}

void SceneManager::loadScene(cc::Scene *new_scene, float delay)
{
    m_current_scene = new_scene;
    cc::Director::sharedDirector()->replaceScene(m_current_scene);
}

