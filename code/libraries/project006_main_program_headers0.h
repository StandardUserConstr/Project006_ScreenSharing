#ifndef SECURITY_PROJECT006_MAIN_PROGRAM_H
#define SECURITY_PROJECT006_MAIN_PROGRAM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>                      //IMG_
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <winsock2.h>  //winsock2.h must be included before windows.h

#include "project006_SDL_TextBox.h"

//==================================================================================================
//Copyright (C)2009-2023 D. R. Commander.  All Rights Reserved.<br>
//Copyright (C)2015 Viktor Szathmáry.  All Rights Reserved.
#include "libjpeg-turbo/turbojpeg.h"
//==================================================================================================

#include "project006_tools0.h"
#include "project006_winsock_server_client0.h"

//for getting date
#include<time.h>

#pragma GCC diagnostic ignored "-Wpmf-conversions" //ingoring warning: converting from 'void* ('ClassName'::*)(void*)' to 'void* (*)(void*)' in function "Server_Menu::server_menu_run()" in file "project006_ServerMenu0.cpp"
                                                   //and in function "Client_Menu::client_menu_run()" in file "project006_ClientMenu0.cpp"

//add -D MAIN_PROGRAM0_DEBUG for debug purpose

SDL_HitTestResult SDLCALL hit_test0(SDL_Window *window, const SDL_Point *pt, void *data);

struct Global_Variables
{
    SDL_UniversalTools0* sdl_universal_tool0;
    UniversalTools0* universal_tool0;
    SDL_Cursor* arrow_cursor;
    SDL_Cursor* beam_cursor;
    TTF_Font* main_ttf;
    SDL_Window* window;
    SDL_Renderer* render;
    uint32_t main_menu_fps;
    bool server_bad_quality_share;   //only for server
    uint32_t inactive_timeout_in_ms; //only for server;
    uint32_t processor_cores;
    uint8_t compression_method;
    tjhandle compressor_handle;
    tjhandle decompress_handle;
};

//                                                                      MAIN_PROGRAM
//===============================================================================================================================================
class MAIN_PROGRAM
{
    void init_everything(Global_Variables* global_variables);
    void file_checks();
    void free_everything(Global_Variables* global_variables);

protected:
//universal_variables:
    Global_Variables* global_variables;
    bool close_program = 0;

//vector_structures
    struct vector_log_request_from_thread
    {
        char* what_save_to_file;
        char* logs_string_text;
        SDL_Color color_of_text;
        SDL_Color color_of_background;
        bool free_memory_from_first_two_arg_or_not;
    };
    struct vector_reset_textures_request_from_thread
    {
        uint8_t state0_or_1_or_2_or_3;
    };
    struct vector_update_textures_in_window0_in_state2_state3_from_thread
    {
        uint8_t which_texture_to_change;
    };

    struct vector_stdout_stderr
    {
        char* buffor;
        bool stdout_or_stderr;  //0 for stdout; 1 for stderr;
        bool free_memory;       //0 for no free memory; 1 for free memory;
    };

    struct vector_thread_send_receive
    {
        uint8_t operation_code;
    };

//universal_funcions:
    void event_standard();

//universal_tools:
    //string_in_out must have '\0' at the end;
    //returns 1 means "string needed shrink"; else if returns 0 then that means "no need to shrink";
    bool shrink_string_to_fit_the_size(TTF_Font* font,char* string_in_out,uint32_t max_width_of_text);

public:
    //constructor
    MAIN_PROGRAM()
    {
        this->global_variables = NULL;
    }

//main_functions:
    void initialization_global_variables(Global_Variables* global_variables)
    {
        if(this->global_variables!=NULL) return;
        this->global_variables = global_variables;

        init_everything(global_variables);
        file_checks();
        return;
    }

    void free_global_variables(Global_Variables* global_variables)
    {
        if(this->global_variables==NULL) return;

        free_everything(global_variables);
        return;
    }

    //destructor
    ~MAIN_PROGRAM()
    {

    }
};
//===============================================================================================================================================









