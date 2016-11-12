#ifndef CLASS_H
#define CLASS_H

#include "object.h"

/*
keyword:  class

 [template_spec]   
 class [decl_spec] [tag [: base_list ]]  
{
	[member_list]
	[func_list]
} [declarators];  
[ class ] tag declarators;
*/

namespace n_class {
	class Cclass :public Object
	{
	public:
		string template_spec;
		string decl_spec;
		string tag;
		string declarators;
		list<char *> base_list;//base class list 

		list<char *> member_list;//base class list 
		list<char *> func_list;//base class list 
	public:
		Cclass();
		int func(void *p=NULL);
		int create(void *p);//Cclass *p
	};

}
using namespace n_class;

#endif
