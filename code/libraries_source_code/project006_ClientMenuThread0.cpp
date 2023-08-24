#include "../libraries/project006_main_program_headers0.h"

//CLIENT_THREAD_FUNCTIONS

//void* Client_Menu::THREAD_capture_screen_to_window2_and_send_data_to_client(void* data)

void* Client_Menu::THREAD_send_data_to_server_and_receive_captured_screen_to_window2_buffor(void* data)
{
    THREAD_client_menu_struct_variables* variables = (THREAD_client_menu_struct_variables*)data;
    this->reset_winsock_operation_variables(variables->THREAD_variables);
    for(;;)
    {
        if(variables->THREAD_variables->destroy_thread==1)
        {
            variables->THREAD_variables->destroy_thread = 0;
            pthread_exit(NULL);
            return NULL;
        }

        //connect to the server if not connected;
        if(variables->THREAD_variables->window0_state==1&&variables->THREAD_variables->client_structure.connected_with_the_server==0) this->THREAD_BACKGROUND_connect_to_the_server(variables);
        else if(variables->THREAD_variables->window0_state!=0)
        {
            if(this->THREAD_BACKGROUND_receive_operation_codes(variables)==1) continue; //if there is some error then window0 is at the state "0" and so continue loop;
            if(this->THREAD_BACKGROUND_unpack_vector_thread_send_receive(variables)==1) continue;
        }
        else SDL_Delay(1);



       // variables->THREAD_variables->active_thread = 0;
    }

    return NULL;
}

void Client_Menu::THREAD_BACKGROUND_connect_to_the_server(THREAD_client_menu_struct_variables* variables)
{
    static int error;
    this->reset_winsock_operation_variables(variables->THREAD_variables);
    for(;;)
    {
        error = variables->THREAD_variables->client.try_to_connect(&variables->THREAD_variables->client_structure);
        if(error==0) //connected with the server;
        {
            #ifdef MAIN_PROGRAM0_DEBUG
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"connected with the server\n",0,0});
            #endif
            this->reset_winsock_operation_variables(variables->THREAD_variables);
            variables->THREAD_variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){0});
            break;
        }
        else if(error!=-1||variables->THREAD_variables->client_is_trying_to_disconnect==1) //error or button "disconnect" has been pressed
        {
            variables->THREAD_variables->window0_state = 0; //if main program doesn't catch up;
            if(variables->THREAD_variables->client_is_trying_to_disconnect==1) //if "disconnect" button has been pressed;
            {
                variables->THREAD_variables->client.close_client(&variables->THREAD_variables->client_structure);
                this->reset_winsock_operation_variables(variables->THREAD_variables);
                break;
            }
            variables->THREAD_variables->client.close_client(&variables->THREAD_variables->client_structure);

            #ifdef MAIN_PROGRAM0_DEBUG
            char* debug_buffor = (char*)malloc(128);
            sprintf(debug_buffor,"ERROR: trying to connect to the server failed; winsock error: %d\n\n",error);
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
            #endif
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": trying to connect to the server failed:\n",(char*)"trying to connect to the server failed:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
            char* buffor0 = (char*)malloc(64);
            sprintf(buffor0,"    winsock error: %d;",error);
            char* buffor1 = (char*)malloc(64);
            sprintf(buffor1,":    winsock error: %d;\n",error);
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){255,0,0,0},{0,0,0,255},1});
            variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({0});
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client has been destroyed;\n",(char*)"client has been destroyed;",(SDL_Color){168,0,0,0},{0,0,0,255},0});
            this->reset_winsock_operation_variables(variables->THREAD_variables);
            break;
        }
        else if(SDL_GetTicks()-variables->THREAD_variables->timeout0>=variables->THREAD_global_variables->inactive_timeout_in_ms) //if timeout reached;
        {
            #ifdef MAIN_PROGRAM0_DEBUG
            char* debug_buffor = (char*)malloc(184);
            sprintf(debug_buffor,"    trying to connect failed: inactivity session timeout reached his limit: %zdms\n",variables->THREAD_global_variables->inactive_timeout_in_ms);
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
            #endif
            variables->THREAD_variables->window0_state = 0; //if main program doesn't catch up;
            variables->THREAD_variables->client.close_client(&variables->THREAD_variables->client_structure);

            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": trying to connect to the server failed:\n",(char*)"trying to connect to the server failed:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)":    timeout reached;\n",(char*)"    timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client has been destroyed;\n",(char*)"client has been destroyed;",(SDL_Color){168,0,0,0},{0,0,0,255},0});
            variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({0});
            this->reset_winsock_operation_variables(variables->THREAD_variables);
            break;
        }
        SDL_Delay(1);
    }
    return;
}

bool Client_Menu::THREAD_BACKGROUND_receive_operation_codes(THREAD_client_menu_struct_variables* variables)
{
    static int32_t error;
    static uint8_t code_buffor;
    for(;;)
    {
        error = variables->THREAD_variables->client.recv_from_server(&code_buffor,1,&variables->THREAD_variables->client_structure);
        if(error==1) //if data has been received
        {
            if(variables->THREAD_variables->how_much_fps_pass_without_red_diode>=1&&code_buffor!=15) //code_buffor == 15 means frame of screen;
            {
                variables->THREAD_variables->diode_red_counter = 1;
            }
            #ifdef MAIN_PROGRAM0_DEBUG
            char* debug_buffor = (char*)malloc(128);
            sprintf(debug_buffor,"received operation code from the server: %zd\n",code_buffor);
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
            #endif
            switch(code_buffor)
            {
                case 1: // accept/reject ScreenShare connection request from the client
                    {
                        variables->THREAD_variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){6});
                        return 0;
                    }
                break;

                case 2: //message sended from the server;
                    {
                        variables->THREAD_variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){7});
                        return 0;
                    }
                break;

                case 3: //received from server 003 (received new value of fps_max from the server)
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": received request from the server:\n",(char*)"received request from the server:",(SDL_Color){255,255,255,0},(SDL_Color){168,168,0,0}});
                        variables->THREAD_variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){8});
                        return 0;
                    }
                break;

                case 4: //received from server 004 (received new value of quality_max from the server)
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": received request from the server:\n",(char*)"received request from the server:",(SDL_Color){255,255,255,0},(SDL_Color){168,168,0,0}});
                        variables->THREAD_variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){9});
                        return 0;
                    }
                break;

                case 5: //received from server 005 (received new value of screen_width from the server)
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": received request from the server:\n",(char*)"received request from the server:",(SDL_Color){255,255,255,0},(SDL_Color){168,168,0,0}});
                        variables->THREAD_variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){10});
                        return 0;
                    }
                break;

                case 6: //received from server 006 (received new value of screen_height from the server)
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": received request from the server:\n",(char*)"received request from the server:",(SDL_Color){255,255,255,0},(SDL_Color){168,168,0,0}});
                        variables->THREAD_variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){11});
                        return 0;
                    }
                break;

                case 7: //received from server 007 (received new value of hash_activate from the server)
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": received request from the server:\n",(char*)"received request from the server:",(SDL_Color){255,255,255,0},(SDL_Color){168,168,0,0}});
                        variables->THREAD_variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){12});
                        return 0;
                    }
                break;

                case 8: //received from server 008 (received information about changing hash from the server)
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": received information from the server:\n",(char*)"received information from the server:",(SDL_Color){255,255,255,0},(SDL_Color){168,168,0,0}});
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": server has been changed the hash;\n",(char*)"server has been changed the hash;",(SDL_Color){0,0,0,0},{0,0,0,255},0});
                        //variables->THREAD_variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){13});
                        continue;
                    }
                break;

                case 9: //received from server 009 (received pause/unpause ScreenSharing from the server)
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": received information from the server:\n",(char*)"received information from the server:",(SDL_Color){255,255,255,0},(SDL_Color){168,168,0,0}});
                        variables->THREAD_variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){14});
                        return 0;
                    }
                break;

                case 10: //received from server 010 (received frame of screen from the server)
                    {
                        variables->THREAD_variables->run_now_frame15_operation = 1;
                        //variables->THREAD_variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){15});
                        return 0;
                    }
                break;

                case 11: //received from server 011 (received new value of max_shared_loss from the server)
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": received request from the server:\n",(char*)"received request from the server:",(SDL_Color){255,255,255,0},(SDL_Color){168,168,0,0}});
                        variables->THREAD_variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){16});
                        return 0;
                    }
                break;

                case 100: //received from server 100 (received refresh signal from the server)
                    {
                        #ifdef MAIN_PROGRAM0_DEBUG
                        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"received refresh signal\n",0,0});
                        #endif
                        variables->THREAD_variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){17});
                        return 0;
                    }
                break;

                case 128: //received from server 128 (received inactivity timeout reached from the server)
                    {
                        variables->THREAD_variables->client.close_client(&variables->THREAD_variables->client_structure);
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": received information from the server:\n",(char*)"received information from the server:",(SDL_Color){255,255,255,0},(SDL_Color){168,168,0,0}});
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": inactivity timeout has been reached;\n",(char*)"inactivity timeout has been reached;",(SDL_Color){0,0,0,0},{0,0,0,255},0});
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": server closed connection with you;\n",(char*)"server closed connection with you;",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client has been destroyed;\n",(char*)"client has been destroyed;",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                        variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({0});
                        this->reset_winsock_operation_variables(variables->THREAD_variables);
                        variables->THREAD_variables->window0_state = 0; //if main program doesn't catch up;
                        //variables->THREAD_variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){18});
                        return 1;
                    }
                break;

                case 129: //received from server 129 (received close connection with the client from the server)
                    {
                        variables->THREAD_variables->client.close_client(&variables->THREAD_variables->client_structure);
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": received information from the server:\n",(char*)"received information from the server:",(SDL_Color){255,255,255,0},(SDL_Color){168,168,0,0}});
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": server closed connection with you;\n",(char*)"server closed connection with you;",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client has been destroyed;\n",(char*)"client has been destroyed;",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                        variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({0});
                        this->reset_winsock_operation_variables(variables->THREAD_variables);
                        variables->THREAD_variables->window0_state = 0; //if main program doesn't catch up;
                        //variables->THREAD_variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){19});
                        return 1;
                    }
                break;

                case 130: //received from server 130 (received server has been shut down from the server)
                    {
                        variables->THREAD_variables->client.close_client(&variables->THREAD_variables->client_structure);
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": received information from the server:\n",(char*)"received information from the server:",(SDL_Color){255,255,255,0},(SDL_Color){168,168,0,0}});
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": server has been shut down;\n",(char*)"server has been shut down;",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client has been destroyed;\n",(char*)"client has been destroyed;",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                        variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({0});
                        this->reset_winsock_operation_variables(variables->THREAD_variables);
                        variables->THREAD_variables->window0_state = 0; //if main program doesn't catch up;
                        //variables->THREAD_variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){20});
                        return 1;
                    }
                break;

                default:
                    {
                        variables->THREAD_variables->client.close_client(&variables->THREAD_variables->client_structure);
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": unknown code received from the server:\n",(char*)"unknown code received from the server:",(SDL_Color){0,0,0,0},(SDL_Color){255,255,255,0}});
                        char* buffor0 = (char*)malloc(64);
                        sprintf(buffor0,"    code: %zd;",code_buffor);
                        char* buffor1 = (char*)malloc(64);
                        sprintf(buffor1,":    code: %zd;\n",code_buffor);
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){255,0,0,0},{0,0,0,255},1});
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client has been destroyed;\n",(char*)"client has been destroyed;",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                        variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({0});
                        this->reset_winsock_operation_variables(variables->THREAD_variables);
                        variables->THREAD_variables->window0_state = 0; //if main program doesn't catch up;
                        return 1;
                    }
                break;
            }
        }
        else if(WSAGetLastError()!=WSAEWOULDBLOCK||variables->THREAD_variables->client_is_trying_to_disconnect==1) //if there is some error or client pressed "disconnect" button;
        {
            error = WSAGetLastError();
            variables->THREAD_variables->window0_state = 0; //if main program doesn't catch up;
            if(variables->THREAD_variables->client_is_trying_to_disconnect==1) //if "disconnect" button has been pressed;
            {
                uint8_t disconnect_buffor = 5; //disconnect code;
                disconnect_buffor = variables->THREAD_variables->client.send_to_server_force(&disconnect_buffor,1,50,1,&variables->THREAD_variables->client_structure);
                #ifdef MAIN_PROGRAM0_DEBUG
                if(disconnect_buffor==1) variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"5 signal has been sended (disconnect from the server);\n",0,0});
                else variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"failed to send disconned signal;\n",0,0});
                #endif
                variables->THREAD_variables->client.close_client(&variables->THREAD_variables->client_structure);
                this->reset_winsock_operation_variables(variables->THREAD_variables);
                return 1;
            }
            variables->THREAD_variables->client.close_client(&variables->THREAD_variables->client_structure);

            #ifdef MAIN_PROGRAM0_DEBUG
            char* debug_buffor = (char*)malloc(128);
            sprintf(debug_buffor,"ERROR: connection has been lost: %d\n\n",error);
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
            #endif
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": connection has been lost:\n",(char*)"connection has been lost:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
            char* buffor0 = (char*)malloc(64);
            sprintf(buffor0,"    winsock error: %d;",error);
            char* buffor1 = (char*)malloc(64);
            sprintf(buffor1,":    winsock error: %d;\n",error);
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){255,0,0,0},{0,0,0,255},1});
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client has been destroyed;\n",(char*)"client has been destroyed;",(SDL_Color){168,0,0,0},{0,0,0,255},0});
            variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({0});
            this->reset_winsock_operation_variables(variables->THREAD_variables);
            return 1;
        }
        else if(variables->THREAD_variables->thread_vector_send_receive->size()!=0&&variables->THREAD_variables->screen_sharing_in_process==0) break; //if there is operation waiting to do;
        else SDL_Delay(1);
    }
    return 0;
}

