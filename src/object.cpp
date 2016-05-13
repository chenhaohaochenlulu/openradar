#include "object.h"
#include <stdio.h>

CObject::CObject()
{
#if OBJECT_DEBUG
	printf("CObject::CObject()\n");
#endif

}

CObject::~CObject()
{
#if OBJECT_DEBUG
	printf("CObject::~CObject()\n");
#endif	
	
}


#if OBJECT_DEBUG
int main(int argc,char * argv[])
{
	CObject radar;
	
	return 0;
}
#endif //OBJECT_DEBUG for CObject