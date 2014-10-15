#ifndef _MUCUS_SCENE_MANAGER_HPP_
#define _MUCUS_SCENE_MANAGER_HPP_

# include "subsystem.hpp"
# include "defs.hpp"

class SceneManager : public subsystem_t
{
    virtual void start() override;
    virtual void stop() override;

public:
    SceneManager();
    
    void loadScene(cc::Scene *scene, float delay = 0);
    
private:
    void transitScene(cc::Scene *scene);
    
    cc::Scene *m_current_scene;
};

#endif
