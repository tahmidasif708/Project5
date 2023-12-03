/**
* Author: Tahmid Asif
* Assignment: Platformer
* Date due: 2023-12-02, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "Win.hpp"

#define WIDTH 18
#define HEIGHT 17

unsigned int win_data[] =
{
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
};

void Win::initialise() {
    
    state.nextScene = -1;

    GLuint mapTextureID = Util::load_texture("tilesheet.png");
    state.map = new Map(WIDTH, HEIGHT, win_data, mapTextureID, 1.0f, 3, 1);

    state.player = new Entity();
    state.player->entityType = PLAYER;

    state.player->position = glm::vec3(5, 0, 0);
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
}

void Win::update(float deltaTime) {
    state.player->update(deltaTime, state.player, state.enemies, 0, state.map);
    
    if (state.player->position.x >= 15.85) {
        state.nextScene = 1;
    }
}

void Win::render(ShaderProgram *g_shader_program) {
    GLuint fontTextureID = Util::load_texture("font1.png");
    Util::draw_text(g_shader_program, fontTextureID, "Wow!", 0.4f, 0.1f, glm::vec3(2.5, 0, 0));
    Util::draw_text(g_shader_program, fontTextureID, "You Win!", 0.6f, 0.1f, glm::vec3(2.0, -10, 0));
        
    state.map->render(g_shader_program);
    state.player->render(g_shader_program);
}
