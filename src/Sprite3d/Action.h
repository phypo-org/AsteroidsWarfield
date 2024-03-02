#ifndef h_Action_h
#define h_Action_h

#include <Sprite3d/Sprite3d.h>
#include <iostream>

//**************************************
class Action
{
public:
  Action() {; }
  virtual~Action()	{;	}
  virtual GLboolean leaveWorld( Sprite3d &pMySprite, void*pParam )
  {
    std::cout << "Action::leaveWorld" << std::endl;
    return GL_TRUE;
  }

  virtual GLboolean enterWorld( Sprite3d &pMySprite, void*pParam )
  {
    std::cout << "Action::enterWorld" << std::endl;
    return GL_TRUE;
  }

  virtual GLboolean animate( Sprite3d &pMySprite, void*pParam )
  {
    std::cout << "Action::animate" << std::endl;
    return GL_TRUE;
  }

  virtual GLboolean collision( Sprite3d &pMySprite, Sprite3d &pSprite, void *pParam )
  {
    std::cout << "Action::collision" << std::endl;
    return GL_TRUE;
  }
  virtual GLboolean kill( Sprite3d &pMySprite, void*pParam )
  {
    std::cout << "Action::kill" << std::endl;
    return GL_TRUE;
  }
  virtual long userAction( Sprite3d &pMySprite, void*pParam0, void*pParam1, void*pParam2 )
  {
    std::cout << "Action::userAction" << std::endl;
    return 0;
  }

};
//**************************************


#endif
