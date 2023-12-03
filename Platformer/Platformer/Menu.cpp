/**
* Author: Tahmid Asif
* Assignment: Platformer
* Date due: 2023-12-02, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "Menu.hpp"

#define MENU_WIDTH 18
#define MENU_HEIGHT 17

unsigned int menu_data[] =
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

void Menu::initialise() {
    
    state.nextScene = -1;

    GLuint mapTextureID = Util::load_texture("tilesheet.png");
    state.map = new Map(MENU_WIDTH, MENU_HEIGHT, menu_data, mapTextureID, 1.0f, 3, 1);

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

void Menu::update(float deltaTime) {
    state.player->update(deltaTime, state.player, state.enemies, 0, state.map);
    
    if (state.player->position.x >= 15.85) {
        state.nextScene = 1;
    }
}

void Menu::render(ShaderProgram *g_shader_program) {
    GLuint fontTextureID = Util::load_texture("font1.png");
    Util::draw_text(g_shader_program, fontTextureID, "Escape Kenny!", 0.5f, 0.1f, glm::vec3(2, -10, 0));
    
    Util::draw_text(g_shader_program, fontTextureID, "Jump & Run", 0.42f, 0.01f, glm::vec3(3.2, -11.1, 0));
    Util::draw_text(g_shader_program, fontTextureID, "Use Arrows and Space", 0.41f, 0.01f, glm::vec3(1.31, -12, 0));
        
    Util::draw_text(g_shader_program, fontTextureID, "Enter to Start", 0.4f, 0.1f, glm::vec3(1.75, -13, 0));
    
    Util::draw_text(g_shader_program, fontTextureID, "nice", 0.4f, 0.01f, glm::vec3(13.0, -14, 0));
    
    state.map->render(g_shader_program);
    state.player->render(g_shader_program);
}
