1.class CRadar (雷达类)
   class CRadar 即用c++类虚拟出一个现实的雷达功能.给其他类,代码提供雷达功能.
   雷达:发射电磁波对目标进行照射并接收其回波，由此获得目标至电磁波发射点的
   距离(distance)、距离变化率(Range change rate)（径向速度）、空间位置(space position/location)、高度(high)等信息。 
 
2.class CSpaceLocation (空间位置类)
  空间位置数据描述地物所在位置。
  提供和记录某一时刻的物体的空间三维坐标系,
  三维坐标系:三维笛卡尔坐标,圆柱坐标,球面坐标,根据实际情况决定实现坐标信息.
  并提供关于位置信息的各种算法和结果.以方便给实际的物体类(class),目标类(class)使用.
  
3.class CObject (通用的物体类)
  各种不同类的物体的基类,以为子类提供通用的物体的物理属性,和物体的各种特征.

