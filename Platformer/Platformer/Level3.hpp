/**
* Author: Tahmid Asif
* Assignment: Platformer
* Date due: 2023-12-02, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "Scene.hpp"

class Level3 : public Scene {
    public:
        Level3(int curr_lives);
        void initialise() override;
        void update(float deltaTime) override;
        void render(ShaderProgram *g_shader_program) override;
};
