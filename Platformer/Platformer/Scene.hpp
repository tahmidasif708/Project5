/**
* Author: Tahmid Asif
* Assignment: Platformer
* Date due: 2023-12-02, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#include "Util.hpp"
#include "Entity.hpp"
#include "Map.hpp"

struct GameState {
    Map *map;
    Entity *player;
    Entity *enemies;
    int nextScene;
    int player_lives;
};
class Scene {
    public:
        GameState state;
        virtual void initialise() = 0;
        virtual void update(float deltaTime) = 0;
        virtual void render(ShaderProgram *g_shader_program) = 0;
    
        void lose_life();
};