//                                                                      Main_Menu
//===============================================================================================================================================
class Main_Menu : private MAIN_PROGRAM
{
//others
    bool close_program = 0;

//main_functions_variables:
    struct Main_Menu_Variables
    {
        //event_variables:
            uint8_t mouse_state = 0;
            uint8_t mouse_focus = 0;
    };

//function_events:
    void event_main_menu(Main_Menu_Variables* variables);

public:
    Main_Menu(Global_Variables* initialized_global_variables)
    {
        this->global_variables = initialized_global_variables;
    }

//main_functions:
    uint8_t main_menu_run();

    ~Main_Menu()
    {

    }
};
//===============================================================================================================================================








//                                                                      Server_Menu
//===============================================================================================================================================
class Server_Menu : private MAIN_PROGRAM
{
//others
    bool close_program = 0;

//main_functions_variables:
    struct Server_Menu_Variables
    {
            Global_Variables* ThreadFriendly_global_variables;
            uint8_t return_value;
            uint32_t window0_ID;
            uint32_t window1_ID;
            uint32_t window2_ID;
            SDL_Window* window1;
            SDL_Window* window2;
            SDL_Renderer* render1;
            SDL_Renderer* render2;
            bool exit_thread;

        //information_variables
            uint8_t* public_ip_string;
            uint32_t public_ip_int;
            uint8_t* local_ip;
            uint8_t* local_port;
            uint8_t* max_shared_fps;
            uint8_t* max_shared_quality;
            uint8_t* screen_width_share;
            uint8_t* screen_height_share;
            uint8_t* password_required;
            uint8_t* password;
            uint8_t* activate_hash;
            uint8_t* hash0;
            uint8_t* hash1;
            uint8_t* hash2;
            uint8_t* hash3;
            uint8_t* message0;
            uint8_t* message1;
            uint8_t* pause_image_path;
            uint8_t* max_shared_loss;

            uint32_t max_shared_fps_int;
            uint32_t screen_width_share_int;
            uint32_t screen_height_share_int;
            uint32_t max_shared_quality_int;
            uint32_t max_shared_loss_int;

            int32_t screen_width_preview;
            int32_t screen_height_preview;
            bool always_top_window2;
            bool is_screen_sharing_paused;
            int32_t buffor_for_screen_width_preview;
            int32_t buffor_for_screen_height_preview;

        //textures:
            //window0
            SDL_Texture* window0_main_background;
            SDL_Texture* window0_status_server_not_created;
            SDL_Texture* window0_status_server_created;
            SDL_Texture* window0_status_client_request;
            SDL_Texture* window0_status_client_accepted;
            SDL_Texture* window0_status_client_accepted_animation0;
            SDL_Texture* window0_bar_lost_focus;
            SDL_Texture** animation0;
            SDL_Texture** window0_state0_text_texture;
            const uint8_t COUNT_OF_WINDOW0_STATE0_TEXT_TEXTURE = 11;
            SDL_Texture** window0_state2_3_text_texture;
            const uint8_t COUNT_OF_WINDOW0_STATE2_3_TEXT_TEXTURE = 6;
            //window1
            SDL_Texture* window1_main_background;
            SDL_Texture* window1_state0;
            SDL_Texture* window1_state1;
            SDL_Texture* window1_bar_lost_focus;
            //window2
            SDL_Texture* window2_pause_image;

            //universal_window0
            SDL_Texture* window0_bar_pressed_button;
            SDL_Texture* window0_pressed_medium_button;
            SDL_Texture* window0_pressed_large_button;
            SDL_Texture* window0_red_diode;
            SDL_Texture* window0_blue_diode;
            //universal_window1
            SDL_Texture* window1_bar_pressed_button;
            SDL_Texture* window1_pressed_medium_button;
            SDL_Texture* window1_beam;
            SDL_Texture* window1_selected_option;
            SDL_Texture* window1_pressed_no_selected_option;
            SDL_Texture* window1_pressed_selected_option;
            SDL_Texture* window1_public_ip;
            //universal_window2
            SDL_Texture* window2_bar_pressed_button;
            SDL_Texture* window2_fullscreen_information;
            SDL_Texture* window2_bar;
            SDL_Texture* window2_main;