bool Client_Menu::THREAD_BACKGROUND_unpack_vector_thread_send_receive(THREAD_client_menu_struct_variables* variables)
{
    static uint8_t* data_buffor;

    if(variables->THREAD_variables->run_now_frame15_operation==1)  //to check if is good;
    {
        #ifdef MAIN_PROGRAM0_DEBUG
        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"receiving frame of screen started:\n",0,0});
        #endif
        data_buffor = (uint8_t*)malloc(10);
        if(this->THREAD_BACKGROUND_receive(variables,data_buffor,10,15)==1)
        {
            free(data_buffor);
            return 1;
        }
        while(variables->THREAD_variables->operation_code_on_main_frame_data!=0) SDL_Delay(1); //thread lock;
        static uint16_t width_from_the_frame;
        static uint16_t height_from_the_frame;
        static uint8_t quality_from_the_frame;
        static uint8_t hash_from_the_frame;
        width_from_the_frame = *(uint16_t*)((uint8_t*)data_buffor+4);
        height_from_the_frame = *(uint16_t*)((uint8_t*)data_buffor+6);
        quality_from_the_frame = *(uint8_t*)((uint8_t*)data_buffor+8);
        hash_from_the_frame = *(uint8_t*)((uint8_t*)data_buffor+9);
        #ifdef MAIN_PROGRAM0_DEBUG
        char* debug_buffor = (char*)malloc(512);
        sprintf(debug_buffor,"    received width of the frame: %zd\n    received height of the frame: %zd\n    received quality of the frame: %zd\n    received hash of actual frame: %zd\n",
                width_from_the_frame,height_from_the_frame,quality_from_the_frame,hash_from_the_frame);
        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
        #endif
        variables->THREAD_variables->width_of_actual_frame = width_from_the_frame;   //if u change these variables in main program then there is protection
        variables->THREAD_variables->height_of_actual_frame = height_from_the_frame; //
        variables->THREAD_variables->quality_of_actual_frame = quality_from_the_frame;//
        variables->THREAD_variables->pitch_of_actual_frame = (variables->THREAD_variables->width_of_actual_frame*24+7)/8;
        variables->THREAD_variables->pitch_of_actual_frame = ((variables->THREAD_variables->pitch_of_actual_frame+3)/4)*4;
        variables->THREAD_variables->loss_of_actual_frame = variables->THREAD_variables->safe_requested_loss;
        variables->THREAD_variables->size_of_main_frame_data = *(uint32_t*)((uint8_t*)data_buffor);
        variables->THREAD_variables->main_frame_data = (uint8_t*)malloc(variables->THREAD_variables->size_of_main_frame_data);

        if(this->THREAD_BACKGROUND_receive(variables,variables->THREAD_variables->main_frame_data,variables->THREAD_variables->size_of_main_frame_data,15)==1)
        {
            free(data_buffor);
            return 1;
        }

        #ifdef MAIN_PROGRAM0_DEBUG
        debug_buffor = (char*)malloc(128);
        sprintf(debug_buffor,"    received image size: %zd\n",variables->THREAD_variables->size_of_main_frame_data);
        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
        #endif

        //unhash here image if needed;
        if(hash_from_the_frame==1)
        {
            uint32_t hash_seed_counter = 0;
            uint8_t* hash_seed = (uint8_t*)malloc(257);
            variables->THREAD_global_variables->universal_tool0->memset_custom<uint8_t>(hash_seed,0,257);
            strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash0); strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash1);
            strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash2); strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash3);
            hash_seed_counter = variables->THREAD_global_variables->universal_tool0->count_string_chars((const char*)hash_seed);
            variables->THREAD_global_variables->universal_tool0->unhash0_32bit(variables->THREAD_variables->main_frame_data,hash_seed,variables->THREAD_variables->size_of_main_frame_data,hash_seed_counter);
            free(hash_seed);

        }

        //here unlock option to change data into image in main_program;
        variables->THREAD_variables->operation_code_on_main_frame_data = 4; //4 means frame screen;

        *(uint32_t*)((uint8_t*)data_buffor) = variables->THREAD_variables->size_of_main_frame_data+5;
        if(variables->THREAD_variables->thread_vector_send_receive[0].size()!=0)
        {
            data_buffor[4] = 1;
            if(this->THREAD_BACKGROUND_send(variables,data_buffor,5,15)==1)
            {
                free(data_buffor);
                return 1;
            }

            free(data_buffor);
            variables->THREAD_variables->run_now_frame15_operation = 0;
        }
        else
        {
            data_buffor[4] = 0;
            if(this->THREAD_BACKGROUND_send(variables,data_buffor,5,15)==1)
            {
                free(data_buffor);
                return 1;
            }

            free(data_buffor);
            variables->THREAD_variables->run_now_frame15_operation = 0;
             //getch();
            return 0;
        }

    }

    switch(variables->THREAD_variables->thread_vector_send_receive[0][0].operation_code)
    {
        case 0: //sended from client to server 001 (connect to the server)
            {
                data_buffor = (uint8_t*)malloc(140);
                data_buffor[0] = 1;
                *(uint32_t*)((uint8_t*)data_buffor+1) = variables->THREAD_variables->public_ip_int;
                memcpy(data_buffor+5,variables->THREAD_variables->password,65);
                *(uint16_t*)((uint8_t*)data_buffor+70) = variables->THREAD_variables->requested_fps_int;
                data_buffor[72] = variables->THREAD_variables->requested_quality_int;
                data_buffor[73] = variables->THREAD_variables->requested_loss_int;
                memcpy(data_buffor+74,variables->THREAD_variables->message0,33);
                memcpy(data_buffor+107,variables->THREAD_variables->message1,33);

                if(this->THREAD_BACKGROUND_send(variables,data_buffor,140,0)==1)
                {
                    free(data_buffor);
                    return 1;
                }
                #ifdef MAIN_PROGRAM0_DEBUG
                char* debug_buffor = (char*)malloc(1024);
                sprintf(debug_buffor,
                       "    sended information to the server:\n"
                       "        public_ip: %s\n"
                       "        requested_quality: %s\n"
                       "        requested_fps: %s\n"
                       "        requested_loss: %zd\n"
                       "        client_message0: %s\n"
                       "        client_message1: %s\n",
                       (const char*)variables->THREAD_variables->public_ip_string,
                       (const char*)variables->THREAD_variables->requested_quality,
                       (const char*)variables->THREAD_variables->requested_fps,
                       variables->THREAD_variables->requested_loss_int,
                       (const char*)variables->THREAD_variables->message0,
                       (const char*)variables->THREAD_variables->message1);
                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                #endif

                char* buffor0;
                char* buffor1;
                SDL_Color background;
                background.r = 0; background.g = 0; background.b = 168; background.a = 0;
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": sended information to the server:\n",(char*)"sended information to the server:",(SDL_Color){255,255,255,0},background,0});
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                sprintf(buffor0,"    client_public_ip: %s;",(const char*)variables->THREAD_variables->public_ip_string);
                sprintf(buffor1,":    client_public_ip: %s;\n",(const char*)variables->THREAD_variables->public_ip_string);
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                sprintf(buffor0,"    requested_fps: %s;",variables->THREAD_variables->requested_fps);
                sprintf(buffor1,":    requested_fps: %s;\n",variables->THREAD_variables->requested_fps);
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                sprintf(buffor0,"    requested_quality: %s;",variables->THREAD_variables->requested_quality);
                sprintf(buffor1,":    requested_quality: %s;\n",variables->THREAD_variables->requested_quality);
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                if(variables->THREAD_variables->requested_loss_int==0)
                {
                    sprintf(buffor0,"    requested_loss: disabled;");
                    sprintf(buffor1,":    requested_loss: disabled;\n");
                }
                else
                {
                    sprintf(buffor0,"    requested_loss: %s;",variables->THREAD_variables->requested_loss);
                    sprintf(buffor1,":    requested_loss: %s;\n",variables->THREAD_variables->requested_loss);
                }
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                if(variables->THREAD_variables->message0[0]!='\0'||variables->THREAD_variables->message1[0]!='\0')
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": your starting message to the server:\n",(char*)"your starting message to the server:",(SDL_Color){255,255,255,0},background,0});
                    if(variables->THREAD_variables->message0[0]!='\0')
                    {
                        buffor0 = (char*)malloc(64);
                        buffor1 = (char*)malloc(64);
                        sprintf(buffor0,"    %s",(const char*)variables->THREAD_variables->message0);
                        sprintf(buffor1,":    %s\n",(const char*)variables->THREAD_variables->message0);
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    }
                    if(variables->THREAD_variables->message1[0]!='\0')
                    {
                        buffor0 = (char*)malloc(64);
                        buffor1 = (char*)malloc(64);
                        sprintf(buffor0,"    %s",(const char*)variables->THREAD_variables->message1);
                        sprintf(buffor1,":    %s\n",(const char*)variables->THREAD_variables->message1);
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    }
                }

                if(this->THREAD_BACKGROUND_receive(variables,data_buffor,1,0)==1)
                {
                    free(data_buffor);
                    return 1;
                }

                if(data_buffor[0]!=1) //incorrect password;
                {
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"you have been failed to connect to the server; your password is incorrect\n",0,0});
                    #endif
                    variables->THREAD_variables->window0_state = 0; //if main program doesn't catch up;
                    variables->THREAD_variables->client.close_client(&variables->THREAD_variables->client_structure);

                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": connection to the server failed:\n",(char*)"connection to the server failed:",(SDL_Color){255,255,255,0},(SDL_Color){168,0,0,0},0});
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)":    your password is incorrect;\n",(char*)"    your password is incorrect;",(SDL_Color){168,0,0,0},(SDL_Color){0,0,0,255},0});
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client has been destroyed;\n",(char*)"client has been destroyed;",(SDL_Color){168,0,0,0},(SDL_Color){0,0,0,255},0});
                    variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({0});
                    this->reset_winsock_operation_variables(variables->THREAD_variables);
                    free(data_buffor);
                    return 1;
                }
                if(this->THREAD_BACKGROUND_receive(variables,data_buffor+1,76,0)==1)
                {
                    free(data_buffor);
                    return 1;
                }

                variables->THREAD_variables->max_shared_quality_int = data_buffor[1];
                variables->THREAD_variables->max_shared_fps_int = *(uint16_t*)((uint8_t*)data_buffor+2);
                variables->THREAD_variables->max_shared_loss_int = data_buffor[4];
                variables->THREAD_variables->screen_width_share_int = *(uint16_t*)((uint8_t*)data_buffor+5);
                variables->THREAD_variables->screen_height_share_int = *(uint16_t*)((uint8_t*)data_buffor+7);
                variables->THREAD_variables->server_password_required = data_buffor[9];
                variables->THREAD_variables->server_hash_activate = data_buffor[10];
                memcpy(variables->THREAD_variables->message0_server,data_buffor+11,33);
                memcpy(variables->THREAD_variables->message1_server,data_buffor+44,33);

                #ifdef MAIN_PROGRAM0_DEBUG
                debug_buffor = (char*)malloc(1024);
                sprintf(debug_buffor,
                        "    received information from the server:\n"
                       "        server_ip (string): %s\n"
                       "        server_port (string): %s\n"
                       "        max_shared_quality: %zd\n"
                       "        max_shared_fps: %zd\n"
                       "        max_shared_loss: %zd\n"
                       "        screen_width_share: %zd\n"
                       "        screen_height_share: %zd\n"
                       "        password_required: %zd\n"
                       "        hash_activate: %zd\n"
                       "        message0: %s\n"
                       "        message1: %s\n",
                       variables->THREAD_variables->server_ip,
                       variables->THREAD_variables->server_port,
                       variables->THREAD_variables->max_shared_quality_int,
                       variables->THREAD_variables->max_shared_fps_int,
                       variables->THREAD_variables->max_shared_loss_int,
                       variables->THREAD_variables->screen_width_share_int,
                       variables->THREAD_variables->screen_height_share_int,
                       variables->THREAD_variables->server_password_required,
                       variables->THREAD_variables->server_hash_activate,
                       variables->THREAD_variables->message0_server,
                       variables->THREAD_variables->message1_server);
                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                #endif


                background.r = 168; background.g = 168; background.b = 0;
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": received information from the server:\n",(char*)"received information from the server:",(SDL_Color){255,255,255,0},background,0});
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                sprintf(buffor0,"    max_shared_fps: %zd;",variables->THREAD_variables->max_shared_fps_int);
                sprintf(buffor1,":    max_shared_fps: %zd;\n",variables->THREAD_variables->max_shared_fps_int);
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                sprintf(buffor0,"    max_shared_quality: %zd;",variables->THREAD_variables->max_shared_quality_int);
                sprintf(buffor1,":    max_shared_quality: %zd;\n",variables->THREAD_variables->max_shared_quality_int);
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                sprintf(buffor0,"    max_shared_loss: %zd;",variables->THREAD_variables->max_shared_loss_int);
                sprintf(buffor1,":    max_shared_loss: %zd;\n",variables->THREAD_variables->max_shared_loss_int);
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                sprintf(buffor0,"    screen_width: %zd;",variables->THREAD_variables->screen_width_share_int);
                sprintf(buffor1,":    screen_width: %zd;\n",variables->THREAD_variables->screen_width_share_int);
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                sprintf(buffor0,"    screen_height: %zd;",variables->THREAD_variables->screen_height_share_int);
                sprintf(buffor1,":    screen_height: %zd;\n",variables->THREAD_variables->screen_height_share_int);
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                if(variables->THREAD_variables->server_password_required==1)
                {
                    sprintf(buffor0,"    password_required: yes;");
                    sprintf(buffor1,":    password_required: yes;\n");
                }
                else
                {
                    sprintf(buffor0,"    password_required: no;");
                    sprintf(buffor1,":    password_required: no;\n");
                }
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                if(variables->THREAD_variables->server_hash_activate==1)
                {
                    sprintf(buffor0,"    hash_activated: yes;");
                    sprintf(buffor1,":    hash_activated: yes;\n");
                }
                else
                {
                    sprintf(buffor0,"    hash_activated: no;");
                    sprintf(buffor1,":    hash_activated: no;\n");
                }
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                if(variables->THREAD_variables->message0_server[0]!='\0'||variables->THREAD_variables->message1_server[0]!='\0')
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": starting message from the server:\n",(char*)"starting message from the server:",(SDL_Color){255,255,255,0},background,0});
                    if(variables->THREAD_variables->message0_server[0]!='\0')
                    {
                        buffor0 = (char*)malloc(64);
                        buffor1 = (char*)malloc(64);
                        sprintf(buffor0,"    %s",(const char*)variables->THREAD_variables->message0_server);
                        sprintf(buffor1,":    %s\n",(const char*)variables->THREAD_variables->message0_server);
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    }
                    if(variables->THREAD_variables->message1_server[0]!='\0')
                    {
                        buffor0 = (char*)malloc(64);
                        buffor1 = (char*)malloc(64);
                        sprintf(buffor0,"    %s",(const char*)variables->THREAD_variables->message1_server);
                        sprintf(buffor1,":    %s\n",(const char*)variables->THREAD_variables->message1_server);
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    }
                }

                //filter data that has been sended to you
                if(variables->THREAD_variables->max_shared_quality_int<variables->THREAD_variables->requested_quality_int)
                {
                    if(variables->THREAD_variables->max_shared_quality_int==0||variables->THREAD_variables->max_shared_quality_int>10)
                    {
                        free(data_buffor);
                        return 1;
                    }
                    variables->THREAD_variables->requested_quality_int = variables->THREAD_variables->max_shared_quality_int;
                    variables->THREAD_global_variables->universal_tool0->uint32_to_string(variables->THREAD_variables->requested_quality_int,(char*)variables->THREAD_variables->requested_quality);
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"requested_quality changed to: %s;",variables->THREAD_variables->requested_quality);
                    sprintf(buffor1,": requested_quality changed to: %s;\n",variables->THREAD_variables->requested_quality);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                    int size_of_textbox_data = 2;
                    int counter = 0;
                    for(; variables->THREAD_variables->textbox_data[3][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->THREAD_variables->textbox_data[3][counter] = '\0';

                    variables->THREAD_variables->requested_quality[size_of_textbox_data] = '\r'; variables->THREAD_variables->requested_quality[size_of_textbox_data+1] = '\n';
                    variables->THREAD_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->THREAD_variables->requested_quality,size_of_textbox_data+2,"\nrequested quality: ",variables->THREAD_variables->client_base_position_in_config,(3+1)*64);
                    variables->THREAD_variables->requested_quality[size_of_textbox_data] = '\0'; variables->THREAD_variables->requested_quality[size_of_textbox_data+1] = '\0';
                    memcpy(variables->THREAD_variables->textbox_data[3],variables->THREAD_variables->requested_quality,2);

                }
                if(variables->THREAD_variables->max_shared_fps_int<variables->THREAD_variables->requested_fps_int)
                {
                    if(variables->THREAD_variables->max_shared_fps_int==0||variables->THREAD_variables->max_shared_fps_int>480)
                    {
                        free(data_buffor);
                        return 1;
                    }

                    variables->THREAD_variables->requested_fps_int = variables->THREAD_variables->max_shared_fps_int;
                    variables->THREAD_global_variables->universal_tool0->uint32_to_string(variables->THREAD_variables->requested_fps_int,(char*)variables->THREAD_variables->requested_fps);
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"requested_fps changed to: %s;",variables->THREAD_variables->requested_fps);
                    sprintf(buffor1,": requested_fps changed to: %s;\n",variables->THREAD_variables->requested_fps);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                    int size_of_textbox_data = 3;
                    int counter = 0;
                    for(; variables->THREAD_variables->textbox_data[2][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->THREAD_variables->textbox_data[2][counter] = '\0';

                    variables->THREAD_variables->requested_fps[size_of_textbox_data] = '\r'; variables->THREAD_variables->requested_fps[size_of_textbox_data+1] = '\n';
                    variables->THREAD_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->THREAD_variables->requested_fps,size_of_textbox_data+2,"\nrequested fps: ",variables->THREAD_variables->client_base_position_in_config,(2+1)*64);
                    variables->THREAD_variables->requested_fps[size_of_textbox_data] = '\0'; variables->THREAD_variables->requested_fps[size_of_textbox_data+1] = '\0';
                    memcpy(variables->THREAD_variables->textbox_data[2],variables->THREAD_variables->requested_fps,3);

                    if(variables->THREAD_variables->requested_fps_int>=variables->THREAD_global_variables->main_menu_fps) {variables->THREAD_global_variables->sdl_universal_tool0->change_fps(variables->THREAD_variables->requested_fps_int);}
                    else {variables->THREAD_global_variables->sdl_universal_tool0->change_fps(variables->THREAD_global_variables->main_menu_fps);}
                }
                if(variables->THREAD_variables->max_shared_loss_int<variables->THREAD_variables->requested_loss_int)
                {
                    if(variables->THREAD_variables->max_shared_loss_int>100)
                    {
                        free(data_buffor);
                        return 1;
                    }
                    variables->THREAD_variables->requested_loss_int = variables->THREAD_variables->max_shared_loss_int;
                    variables->THREAD_global_variables->universal_tool0->uint32_to_string(variables->THREAD_variables->requested_loss_int,(char*)variables->THREAD_variables->requested_loss);
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"requested_loss changed to: %s;",variables->THREAD_variables->requested_loss);
                    sprintf(buffor1,": requested_loss changed to: %s;\n",variables->THREAD_variables->requested_loss);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                    int size_of_textbox_data = 3;
                    int counter = 0;
                    for(; variables->THREAD_variables->textbox_data[4][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->THREAD_variables->textbox_data[4][counter] = '\0';

                    variables->THREAD_variables->requested_loss[size_of_textbox_data] = '\r'; variables->THREAD_variables->requested_loss[size_of_textbox_data+1] = '\n';
                    variables->THREAD_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->THREAD_variables->requested_loss,size_of_textbox_data+2,"\nrequested loss: ",variables->THREAD_variables->client_base_position_in_config,(4+1)*64);
                    variables->THREAD_variables->requested_loss[size_of_textbox_data] = '\0'; variables->THREAD_variables->requested_loss[size_of_textbox_data+1] = '\0';
                    memcpy(variables->THREAD_variables->textbox_data[4],variables->THREAD_variables->requested_loss,3);
                }
                if(this->shrink_string_to_fit_the_size(variables->THREAD_global_variables->main_ttf,(char*)variables->THREAD_variables->message0_server,210)!=0)
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": message0 was shrinked 'cause of its size;\n",(char*)"message0 was shrinked 'cause of its size;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                }
                if(this->shrink_string_to_fit_the_size(variables->THREAD_global_variables->main_ttf,(char*)variables->THREAD_variables->message1_server,210)!=0)
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": message1 was shrinked 'cause of its size;\n",(char*)"message1 was shrinked 'cause of its size;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                }

                background.r = 255; background.g = 255; background.b = 255;
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": waiting for accept/reject the connection;\n",(char*)"waiting for accept/reject the connection;",(SDL_Color){0,0,0,0},background,0});
                variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({2});
                free(data_buffor);
            }
        break;

        case 1: //sended from client to server 002 (send message to the server)
            {
                data_buffor = (uint8_t*)malloc(67);
                data_buffor[0] = 2;
                memcpy(data_buffor+1,variables->THREAD_variables->message0,33);
                memcpy(data_buffor+34,variables->THREAD_variables->message1,33);

                if(this->THREAD_BACKGROUND_send(variables,data_buffor,67,1)==1)
                {
                    free(data_buffor);
                    return 1;
                }

                #ifdef MAIN_PROGRAM0_DEBUG
                char* debug_buffor = (char*)malloc(256);
                sprintf(debug_buffor,"    sended message to the server:\n"
                        "        %s\n"
                        "        %s\n",
                (const char*)data_buffor+1,
                (const char*)data_buffor+34);
                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                #endif

                SDL_Color background;
                background.r = 0; background.g = 0; background.b = 168; background.a = 0;
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": sended message to the server:\n",(char*)"sended message to the server:",(SDL_Color){255,255,255,0},background,0});
                if(data_buffor[1]!='\0'||data_buffor[34]!='\0')
                {
                    char* buffor0;
                    char* buffor1;
                    if(data_buffor[1]!='\0')
                    {
                        buffor0 = (char*)malloc(64);
                        buffor1 = (char*)malloc(64);
                        sprintf(buffor0,"    %s",(const char*)data_buffor+1);
                        sprintf(buffor1,":    %s\n",(const char*)data_buffor+1);
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    }
                    if(data_buffor[34]!='\0')
                    {
                        buffor0 = (char*)malloc(64);
                        buffor1 = (char*)malloc(64);
                        sprintf(buffor0,"    %s",(const char*)data_buffor+34);
                        sprintf(buffor1,":    %s\n",(const char*)data_buffor+34);
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    }
                }

                free(data_buffor);
            }
        break;

        case 2: //sended from client to server 003 (send change of requested_fps)
            {
                data_buffor = (uint8_t*)malloc(3);
                data_buffor[0] = 3;
                *(uint16_t*)((uint8_t*)data_buffor+1) = variables->THREAD_variables->requested_fps_int;
                if(this->THREAD_BACKGROUND_send(variables,data_buffor,3,2)==1)
                {
                    free(data_buffor);
                    return 1;
                }
                if(this->THREAD_BACKGROUND_receive(variables,data_buffor,1,2)==1)
                {
                    free(data_buffor);
                    return 1;
                }
                if(data_buffor[0]!=0)
                {
                    while(variables->THREAD_variables->operation_code_on_main_frame_data!=0) SDL_Delay(1); //thread lock;
                    if(data_buffor[0]==1)
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_fps was too big;\n",(char*)"requested_fps was too big;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                    }
                    else
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_fps was too small;\n",(char*)"requested_fps was too small;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                    }

                    char* buffor0,*buffor1;
                    variables->THREAD_variables->requested_fps_int = variables->THREAD_variables->max_shared_fps_int;
                    variables->THREAD_global_variables->universal_tool0->uint32_to_string(variables->THREAD_variables->requested_fps_int,(char*)variables->THREAD_variables->requested_fps);
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"requested_fps changed to: %s;",variables->THREAD_variables->requested_fps);
                    sprintf(buffor1,": requested_fps changed to: %s;\n",variables->THREAD_variables->requested_fps);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                    int size_of_textbox_data = 3;
                    int counter = 0;
                    for(; variables->THREAD_variables->textbox_data[2][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->THREAD_variables->textbox_data[2][counter] = '\0';

                    variables->THREAD_variables->requested_fps[size_of_textbox_data] = '\r'; variables->THREAD_variables->requested_fps[size_of_textbox_data+1] = '\n';
                    variables->THREAD_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->THREAD_variables->requested_fps,size_of_textbox_data+2,"\nrequested fps: ",variables->THREAD_variables->client_base_position_in_config,(2+1)*64);
                    variables->THREAD_variables->requested_fps[size_of_textbox_data] = '\0'; variables->THREAD_variables->requested_fps[size_of_textbox_data+1] = '\0';
                    memcpy(variables->THREAD_variables->textbox_data[2],variables->THREAD_variables->requested_fps,3);

                    if(variables->THREAD_variables->requested_fps_int>=variables->THREAD_global_variables->main_menu_fps) {variables->THREAD_global_variables->sdl_universal_tool0->change_fps(variables->THREAD_variables->requested_fps_int);}
                    else {variables->THREAD_global_variables->sdl_universal_tool0->change_fps(variables->THREAD_global_variables->main_menu_fps);}

                    variables->THREAD_variables->textbox_variables[2]->update_textbox();
                }
                else
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": changes sended to the server;\n",(char*)"changes sended to the server;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                }

                free(data_buffor);
            }
        break;

        case 3: //sended from client to server 004 (send change of requested_quality)
            {
                data_buffor = (uint8_t*)malloc(2);
                data_buffor[0] = 4;
                data_buffor[1] = (uint8_t)variables->THREAD_variables->requested_quality_int;
                if(this->THREAD_BACKGROUND_send(variables,data_buffor,2,3)==1)
                {
                    free(data_buffor);
                    return 1;
                }
                if(this->THREAD_BACKGROUND_receive(variables,data_buffor,1,3)==1)
                {
                    free(data_buffor);
                    return 1;
                }
                if(data_buffor[0]!=0)
                {
                    while(variables->THREAD_variables->operation_code_on_main_frame_data!=0) SDL_Delay(1); //thread lock;
                    if(data_buffor[0]==1)
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_quality was too big;\n",(char*)"requested_quality was too big;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                    }
                    else
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_quality was too small;\n",(char*)"requested_quality was too small;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                    }

                    char* buffor0,*buffor1;
                    variables->THREAD_variables->requested_quality_int = variables->THREAD_variables->max_shared_quality_int;
                    variables->THREAD_global_variables->universal_tool0->uint32_to_string(variables->THREAD_variables->requested_quality_int,(char*)variables->THREAD_variables->requested_quality);
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"requested_quality changed to: %s;",variables->THREAD_variables->requested_quality);
                    sprintf(buffor1,": requested_quality changed to: %s;\n",variables->THREAD_variables->requested_quality);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                    int size_of_textbox_data = 2;
                    int counter = 0;
                    for(; variables->THREAD_variables->textbox_data[3][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->THREAD_variables->textbox_data[3][counter] = '\0';

                    variables->THREAD_variables->requested_quality[size_of_textbox_data] = '\r'; variables->THREAD_variables->requested_quality[size_of_textbox_data+1] = '\n';
                    variables->THREAD_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->THREAD_variables->requested_quality,size_of_textbox_data+2,"\nrequested quality: ",variables->THREAD_variables->client_base_position_in_config,(3+1)*64);
                    variables->THREAD_variables->requested_quality[size_of_textbox_data] = '\0'; variables->THREAD_variables->requested_quality[size_of_textbox_data+1] = '\0';
                    memcpy(variables->THREAD_variables->textbox_data[3],variables->THREAD_variables->requested_quality,2);

                    variables->THREAD_variables->textbox_variables[3]->update_textbox();
                }
                else
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": changes sended to the server;\n",(char*)"changes sended to the server;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                }


                free(data_buffor);

            }
        break;

        /*case 4: //sended from client to server 005 (disconnect from the server)
            {

            }
        break;*/

        case 5: //sended from client to server 006 (send change of requested_loss)
            {
                data_buffor = (uint8_t*)malloc(2);
                data_buffor[0] = 6;
                data_buffor[1] = variables->THREAD_variables->requested_loss_int;
                if(this->THREAD_BACKGROUND_send(variables,data_buffor,2,5)==1)
                {
                    free(data_buffor);
                    return 1;
                }
                if(this->THREAD_BACKGROUND_receive(variables,data_buffor,1,5)==1)
                {
                    free(data_buffor);
                    return 1;
                }
                if(data_buffor[0]!=0)
                {
                    while(variables->THREAD_variables->operation_code_on_main_frame_data!=0) SDL_Delay(1); //thread lock;
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_loss was too big;\n",(char*)"requested_loss was too big;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});

                    char* buffor0,*buffor1;
                    variables->THREAD_variables->requested_loss_int = variables->THREAD_variables->max_shared_loss_int;
                    variables->THREAD_global_variables->universal_tool0->uint32_to_string(variables->THREAD_variables->requested_loss_int,(char*)variables->THREAD_variables->requested_loss);
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"requested_loss changed to: %s;",variables->THREAD_variables->requested_loss);
                    sprintf(buffor1,": requested_loss changed to: %s;\n",variables->THREAD_variables->requested_loss);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                    int size_of_textbox_data = 3;
                    int counter = 0;
                    for(; variables->THREAD_variables->textbox_data[4][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->THREAD_variables->textbox_data[4][counter] = '\0';

                    variables->THREAD_variables->requested_loss[size_of_textbox_data] = '\r'; variables->THREAD_variables->requested_loss[size_of_textbox_data+1] = '\n';
                    variables->THREAD_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->THREAD_variables->requested_loss,size_of_textbox_data+2,"\nrequested loss: ",variables->THREAD_variables->client_base_position_in_config,(4+1)*64);
                    variables->THREAD_variables->requested_loss[size_of_textbox_data] = '\0'; variables->THREAD_variables->requested_loss[size_of_textbox_data+1] = '\0';
                    memcpy(variables->THREAD_variables->textbox_data[4],variables->THREAD_variables->requested_loss,3);

                    variables->THREAD_variables->textbox_variables[4]->update_textbox();
                }
                else
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": changes sended to the server;\n",(char*)"changes sended to the server;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                }
                variables->THREAD_variables->safe_requested_loss = variables->THREAD_variables->requested_loss_int;

                free(data_buffor);
            }
        break;

        case 6: //received from server 001 (accept/reject ScreenShare connection request from the client)
            {
                data_buffor = (uint8_t*)malloc(6);
                //char* buffor0,*buffor1;
                if(this->THREAD_BACKGROUND_receive(variables,data_buffor,1,6)==1)
                {
                    free(data_buffor);
                    return 1;
                }
                if(data_buffor[0]==1) //accept
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": server accepted connection;\n",(char*)"server accepted connection;",(SDL_Color){255,255,255,0},{0,168,0,0},0});
                    variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({3});
                    if(this->THREAD_BACKGROUND_receive(variables,data_buffor,6,14)==1)
                    {
                        free(data_buffor);
                        return 1;
                    }
                    uint32_t size_of_pause_image = *(uint32_t*)((uint8_t*)data_buffor+2);
                    variables->THREAD_variables->main_frame_data = (uint8_t*)malloc(size_of_pause_image);
                    variables->THREAD_variables->size_of_main_frame_data = size_of_pause_image;

                    if(this->THREAD_BACKGROUND_receive(variables,variables->THREAD_variables->main_frame_data,size_of_pause_image,14)==1)
                    {
                        free(data_buffor);
                        return 1;
                    }

                    //unhash here image if needed;
                    if(variables->THREAD_variables->server_hash_activate==1)
                    {
                        uint32_t hash_seed_counter = 0;
                        uint8_t* hash_seed = (uint8_t*)malloc(257);
                        variables->THREAD_global_variables->universal_tool0->memset_custom<uint8_t>(hash_seed,0,257);
                        strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash0); strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash1);
                        strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash2); strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash3);
                        hash_seed_counter = variables->THREAD_global_variables->universal_tool0->count_string_chars((const char*)hash_seed);
                        variables->THREAD_global_variables->universal_tool0->unhash0_32bit(variables->THREAD_variables->main_frame_data,hash_seed,size_of_pause_image,hash_seed_counter);
                        free(hash_seed);

                    }

                    //here unlock option to change data into image in main_program;
                    variables->THREAD_variables->operation_code_on_main_frame_data = 1; //1 means pause image (first_enter);

                    *(uint32_t*)((uint8_t*)data_buffor) = size_of_pause_image+6;
                    if(this->THREAD_BACKGROUND_send(variables,data_buffor,4,14)==1)
                    {
                        free(data_buffor);
                        return 1;
                    }

                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": received information from the server:\n",(char*)"received information from the server:",(SDL_Color){255,255,255,0},(SDL_Color){168,168,0,0}});
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": ScreenSharing has been paused by server;\n",(char*)"ScreenSharing has been paused by server;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255}});

                    variables->THREAD_variables->window0_state = 3; //if main program doesn't catch up;
                    variables->THREAD_variables->is_screen_sharing_paused = 1;
                    variables->THREAD_variables->screen_sharing_in_process = 0;
                    variables->THREAD_variables->run_now_frame15_operation = 0;
                    variables->THREAD_variables->safe_requested_loss = variables->THREAD_variables->requested_loss_int;
                }
                else                  //reject
                {
                    variables->THREAD_variables->client.close_client(&variables->THREAD_variables->client_structure);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": server rejected connection;\n",(char*)"server rejected connection;",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client has been destroyed;\n",(char*)"client has been destroyed;",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                    variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({0});
                    this->reset_winsock_operation_variables(variables->THREAD_variables);
                    variables->THREAD_variables->window0_state = 0; //if main program doesn't catch up;
                    return 1;
                }
                free(data_buffor);
            }
        break;

        case 7: //received from server 002 (receive message from the server)
            {
                data_buffor = (uint8_t*)malloc(66);
                char* buffor0,*buffor1;
                if(this->THREAD_BACKGROUND_receive(variables,data_buffor,66,7)==1)
                {
                    free(data_buffor);
                    return 1;
                }
                memcpy(variables->THREAD_variables->message0_server,data_buffor,33);
                memcpy(variables->THREAD_variables->message1_server,data_buffor+33,33);
                #ifdef MAIN_PROGRAM0_DEBUG
                char* debug_buffor = (char*)malloc(256);
                sprintf(debug_buffor,"    received message from the server:\n"
                        "        %s\n"
                        "        %s\n",
                (const char*)data_buffor,
                (const char*)data_buffor+33);
                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                #endif
                SDL_Color background;
                background.r = 168; background.g = 168; background.b = 0; background.a = 0;
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": received message from the server:\n",(char*)"received message from the server:",(SDL_Color){255,255,255,0},background,0});
                if(variables->THREAD_variables->message0_server[0]!='\0'||variables->THREAD_variables->message1_server[0]!='\0')
                {
                    if(variables->THREAD_variables->message0_server[0]!='\0')
                    {
                        buffor0 = (char*)malloc(64);
                        buffor1 = (char*)malloc(64);
                        sprintf(buffor0,"    %s",(const char*)variables->THREAD_variables->message0_server);
                        sprintf(buffor1,":    %s\n",(const char*)variables->THREAD_variables->message0_server);
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    }
                    if(variables->THREAD_variables->message1_server[0]!='\0')
                    {
                        buffor0 = (char*)malloc(64);
                        buffor1 = (char*)malloc(64);
                        sprintf(buffor0,"    %s",(const char*)variables->THREAD_variables->message1_server);
                        sprintf(buffor1,":    %s\n",(const char*)variables->THREAD_variables->message1_server);
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    }
                }

                if(this->shrink_string_to_fit_the_size(variables->THREAD_global_variables->main_ttf,(char*)variables->THREAD_variables->message0_server,210)!=0)
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": message0 was shrinked 'cause of its size;\n",(char*)"message0 was shrinked 'cause of its size;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                }
                if(this->shrink_string_to_fit_the_size(variables->THREAD_global_variables->main_ttf,(char*)variables->THREAD_variables->message1_server,210)!=0)
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": message1 was shrinked 'cause of its size;\n",(char*)"message1 was shrinked 'cause of its size;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                }
                variables->THREAD_variables->thread_vector_update_window0_state2_state3.push_back((Client_Menu::vector_update_textures_in_window0_in_state2_state3_from_thread){8});
                variables->THREAD_variables->thread_vector_update_window0_state2_state3.push_back((Client_Menu::vector_update_textures_in_window0_in_state2_state3_from_thread){9});

                free(data_buffor);

            }
        break;

        case 8: //received from server 003 (receive new value of fps_max from the server)
            {
                data_buffor = (uint8_t*)malloc(2);
                if(this->THREAD_BACKGROUND_receive(variables,data_buffor,2,8)==1)
                {
                    free(data_buffor);
                    return 1;
                };

                char* buffor0,*buffor1;
                variables->THREAD_variables->max_shared_fps_int = *(uint16_t*)((uint8_t*)data_buffor);
                if(variables->THREAD_variables->max_shared_fps_int==0||variables->THREAD_variables->max_shared_fps_int>480)
                {
                    free(data_buffor);
                    return 1;
                }
                while(variables->THREAD_variables->wait_to_end_operation_save_to_file_and_change_quality_fps_loss_variables==1) SDL_Delay(1);
                variables->THREAD_variables->wait_to_end_operation_save_to_file_and_change_quality_fps_loss_variables = 1;
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                sprintf(buffor0,"max_shared_fps chagned to: %zd;",variables->THREAD_variables->max_shared_fps_int);
                sprintf(buffor1,": max_shared_fps chagned to: %zd;\n",variables->THREAD_variables->max_shared_fps_int);
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                if(variables->THREAD_variables->max_shared_fps_int<variables->THREAD_variables->requested_fps_int)
                {
                    variables->THREAD_variables->requested_fps_int = variables->THREAD_variables->max_shared_fps_int;
                    variables->THREAD_global_variables->universal_tool0->uint32_to_string(variables->THREAD_variables->requested_fps_int,(char*)variables->THREAD_variables->requested_fps);
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"requested_fps changed to: %s;",variables->THREAD_variables->requested_fps);
                    sprintf(buffor1,": requested_fps changed to: %s;\n",variables->THREAD_variables->requested_fps);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                    int size_of_textbox_data = 3;
                    int counter = 0;
                    for(; variables->THREAD_variables->textbox_data[2][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->THREAD_variables->textbox_data[2][counter] = '\0';

                    variables->THREAD_variables->requested_fps[size_of_textbox_data] = '\r'; variables->THREAD_variables->requested_fps[size_of_textbox_data+1] = '\n';
                    variables->THREAD_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->THREAD_variables->requested_fps,size_of_textbox_data+2,"\nrequested fps: ",variables->THREAD_variables->client_base_position_in_config,(2+1)*64);
                    variables->THREAD_variables->requested_fps[size_of_textbox_data] = '\0'; variables->THREAD_variables->requested_fps[size_of_textbox_data+1] = '\0';
                    memcpy(variables->THREAD_variables->textbox_data[2],variables->THREAD_variables->requested_fps,3);

                    variables->THREAD_variables->textbox_variables[2]->update_textbox();

                    if(variables->THREAD_variables->requested_fps_int>=variables->THREAD_global_variables->main_menu_fps) {variables->THREAD_global_variables->sdl_universal_tool0->change_fps(variables->THREAD_variables->requested_fps_int);}
                    else {variables->THREAD_global_variables->sdl_universal_tool0->change_fps(variables->THREAD_global_variables->main_menu_fps);}
                }
                variables->THREAD_variables->thread_vector_update_window0_state2_state3.push_back((Client_Menu::vector_update_textures_in_window0_in_state2_state3_from_thread){1});
                variables->THREAD_variables->wait_to_end_operation_save_to_file_and_change_quality_fps_loss_variables = 0;
                free(data_buffor);
            }
        break;

        case 9: //received from server 004 (receive new value of quality_max from the server)
            {
                data_buffor = (uint8_t*)malloc(1);
                if(this->THREAD_BACKGROUND_receive(variables,data_buffor,1,9)==1)
                {
                    free(data_buffor);
                    return 1;
                }

                char* buffor0,*buffor1;
                variables->THREAD_variables->max_shared_quality_int = data_buffor[0];
                if(variables->THREAD_variables->max_shared_quality_int==0||variables->THREAD_variables->max_shared_quality_int>10)
                {
                    free(data_buffor);
                    return 1;
                }
                while(variables->THREAD_variables->wait_to_end_operation_save_to_file_and_change_quality_fps_loss_variables==1) SDL_Delay(1);
                variables->THREAD_variables->wait_to_end_operation_save_to_file_and_change_quality_fps_loss_variables = 1;
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                sprintf(buffor0,"max_shared_quality chagned to: %zd;",variables->THREAD_variables->max_shared_quality_int);
                sprintf(buffor1,": max_shared_quality chagned to: %zd;\n",variables->THREAD_variables->max_shared_quality_int);
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                if(variables->THREAD_variables->max_shared_quality_int<variables->THREAD_variables->requested_quality_int)
                {
                    variables->THREAD_variables->requested_quality_int = variables->THREAD_variables->max_shared_quality_int;
                    variables->THREAD_global_variables->universal_tool0->uint32_to_string(variables->THREAD_variables->requested_quality_int,(char*)variables->THREAD_variables->requested_quality);
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"requested_quality changed to: %s;",variables->THREAD_variables->requested_quality);
                    sprintf(buffor1,": requested_quality changed to: %s;\n",variables->THREAD_variables->requested_quality);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                    int size_of_textbox_data = 2;
                    int counter = 0;
                    for(; variables->THREAD_variables->textbox_data[3][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->THREAD_variables->textbox_data[3][counter] = '\0';

                    variables->THREAD_variables->requested_quality[size_of_textbox_data] = '\r'; variables->THREAD_variables->requested_quality[size_of_textbox_data+1] = '\n';
                    variables->THREAD_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->THREAD_variables->requested_quality,size_of_textbox_data+2,"\nrequested quality: ",variables->THREAD_variables->client_base_position_in_config,(3+1)*64);
                    variables->THREAD_variables->requested_quality[size_of_textbox_data] = '\0'; variables->THREAD_variables->requested_quality[size_of_textbox_data+1] = '\0';
                    memcpy(variables->THREAD_variables->textbox_data[3],variables->THREAD_variables->requested_quality,2);

                    variables->THREAD_variables->textbox_variables[3]->update_textbox();
                }
                variables->THREAD_variables->thread_vector_update_window0_state2_state3.push_back((Client_Menu::vector_update_textures_in_window0_in_state2_state3_from_thread){2});
                variables->THREAD_variables->wait_to_end_operation_save_to_file_and_change_quality_fps_loss_variables = 0;
                free(data_buffor);
            }
        break;

        case 10: //received from server 005 (receive new value of screen_width from the server)
            {
                data_buffor = (uint8_t*)malloc(2);
                char* buffor0,*buffor1;
                if(this->THREAD_BACKGROUND_receive(variables,data_buffor,2,10)==1)
                {
                    free(data_buffor);
                    return 1;
                }
                variables->THREAD_variables->screen_width_share_int = *(uint16_t*)((uint8_t*)data_buffor);
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                sprintf(buffor0,"screen_width chagned to: %zd;",variables->THREAD_variables->screen_width_share_int);
                sprintf(buffor1,": screen_width chagned to: %zd;\n",variables->THREAD_variables->screen_width_share_int);
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});

                variables->THREAD_variables->thread_vector_update_window0_state2_state3.push_back((Client_Menu::vector_update_textures_in_window0_in_state2_state3_from_thread){4});

                free(data_buffor);

            }
        break;

        case 11: //received from server 006 (receive new value of screen_height from the server)
            {
                data_buffor = (uint8_t*)malloc(2);
                char* buffor0,*buffor1;
                if(this->THREAD_BACKGROUND_receive(variables,data_buffor,2,11)==1)
                {
                    free(data_buffor);
                    return 1;
                }
                variables->THREAD_variables->screen_height_share_int = *(uint16_t*)((uint8_t*)data_buffor);
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                sprintf(buffor0,"screen_height chagned to: %zd;",variables->THREAD_variables->screen_height_share_int);
                sprintf(buffor1,": screen_height chagned to: %zd;\n",variables->THREAD_variables->screen_height_share_int);
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});

                variables->THREAD_variables->thread_vector_update_window0_state2_state3.push_back((Client_Menu::vector_update_textures_in_window0_in_state2_state3_from_thread){5});

                free(data_buffor);
            }
        break;

        case 12: //received from server 007 (receive new value of hash_activate from the server)
            {
                data_buffor = (uint8_t*)malloc(1);
                char* buffor0,*buffor1;
                if(this->THREAD_BACKGROUND_receive(variables,data_buffor,1,12)==1)
                {
                    free(data_buffor);
                    return 1;
                }
                variables->THREAD_variables->server_hash_activate = *(uint8_t*)((uint8_t*)data_buffor);
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                if(variables->THREAD_variables->server_hash_activate==1)
                {
                    sprintf(buffor0,"hash_activate chagned to: yes;");
                    sprintf(buffor1,": hash_activate chagned to: yes;\n");
                }
                else
                {
                    sprintf(buffor0,"hash_activate chagned to: no;");
                    sprintf(buffor1,": hash_activate chagned to: no;\n");
                }

                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});

                variables->THREAD_variables->thread_vector_update_window0_state2_state3.push_back((Client_Menu::vector_update_textures_in_window0_in_state2_state3_from_thread){7});

                free(data_buffor);
            }
        break;

        /*case 13: //received from server 008 (receive information about changing hash from the server)
            {

            }
        break;*/

        case 14: //received from server 009 (receive pause/unpause ScreenSharing from the server)  (to check if is good)
            {
                data_buffor = (uint8_t*)malloc(5);

                if(this->THREAD_BACKGROUND_receive(variables,data_buffor,1,14)==1)
                {
                    free(data_buffor);
                    return 1;
                }
                while(variables->THREAD_variables->operation_code_on_main_frame_data!=0) SDL_Delay(1); //thread lock;

                if(data_buffor[0]==1) //if paused
                {

                    if(this->THREAD_BACKGROUND_receive(variables,data_buffor,4,14)==1)
                    {
                        free(data_buffor);
                        return 1;
                    }
                    uint32_t size_of_pause_image = *(uint32_t*)((uint8_t*)data_buffor);
                    variables->THREAD_variables->main_frame_data = (uint8_t*)malloc(size_of_pause_image);
                    variables->THREAD_variables->size_of_main_frame_data = size_of_pause_image;

                    if(this->THREAD_BACKGROUND_receive(variables,variables->THREAD_variables->main_frame_data,size_of_pause_image,14)==1)
                    {
                        free(data_buffor);
                        return 1;
                    }
                    //unhash here image if needed;
                    if(variables->THREAD_variables->server_hash_activate==1)
                    {
                        uint32_t hash_seed_counter = 0;
                        uint8_t* hash_seed = (uint8_t*)malloc(257);
                        variables->THREAD_global_variables->universal_tool0->memset_custom<uint8_t>(hash_seed,0,257);
                        strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash0); strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash1);
                        strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash2); strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash3);
                        hash_seed_counter = variables->THREAD_global_variables->universal_tool0->count_string_chars((const char*)hash_seed);
                        variables->THREAD_global_variables->universal_tool0->unhash0_32bit(variables->THREAD_variables->main_frame_data,hash_seed,size_of_pause_image,hash_seed_counter);
                        free(hash_seed);

                    }

                    //here unlock option to change data into image in main_program;
                    variables->THREAD_variables->operation_code_on_main_frame_data = 2; //2 means server sended pause image;

                    *(uint32_t*)((uint8_t*)data_buffor) = size_of_pause_image+6;
                    if(this->THREAD_BACKGROUND_send(variables,data_buffor,4,14)==1)
                    {
                        free(data_buffor);
                        return 1;
                    }

                    variables->THREAD_variables->screen_sharing_in_process = 0;
                    variables->THREAD_variables->is_screen_sharing_paused = 1;
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": ScreenSharing has been paused by server;\n",(char*)"ScreenSharing has been paused by server;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255}});
                }
                else //if unpaused;
                {
                    variables->THREAD_variables->operation_code_on_main_frame_data = 3; //3 means server starts sending frame of screen;

                    *(uint32_t*)((uint8_t*)data_buffor) = 2;
                    if(this->THREAD_BACKGROUND_send(variables,data_buffor,4,14)==1)
                    {
                        free(data_buffor);
                        return 1;
                    }

                    variables->THREAD_variables->screen_sharing_in_process = 1;
                    variables->THREAD_variables->is_screen_sharing_paused = 0;
                    variables->THREAD_variables->thread_vector_send_receive[0].clear(); //it's safe and compatible with pop_front event if vector is clear;
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": ScreenSharing has been unpaused by server;\n",(char*)"ScreenSharing has been unpaused by server;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255}});
                }

                free(data_buffor);


            }
        break;

        /*case 15: //received from server 010 (receive frame of screen from the server)
            {

            }
        break;*/

        case 16: //received from server 011 (receive new value of max_shared_loss from the server)
            {
                data_buffor = (uint8_t*)malloc(1);
                if(this->THREAD_BACKGROUND_receive(variables,data_buffor,1,16)==1)
                {
                    free(data_buffor);
                    return 1;
                }

                char* buffor0,*buffor1;
                variables->THREAD_variables->max_shared_loss_int = data_buffor[0];
                if(variables->THREAD_variables->max_shared_loss_int>100)
                {
                    free(data_buffor);
                    return 1;
                }
                while(variables->THREAD_variables->wait_to_end_operation_save_to_file_and_change_quality_fps_loss_variables==1) SDL_Delay(1);
                variables->THREAD_variables->wait_to_end_operation_save_to_file_and_change_quality_fps_loss_variables = 1;
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                sprintf(buffor0,"max_shared_loss chagned to: %zd;",variables->THREAD_variables->max_shared_loss_int);
                sprintf(buffor1,": max_shared_loss chagned to: %zd;\n",variables->THREAD_variables->max_shared_loss_int);
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                if(variables->THREAD_variables->max_shared_loss_int<variables->THREAD_variables->requested_loss_int)
                {
                    variables->THREAD_variables->requested_loss_int = variables->THREAD_variables->max_shared_loss_int;
                    variables->THREAD_global_variables->universal_tool0->uint32_to_string(variables->THREAD_variables->requested_loss_int,(char*)variables->THREAD_variables->requested_loss);
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"requested_loss changed to: %s;",variables->THREAD_variables->requested_loss);
                    sprintf(buffor1,": requested_loss changed to: %s;\n",variables->THREAD_variables->requested_loss);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                    int size_of_textbox_data = 3;
                    int counter = 0;
                    for(; variables->THREAD_variables->textbox_data[4][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->THREAD_variables->textbox_data[4][counter] = '\0';

                    variables->THREAD_variables->requested_loss[size_of_textbox_data] = '\r'; variables->THREAD_variables->requested_loss[size_of_textbox_data+1] = '\n';
                    variables->THREAD_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->THREAD_variables->requested_loss,size_of_textbox_data+2,"\nrequested loss: ",variables->THREAD_variables->client_base_position_in_config,(4+1)*64);
                    variables->THREAD_variables->requested_loss[size_of_textbox_data] = '\0'; variables->THREAD_variables->requested_loss[size_of_textbox_data+1] = '\0';
                    memcpy(variables->THREAD_variables->textbox_data[4],variables->THREAD_variables->requested_loss,3);

                    variables->THREAD_variables->textbox_variables[4]->update_textbox();
                    variables->THREAD_variables->safe_requested_loss = variables->THREAD_variables->requested_loss_int;
                }
                variables->THREAD_variables->thread_vector_update_window0_state2_state3.push_back((Client_Menu::vector_update_textures_in_window0_in_state2_state3_from_thread){3});
                variables->THREAD_variables->wait_to_end_operation_save_to_file_and_change_quality_fps_loss_variables = 0;
                free(data_buffor);
            }
        break;

        case 17: //received from server 100 (receive refresh signal from the server)
            {
                data_buffor = (uint8_t*)malloc(1);
                data_buffor[0] = 100;
                if(this->THREAD_BACKGROUND_send(variables,data_buffor,1,17)==1)
                {
                    free(data_buffor);
                    return 1;
                }

                #ifdef MAIN_PROGRAM0_DEBUG
                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"sended response to refresh signal\n",0,0});
                #endif
                free(data_buffor);
            }
        break;

        /*case 18: //received from server 128 (receive inactivity timeout reached from the server)
            {

            }
        break;

        case 19: //received from server 129 (receive close connection with the client from the server)
            {

            }
        break;

        case 20: //received from server 130 (receive server has been shut down from the server)
            {

            }
        break;*/



        default: break;
    }
    variables->THREAD_variables->thread_vector_send_receive[0].pop_front();
    return 0;
}

