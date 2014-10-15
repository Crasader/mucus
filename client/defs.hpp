#ifndef _MUCUS_DEFS_HPP_
#define _MUCUS_DEFS_HPP_

# include <cocos2d.h>
# include <Box2D/Box2D.h>
# include "SimpleAudioEngine.h"

# include <functional>
# include <memory>

namespace cc = cocos2d;
namespace cd = CocosDenshion;

// development defines
#define NO_MENU
#define NO_SOUND

//for using std::max, std::min
#ifdef _WINDOWS
    #undef max
	#undef min
#endif

typedef std::function<void()> LazyFunction;

#endif
