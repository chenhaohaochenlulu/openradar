src := $(shell ls *.cpp)
objs := $(patsubst %.cpp , %.o ,$(src))
CFLAGS += -std=gnu++11 -DLINUX_OS -o 

iradar : $(objs)
	g++ $(CFLAGS) $@ $^ -lpthread

%.o : %.cpp
	g++ $(CFLAGS) $@ $< -lpthread

clean :
	rm -f iradar *.o *~
