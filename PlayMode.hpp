#include "Mode.hpp"

#include "Scene.hpp"
#include "WalkMesh.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <queue>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//----- game state -----

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up, action;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;

	//int gamestate = 0;
	float cooldown = 0.0f;

	struct Prompt {
		std::string text;
		float time;
		Prompt(std::string text_, float time_){
			text = text_;
			time = time_;
		}
	};
	std::queue<Prompt> prompts; 

	std::vector<Scene::Transform*> zees;
	int next[16] = {9,6,3,2,13,7,1,5,10,0,8,12,11,4,15,15};

	//player info:
	struct Player {
		WalkPoint at;
		//transform is at player's feet and will be yawed by mouse left/right motion:
		Scene::Transform *transform = nullptr;
		//camera is at player's head and will be pitched by mouse up/down motion:
		Scene::Camera *camera = nullptr;
	} player;
};
