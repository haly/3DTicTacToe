#include "Human.h"

Human::Human(std::string name) : Player(name){
}


Human::~Human() {
}

IntVector3 Human::getMove(const CuboidArray& ca) {
	return IntVector3(0, 0, 0);
}