        //rects:
            //window0
            SDL_Rect rect_window0_main_background = (SDL_Rect){0,0,512,431};
            SDL_Rect rect_window0_status_server_not_created = (SDL_Rect){269,42,241,375};
            SDL_Rect rect_window0_status_server_created = (SDL_Rect){271,42,239,375};
            SDL_Rect rect_window0_status_client_request = (SDL_Rect){269,42,241,375};
            SDL_Rect rect_window0_status_client_accepted = (SDL_Rect){268,40,242,377};
            SDL_Rect rect_window0_status_client_accepted_animation0 = (SDL_Rect){420,201,75,23};
            SDL_Rect rect_window0_bar_lost_focus = (SDL_Rect){3,3,506,18};
            SDL_Rect rect_window0_animation = (SDL_Rect){282,351,32,32};
            SDL_Rect* rect_window0_state0_text_texture;
            SDL_Rect* rect_window0_state2_3_text_texture;
            //window1
            SDL_Rect rect_window1_main_background = (SDL_Rect){0,0,608,420};
            SDL_Rect rect_window1_status0 = (SDL_Rect){16,43,569,306};
            SDL_Rect rect_window1_status1 = (SDL_Rect){16,43,569,306};
            SDL_Rect rect_window1_bar_lost_focus = (SDL_Rect){4,4,600,18};
            SDL_Rect rect_window1_public_ip;
            //window2

            SDL_Rect rect_window2_pause_image;
            //universal
            SDL_Rect rect_bar_pressed_button;
            SDL_Rect rect_pressed_medium_button;
            SDL_Rect rect_pressed_large_button;
            SDL_Rect rect_red_diode = (SDL_Rect){50,32,4,4};
            SDL_Rect rect_blue_diode = (SDL_Rect){59,32,4,4};
            SDL_Rect rect_selected_option;
            SDL_Rect rect_pressed_no_selected_option;
            SDL_Rect rect_pressed_selected_option;
            //SDL_Rect rect_window2_fullscreen_information;
            SDL_Rect rect_window2_bar;

        //hittest rects:
            SDL_Rect window0_hittest = (SDL_Rect){0,0,447,21};
            SDL_Rect window1_hittest = (SDL_Rect){0,0,568,22};
            SDL_Rect window2_hittest;



        //event_variables
            uint8_t window0_mouse_state;
            uint8_t window1_mouse_state;
            uint8_t window2_mouse_state;

        //at_what_state_is_window
            uint8_t window0_state;
            uint8_t window1_state;
            uint8_t window2_state;

            uint8_t window0_animation;
            uint8_t window1_animation;
            uint8_t window2_animation;

            bool window0_display;
            bool window1_hide;
            bool window1_minimalize;
            bool window2_hide;
            bool window2_minimalize;
            bool window2_is_fullscreen;

        //logs_variables
            const uint32_t H_SIZE_OF_LOGS = 3328; //one line is 13;
            const int H_MAX_OF_DISPLAY = 365;
            SDL_Surface* main_logs_surface;
            SDL_Texture* main_logs_texture;
            SDL_Rect rect_logs_dst;
            SDL_Rect rect_logs_src;
            int32_t y_logs_position;
            FILE* logs_file;

        //window2_animations
            bool bar_animation_opacity;
            int16_t bar_animation_actual_opacity;
            uint32_t bar_animation_timer0;
            uint32_t bar_animation_timer1;
            uint32_t fullscreen_info_timer0;
            uint32_t fullscreen_info_timer1;
            int16_t fullscreen_actual_opacity;

        //timers:
            //animation_window0
            uint32_t timer0_0;
            uint32_t timer0_1;

        //diode_animation
            uint8_t diode_red_counter;
            uint8_t diode_blue_counter;
            uint32_t how_much_fps_pass_without_red_diode;
            uint32_t how_much_fps_pass_without_blue_diode;

        //textbox
            const uint8_t COUNT_OF_TEXBOXES = 17;
            TextBoxClass** textbox_variables;
            TextBoxClass::TextBoxStructure_settings** textbox_settings0;
            uint8_t** textbox_data;
            bool beam_is_unlock;

