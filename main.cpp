
#include "src/Game.cpp"
#define DEBUG(x) std::cout << x << std::endl;

int main(void){

	auto test = new Game();
	test->run();
	DEBUG("finished execution");
	delete test;
}