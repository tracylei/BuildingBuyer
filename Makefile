CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = flood
OBJECTS =  main.o controller.o game.o nonproperty.o gym.o residence.o property.o cell.o academicbuilding.o player.o boarddisplay.o celldisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

.PHONY: clean