        //winsock:
            Winsock_server_structure server_structure;
            Winsock_server server;
            uint32_t timeout0;
            //have to be reset;
            uint8_t state_of_waiting_for_client;
            uint8_t is_server_busy;
            const uint8_t SIZE_OF_OPERATION_ARRAY = 143;
            bool server_operation[143]; //SIZE_OF_OPERATION_ARRAY;
            uint8_t client_first_send_request;
            int16_t priority_number;
            uint8_t buffor_to_response_code;
            uint32_t next_frame_timer;
            bool should_be_next_frame;
            bool wait_for_client_request;

        //threads
            volatile bool active_thread;
            volatile bool destroy_thread;
            volatile bool do_server_is_destroying;
            volatile bool do_client_is_rejecting;
            volatile bool frame_data_should_be_displaying;
            volatile uint8_t operation_on_data_frame;
            volatile bool wait_before_changing_loss_quality_fps0;
            uint32_t width_of_actual_frame;
            uint32_t height_of_actual_frame;
            uint32_t quality_of_actual_frame;
            uint8_t hash_active_of_actual_frame;
            uint32_t pitch_of_actual_frame;
            uint8_t* main_frame_data;
            uint8_t* main_frame_data_jpeg;
            uint32_t size_of_main_frame_data_jpeg;
            custom_vector0_ThreadSafePushBack<vector_reset_textures_request_from_thread>* thread_vector_reset_windows_request;
            custom_vector0_ThreadSafePushBack<vector_log_request_from_thread>* thread_vector_logs_request;
            custom_vector0_ThreadSafePushBack<vector_update_textures_in_window0_in_state2_state3_from_thread> thread_vector_update_window0_state2_state3;
            custom_vector0_ThreadSafePushBack<vector_stdout_stderr>* thread_vector_stdout_stderr;


        //client_variables
            uint8_t* client_public_ip_string;
            uint32_t client_public_ip_int;
            uint8_t requested_quality;
            uint16_t requested_fps;
            uint8_t requested_loss;
            uint8_t* message0_client;
            uint8_t* message1_client;
            uint8_t* password_client;

        //extra_function_variables
            bool VARIABLE_do_prepared_textboxes_FORCE_TO_RESET_TO_0;
            bool VARIABLE_reset_window0_and_window1_to_state0_or_1_or_2_or_3_PAUSE_WINDOW;

    };

//thread_structures:
    struct THREAD_server_menu_struct_variables
    {
        Global_Variables* THREAD_global_variables;
        Server_Menu_Variables* THREAD_variables;

    };

//function_events:
    void event_server_menu(Server_Menu_Variables* variables);

    //server_menu:
        //returns 0 if there is no error. otherwise returns non-zero;
        uint8_t server_menu_sets_variables(Server_Menu_Variables* variables);
        void free_server_menu_variables(Server_Menu_Variables* variables);

        void server_paste_textures_to_render_and_display(Server_Menu_Variables* variables);
        void server_paste_texture_to_render_and_display_window2(Server_Menu_Variables* variables);
        void server_animation0(Server_Menu_Variables* variables,bool mode);
        void server_unpack_vectors(Server_Menu_Variables* variables);

        void do_prepared_textboxes(SDL_Event* event,Server_Menu_Variables* variables);

        void* THREAD_capture_screen_to_window2_and_send_data_to_client(void* data);
        void THREAD_send_data_to_client_tool0(THREAD_server_menu_struct_variables* variables,char* log_buffor0,char* log_buffor1,uint8_t* buffor0_static);
        void THREAD_receive_data_to_client_tool0(THREAD_server_menu_struct_variables* variables,char* log_buffor0,char* log_buffor1,uint8_t* buffor0_static);
        void THREAD_BACKGROUND_send_data_to_client_tool1(THREAD_server_menu_struct_variables* variables,const uint8_t* const data_pointer,uint8_t* function_help_data);
        void THREAD_BACKGROUND_receive_data_to_client_tool1(THREAD_server_menu_struct_variables* variables,uint8_t*  data_pointer,uint8_t* function_help_data);

