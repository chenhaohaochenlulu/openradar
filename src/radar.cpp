#include "radar.h"
#include <stdio.h>

CRadar::CRadar()
{
#if RADAR_DEBUG
	printf("CRadar::CRadar()\n");
#endif

}

CRadar::~CRadar()
{
#if RADAR_DEBUG
	printf("CRadar::~CRadar()\n");
#endif	
	
}


#if RADAR_DEBUG
int main(int argc,char * argv[])
{
	CRadar radar;
	
	return 0;
}
#endif //RADAR_DEBUG for CRadar