bool Client_Menu::THREAD_BACKGROUND_send(THREAD_client_menu_struct_variables* variables,uint8_t* main_pointer_to_data,uint32_t sizeof_data,uint8_t operation_code)
{
    static int32_t error_status;
    static uint32_t how_much_data_is_needed_right_now;
    static uint32_t failed_attempts;
    failed_attempts = 0;
    how_much_data_is_needed_right_now = sizeof_data;
    variables->THREAD_variables->timeout0 = SDL_GetTicks();
    for(;;)
    {
        if(SDL_GetTicks()-variables->THREAD_variables->timeout0>=variables->THREAD_global_variables->inactive_timeout_in_ms)
        {
            #ifdef MAIN_PROGRAM0_DEBUG
            char* debug_buffor = (char*)malloc(512);
            sprintf(debug_buffor,"    sending data failed: inactivity session timeout reached his limit: %zdms\n    your data wasn't sended to the server in complete piece: %dbytes sended from %d needed;\n",
            variables->THREAD_global_variables->inactive_timeout_in_ms,sizeof_data-how_much_data_is_needed_right_now,sizeof_data);
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
            #endif
            variables->THREAD_variables->window0_state = 0; //if main program doesn't catch up;
            variables->THREAD_variables->client.close_client(&variables->THREAD_variables->client_structure);

            switch(operation_code)
            {
                case 0:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": wasn't able to send data to the server:\n",(char*)"wasn't able to send data to the server:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 1:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": wasn't able to send message:\n",(char*)"wasn't able to send message:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 2:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": wasn't able to send requested_fps:\n",(char*)"wasn't able to send requested_fps:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 3:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": wasn't able to send requested_quality:\n",(char*)"wasn't able to send requested_quality:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 5:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": wasn't able to send requested_loss:\n",(char*)"wasn't able to send requested_loss:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 14:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": wasn't able to send pause/unpause:\n",(char*)"wasn't able to send pause/unpause:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 15:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": wasn't able to send frame response:\n",(char*)"wasn't able to send frame response:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 17:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": wasn't able to response to refresh signal:\n",(char*)"wasn't able to response to refresh signal:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                default: break;

            }
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)":    timeout reached;\n",(char*)"    timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client has been destroyed;\n",(char*)"client has been destroyed;",(SDL_Color){168,0,0,0},{0,0,0,255},0});
            variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({0});
            this->reset_winsock_operation_variables(variables->THREAD_variables);

            return 1;
        }

        error_status = variables->THREAD_variables->client.send_to_server(main_pointer_to_data+(sizeof_data-how_much_data_is_needed_right_now),how_much_data_is_needed_right_now,&variables->THREAD_variables->client_structure);
        if(error_status!=-1) how_much_data_is_needed_right_now-=error_status;
        else if(WSAGetLastError()!=WSAEWOULDBLOCK||variables->THREAD_variables->client_is_trying_to_disconnect==1) //if there was error;
        {
            error_status = WSAGetLastError();
            variables->THREAD_variables->window0_state = 0; //if main program doesn't catch up;
            if(variables->THREAD_variables->client_is_trying_to_disconnect==1) //if "disconnect" button has been pressed;
            {
                uint8_t disconnect_buffor = 5; //disconnect code;
                disconnect_buffor = variables->THREAD_variables->client.send_to_server_force(&disconnect_buffor,1,50,1,&variables->THREAD_variables->client_structure);
                #ifdef MAIN_PROGRAM0_DEBUG
                if(disconnect_buffor==1) variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"5 signal has been sended (disconnect from the server);\n",0,0});
                else variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"failed to send disconned signal;\n",0,0});
                #endif
                variables->THREAD_variables->client.close_client(&variables->THREAD_variables->client_structure);
                this->reset_winsock_operation_variables(variables->THREAD_variables);
                return 1;
            }
            variables->THREAD_variables->client.close_client(&variables->THREAD_variables->client_structure);

            #ifdef MAIN_PROGRAM0_DEBUG
            char* debug_buffor = (char*)malloc(128);
            sprintf(debug_buffor,"ERROR: connection has been lost: %d\n\n",error_status);
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
            #endif
            switch(operation_code)
            {
                case 0:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": wasn't able to send data to the server:\n",(char*)"wasn't able to send data to the server:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 1:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": wasn't able to send message:\n",(char*)"wasn't able to send message:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 2:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": wasn't able to send requested_fps:\n",(char*)"wasn't able to send requested_fps:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 3:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": wasn't able to send requested_quality:\n",(char*)"wasn't able to send requested_quality:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 5:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": wasn't able to send requested_loss:\n",(char*)"wasn't able to send requested_loss:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 14:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": wasn't able to send pause/unpause signal:\n",(char*)"wasn't able to send pause/unpause signal:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 15:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": wasn't able to send frame response:\n",(char*)"wasn't able to send frame response:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 17:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": wasn't able to response to refresh signal:\n",(char*)"wasn't able to response to refresh signal:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                default: break;
            }
            char* buffor0 = (char*)malloc(64);
            sprintf(buffor0,"    winsock error: %d;",error_status);
            char* buffor1 = (char*)malloc(64);
            sprintf(buffor1,":    winsock error: %d;\n",error_status);
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){255,0,0,0},{0,0,0,255},1});
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client has been destroyed;\n",(char*)"client has been destroyed;",(SDL_Color){168,0,0,0},{0,0,0,255},0});
            variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({0});
            this->reset_winsock_operation_variables(variables->THREAD_variables);
            return 1;
        }
        else if(failed_attempts!=50) failed_attempts++;
        else if(error_status==-1) SDL_Delay(1);

        if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1&&error_status!=-1)
        {
            if(how_much_data_is_needed_right_now==0)
            {
                if(operation_code==15) variables->THREAD_variables->diode_blue_counter = 1; //if send response to frame of screen 010;
                else variables->THREAD_variables->diode_blue_counter = 2;
            }
            else variables->THREAD_variables->diode_blue_counter = 1;
        }

        if(how_much_data_is_needed_right_now==0) break; //if all data needed has been sended;

    }
    return 0;
}
bool Client_Menu::THREAD_BACKGROUND_receive(THREAD_client_menu_struct_variables* variables,uint8_t* main_pointer_to_data,uint32_t sizeof_data,uint8_t operation_code)
{
    static int32_t error_status;
    static uint32_t how_much_data_is_needed_right_now;
    static uint32_t failed_attempts;
    failed_attempts = 0;
    how_much_data_is_needed_right_now = sizeof_data;
    variables->THREAD_variables->timeout0 = SDL_GetTicks();
    for(;;)
    {
        if(SDL_GetTicks()-variables->THREAD_variables->timeout0>=variables->THREAD_global_variables->inactive_timeout_in_ms)
        {
            #ifdef MAIN_PROGRAM0_DEBUG
            char* debug_buffor = (char*)malloc(512);
            sprintf(debug_buffor,"    receive data error: inactivity session timeout reached his limit: %zdms\n    data from the server wasn't sended in complete piece: %dbytes received from %zd needed;\n\n",
            variables->THREAD_global_variables->inactive_timeout_in_ms,sizeof_data-how_much_data_is_needed_right_now,sizeof_data);
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
            #endif
            variables->THREAD_variables->window0_state = 0; //if main program doesn't catch up;
            variables->THREAD_variables->client.close_client(&variables->THREAD_variables->client_structure);

            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": server wasn't able to send response:\n",(char*)"server wasn't able to send response:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)":    timeout reached;\n",(char*)"    timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client has been destroyed;\n",(char*)"client has been destroyed;",(SDL_Color){168,0,0,0},{0,0,0,255},0});
            variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({0});
            this->reset_winsock_operation_variables(variables->THREAD_variables);

            return 1;
        }

        error_status = variables->THREAD_variables->client.recv_from_server(main_pointer_to_data+(sizeof_data-how_much_data_is_needed_right_now),how_much_data_is_needed_right_now,&variables->THREAD_variables->client_structure);
        if(error_status!=-1) how_much_data_is_needed_right_now-=error_status;
        else if(WSAGetLastError()!=WSAEWOULDBLOCK||variables->THREAD_variables->client_is_trying_to_disconnect==1) //if there was error;
        {
            error_status = WSAGetLastError();
            variables->THREAD_variables->window0_state = 0; //if main program doesn't catch up;
            if(variables->THREAD_variables->client_is_trying_to_disconnect==1) //if "disconnect" button has been pressed;
            {
                uint8_t disconnect_buffor = 5; //disconnect code;
                disconnect_buffor = variables->THREAD_variables->client.send_to_server_force(&disconnect_buffor,1,50,1,&variables->THREAD_variables->client_structure);
                #ifdef MAIN_PROGRAM0_DEBUG
                if(disconnect_buffor==1) variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"5 signal has been sended (disconnect from the server);\n",0,0});
                else variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"failed to send disconned signal;\n",0,0});
                #endif
                variables->THREAD_variables->client.close_client(&variables->THREAD_variables->client_structure);
                this->reset_winsock_operation_variables(variables->THREAD_variables);
                return 1;
            }
            variables->THREAD_variables->client.close_client(&variables->THREAD_variables->client_structure);

            #ifdef MAIN_PROGRAM0_DEBUG
            char* debug_buffor = (char*)malloc(128);
            sprintf(debug_buffor,"ERROR: connection has been lost: %d\n\n",error_status);
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
            #endif

            switch(operation_code)
            {
                case 0:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": receiving connection info failed:\n",(char*)"receiving connection info failed:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 2:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": receiving requested_fps response failed:\n",(char*)"receiving requested_fps response failed:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 3:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)":  receiving requested_quality response failed:\n",(char*)"receiving requested_quality response failed:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 5:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)":  receiving requested_loss response failed:\n",(char*)"receiving requested_loss response failed:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 6:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)":  receiving accept/reject response failed:\n",(char*)"receiving accept/reject response failed:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 7:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)":  receiving message failed:\n",(char*)"receiving message failed:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 8:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)":  receiving max_shared_fps failed:\n",(char*)"receiving max_shared_fps failed:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 9:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)":  receiving max_shared_quality failed:\n",(char*)"receiving max_shared_quality failed:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 10:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)":  receiving screen_width failed:\n",(char*)"receiving screen_width failed:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 11:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)":  receiving screen_height failed:\n",(char*)"receiving screen_height failed:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 12:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)":  receiving hash_activated failed:\n",(char*)"receiving hash_activated failed:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 14:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)":  receiving pause/unpause signal failed:\n",(char*)"receiving pause/unpause signal failed:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 15:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)":  receiving screen frame failed:\n",(char*)"receiving screen frame failed:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;

                case 16:
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)":  receiving max_shared_loss failed:\n",(char*)"receiving max_shared_loss failed:",(SDL_Color){255,255,255,0},{168,0,0,0},0});
                    }
                break;



                default: break;
            }
            char* buffor0 = (char*)malloc(64);
            sprintf(buffor0,"    winsock error: %d;",error_status);
            char* buffor1 = (char*)malloc(64);
            sprintf(buffor1,":    winsock error: %d;\n",error_status);
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){255,0,0,0},{0,0,0,255},1});
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client has been destroyed;\n",(char*)"client has been destroyed;",(SDL_Color){168,0,0,0},{0,0,0,255},0});
            variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({0});
            this->reset_winsock_operation_variables(variables->THREAD_variables);
            return 1;
        }
        else if(failed_attempts!=50) failed_attempts++;
        else if(error_status==-1) SDL_Delay(1);

        if(variables->THREAD_variables->how_much_fps_pass_without_red_diode>=1&&error_status!=-1)
        {
            if(how_much_data_is_needed_right_now==0)
            {
                if(operation_code==15) variables->THREAD_variables->diode_red_counter = 1; //if send response to frame of screen 010;
                else variables->THREAD_variables->diode_red_counter = 2;
            }
            else variables->THREAD_variables->diode_red_counter = 1;
        }

        if(how_much_data_is_needed_right_now==0) break; //if all data needed has been sended;

    }

    return 0;
}

void Client_Menu::reset_winsock_operation_variables(Client_Menu_Variables* variables)
{
    variables->timeout0 = SDL_GetTicks();
    variables->thread_vector_send_receive[0].clear();
    variables->run_now_frame15_operation = 0;
    variables->screen_sharing_in_process = 0;

    variables->client_is_trying_to_disconnect = 0; //should be at the end;
    return;
}
