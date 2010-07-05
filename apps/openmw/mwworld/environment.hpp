#ifndef GAME_WORLD_INVIRONMENT_H
#define GAME_WORLD_INVIRONMENT_H

namespace MWSound
{
    class SoundManager;
}

namespace MWScript
{
    class GlobalScripts;
}

namespace MWWorld
{
    class World;

    ///< Collection of script-accessable sub-systems
    struct Environment
    {   
        Environment() : mWorld (0), mSoundManager (0), mGlobalScripts (0) {}
    
        World *mWorld;
        MWSound::SoundManager *mSoundManager;
        MWScript::GlobalScripts *mGlobalScripts;
    };
}

#endif