        //server_tools:
        //if color_of_background.a is 255, then OFF background;
        void save_logs_to_file_and_create_texture(Server_Menu_Variables* variables,const char* what_save_to_file,const char* logs_string_text,SDL_Color color_of_text,SDL_Color color_of_background);
        void reset_window0_and_window1_to_state0_or_1_or_2_or_3(Server_Menu_Variables* variables,uint8_t state0_or_1_or_2_or_3);
        void reset_all_server_state_variables(Server_Menu_Variables* variables);
        void force_update_textboes(Server_Menu_Variables* variables);

public:
    Server_Menu(Global_Variables* initialized_global_variables)
    {
        this->global_variables = initialized_global_variables;
    }

//main_functions:
    uint8_t server_menu_run();

    ~Server_Menu()
    {

    }
};
//===============================================================================================================================================











//                                                                      Client_Menu
//===============================================================================================================================================
class Client_Menu : private MAIN_PROGRAM
{

    struct Client_Menu_Variables
    {
        Global_Variables* ThreadFriendly_global_variables;
        uint8_t return_value;
        uint32_t window0_ID;
        uint32_t window1_ID;
        uint32_t window2_ID;
        SDL_Window* window1;
        SDL_Window* window2;
        SDL_Renderer* render1;
        SDL_Renderer* render2;

        //information_variables
            uint8_t* public_ip_string;
            uint8_t* server_ip;
            uint8_t* server_port;
            uint8_t* requested_quality;
            uint8_t* requested_fps;
            uint8_t* requested_loss;
            uint8_t* message0;
            uint8_t* message1;
            uint8_t* password;
            uint8_t* hash0;
            uint8_t* hash1;
            uint8_t* hash2;
            uint8_t* hash3;
            uint32_t public_ip_int;
            uint8_t requested_quality_int;
            uint16_t requested_fps_int;
            uint8_t requested_loss_int;

            //server_variables:
                uint32_t max_shared_fps_int;
                uint32_t max_shared_quality_int;
                uint32_t max_shared_loss_int;
                uint32_t screen_width_share_int;
                uint32_t screen_height_share_int;
                bool server_password_required;
                bool server_hash_activate;
                uint8_t* message0_server;
                uint8_t* message1_server;

            int32_t screen_width_preview;
            int32_t screen_height_preview;
            bool is_screen_sharing_paused;
            bool always_top_window2;
            int32_t buffor_for_screen_width_preview;
            int32_t buffor_for_screen_height_preview;

        //textures:
            //window0
                SDL_Texture* window0_main_background;
                SDL_Texture* window0_status_client_not_connected;
                SDL_Texture* window0_status_client_trying_to_connect;
                SDL_Texture* window0_status_client_waiting_for_accept;
                SDL_Texture* window0_status_client_accepted;
                SDL_Texture* window0_bar_lost_focus;
                SDL_Texture** animation0;
                SDL_Texture** window0_state0_text_texture;
                const uint8_t COUNT_OF_WINDOW0_STATE0_TEXT_TEXTURE = 8;
                SDL_Texture** window0_state2_3_text_texture;
                const uint8_t COUNT_OF_WINDOW0_STATE2_3_TEXT_TEXTURE = 10;
            //window1
                SDL_Texture* window1_main_background;
                SDL_Texture* window1_state0;
                SDL_Texture* window1_state1;
                SDL_Texture* window1_bar_lost_focus;
            //window2
                SDL_Texture* window2_background_no_signal;
                uint8_t* buffor_to_image012;
                uint32_t size_of_image012;

