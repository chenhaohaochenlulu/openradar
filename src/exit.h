#ifndef exit_H
#define exit_H

#include "object.h"

namespace n_exit {
	class Cexit :public Object
	{
	public:
		Cexit();
		int func(void *p=NULL);
	};

}
using namespace n_exit;

#endif
