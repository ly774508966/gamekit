/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2012 Petr Havlena (havlenapetr@gmail.com)
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/

#include <OgreKit.h>

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <android/window.h>
#include <android_native_app_glue.h>

class OgreKit : public gkCoreApplication, public gkWindowSystem::Listener {
public:
    OgreKit(ANativeActivity* activity);
    virtual ~OgreKit() {}

    void keyReleased(const gkKeyboard& key, const gkScanCode& sc);

private:
    gkString m_blend;
    gkScene* m_scene;
};

OgreKit::OgreKit(ANativeActivity* activity) {
    ANativeActivity_setWindowFlags(activity,
            AWINDOW_FLAG_FULLSCREEN | AWINDOW_FLAG_KEEP_SCREEN_ON, 0);
}

void OgreKit::keyReleased(const gkKeyboard& key, const gkScanCode& sc) {
    if (sc == KC_ESCKEY)
        m_engine->requestExit();
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state) {
    assert(state);

    // Make sure glue isn't stripped.
    app_dummy();

    OgreKit engine(state->activity);
    engine.run();
}