            //universal_window0
                SDL_Texture* window0_bar_pressed_button;
                SDL_Texture* window0_pressed_medium_button;
                SDL_Texture* window0_pressed_large_button;
                SDL_Texture* window0_red_diode;
                SDL_Texture* window0_blue_diode;
            //universal_window1
                SDL_Texture* window1_bar_pressed_button;
                SDL_Texture* window1_pressed_medium_button;
                SDL_Texture* window1_beam;
                SDL_Texture* window1_selected_option;
                SDL_Texture* window1_pressed_no_selected_option;
                SDL_Texture* window1_pressed_selected_option;
                SDL_Texture* window1_public_ip;
            //universal_window2
                SDL_Texture* window2_bar_pressed_button;
                SDL_Texture* window2_fullscreen_information;
                SDL_Texture* window2_bar;
                SDL_Texture* window2_main;
        //rects:
            //window0
                SDL_Rect rect_window0_main_background = (SDL_Rect){0,0,512,414};
                SDL_Rect rect_window0_status_client_not_connected = (SDL_Rect){266,42,244,358};
                SDL_Rect rect_window0_status_client_trying_to_connect = (SDL_Rect){266,42,244,358};
                SDL_Rect rect_window0_status_client_waiting_for_accept = (SDL_Rect){266,40,244,360};
                SDL_Rect rect_window0_status_client_accepted = (SDL_Rect){266,40,244,360};
                SDL_Rect rect_window0_bar_lost_focus = (SDL_Rect){3,3,506,18};
                SDL_Rect rect_window0_animation = (SDL_Rect){282,332,33,38};
                SDL_Rect* rect_window0_state0_text_texture;
                SDL_Rect* rect_window0_state2_3_text_texture;
            //window1
                SDL_Rect rect_window1_main_background = (SDL_Rect){0,0,608,338};
                SDL_Rect rect_window1_status0 = (SDL_Rect){16,43,569,275};
                SDL_Rect rect_window1_status1 = (SDL_Rect){16,43,569,275};
                SDL_Rect rect_window1_bar_lost_focus = (SDL_Rect){4,4,600,18};
                SDL_Rect rect_window1_public_ip;
            //window2
                SDL_Rect rect_window2_pause_image;

            //universal
                SDL_Rect rect_bar_pressed_button;
                SDL_Rect rect_pressed_medium_button;
                SDL_Rect rect_pressed_large_button;
                SDL_Rect rect_red_diode = (SDL_Rect){50,32,4,4};
                SDL_Rect rect_blue_diode = (SDL_Rect){59,32,4,4};
                SDL_Rect rect_selected_option;
                SDL_Rect rect_pressed_no_selected_option;
                SDL_Rect rect_pressed_selected_option;
                //SDL_Rect rect_window2_fullscreen_information;
                SDL_Rect rect_window2_bar;

        //hittest rects:
            SDL_Rect window0_hittest = (SDL_Rect){0,0,447,21};
            SDL_Rect window1_hittest = (SDL_Rect){0,0,568,22};
            SDL_Rect window2_hittest;

        //event_variables
            uint8_t window0_mouse_state;
            uint8_t window1_mouse_state;
            uint8_t window2_mouse_state;

        //at_what_state_is_window
            uint8_t window0_state;
            uint8_t window1_state;
            uint8_t window2_state;

            uint8_t window0_animation;
            uint8_t window1_animation;
            uint8_t window2_animation;

            bool window0_display;
            bool window1_hide;
            bool window1_minimalize;
            bool window2_hide;
            bool window2_minimalize;
            bool window2_is_fullscreen;

        //logs_variables
            const uint32_t H_SIZE_OF_LOGS = 3328; //one line is 13;
            const int H_MAX_OF_DISPLAY = 352; //TODO: to change propably later;
            SDL_Surface* main_logs_surface;
            SDL_Texture* main_logs_texture;
            SDL_Rect rect_logs_dst;
            SDL_Rect rect_logs_src;
            int32_t y_logs_position;
            FILE* logs_file;

        //window2_animations
            bool bar_animation_opacity;
            int16_t bar_animation_actual_opacity;
            uint32_t bar_animation_timer0;
            uint32_t bar_animation_timer1;
            uint32_t fullscreen_info_timer0;
            uint32_t fullscreen_info_timer1;
            int16_t fullscreen_actual_opacity;

        //timers:
            //animation_window0
            uint32_t timer0_0;
            uint32_t timer0_1;

        //diode_animation
            uint8_t diode_red_counter;
            uint8_t diode_blue_counter;
            uint32_t how_much_fps_pass_without_red_diode;
            uint32_t how_much_fps_pass_without_blue_diode;

        //textbox
            const uint8_t COUNT_OF_TEXBOXES = 14;
            TextBoxClass** textbox_variables;
            TextBoxClass::TextBoxStructure_settings** textbox_settings0;
            uint8_t** textbox_data;
            bool beam_is_unlock;

        //winsock
            Winsock_client_structure client_structure;
            Winsock_client client;
            uint32_t timeout0;
            //uint8_t client_state_operation;
            bool client_is_trying_to_disconnect;

