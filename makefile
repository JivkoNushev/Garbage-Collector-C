CXX = gcc
CXXFLAGS = -Wall
EXEC = GarbageCollectorTesting

OBJECTS = main.o gc.o LinkedList.o wrappers.o unique_ptr.o

ifeq ($(OS), Windows_NT)
	CLEAN = del
	EXEC := $(EXEC).exe
else
	CLEAN = rm
endif


$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)


MAIN_DEP = unique_ptr.h gc.h wrappers.h
main.o: main.c $(MAIN_DEP)
	$(CXX) $(CXXFLAGS) -c main.c


GC_DEP = gc.h wrappers.h 
gc.o: gc.c $(GC_DEP)
	$(CXX) $(CXXFLAGS) -c gc.c


LINKEDLIST_DEP = LinkedList.h gc.h wrappers.h
LinkedList.o: LinkedList.c $(LINKEDLIST_DEP)
	$(CXX) $(CXXFLAGS) -c LinkedList.c


WRAPPERS_DEP = wrappers.h gc.h
wrappers.o: wrappers.c $(WRAPPERS_DEP)
	$(CXX) $(CXXFLAGS) -c wrappers.c


UNIQUE_PTR_DEP = unique_ptr.h wrappers.h gc.h
unique_ptr.o: unique_ptr.c $(UNIQUE_PTR_DEP)
	$(CXX) $(CXXFLAGS) -c unique_ptr.c


clean:
	$(CLEAN) $(EXEC) $(OBJECTS)


# or just ?
# all:
# 	gcc -Wall ${ALL_SOURCE_FILES} -o GarbageCollectorTesting