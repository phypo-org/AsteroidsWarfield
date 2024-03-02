#ifndef H_PAutoPtr_H
#define H_PAutoPtr_H



// ********************************************************
template <typename OBJ>
class AutoPtr {

OBJ* ptr;

  public :

  AutoPtr( OBJ* obj=NULL ) 
    :ptr(obj)
  {    
  }

  AutoPtr( AutoPtr<OBJ>& ap ) 
    :ptr(ap.ptr)
  {    
    ap.ptr = NULL;
  }

  ~AutoPtr()
  {
    delete ptr;
		ptr = NULL;
  }

	void drop()
		{
			delete ptr;
			ptr = NULL;
		}

  int operator == (void*p_ptr)
    {
      return ptr == p_ptr;
    }

  int operator == (OBJ* p_ptr)
    {
      return ptr == p_ptr;
    }

  void operator = (AutoPtr<OBJ>& ap)
  {
    delete ptr;
    ptr = ap.ptr;
    ap.ptr = NULL;
  }


  void operator = ( OBJ* obj )
  {
    delete ptr;
    ptr = obj;
  }


  OBJ* operator->() const 
  {
    return (OBJ*)ptr;
  }

  OBJ* operator()()
  {
    return ptr;
  }

  operator OBJ*()
  {
    return ptr;
  }

	OBJ* give()
	{
		OBJ* tmp = ptr;
		ptr = NULL;
		return tmp;
	}

  OBJ* getPtr()
	{
		return ptr;
	}
};
// ********************************************************

#endif
