#include "src/rend/Renderer.hpp"
#include "src/Engine.hpp"

int main() {
	std::cout << "Starting application..." << std::endl;
	
	Engine engine;
	std::cout << "Engine created" << std::endl;
	
	engine.Start();
	std::cout << "Engine started" << std::endl;

	std::cout << "Creating renderer..." << std::endl;
	Renderer renderer(engine.getEntitiesPtr()); //i will feed the main scene to Renderer so it can access data fast
	std::cout << "Renderer created" << std::endl;

	auto update = [&](float dt) { engine.UpdateLoop(dt); };
	auto drawUI = [&]() { engine.imGuiDraw_eng(); };

	std::cout << "Starting renderer..." << std::endl;
	renderer.run(update, drawUI);
	
	return 0;
}