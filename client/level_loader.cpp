#include "level_loader.hpp"

#include "view.hpp"
#include "physics.hpp"
#include "object_manager.hpp"
#include "player.hpp"
#include "loop.hpp"
#include "effect_manager.hpp"

#include "resource_utils.hpp"

#include "objects/background.hpp"
#include "objects/platform.hpp"

#include <json/json.h>

void LevelLoader::start()
{
}

void LevelLoader::stop()
{

}

LevelLoader::LevelLoader()
{
}

void LevelLoader::loadLevel(const char *level_name)
{
    LOG() << "Begin loading of level \"" << level_name << "\"";
    std::string level_description_str = res::load_file_content(res::level_description(level_name));

    Json::Value description;
    Json::Reader parser;
    parser.parse(level_description_str, description);

    LOG() << "reload scheduler";
    master_t::subsystem<Loop>().reload();

    LOG() << "reload effects";
    master_t::subsystem<EffectManager>().reload();

    LOG() << "clear old objects";
    master_t::subsystem<ObjectManager>().reload();
    LOG() << "reload avatar";
    master_t::subsystem<Player>().reload();


    LOG() << "load background";
    const std::string bg_name_base = res::picture(description["background_base"].asCString());
    const std::string bg_name_parallax = res::picture(description["background_parallax"].asCString());
    LOG() << "background base picture = " << bg_name_base;
    LOG() << "background parallax picture = " << bg_name_parallax;

    cc::Sprite *bg = cc::Sprite::create(bg_name_base.c_str());
    cc::Size bg_size = bg->getContentSize();

    LOG() << "load world size";
    const Json::Value &world_size_descr = description["world_size"];
    float world_size_x = world_size_descr["width"].asFloat();
    float world_size_y = world_size_descr["height"].asFloat();
    pr::Vec2 world_size = pr::Vec2(world_size_x, world_size_y);
    LOG() << "world size = {" << world_size_x << "," << world_size_y << "}";

    LOG() << "reload physics";
    master_t::subsystem<Physics>().reload(world_size);

    LOG() << "reload view parameters";
    master_t::subsystem<View>().reload(bg_size, world_size);

#ifdef NO_SOUND
    LOG() << "preload background music";
    const std::string bg_music_file = res::background_sound(description["background_trek"].asCString());
    LOG() << "background music file = " << bg_music_file;
    master_t::subsystem<cd::SimpleAudioEngine>().preloadBackgroundMusic(bg_music_file.c_str());
    master_t::subsystem<cd::SimpleAudioEngine>().playBackgroundMusic(bg_music_file.c_str(), true);
    master_t::subsystem<cd::SimpleAudioEngine>().pauseBackgroundMusic();
    master_t::subsystem<cd::SimpleAudioEngine>().setBackgroundMusicVolume(float(0.3));
#endif

    LOG() << "create background";
    Json::Value bg_descr;
    bg_descr["class"] = "background";
    bg_descr["bg_name_base"] = bg_name_base;
    bg_descr["bg_name_parallax"] = bg_name_parallax;
    master_t::subsystem<ObjectManager>().createObject(bg_descr);


    LOG() << "create platforms";
    const Json::Value &platforms = description["platforms"];
    for (auto it = platforms.begin(); it != platforms.end(); ++it)
    {
        const Json::Value &platform_points = *it;
        Json::Value platform_descr;
        platform_descr["points"] = platform_points;
        platform_descr["class"] = "platform";

        master_t::subsystem<ObjectManager>().createObject(platform_descr);
    }

    LOG() << "create objects";
    const Json::Value objects = description["objects"];
    auto obj_names = objects.getMemberNames();
    for (auto it = obj_names.begin(); it != obj_names.end(); ++it)
    {
        LOG() << "    " << *it;
        Json::Value obj = objects[*it];
        master_t::subsystem<ObjectManager>().createObject(obj);
    }

    LOG() << "create player avatar";
    const Json::Value &player_position = description["player_start_position"];
	//master_t::subsystem<Player>().createAvatar( pr::Vec2(player_position["x"].asFloat(), player_position["y"].asFloat()) );
}
