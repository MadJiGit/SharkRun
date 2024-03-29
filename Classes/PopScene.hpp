//
//  PopScene.hpp
//  TestGame
//
//  Created by Madji on 8.08.20.
//

#ifndef PopScene_h
#define PopScene_h

#include <type_traits>
#include <cocos2d.h>

#pragma once

//------------------------------------------------------------------------------

/// Transition adapter that pops current scene with transition passed as an argument.
///
/// Example:
///     Instead of calling cocos2d::Director::getInstance()->popScene() just call:
///
///     cocos2d::Director::getInstance()->pushScene(
///         pop_scene_with<cocos2d::TransitionFlipX>::create(1.0f, cocos2d::TransitionScene::Orientation::LEFT_OVER)
///     );
///
/// Note that there is no typical 2nd argument taking the scene for the transition,
/// one simply passes all the arguments they would pass to the transition's create
/// method except for the 2nd argument carrying the scene.
template <typename Transition>
struct pop_scene_with : Transition
{

    static_assert(std::is_base_of<cocos2d::TransitionScene, Transition>::value, "Type argument must be a class derived from cocos2d::TransitionScene");

private:

    /// A helper class to access protected member of a director we need
    struct DirectorAccessor : cocos2d::Director
    {
        /// Returns the scene that is previous to the current scene.
        cocos2d::Scene* getPreviousScene() const
        {
            assert(_scenesStack.size() > 1); // Top is current scene and the user is asking for previous, which must exist
            return _scenesStack.at(_scenesStack.size() - 2);
        }
    };

    /// Catch the end of the transition to pop the actual scene
    virtual void onExit() override
    {
        Transition::onExit();
        cocos2d::Director::getInstance()->popScene(); // Pop the replica of the previous scene we pushed
        cocos2d::Director::getInstance()->popScene(); // Pop the scene we were actually trying to pop
    }

public:

    /// Creator of the scene popper.
    template<typename... Args>
    static pop_scene_with* create(float t, Args&&... args)
    {
        pop_scene_with* pThisScene = new (std::nothrow) pop_scene_with();
        cocos2d::Scene* pPrevScene = static_cast<DirectorAccessor*>(cocos2d::Director::getInstance())->getPreviousScene();

        if (pThisScene && pThisScene->initWithDuration(t, pPrevScene, std::forward<Args>(args)...))
        {
            pThisScene->autorelease();
            return pThisScene;
        }

        CC_SAFE_DELETE(pThisScene);
        return nullptr;
    }
};

//------------------------------------------------------------------------------


#endif /* PopScene_h */
