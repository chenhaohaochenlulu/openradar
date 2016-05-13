#include "spaceLocation.h"
#include <stdio.h>

CSpaceLocation::CSpaceLocation()
{
#if SPACE_LOCATION_DEBUG
	printf("CSpaceLocation::CSpaceLocation()\n");
#endif

}

CSpaceLocation::~CSpaceLocation()
{
#if SPACE_LOCATION_DEBUG
	printf("CSpaceLocation::~CSpaceLocation()\n");
#endif	
	
}


#if SPACE_LOCATION_DEBUG
int main(int argc,char * argv[])
{
	CSpaceLocation spaceLocation;
	
	return 0;
}
#endif //SPACE_LOCATION_DEBUG for CSpaceLocation