        //threads
            //volatile bool active_thread;
            volatile bool destroy_thread;
            custom_vector0_ThreadSafePushBack<vector_reset_textures_request_from_thread>* thread_vector_reset_windows_request;
            custom_vector0_ThreadSafePushBack<vector_log_request_from_thread>* thread_vector_logs_request;
            custom_vector0_ThreadSafePushBack<vector_update_textures_in_window0_in_state2_state3_from_thread> thread_vector_update_window0_state2_state3;
            custom_vector0_ThreadSafePushBack<vector_stdout_stderr>* thread_vector_stdout_stderr;
            custom_vector0_ThreadSafePushBack<vector_thread_send_receive>* thread_vector_send_receive;
            volatile bool wait_to_end_operation_save_to_file_and_change_quality_fps_loss_variables;
            uint8_t* main_frame_data;
            volatile uint8_t operation_code_on_main_frame_data;
            uint32_t size_of_main_frame_data;
            uint32_t width_of_actual_frame;
            uint32_t height_of_actual_frame;
            uint32_t quality_of_actual_frame;
            uint32_t loss_of_actual_frame;
            uint32_t pitch_of_actual_frame;
            uint8_t safe_requested_loss;

            bool run_now_frame15_operation;
            bool screen_sharing_in_process;

        //extra_function_variables
            bool VARIABLE_do_prepared_textboxes_FORCE_TO_RESET_TO_0;

        //speed_up_config_functions_operations_variable
            int32_t client_base_position_in_config;


        //TEST VARIABLE (TO DELETE)

    };

//thread_structures:
    struct THREAD_client_menu_struct_variables
    {
        Global_Variables* THREAD_global_variables;
        Client_Menu_Variables* THREAD_variables;

    };

//function_events:
    void event_client_menu(Client_Menu_Variables* variables);

//client_menu:
    uint8_t client_menu_sets_variables(Client_Menu_Variables* variables);
    void free_client_menu_variables(Client_Menu_Variables* variables);

    void client_paste_textures_to_render_and_display(Client_Menu_Variables* variables);
    void client_paste_texture_to_render_and_display_window2(Client_Menu_Variables* variables);
    void client_animation0(Client_Menu_Variables* variables,bool mode);
    void client_unpack_vectors(Client_Menu_Variables* variables);
    void client_pause_frame_operations(Client_Menu_Variables* variables);

    void do_prepared_textboxes(SDL_Event* event,Client_Menu_Variables* variables);

    void* THREAD_send_data_to_server_and_receive_captured_screen_to_window2_buffor(void* data);
    void THREAD_BACKGROUND_connect_to_the_server(THREAD_client_menu_struct_variables* variables);
    bool THREAD_BACKGROUND_receive_operation_codes(THREAD_client_menu_struct_variables* variables);
    bool THREAD_BACKGROUND_unpack_vector_thread_send_receive(THREAD_client_menu_struct_variables* variables);
    bool THREAD_BACKGROUND_send(THREAD_client_menu_struct_variables* variables,uint8_t* main_pointer_to_data,uint32_t sizeof_data,uint8_t operation_code);
    bool THREAD_BACKGROUND_receive(THREAD_client_menu_struct_variables* variables,uint8_t* main_pointer_to_data,uint32_t sizeof_data,uint8_t operation_code);

    void reset_winsock_operation_variables(Client_Menu_Variables* variables);

    //client_tools:
    //if color_of_background.a is 255, then OFF background;
    void save_logs_to_file_and_create_texture(Client_Menu_Variables* variables,const char* what_save_to_file,const char* logs_string_text,SDL_Color color_of_text,SDL_Color color_of_background);
    void reset_window0_and_window1_to_state0_or_1_or_2_or_3(Client_Menu_Variables* variables,uint8_t state0_or_1_or_2_or_3);
    void force_update_textboes(Client_Menu_Variables* variables);

public:
    Client_Menu(Global_Variables* initialized_global_variables)
    {
        this->global_variables = initialized_global_variables;
    }

//main_functions:
    uint8_t client_menu_run();

    ~Client_Menu()
    {

    }
};
//===============================================================================================================================================

#endif
