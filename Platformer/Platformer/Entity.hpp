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
#include "Map.hpp"

enum EntityType {PLAYER, PLATFORM, ENEMY};
enum AIType { WALKER, WAITANDGO };
enum AIState { IDLE, ACTIVE };

class Entity {
    public:
        EntityType entityType;
        AIType aiType;
        AIState aiState;
        
        glm::vec3 position;
        glm::vec3 movement;
        glm::vec3 acceleration;
        glm::vec3 velocity;
        
        float width = 1;
        float height = 1;
        
        float jump = false;
        float jump_power = 0;
        
        float speed;
        
        GLuint textureID;
        
        glm::mat4 modelMatrix;
        
        int *anim_right = NULL;
        int *anim_left = NULL;
        int *anim_up = NULL;
        int *anim_down = NULL;

        int *anim_indx = NULL;
        int anim_frames = 0;
        int anim_index = 0;
        float anim_time = 0;
        int anim_columns = 0;
        int anim_rows = 0;
        
        bool isActive = true;
        float lives = 3;
        
        bool collidedTop = false;
        bool collidedBottom = false;
        bool collidedLeft = false;
        bool collidedRight = false;
    
        bool defeatedEnemies = false;
        bool wasDefeated = false;
        
        Entity();
        
        bool CheckCollision(Entity *other);
        void CheckCollisionsY(Entity *objects, int objectCount);
        void CheckCollisionsX(Entity *objects, int objectCount);
        void CheckCollisionsX(Map *map);
        void CheckCollisionsY(Map *map);
        
        void update(float deltaTime, Entity *player, Entity *objects, int objectCount, Map *map);
        void render(ShaderProgram *g_shader_program);
        void draw_sprite_from_texture_atlas(ShaderProgram *g_shader_program, GLuint textureID, int index);
        
        void CheckEnemyCollision(Entity *enemies, int enemyCount);
        void AI(Entity *player);
        void AIWalker();
        void AIWaitAndGo(Entity *player);
};
