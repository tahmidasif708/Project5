/**
* Author: Tahmid Asif
* Assignment: Platformer
* Date due: 2023-12-02, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "Level1.hpp"

#define LEVEL1_WIDTH 18
#define LEVEL1_HEIGHT 17

#define LEVEL1_ENEMY_COUNT 1

unsigned int level1_data[] =
{
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 2, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 2, 0, 0, 2, 0, 3,
    3, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 3, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 3, 3, 3, 0, 3,
    3, 0, 0, 0, 2, 2, 0, 0, 2, 2, 3, 0, 0, 0, 0, 0, 0, 3,
    3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 2, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 3, 0, 0, 3,
    3, 0, 0, 0, 3, 3, 0, 0, 2, 0, 0, 0, 2, 3, 0, 0, 0, 3,
    3, 3, 2, 2, 3, 0, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 0, 0, 3
};

Level1::Level1(int curr_lives) {
    state.player_lives = curr_lives;
}

void Level1::initialise() {
    
    state.nextScene = -10;
    
    GLuint mapTextureID = Util::load_texture("tilesheet.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 3, 1);
    
    state.player = new Entity();
    state.player->entityType = PLAYER;
    
    state.player->position = glm::vec3(6, 0, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -9.81f, 0);
    state.player->speed = 2.5f;
    state.player->textureID = Util::load_texture("kenny2.png");
    
    state.player->anim_right = new int[4] {36, 37, 38, 39};
    state.player->anim_left = new int[4] {46, 47, 48, 49};
    state.player->anim_up = new int[4] {0, 4, 8, 7};
    state.player->anim_down = new int[4] {0, 4, 8, 7};

    state.player->anim_indx = state.player->anim_right;
    state.player->anim_frames = 4;
    state.player->anim_index = 0;
    state.player->anim_time = 0;
    state.player->anim_columns = 9;
    state.player->anim_rows = 6;
    
    state.player->height = 0.8f;
    state.player->width = 0.35f;
    
    state.player->jump_power = 5.0f;
    
    state.enemies = new Entity[LEVEL1_ENEMY_COUNT];
    
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].position = glm::vec3(9, -9, 0);
    state.enemies[0].acceleration = glm::vec3(0, -9.81f, 0);
    
    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = IDLE;
    
    state.enemies[0].textureID = Util::load_texture("ai.png");
    state.enemies[0].height = 1.0f;
    state.enemies[0].width = 0.5f;
    state.enemies[0].movement = glm::vec3(0);
    state.enemies[0].speed = 1;
}

void Level1::update(float deltaTime) {
    state.player->update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);
    
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);
    }
    
    std::cout << "Lives: " << state.player_lives << "\n";
    
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        std::cout << "Enemy: (" << state.enemies[i].position.x << ", ";
        std::cout << state.enemies[0].position.y << ") \n";
        
        if(state.player->CheckCollision(&state.enemies[i])) {
            if(state.enemies[i].collidedTop) {
                std::cout << "yes!\n";
                state.enemies[i].isActive = false;
            }
            else {
                std::cout << "ah!\n";
                lose_life();
                state.nextScene = 1;
            }
        }
    }
    
    if (state.player->position.x >= 15.85) {
        state.nextScene = 2;
    }
    else if (state.player->position.y < -15.5) {
        lose_life();
        if (state.player->lives == 0) {
            state.nextScene = 5;
        }
        else {
            state.nextScene = 1;
        }
    }
}

void Level1::render(ShaderProgram *g_shader_program) {
    GLuint fontTextureID = Util::load_texture("font1.png");
    Util::draw_text(g_shader_program, fontTextureID, "Level 1", 0.8f, 0.1f, glm::vec3(2, -13, 0));
    
    Util::draw_text(g_shader_program, fontTextureID, "Up!", 0.4f, 0.05f, glm::vec3(8.7, -10, 0));
    Util::draw_text(g_shader_program, fontTextureID, "Up!", 0.4f, 0.05f, glm::vec3(8.7, -11, 0));
    Util::draw_text(g_shader_program, fontTextureID, "Up!", 0.4f, 0.05f, glm::vec3(8.7, -12, 0));
    
    Util::draw_text(g_shader_program, fontTextureID, "Climb!", 0.4f, 0.05f, glm::vec3(2.0, -4.8, 0));
    
    Util::draw_text(g_shader_program, fontTextureID, "Finished!", 0.4f, 0.1f, glm::vec3(11.8, 0.5, 0));
    
    std::string lives_str = std::to_string(state.player_lives);
    
    std::string rounded = lives_str.substr(0, lives_str.find(".")+0);
    
    std::string lives_left = "Lives: " + rounded;
    
    Util::draw_text(g_shader_program, fontTextureID, lives_left, 0.5f, 0.1f, glm::vec3(3, 1.0, 0));
    
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].render(g_shader_program);
    }
    
    state.map->render(g_shader_program);
    state.player->render(g_shader_program);
    
}
