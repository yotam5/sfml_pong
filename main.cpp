
#include "src/Game.cpp"

int main(void){

	auto test = new Game();
	test->run();
	std::cout << "finished" << std::endl;
	delete test;
}