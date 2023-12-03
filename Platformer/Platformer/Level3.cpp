/**
* Author: Tahmid Asif
* Assignment: Platformer
* Date due: 2023-12-02, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "Level3.hpp"

#define LEVEL3_WIDTH 18
#define LEVEL3_HEIGHT 17

#define LEVEL3_ENEMY_COUNT 3

unsigned int level3_data[] =
{
    3, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 3,
    3, 0, 0, 2, 0, 0, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 2, 3,
    3, 0, 0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 3,
    3, 0, 2, 3, 3, 3, 0, 0, 0, 3, 0, 0, 0, 3, 3, 3, 3, 3,
    3, 0, 0, 0, 0, 0, 0, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 2, 2, 2, 3, 2, 0, 2, 0, 0, 2, 0, 3,
    3, 1, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 3,
    3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 3, 3, 0, 3,
    3, 3, 2, 1, 0, 0, 1, 1, 0, 0, 1, 1, 3, 3, 3, 3, 0, 3,
    3, 0, 2, 2, 2, 2, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 3,
    3, 2, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 3,
    3, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 2, 3, 3, 3, 3,
    3, 0, 0, 3, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 3, 3, 3, 3,
    3, 3, 0, 0, 3, 3, 0, 0, 2, 3, 3, 0, 0, 3, 2, 3, 3, 3,
    3, 3, 3, 0, 0, 0, 0, 3, 2, 0, 0, 0, 2, 2, 2, 3, 3, 3,
    3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3
};

Level3::Level3(int curr_lives) {
    state.player_lives = curr_lives;
}

void Level3::initialise() {
    state.nextScene = -10;
    
    GLuint mapTextureID = Util::load_texture("tilesheet.png");
    state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 3, 1);
    
    state.player = new Entity();
    state.player->entityType = PLAYER;
    
    state.player->position = glm::vec3(14.8, 0, 0);
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
    
    state.player->jump_power = 6.0f;
    
    state.enemies = new Entity[LEVEL3_ENEMY_COUNT];
        
    GLuint enemyTextureID = Util::load_texture("ai.png");;
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i ++) {
        state.enemies[i].entityType = ENEMY;
        
        if (i == 0) {
            state.enemies[i].position = glm::vec3(13.0f, -9.5f, 0);
        }
        else if (i == 1) {
            state.enemies[i].position = glm::vec3(8.8f, -8.0f, 0);
        }
        else {
            state.enemies[i].position = glm::vec3(9.8f, 0.0f, 0);
        }
        
        state.enemies[i].acceleration = glm::vec3(0, -9.81f, 0);
        state.enemies[i].aiType = WAITANDGO;
        state.enemies[i].aiState = IDLE;
        
        state.enemies[i].textureID = enemyTextureID;
        state.enemies[i].height = 1.0f;
        state.enemies[i].width = 0.5f;
        
        state.enemies[i].movement = glm::vec3(0);
        state.enemies[i].speed = 1;
    }
}

void Level3::update(float deltaTime) {
    state.player->update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map);
    
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map);
    }
    
    std::cout << "Lives: " << state.player_lives << "\n";
    
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
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
                state.nextScene = 3;
            }
        }
    }
    
    if ((state.player->position.x >= 10.2) && (state.player->position.y >= 0.85)) {
        state.nextScene = 4;
    }
    else if (state.player->position.y < -15.5) {
        lose_life();
        if (state.player->lives == 0) {
            state.nextScene = 5;
        }
        else {
            state.nextScene = 3;
        }
    }
}

void Level3::render(ShaderProgram *g_shader_program) {
    GLuint fontTextureID = Util::load_texture("font1.png");
    Util::draw_text(g_shader_program, fontTextureID, "Level", 0.8f, 0.1f, glm::vec3(12.05, 1.0, 0));
    Util::draw_text(g_shader_program, fontTextureID, "3", 0.8f, 0.1f, glm::vec3(13.75, -0.1, 0));
    
    Util::draw_text(g_shader_program, fontTextureID, "End!", 0.38f, 0.05f, glm::vec3(9.85, 1.05, 0));
    
    std::string lives_str = std::to_string(state.player_lives);
    
    std::string rounded = lives_str.substr(0, lives_str.find(".")+0);
    
    std::string lives_left = "Lives: " + rounded;
    
    Util::draw_text(g_shader_program, fontTextureID, lives_left, 0.5f, 0.1f, glm::vec3(3, 1.0, 0));
    
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        state.enemies[i].render(g_shader_program);
    }
    
    state.map->render(g_shader_program);
    state.player->render(g_shader_program);
}
