/**
* Author: Tahmid Asif
* Assignment: Platformer
* Date due: 2023-12-02, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#include "Entity.hpp"
#include "Win.hpp"
#include "Lose.hpp"
#include "Map.hpp"
#include "Scene.hpp"
#include "Menu.hpp"
#include "Util.hpp"
#include "Level1.hpp"
#include "Level2.hpp"
#include "Level3.hpp"


SDL_Window* g_display_window;
bool g_game_is_running = true;

ShaderProgram g_shader_program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

Scene *curr_scene;
Scene *sceneList[6];

Mix_Music *music;
Mix_Chunk *hop;

void UpdateScene(int next_scene, int curr_lives=3) {
    if (next_scene == 1) {
        curr_scene = new Level1(curr_lives);
    }
    else if (next_scene == 2) {
        curr_scene = new Level2(curr_lives);
    }
    else if (next_scene == 3) {
        curr_scene = new Level3(curr_lives);
    }
    
    else {
        curr_scene = sceneList[next_scene];
    }
    curr_scene->initialise();
}

void initialise() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    g_display_window = SDL_CreateWindow("Escape!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 640, 480);
    
    g_shader_program.load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS("HotPursuit.mp3");
    Mix_PlayMusic(music, -1);
    
    hop = Mix_LoadWAV("boing.wav");
    
    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    g_shader_program.set_projection_matrix(projectionMatrix);
    g_shader_program.set_view_matrix(viewMatrix);
    
    glUseProgram(g_shader_program.get_program_id());
    
    glClearColor(0.18f, 0.31f, 0.31f, 1.0f);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    sceneList[0] = new Menu();
    sceneList[1] = new Level1(3);
    sceneList[2] = new Level2(3);
    sceneList[3] = new Level3(3);
    sceneList[4] = new Win();
    sceneList[5] = new Lose();
    UpdateScene(0);
}

void process_input() {
    
    curr_scene->state.player->movement = glm::vec3(0);
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                g_game_is_running = false;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        break;
                        
                    case SDLK_RIGHT:
                        break;
                    
                    case SDLK_RETURN:
                        curr_scene->state.player_lives = 3;
                        UpdateScene(1);
                        break;
                        
                    case SDLK_SPACE:
                        if (curr_scene->state.player->collidedBottom) {
                            curr_scene->state.player->jump = true;
                            Mix_PlayChannel(-1, hop, 0);
                        }
                        break;
                }
                break; 
        }
    }
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_RETURN]) {
        curr_scene->state.player_lives = 3;
        UpdateScene(1);
    }
    
    if (keys[SDL_SCANCODE_LEFT]) {
        curr_scene->state.player->movement.x = -1.0f;
        curr_scene->state.player->anim_indx = curr_scene->state.player->anim_left;
    }
    else if (keys[SDL_SCANCODE_RIGHT]) {
        curr_scene->state.player->movement.x = 1.0f;
        curr_scene->state.player->anim_indx = curr_scene->state.player->anim_right;
    }
    

    if (glm::length(curr_scene->state.player->movement) > 1.0f) {
        curr_scene->state.player->movement = glm::normalize(curr_scene->state.player->movement);
    }

}

#define FIXED_TIMESTEP 0.0166666f
float lastTicks = 0;
float accumulator = 0.0f;

void update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;

    deltaTime += accumulator;
    if (deltaTime < FIXED_TIMESTEP) {
        accumulator = deltaTime;
        return;
    }

    while (deltaTime >= FIXED_TIMESTEP) {
        curr_scene->update(FIXED_TIMESTEP);
        deltaTime -= FIXED_TIMESTEP;
    }

    accumulator = deltaTime;
    
    viewMatrix = glm::mat4(1.0f);
    
    if (curr_scene->state.player->position.y > -12.5) {
        if (curr_scene->state.player->position.x > 5) {
            if (curr_scene->state.player->position.x > 12) {
                if (curr_scene->state.player->position.y > -2) {
                    viewMatrix = glm::translate(viewMatrix, glm::vec3(-12, 2.1, 0));
                }
                else {
                    viewMatrix = glm::translate(viewMatrix, glm::vec3(-12, -curr_scene->state.player->position.y, 0));
                }
            }
            else {
                if (curr_scene->state.player->position.y > -2) {
                    viewMatrix = glm::translate(viewMatrix, glm::vec3(-curr_scene->state.player->position.x, 2.1, 0));
                }
                else {
                    viewMatrix = glm::translate(viewMatrix, glm::vec3(-curr_scene->state.player->position.x, -curr_scene->state.player->position.y, 0));
                }
            }
        }
        else {
            if (curr_scene->state.player->position.y > -2) {
                if (curr_scene->state.player->position.x < 5) {
                    viewMatrix = glm::translate(viewMatrix, glm::vec3(-5, 2.1, 0));
                }
                else {
                    viewMatrix = glm::translate(viewMatrix, glm::vec3(-curr_scene->state.player->position.x, 2.1, 0));
                }
            }
            else {
                viewMatrix = glm::translate(viewMatrix, glm::vec3(-5, -curr_scene->state.player->position.y, 0));
            }
        }
    }
    else {
        if (curr_scene->state.player->position.x < 5) {
            viewMatrix = glm::translate(viewMatrix, glm::vec3(-5, 12.75, 0));
        }
        else {
            viewMatrix = glm::translate(viewMatrix, glm::vec3(-curr_scene->state.player->position.x, 12.75, 0));
        }
    }
    
    std::cout << "(" << curr_scene->state.player->position.x
        << ", " << curr_scene->state.player->position.y;
    std::cout << ")\n";
}


void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    g_shader_program.set_view_matrix(viewMatrix);
    
    curr_scene->render(&g_shader_program);
    
    SDL_GL_SwapWindow(g_display_window);
}


void shutdown() {
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    initialise();
    
    while (g_game_is_running) {
        process_input();
        update();
        
        if (curr_scene->state.nextScene >= 0) {
            if (curr_scene->state.player_lives == 0) {
                UpdateScene(5);
            }
            else {
                UpdateScene(curr_scene->state.nextScene, curr_scene->state.player_lives);
            }
        }
        
        render();
    }
    
    shutdown();
    return 0;
}
