CXX=g++ 
CXXFLAGS=-Wall -MMD -g
EXEC=cc3k
GAME=Game/cell.o Game/chamber.o Game/controller.o Game/game.o Game/ChamberCrawler.o Game/map.o
ENEMY=monsters/dragon.o monsters/dwarf.o monsters/elf.o monsters/enemy.o monsters/halfling.o monsters/human.o monsters/merchant.o monsters/orc.o
ITEM=items/pa.o items/pd.o items/ph.o items/potion.o items/tresure.o items/item.o
CHARACTER=characters/drow.o characters/hero.o characters/shade.o characters/troll.o characters/vampire.o characters/character.o characters/goblin.o
OBJECTS= ${GAME} ${ENEMY} ${ITEM} ${CHARACTER}
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
