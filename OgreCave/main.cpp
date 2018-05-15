#include <ogremain.h>


#undef main

int main(){
    //OgreMain mOgre;
    //mOgre.initApp();
    //mOgre.getRoot()->startRendering();
    //mOgre.closeApp();
    auto mOgrep=new OgreMain;
    mOgrep->initApp();
    mOgrep->getRoot()->startRendering();
    mOgrep->closeApp();
    return 0;
}
