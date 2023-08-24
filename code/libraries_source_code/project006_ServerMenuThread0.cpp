#include "../libraries/project006_main_program_headers0.h"

//SERVER_THREAD_FUNCTIONS

//void* MAIN_PROGRAM::THREAD_capture_screen_to_window2_and_send_data_to_client(void* data)
//void MAIN_PROGRAM::THREAD_BACKGROUND_send_data_to_client_tool1(THREAD_server_menu_struct_variables* variables,const uint8_t* const data_pointer,uint8_t* function_help_data)
//void MAIN_PROGRAM::THREAD_BACKGROUND_receive_data_to_client_tool1(THREAD_server_menu_struct_variables* variables,uint8_t* data_pointer,uint8_t* function_help_data)
//void MAIN_PROGRAM::THREAD_send_data_to_client_tool0(THREAD_server_menu_struct_variables* variables,char* log_buffor0,char* log_buffor1,uint8_t* buffor0_static)
//void MAIN_PROGRAM::THREAD_receive_data_to_client_tool0(THREAD_server_menu_struct_variables* variables,char* log_buffor0,char* log_buffor1,uint8_t* buffor0_static)

void* Server_Menu::THREAD_capture_screen_to_window2_and_send_data_to_client(void* data)
{
    THREAD_server_menu_struct_variables* variables = (THREAD_server_menu_struct_variables*)data;
    static bool frame_data_is_to_delocate;
    frame_data_is_to_delocate = 0;

    for(;;)
    {
        if(frame_data_is_to_delocate==1) //it has to be there 'cause in case when window0 is in state0 and state1 then there are inside this function instructions "continue" that can be executed;
        {
            while(variables->THREAD_variables->frame_data_should_be_displaying==1) SDL_Delay(1);  //thread lock
            free(variables->THREAD_variables->main_frame_data);
            if(variables->THREAD_variables->operation_on_data_frame==1||variables->THREAD_variables->operation_on_data_frame==3)
            {
                tj3Free(variables->THREAD_variables->main_frame_data_jpeg);
            }
        }


        while(variables->THREAD_variables->active_thread==0) SDL_Delay(1);

        if(variables->THREAD_variables->destroy_thread==1)
        {
            variables->THREAD_variables->exit_thread = 1;
            pthread_exit(NULL);
            return NULL;
        }

        frame_data_is_to_delocate = 0;

    //capture_screen
        //operation_on_data_frame:
        //0 - without client without compression
        //1 - without client with compression
        //2 - with client without compression
        //3 - with client with compression
        static int32_t pitch_calculate0;
        if(((variables->THREAD_variables->window0_state==3&&variables->THREAD_variables->wait_for_client_request==0)||(variables->THREAD_variables->window0_state==2&&variables->THREAD_variables->window2_hide==0&&variables->THREAD_variables->window2_minimalize==0))) //if connected with the client
        {
            uint32_t actual_time = SDL_GetTicks();
            if(variables->THREAD_variables->server_operation[8]==1) //if server is in accepting operation; (fixing the visual bug);
            {

            }
            else if(actual_time-variables->THREAD_variables->next_frame_timer>=(uint32_t)1000.0/variables->THREAD_variables->requested_fps)
            {
                variables->THREAD_variables->next_frame_timer = actual_time;

                while(variables->THREAD_variables->frame_data_should_be_displaying==1) SDL_Delay(1);     //thread lock

                variables->THREAD_variables->width_of_actual_frame = (variables->THREAD_variables->screen_width_share_int*0.1)*variables->THREAD_variables->requested_quality;   //if u change these variables in main program then there is protection
                variables->THREAD_variables->height_of_actual_frame = (variables->THREAD_variables->screen_height_share_int*0.1)*variables->THREAD_variables->requested_quality; //
                variables->THREAD_variables->quality_of_actual_frame = variables->THREAD_variables->requested_quality;
                variables->THREAD_variables->hash_active_of_actual_frame = (variables->THREAD_variables->activate_hash[0]=='y') ? 1 : 0;

                pitch_calculate0 =  (variables->THREAD_variables->width_of_actual_frame * 24 + 7) / 8;
                variables->THREAD_variables->pitch_of_actual_frame = ((pitch_calculate0 + 3) / 4) * 4;

                if(variables->THREAD_variables->window0_state==3&&variables->THREAD_variables->is_screen_sharing_paused==1) //if pause is ON;
                {

                }
                else if(variables->THREAD_variables->requested_loss==0)
                {

                    variables->THREAD_variables->main_frame_data = (uint8_t*)malloc((variables->THREAD_variables->width_of_actual_frame+1)*(variables->THREAD_variables->height_of_actual_frame*3));
                    variables->THREAD_global_variables->universal_tool0->capture_screen_to_buffor_RGB((uint8_t*)variables->THREAD_variables->main_frame_data,
                                                                                                        variables->THREAD_variables->screen_width_share_int,
                                                                                                        variables->THREAD_variables->screen_height_share_int,
                                                                                                        variables->THREAD_variables->requested_quality,
                                                                                                    1,variables->THREAD_global_variables->server_bad_quality_share);

                    variables->THREAD_variables->operation_on_data_frame = 2;
                    variables->THREAD_variables->frame_data_should_be_displaying = 1;                       //thread lock
                    frame_data_is_to_delocate = 1;
                    variables->THREAD_variables->should_be_next_frame = 1;
                }
                else
                {
                    variables->THREAD_variables->main_frame_data = (uint8_t*)malloc((variables->THREAD_variables->width_of_actual_frame+1)*(variables->THREAD_variables->height_of_actual_frame*3));
                    variables->THREAD_global_variables->universal_tool0->capture_screen_to_buffor_RGB((uint8_t*)variables->THREAD_variables->main_frame_data,
                                                                                                        variables->THREAD_variables->screen_width_share_int,
                                                                                                        variables->THREAD_variables->screen_height_share_int,
                                                                                                        variables->THREAD_variables->requested_quality,
                                                                                                    1,variables->THREAD_global_variables->server_bad_quality_share);

                    tj3Set(variables->THREAD_global_variables->compressor_handle,TJPARAM_QUALITY,variables->THREAD_variables->requested_loss);
                    tj3Set(variables->THREAD_global_variables->compressor_handle,TJPARAM_SUBSAMP,variables->THREAD_global_variables->compression_method);
                    variables->THREAD_variables->size_of_main_frame_data_jpeg = 0;
                    variables->THREAD_variables->main_frame_data_jpeg = NULL;
                    if(tj3Compress8(variables->THREAD_global_variables->compressor_handle,variables->THREAD_variables->main_frame_data,variables->THREAD_variables->width_of_actual_frame,
                                    variables->THREAD_variables->pitch_of_actual_frame,
                                    variables->THREAD_variables->height_of_actual_frame,TJPF_BGR,
                                    &variables->THREAD_variables->main_frame_data_jpeg,&variables->THREAD_variables->size_of_main_frame_data_jpeg)==-1)
                    {
                        #ifdef MAIN_PROGRAM0_DEBUG
                        char* debug_buffor = (char*)malloc(256);
                        sprintf(debug_buffor,"ERROR: %s\n",tj3GetErrorStr(variables->THREAD_global_variables->compressor_handle));
                        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                        #endif
                        free(variables->THREAD_variables->main_frame_data);

                    }
                    else
                    {
                        variables->THREAD_variables->operation_on_data_frame = 3;
                        variables->THREAD_variables->frame_data_should_be_displaying = 1;                       //thread lock
                        frame_data_is_to_delocate = 1;
                        variables->THREAD_variables->should_be_next_frame = 1;
                    }

                }
            }

        }
        else if(variables->THREAD_variables->window2_hide==0&&variables->THREAD_variables->window2_minimalize==0)
        {
            uint32_t actual_time = SDL_GetTicks();
            if(actual_time-variables->THREAD_variables->next_frame_timer>=(uint32_t)1000.0/variables->THREAD_variables->max_shared_fps_int)
            {
                variables->THREAD_variables->next_frame_timer = actual_time;
                while(variables->THREAD_variables->frame_data_should_be_displaying==1) SDL_Delay(1);     //thread lock

                variables->THREAD_variables->width_of_actual_frame = (variables->THREAD_variables->screen_width_share_int*0.1)*variables->THREAD_variables->max_shared_quality_int;   //if u change these variables in main program then there is protection
                variables->THREAD_variables->height_of_actual_frame = (variables->THREAD_variables->screen_height_share_int*0.1)*variables->THREAD_variables->max_shared_quality_int; //
                variables->THREAD_variables->quality_of_actual_frame = variables->THREAD_variables->max_shared_quality_int;                                                           //

                pitch_calculate0 =  (variables->THREAD_variables->width_of_actual_frame * 24 + 7) / 8;
                variables->THREAD_variables->pitch_of_actual_frame = ((pitch_calculate0 + 3) / 4) * 4;

                variables->THREAD_variables->main_frame_data = (uint8_t*)malloc((variables->THREAD_variables->width_of_actual_frame+1)*(variables->THREAD_variables->height_of_actual_frame*3));   // DELETE *2
                variables->THREAD_global_variables->universal_tool0->capture_screen_to_buffor_RGB(variables->THREAD_variables->main_frame_data,variables->THREAD_variables->screen_width_share_int
                                                                                                  ,variables->THREAD_variables->screen_height_share_int
                                                                                                  ,variables->THREAD_variables->max_shared_quality_int
                                                                                                  ,1,variables->THREAD_global_variables->server_bad_quality_share);
                if(variables->THREAD_variables->max_shared_loss_int==0)
                {

                    variables->THREAD_variables->operation_on_data_frame = 0;
                    variables->THREAD_variables->frame_data_should_be_displaying = 1;                       //thread lock
                    frame_data_is_to_delocate = 1;
                }
                else
                {

                    tj3Set(variables->THREAD_global_variables->compressor_handle,TJPARAM_QUALITY,variables->THREAD_variables->max_shared_loss_int);
                    tj3Set(variables->THREAD_global_variables->compressor_handle,TJPARAM_SUBSAMP,variables->THREAD_global_variables->compression_method);
                    variables->THREAD_variables->size_of_main_frame_data_jpeg = 0;
                    variables->THREAD_variables->main_frame_data_jpeg = NULL;
                    if(tj3Compress8(variables->THREAD_global_variables->compressor_handle,variables->THREAD_variables->main_frame_data,variables->THREAD_variables->width_of_actual_frame,
                                    variables->THREAD_variables->pitch_of_actual_frame,
                                    variables->THREAD_variables->height_of_actual_frame,TJPF_BGR,
                                    &variables->THREAD_variables->main_frame_data_jpeg,&variables->THREAD_variables->size_of_main_frame_data_jpeg)==-1)
                    {
                        #ifdef MAIN_PROGRAM0_DEBUG
                        char* debug_buffor = (char*)malloc(256);
                        sprintf(debug_buffor,"ERROR: %s\n",tj3GetErrorStr(variables->THREAD_global_variables->compressor_handle));
                        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                        #endif
                        free(variables->THREAD_variables->main_frame_data);

                    }
                    else
                    {
                        variables->THREAD_variables->operation_on_data_frame = 1;
                        variables->THREAD_variables->frame_data_should_be_displaying = 1;                       //thread lock
                        frame_data_is_to_delocate = 1;
                    }

                }


            }
        }

        //server_state
        static int error_status;
        static uint8_t buffor0_static[138];
        static uint32_t how_much_data_is_needed_right_now;

        if(variables->THREAD_variables->window0_state==1)
        {
            if(variables->THREAD_variables->state_of_waiting_for_client==2) //if data wasn't sended in one piece;
            {
                if(SDL_GetTicks()-variables->THREAD_variables->timeout0>=variables->THREAD_global_variables->inactive_timeout_in_ms)
                {
                    variables->THREAD_variables->state_of_waiting_for_client = 0;
                    //sending information to client about reached limit
                    uint8_t buffor0 = 128;
                    variables->THREAD_variables->server.send_to_client(&buffor0,1,&variables->THREAD_variables->server_structure);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"128 signal has been sended;\n",0,0});
                    #endif
                    buffor0 = 129;
                    variables->THREAD_variables->server.send_to_client(&buffor0,1,&variables->THREAD_variables->server_structure);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"129 signal has been sended;\n",0,0});
                    #endif
                    variables->THREAD_variables->diode_blue_counter = 2;
                    //reject client
                    variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                                      &variables->THREAD_variables->server_structure);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    char* debug_buffor = (char*)malloc(256);
                    sprintf(debug_buffor,"    connection rejected: inactivity session timeout reached his limit: %zdms\n    data from a client wasn't complete: %dbytes received from 139 needed;\n",variables->THREAD_global_variables->inactive_timeout_in_ms,139-how_much_data_is_needed_right_now);
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                    #endif
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": connection rejected:\n",(char*)"connection rejected:",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},(SDL_Color){0,0,0,255},0});
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   data from a client wasn't complete;\n",(char*)"    data from a client wasn't complete;",(SDL_Color){168,0,0,0},(SDL_Color){0,0,0,255},0});
                    variables->THREAD_variables->active_thread = 0;
                    continue;
                }
                error_status = variables->THREAD_variables->server.recv_from_client(buffor0_static+(139-how_much_data_is_needed_right_now),how_much_data_is_needed_right_now,&variables->THREAD_variables->server_structure);
                if(error_status!=-1) how_much_data_is_needed_right_now-=error_status;
                else if(WSAGetLastError()!=WSAEWOULDBLOCK) //disconnect a client (client error);
                {
                    if(variables->THREAD_variables->do_server_is_destroying==1) //if "disconnect" event has been executed in the main program;
                    {
                        variables->THREAD_variables->do_server_is_destroying = 0;
                        this->reset_all_server_state_variables(variables->THREAD_variables);
                        variables->THREAD_variables->active_thread = 0;
                        continue;
                    }
                    error_status = WSAGetLastError();
                    variables->THREAD_variables->state_of_waiting_for_client = 0;
                    uint8_t buffor_code0 = 129;
                    variables->THREAD_variables->server.send_to_client(&buffor_code0,1,&variables->THREAD_variables->server_structure);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"129 signal has been sended;\n",0,0});
                    #endif
                    variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                                      &variables->THREAD_variables->server_structure);
                    printf_error_args("a client failed to connect to you; winsock error: %d\n",error_status);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": a client connection failed:\n",(char*)"a client connection failed:",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                    char* buffor0 = (char*)malloc(64);
                    sprintf(buffor0,"    winsock error from a client: %d;",error_status);
                    char* buffor1 = (char*)malloc(64);
                    sprintf(buffor1,":   winsock error from a client: %d;\n",error_status);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){255,0,0,0},(SDL_Color){0,0,0,255},1});
                    variables->THREAD_variables->active_thread = 0;
                    continue;
                }
                if(variables->THREAD_variables->how_much_fps_pass_without_red_diode>=1&&error_status!=-1)  variables->THREAD_variables->diode_red_counter = 1;
                if(how_much_data_is_needed_right_now==0) //if all data needed has been sended;
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": successively received data from a client;\n",(char*)"successively received data from a client;",(SDL_Color){0,0,0,0},{0,0,0,255},0});
                    variables->THREAD_variables->state_of_waiting_for_client = 3;
                }
            }
            else if(variables->THREAD_variables->state_of_waiting_for_client==1)
            {
                if(SDL_GetTicks()-variables->THREAD_variables->timeout0>=variables->THREAD_global_variables->inactive_timeout_in_ms)
                {
                    variables->THREAD_variables->state_of_waiting_for_client = 0;
                    //sending information to client about reached limit
                    uint8_t buffor0 = 128;
                    variables->THREAD_variables->server.send_to_client(&buffor0,1,&variables->THREAD_variables->server_structure);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"128 signal has been sended;\n",0,0});
                    #endif
                    buffor0 = 129;
                    variables->THREAD_variables->server.send_to_client(&buffor0,1,&variables->THREAD_variables->server_structure);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"129 signal has been sended;\n",0,0});
                    #endif
                    variables->THREAD_variables->diode_blue_counter = 2;
                    //reject client
                    variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                                      &variables->THREAD_variables->server_structure);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    char* debug_buffor = (char*)malloc(184);
                    sprintf(debug_buffor,"    connection rejected: inactivity session timeout reached his limit: %zdms\n",variables->THREAD_global_variables->inactive_timeout_in_ms);
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                    #endif
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": connection rejected:\n",(char*)"connection rejected:",(SDL_Color){0,0,0,0},{0,0,0,255},0});
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":    inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                    variables->THREAD_variables->active_thread = 0;
                    continue;
                }
                uint8_t data1 = 0;
                error_status = variables->THREAD_variables->server.recv_from_client(&data1,1,&variables->THREAD_variables->server_structure);
                if(error_status!=1)
                {
                    error_status = WSAGetLastError();
                    if(error_status!=WSAEWOULDBLOCK) //disconnect a client (client error);
                    {
                        if(variables->THREAD_variables->do_server_is_destroying==1) //if "disconnect" event has been executed in the main program;
                        {
                            variables->THREAD_variables->do_server_is_destroying = 0;
                            this->reset_all_server_state_variables(variables->THREAD_variables);
                            variables->THREAD_variables->active_thread = 0;
                            continue;
                        }
                        variables->THREAD_variables->state_of_waiting_for_client = 0;
                        variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
                        variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
                        variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                                      &variables->THREAD_variables->server_structure);
                        #ifdef MAIN_PROGRAM0_DEBUG
                        char* debug_buffor = (char*)malloc(128);
                        sprintf(debug_buffor,"a client failed to connect to you; winsock error: %d\n",error_status);
                        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                        #endif
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": a client connection failed:\n",(char*)"a client connection failed:",(SDL_Color){0,0,0,0},{0,0,0,255},0});
                        char* buffor0 = (char*)malloc(64);
                        sprintf(buffor0,"    winsock error from a client: %d;",error_status);
                        char* buffor1 = (char*)malloc(64);
                        sprintf(buffor1,":    winsock error from a client: %d;\n",error_status);
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){255,0,0,0},{0,0,0,255},1});
                        variables->THREAD_variables->active_thread = 0;
                        continue;
                    }
                }
                else //if data was sended to server;
                {
                    if(data1!=1) //disconnect a client (wrong code sended);
                    {
                        variables->THREAD_variables->diode_red_counter = 2;
                        variables->THREAD_variables->state_of_waiting_for_client = 0;
                        uint8_t buffor_code0 = 129;
                        variables->THREAD_variables->server.send_to_client(&buffor_code0,1,&variables->THREAD_variables->server_structure);
                        #ifdef MAIN_PROGRAM0_DEBUG
                        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"129 signal has been sended;\n",0,0});
                        #endif
                        variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
                        variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
                        variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                                      &variables->THREAD_variables->server_structure);
                        #ifdef MAIN_PROGRAM0_DEBUG
                        char* debug_buffor = (char*)malloc(64);
                        sprintf(debug_buffor,"code operation sended from client: %d\n",data1);
                        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                        #endif

                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": a client connection failed:\n",(char*)"a client connection failed:",(SDL_Color){0,0,0,0},{0,0,0,255},0});
                        char* buffor0 = (char*)malloc(64);
                        sprintf(buffor0,"    a client sended wrong action code: %d;",data1);
                        char* buffor1 = (char*)malloc(64);
                        sprintf(buffor1,":    a client sended wrong action code: %d;\n",data1);
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){168,0,0,0},{0,0,0,255},1});
                        variables->THREAD_variables->active_thread = 0;
                        continue;
                    }
                    error_status = variables->THREAD_variables->server.recv_from_client(buffor0_static,139,&variables->THREAD_variables->server_structure);
                    if(error_status!=139) //if data wasn't sended in one piece;
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": failed to receive all of the data from a client;\n",(char*)"failed to receive all of the data from a client;",(SDL_Color){0,0,0,0},{0,0,0,255},0});
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":    retries are performed\n",(char*)"    retries are performed;",(SDL_Color){0,0,0,0},{0,0,0,255},0});
                        if(error_status!=-1)
                        {
                            variables->THREAD_variables->diode_red_counter = 1;
                            how_much_data_is_needed_right_now = 139-error_status;
                        }
                        else
                        {
                            variables->THREAD_variables->diode_red_counter = 0;
                            how_much_data_is_needed_right_now = 139;
                        }

                        variables->THREAD_variables->state_of_waiting_for_client = 2;
                        variables->THREAD_variables->timeout0 = SDL_GetTicks();
                        variables->THREAD_variables->active_thread = 0;
                        continue;
                    }
                    else //if all data needed has been sended;
                    {
                        variables->THREAD_variables->state_of_waiting_for_client = 3;
                        variables->THREAD_variables->diode_red_counter = 2;
                    }
                }
            }
            else if(variables->THREAD_variables->state_of_waiting_for_client==0)
            {
                error_status = variables->THREAD_variables->server.waiting_for_client(&variables->THREAD_variables->server_structure);
                if(error_status==0) //connected with a client;
                {
                    variables->THREAD_variables->state_of_waiting_for_client = 1;
                    variables->THREAD_variables->diode_red_counter = 2;
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": a client is trying to connect to you;\n",(char*)"a client is trying to connect to you;",(SDL_Color){168,168,0,0},{0,0,0,255},0});
                    //start timer timout;
                    variables->THREAD_variables->timeout0 = SDL_GetTicks();
                    variables->THREAD_variables->active_thread = 0;
                    continue;
                }
                else if(error_status!=WSAEWOULDBLOCK) //stop waiting for a client (server error);
                {
                    if(variables->THREAD_variables->do_server_is_destroying==1) //if "disconnect" event has been executed in the main program;
                    {
                        variables->THREAD_variables->do_server_is_destroying = 0;
                        this->reset_all_server_state_variables(variables->THREAD_variables);
                        variables->THREAD_variables->active_thread = 0;
                        continue;
                    }
                    variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                                      &variables->THREAD_variables->server_structure);

                    #ifdef MAIN_PROGRAM0_DEBUG
                    char* debug_buffor = (char*)malloc(128);
                    sprintf(debug_buffor,"ERROR: waiting for a client failed; winsock error: %d\n\n",error_status);
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                    #endif
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": waiting for a client failed:\n",(char*)"waiting for a client failed:",(SDL_Color){0,0,0,0},{0,0,0,255},0});
                    char* buffor0 = (char*)malloc(64);
                    sprintf(buffor0,"    winsock error: %d;",error_status);
                    char* buffor1 = (char*)malloc(64);
                    sprintf(buffor1,":    winsock error: %d;\n",error_status);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){255,0,0,0},{0,0,0,255},1});
                    variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({0});
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": server has been destroyed;\n",(char*)"server has been destroyed;",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                    variables->THREAD_variables->active_thread = 0;
                    continue;
                }
            }

            if(variables->THREAD_variables->state_of_waiting_for_client==3) //if all data needed has been sended;
            {
                variables->THREAD_variables->state_of_waiting_for_client = 0;
                variables->THREAD_variables->client_public_ip_int = *(uint32_t*)((uint8_t*)buffor0_static);
                for(int i = 0,offset = 0,j; i!=4; i++)
                {
                    variables->THREAD_global_variables->universal_tool0->uint32_to_string(*((uint8_t*)&variables->THREAD_variables->client_public_ip_int+i),(char*)&variables->THREAD_variables->client_public_ip_string[offset]);
                    for(j = offset; ; j++)
                    {
                        if(variables->THREAD_variables->client_public_ip_string[j]=='\0')
                        {
                            if(i!=3)
                            {
                                offset = j+1;
                                variables->THREAD_variables->client_public_ip_string[j] = '.';
                                break;
                            }
                            else break;
                        }
                    }
                }
                for(int i = 0; i!=64; i+=4) *(uint32_t*)((uint8_t*)variables->THREAD_variables->password_client+i) = *(uint32_t*)((uint8_t*)buffor0_static+4+i);
                variables->THREAD_variables->password_client[64] = '\0';

                variables->THREAD_variables->requested_fps = *(uint16_t*)((uint8_t*)buffor0_static+69);
                variables->THREAD_variables->requested_quality = *(uint8_t*)((uint8_t*)buffor0_static+71);
                variables->THREAD_variables->requested_loss = *(uint8_t*)((uint8_t*)buffor0_static+72);

                for(int i = 0; i!=32; i+=4) *(uint32_t*)((uint8_t*)variables->THREAD_variables->message0_client+i) = *(uint32_t*)((uint8_t*)buffor0_static+73+i);
                variables->THREAD_variables->message0_client[32] = '\0';

                for(int i = 0; i!=32; i+=4) *(uint32_t*)((uint8_t*)variables->THREAD_variables->message1_client+i) = *(uint32_t*)((uint8_t*)buffor0_static+106+i);
                variables->THREAD_variables->message1_client[32] = '\0';


                #ifdef MAIN_PROGRAM0_DEBUG
                char* debug_buffor = (char*)malloc(1024);
                sprintf(debug_buffor,
                        "    received information from a client:\n"
                       "        client_public_ip (int): %zd\n"
                       "        client_public_ip (string): %s\n"
                       "        client_password: %s\n"
                       "        client_requested_fps: %zd\n"
                       "        client_requested_quality: %zd\n"
                       "        client_requested_loss: %zd\n"
                       "        client_message0: %s\n"
                       "        client_message1: %s\n",
                       variables->THREAD_variables->client_public_ip_int,
                       variables->THREAD_variables->client_public_ip_string,
                       variables->THREAD_variables->password_client,
                       variables->THREAD_variables->requested_fps,
                       variables->THREAD_variables->requested_quality,
                       variables->THREAD_variables->requested_loss,
                       variables->THREAD_variables->message0_client,
                       variables->THREAD_variables->message1_client);
                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                #endif

                char* buffor0 = (char*)malloc(64);
                char* buffor1 = (char*)malloc(64);
                SDL_Color background = {168,168,0,0};
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": received information from a client:\n",(char*)"received information from a client:",(SDL_Color){255,255,255,0},background,0});
                sprintf(buffor0,"    client_public_ip: %s;",variables->THREAD_variables->client_public_ip_string);
                sprintf(buffor1,":    client_public_ip: %s;\n",variables->THREAD_variables->client_public_ip_string);
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                sprintf(buffor0,"    client_requested_fps: %zd;",variables->THREAD_variables->requested_fps);
                sprintf(buffor1,":    client_requested_fps: %zd;\n",variables->THREAD_variables->requested_fps);
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                sprintf(buffor0,"    client_requested_quality: %zd;",variables->THREAD_variables->requested_quality);
                sprintf(buffor1,":    client_requested_quality: %zd;\n",variables->THREAD_variables->requested_quality);
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                buffor0 = (char*)malloc(64);
                buffor1 = (char*)malloc(64);
                if(variables->THREAD_variables->requested_loss==0)
                {
                    sprintf(buffor0,"    client_requested_loss: disabled;");
                    sprintf(buffor1,":    client_requested_loss: disabled;\n");
                }
                else
                {
                    sprintf(buffor0,"    client_requested_loss: %zd;",variables->THREAD_variables->requested_loss);
                    sprintf(buffor1,":    client_requested_loss: %zd;\n",variables->THREAD_variables->requested_loss);
                }
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                if(variables->THREAD_variables->message0_client[0]!='\0'||variables->THREAD_variables->message1_client[0]!='\0')
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": starting message from a client:\n",(char*)"starting message from a client:",(SDL_Color){255,255,255,0},background,0});
                    if(variables->THREAD_variables->message0_client[0]!='\0')
                    {
                        buffor0 = (char*)malloc(64);
                        buffor1 = (char*)malloc(64);
                        sprintf(buffor0,"    %s",(const char*)variables->THREAD_variables->message0_client);
                        sprintf(buffor1,":    %s\n",(const char*)variables->THREAD_variables->message0_client);
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    }
                    if(variables->THREAD_variables->message1_client[0]!='\0')
                    {
                        buffor0 = (char*)malloc(64);
                        buffor1 = (char*)malloc(64);
                        sprintf(buffor0,"    %s",(const char*)variables->THREAD_variables->message1_client);
                        sprintf(buffor1,":    %s\n",(const char*)variables->THREAD_variables->message1_client);
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    }
                }

                if(variables->THREAD_variables->password_required[0]=='y')
                {
                    int error_break = 0;
                    int size_of_server_password = variables->THREAD_global_variables->universal_tool0->count_string_chars((const char*)variables->THREAD_variables->password);
                    int size_of_client_password = variables->THREAD_global_variables->universal_tool0->count_string_chars((const char*)variables->THREAD_variables->password_client);
                    if(size_of_client_password!=size_of_server_password) error_break++;
                    if(variables->THREAD_global_variables->universal_tool0->compare_data(variables->THREAD_variables->password,variables->THREAD_variables->password_client,size_of_client_password)==1) error_break++;
                    if(error_break!=0)
                    {
                        uint8_t buffor0 = 2;
                        variables->THREAD_variables->server.send_to_client(&buffor0,1,&variables->THREAD_variables->server_structure);
                        #ifdef MAIN_PROGRAM0_DEBUG
                        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"2 signal has been sended;\n",0,0});
                        #endif
                        buffor0 = 129;
                        variables->THREAD_variables->server.send_to_client(&buffor0,1,&variables->THREAD_variables->server_structure);
                        #ifdef MAIN_PROGRAM0_DEBUG
                        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"129 signal has been sended;\n",0,0});
                        #endif
                        variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
                        variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
                        variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                                      &variables->THREAD_variables->server_structure);
                        #ifdef MAIN_PROGRAM0_DEBUG
                        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"a client failed to connect to you; client password is incorrect\n",0,0});
                        #endif
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": a client connection failed:\n",(char*)"a client connection failed:",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":    a client password is incorrect;\n",(char*)"    a client password is incorrect;",(SDL_Color){168,0,0,0},(SDL_Color){0,0,0,255},0});
                        variables->THREAD_variables->active_thread = 0;
                        continue;
                    }
                    else
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": a client password is correct;\n",(char*)"a client password is correct;",(SDL_Color){0,168,0,0},(SDL_Color){0,0,0,255},0});
                    }
                }
                if(this->shrink_string_to_fit_the_size(variables->THREAD_global_variables->main_ttf,(char*)variables->THREAD_variables->message0_client,210)!=0)
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": message0 was shrinked 'cause of its size;\n",(char*)"message0 was shrinked 'cause of its size;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                }
                if(this->shrink_string_to_fit_the_size(variables->THREAD_global_variables->main_ttf,(char*)variables->THREAD_variables->message1_client,210)!=0)
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": message1 was shrinked 'cause of its size;\n",(char*)"message1 was shrinked 'cause of its size;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                }
                if((variables->THREAD_variables->requested_fps>variables->THREAD_variables->max_shared_fps_int)||(variables->THREAD_variables->requested_fps>480||variables->THREAD_variables->requested_fps==0))
                {
                    variables->THREAD_variables->requested_fps = variables->THREAD_variables->max_shared_fps_int;
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"requested_fps changed to: %zd;",variables->THREAD_variables->requested_fps);
                    sprintf(buffor1,": requested_fps changed to: %zd;\n",variables->THREAD_variables->requested_fps);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,168,0},(SDL_Color){0,0,0,255},1});

                }
                if((variables->THREAD_variables->requested_quality>variables->THREAD_variables->max_shared_quality_int)||(variables->THREAD_variables->requested_quality>10||variables->THREAD_variables->requested_quality==0))
                {
                    variables->THREAD_variables->requested_quality = variables->THREAD_variables->max_shared_quality_int;
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"requested_quality changed to: %zd;",variables->THREAD_variables->requested_quality);
                    sprintf(buffor1,": requested_quality changed to: %zd;\n",variables->THREAD_variables->requested_quality);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,168,0},{0,0,0,255},1});
                }
                if((variables->THREAD_variables->requested_loss>variables->THREAD_variables->max_shared_loss_int)||(variables->THREAD_variables->requested_loss>100))
                {
                    variables->THREAD_variables->requested_loss = variables->THREAD_variables->max_shared_loss_int;
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"requested_loss changed to: %zd;",variables->THREAD_variables->requested_loss);
                    sprintf(buffor1,": requested_loss changed to: %zd;\n",variables->THREAD_variables->requested_loss);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,168,0},{0,0,0,255},1});
                }




                //send server information to client here;
                variables->THREAD_global_variables->universal_tool0->memset_custom(buffor0_static,'\0',76);
                buffor0_static[0] = 1;
                buffor0_static[1] = variables->THREAD_variables->max_shared_quality_int;
                *(uint16_t*)((uint8_t*)buffor0_static+2) = variables->THREAD_variables->max_shared_fps_int;
                buffor0_static[4] = variables->THREAD_variables->max_shared_loss_int;
                *(uint16_t*)((uint8_t*)buffor0_static+5) = (uint16_t)variables->THREAD_variables->screen_width_share_int;
                *(uint16_t*)((uint8_t*)buffor0_static+7) = (uint16_t)variables->THREAD_variables->screen_height_share_int;
                buffor0_static[9] = (variables->THREAD_variables->password_required[0]=='y') ? 1 : 0;
                buffor0_static[10] = (variables->THREAD_variables->activate_hash[0]=='y') ? 1 : 0;
                int counter0 = 0;
                for(; variables->THREAD_variables->message0[counter0]!='\0'; counter0++) buffor0_static[11+counter0] = variables->THREAD_variables->message0[counter0];
                buffor0_static[11+counter0] = '\0';
                for(counter0 = 0; variables->THREAD_variables->message1[counter0]!='\0'; counter0++) buffor0_static[44+counter0] = variables->THREAD_variables->message1[counter0];
                buffor0_static[44+counter0] = '\0';

                error_status = variables->THREAD_variables->server.send_to_client(buffor0_static,77,&variables->THREAD_variables->server_structure);
                if(error_status!=77) //if data wasn't sended in one piece;
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": failed to send all of the data to a client;\n",(char*)"failed to send all of the data to a client;",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":    retries are performed\n",(char*)"    retries are performed;",(SDL_Color){0,0,0,0},{0,0,0,255},0});
                    if(error_status!=-1)
                    {
                        variables->THREAD_variables->diode_blue_counter = 1;
                        how_much_data_is_needed_right_now = 77-error_status;
                    }
                    else
                    {
                        variables->THREAD_variables->diode_blue_counter = 0;
                        how_much_data_is_needed_right_now = 77;
                    }

                    variables->THREAD_variables->state_of_waiting_for_client = 4;
                    variables->THREAD_variables->timeout0 = SDL_GetTicks();
                }
                else //if all data needed has been sended;
                {
                    #ifdef MAIN_PROGRAM0_DEBUG
                    char* debug_buffor = (char*)malloc(1024);
                    sprintf(debug_buffor,
                           "    sended information to a client:\n"
                           "        max_shared_quality: %s\n"
                           "        max_shared_fps: %s\n"
                           "        screen_width: %s\n"
                           "        screen_height: %s\n"
                           "        max_shared_loss: %zd\n"
                           "        password_required: %s\n"
                           "        hash_activated: %s\n"
                           "        server_message0: %s\n"
                           "        server_message1: %s\n",
                           (const char*)variables->THREAD_variables->max_shared_quality,
                           (const char*)variables->THREAD_variables->max_shared_fps,
                           (const char*)variables->THREAD_variables->screen_width_share,
                           (const char*)variables->THREAD_variables->screen_height_share,
                           variables->THREAD_variables->max_shared_loss_int,
                           (const char*)variables->THREAD_variables->password_required,
                           (const char*)variables->THREAD_variables->activate_hash,
                           (const char*)variables->THREAD_variables->message0,
                           (const char*)variables->THREAD_variables->message1);
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                    #endif

                    background.r = 0; background.g = 0; background.b = 168;
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sended information to a client:\n",(char*)"sended information to a client:",(SDL_Color){255,255,255,0},background,0});
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"    max_shared_fps: %s;",(const char*)variables->THREAD_variables->max_shared_fps);
                    sprintf(buffor1,":    max_shared_fps: %s;\n",(const char*)variables->THREAD_variables->max_shared_fps);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"    max_shared_quality: %s;",(const char*)variables->THREAD_variables->max_shared_quality);
                    sprintf(buffor1,":    max_shared_quality: %s;\n",(const char*)variables->THREAD_variables->max_shared_quality);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"    max_shared_loss: %s;",(const char*)variables->THREAD_variables->max_shared_loss);
                    sprintf(buffor1,":    max_shared_loss: %s;\n",(const char*)variables->THREAD_variables->max_shared_loss);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"    screen_width: %s;",(const char*)variables->THREAD_variables->screen_width_share);
                    sprintf(buffor1,":    screen_width: %s;\n",(const char*)variables->THREAD_variables->screen_width_share);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"    screen_height: %s;",(const char*)variables->THREAD_variables->screen_height_share);
                    sprintf(buffor1,":    screen_height: %s;\n",(const char*)variables->THREAD_variables->screen_height_share);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"    password_required: %s;",(const char*)variables->THREAD_variables->password_required);
                    sprintf(buffor1,":    password_required: %s;\n",(const char*)variables->THREAD_variables->password_required);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"    hash_activated: %s;",(const char*)variables->THREAD_variables->activate_hash);
                    sprintf(buffor1,":    hash_activated: %s;\n",(const char*)variables->THREAD_variables->activate_hash);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    if(variables->THREAD_variables->message0[0]!='\0'||variables->THREAD_variables->message1[0]!='\0')
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": your starting message to a client:\n",(char*)"your starting message to a client:",(SDL_Color){255,255,255,0},background,0});
                        if(variables->THREAD_variables->message0[0]!='\0')
                        {
                            buffor0 = (char*)malloc(64);
                            buffor1 = (char*)malloc(64);
                            sprintf(buffor0,"    %s",(const char*)variables->THREAD_variables->message0);
                            sprintf(buffor1,":    %s\n",(const char*)variables->THREAD_variables->message0);
                            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                        }
                        if(variables->THREAD_variables->message1[0]!='\0')
                        {
                            buffor0 = (char*)malloc(64);
                            buffor1 = (char*)malloc(64);
                            sprintf(buffor0,"    %s",(const char*)variables->THREAD_variables->message1);
                            sprintf(buffor1,":    %s\n",(const char*)variables->THREAD_variables->message1);
                            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                        }
                    }

                    variables->THREAD_variables->state_of_waiting_for_client = 0;
                    variables->THREAD_variables->diode_blue_counter = 2;
                    this->reset_all_server_state_variables(variables->THREAD_variables);
                    variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({2});
                    variables->THREAD_variables->window0_state = 2; //if main thread was too slow, then here is protection;
                    variables->THREAD_variables->timeout0 = SDL_GetTicks();     // reset timer for refresh signal
                    variables->THREAD_variables->next_frame_timer = SDL_GetTicks(); //share_screen fps timer;
                    background.r = 255; background.g = 255; background.b = 255;
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": waiting for accept/reject the connection;\n",(char*)"waiting for accept/reject the connection;",(SDL_Color){0,0,0,0},background,0});
                    variables->THREAD_variables->active_thread = 0;
                    continue;
                }
            }
            if(variables->THREAD_variables->state_of_waiting_for_client==4)
            {
                SDL_Color background = {168,0,0,0};
                if(SDL_GetTicks()-variables->THREAD_variables->timeout0>=variables->THREAD_global_variables->inactive_timeout_in_ms)
                {
                    variables->THREAD_variables->state_of_waiting_for_client = 0;
                    //sending information to client about reached limit
                    uint8_t buffor0 = 128;
                    variables->THREAD_variables->server.send_to_client(&buffor0,1,&variables->THREAD_variables->server_structure);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"128 signal has been sended;\n",0,0});
                    #endif
                    buffor0 = 129;
                    variables->THREAD_variables->server.send_to_client(&buffor0,1,&variables->THREAD_variables->server_structure);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"129 signal has been sended;\n",0,0});
                    #endif
                    //reject client
                    variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                                      &variables->THREAD_variables->server_structure);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    char* debug_buffor = (char*)malloc(512);
                    sprintf(debug_buffor,"    connection failed: inactivity session timeout reached his limit: %zdms\n    your data wasn't sended to a client in complete piece: %dbytes sended from 76 needed;\n",variables->THREAD_global_variables->inactive_timeout_in_ms,76-how_much_data_is_needed_right_now);
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                    #endif
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": connection failed:\n",(char*)"connection failed:",(SDL_Color){255,255,255,0},background,0});
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   you wasn't able to send complete data;\n",(char*)"    you wasn't able to send complete data;",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                    variables->THREAD_variables->active_thread = 0;
                    continue;
                }
                error_status = variables->THREAD_variables->server.recv_from_client(buffor0_static+(76-how_much_data_is_needed_right_now),how_much_data_is_needed_right_now,&variables->THREAD_variables->server_structure);
                if(error_status!=-1) how_much_data_is_needed_right_now-=error_status;
                else if(WSAGetLastError()!=WSAEWOULDBLOCK) //disconnect from a client (server error);
                {
                    if(variables->THREAD_variables->do_server_is_destroying==1) //if "disconnect" event has been executed in the main program;
                    {
                        variables->THREAD_variables->do_server_is_destroying = 0;
                        this->reset_all_server_state_variables(variables->THREAD_variables);
                        variables->THREAD_variables->active_thread = 0;
                        continue;
                    }
                    error_status = WSAGetLastError();
                    variables->THREAD_variables->state_of_waiting_for_client = 0;
                    uint8_t buffor_code0 = 129;
                    variables->THREAD_variables->server.send_to_client(&buffor_code0,1,&variables->THREAD_variables->server_structure);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"129 signal has been sended;\n",0,0});
                    #endif
                    variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                                      &variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": connection failed;\n",(char*)"connection failed;",(SDL_Color){255,255,255,0},background,0});

                    printf_error_args("you've been failed to send data to client; winsock error: %d\n",error_status);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": you've been failed to send data to a client:\n",(char*)"you've been failed to send data to a client:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                    char* buffor0 = (char*)malloc(64);
                    sprintf(buffor0,"    winsock error: %d;",error_status);
                    char* buffor1 = (char*)malloc(64);
                    sprintf(buffor1,":   winsock error: %d;\n",error_status);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){255,0,0,0},{0,0,0,255},1});
                    variables->THREAD_variables->active_thread = 0;
                    continue;
                }
                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1&&error_status!=-1)  variables->THREAD_variables->diode_blue_counter = 1;

                if(how_much_data_is_needed_right_now==0) //if all data needed has been sended;
                {
                    char* buffor0 = (char*)malloc(64);
                    char* buffor1 = (char*)malloc(64);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    char* debug_buffor = (char*)malloc(1024);
                    sprintf(debug_buffor,
                           "    sended information to a client:\n"
                           "        max_shared_quality: %s\n"
                           "        max_shared_fps: %s\n"
                           "        screen_width: %s\n"
                           "        screen_height: %s\n"
                           "        max_shared_loss: %zd\n"
                           "        password_required: %s\n"
                           "        hash_activated: %s\n"
                           "        server_message0: %s\n"
                           "        server_message1: %s\n",
                           (const char*)variables->THREAD_variables->max_shared_quality,
                           (const char*)variables->THREAD_variables->max_shared_fps,
                           (const char*)variables->THREAD_variables->screen_width_share,
                           (const char*)variables->THREAD_variables->screen_height_share,
                           variables->THREAD_variables->max_shared_loss_int,
                           (const char*)variables->THREAD_variables->password_required,
                           (const char*)variables->THREAD_variables->activate_hash,
                           (const char*)variables->THREAD_variables->message0,
                           (const char*)variables->THREAD_variables->message1);
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                    #endif
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": successively sended data to a client;\n",(char*)"successively sended data to a client;",(SDL_Color){0,168,0,0},{0,0,0,255},0});
                    background.r = 0; background.g = 0; background.b = 168;
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sended information to a client:\n",(char*)"sended information to a client:",(SDL_Color){255,255,255,0},background,0});
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"    max_shared_fps: %s;",(const char*)variables->THREAD_variables->max_shared_fps);
                    sprintf(buffor1,":    max_shared_fps: %s;\n",(const char*)variables->THREAD_variables->max_shared_fps);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"    max_shared_quality: %s;",(const char*)variables->THREAD_variables->max_shared_quality);
                    sprintf(buffor1,":    max_shared_quality: %s;\n",(const char*)variables->THREAD_variables->max_shared_quality);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"    max_shared_loss: %s;",(const char*)variables->THREAD_variables->max_shared_loss);
                    sprintf(buffor1,":    max_shared_loss: %s;\n",(const char*)variables->THREAD_variables->max_shared_loss);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"    screen_width: %s;",(const char*)variables->THREAD_variables->screen_width_share);
                    sprintf(buffor1,":    screen_width: %s;\n",(const char*)variables->THREAD_variables->screen_width_share);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"    screen_height: %s;",(const char*)variables->THREAD_variables->screen_height_share);
                    sprintf(buffor1,":    screen_height: %s;\n",(const char*)variables->THREAD_variables->screen_height_share);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"    password_required: %s;",(const char*)variables->THREAD_variables->password_required);
                    sprintf(buffor1,":    password_required: %s;\n",(const char*)variables->THREAD_variables->password_required);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    buffor0 = (char*)malloc(64);
                    buffor1 = (char*)malloc(64);
                    sprintf(buffor0,"    hash_activated: %s;",(const char*)variables->THREAD_variables->activate_hash);
                    sprintf(buffor1,":    hash_activated: %s;\n",(const char*)variables->THREAD_variables->activate_hash);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                    if(variables->THREAD_variables->message0[0]!='\0'||variables->THREAD_variables->message1[0]!='\0')
                    {
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": your starting message to a client:\n",(char*)"your starting message to a client:",(SDL_Color){255,255,255,0},background,0});
                        if(variables->THREAD_variables->message0[0]!='\0')
                        {
                            buffor0 = (char*)malloc(64);
                            buffor1 = (char*)malloc(64);
                            sprintf(buffor0,"    %s",(const char*)variables->THREAD_variables->message0);
                            sprintf(buffor1,":    %s\n",(const char*)variables->THREAD_variables->message0);
                            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                        }
                        if(variables->THREAD_variables->message1[0]!='\0')
                        {
                            buffor0 = (char*)malloc(64);
                            buffor1 = (char*)malloc(64);
                            sprintf(buffor0,"    %s",(const char*)variables->THREAD_variables->message1);
                            sprintf(buffor1,":    %s\n",(const char*)variables->THREAD_variables->message1);
                            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                        }
                    }
                    this->reset_all_server_state_variables(variables->THREAD_variables);
                    variables->THREAD_variables->timeout0 = SDL_GetTicks();     // reset timer for refresh signal
                    variables->THREAD_variables->next_frame_timer = SDL_GetTicks(); //share_screen fps timer;
                    variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({2});
                    variables->THREAD_variables->window0_state = 2; //if main thread was too slow, then here is protection;
                    background.r = 255; background.g = 255; background.b = 255;
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": waiting for accept/reject the connection;\n",(char*)"waiting for accept/reject the connection;",(SDL_Color){0,0,0,0},background,0});
                    variables->THREAD_variables->active_thread = 0;
                    continue;
                }
            }
        }
        else if(variables->THREAD_variables->window0_state==2||variables->THREAD_variables->window0_state==3)
        {
            static char log_buffor0[64];
            static char log_buffor1[64];
            static SDL_Color background;
            //in this state you have to sends refresh signal to keep connection (to check if that's correct);
            //1. send to client;
            //2. receive from client;
            //3. refresh if nedded;

            if(SDL_GetTicks()-variables->THREAD_variables->timeout0>=variables->THREAD_global_variables->inactive_timeout_in_ms
               &&(variables->THREAD_variables->window0_state==2||variables->THREAD_variables->wait_for_client_request==1
                  ||(variables->THREAD_variables->window0_state==3&&variables->THREAD_variables->is_screen_sharing_paused==1)))
            {
                variables->THREAD_variables->server_operation[1] = 1;
            }


    //RECEIVE_FIRST_REQUEST_FROM_THE_CLIENT;
//=============================================================================
            //receive code from the client if exist;
            //code from here MUST HAVE PRIORITY TO NOT LOCK CLIENT; PRIORITIZE EVERYTHING THAT COMES FROM CLIENT FIRST;
            if(variables->THREAD_variables->is_server_busy==0)
            {
                error_status = variables->THREAD_variables->server.recv_from_client(buffor0_static,1,&variables->THREAD_variables->server_structure);
                if(error_status!=-1)
                {
                    SDL_Color main_color0;

                    if(variables->THREAD_variables->how_much_fps_pass_without_red_diode>=1)  variables->THREAD_variables->diode_red_counter = 2;

                    switch(buffor0_static[0])
                    {
                        case 2: //message sended from the client;
                            {
                                variables->THREAD_variables->priority_number = 137;
                                variables->THREAD_variables->server_operation[variables->THREAD_variables->priority_number] = 1;
                                variables->THREAD_variables->client_first_send_request = 1; //only receive;
                                main_color0.r = 168; main_color0.g = 168;
                                main_color0.b = 0; main_color0.a = 0;
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": received message from the client:\n",(char*)"received message from the client:",(SDL_Color){255,255,255,0},main_color0});
                            }
                        break;

                        case 3: //sended change of requested_fps from the client;
                            {
                                variables->THREAD_variables->priority_number = 136;
                                variables->THREAD_variables->server_operation[variables->THREAD_variables->priority_number] = 1;
                                variables->THREAD_variables->client_first_send_request = 2; //receive and send return code;
                                main_color0.r = 168; main_color0.g = 168;
                                main_color0.b = 0; main_color0.a = 0;
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": received request from the client:\n",(char*)"received request from the client:",(SDL_Color){255,255,255,0},main_color0});
                            }
                        break;

                        case 4: //sended change of requested_quality from the client;
                            {
                                variables->THREAD_variables->priority_number = 138;
                                variables->THREAD_variables->server_operation[variables->THREAD_variables->priority_number] = 1;
                                variables->THREAD_variables->client_first_send_request = 2; //receive and send return code;
                                main_color0.r = 168; main_color0.g = 168;
                                main_color0.b = 0; main_color0.a = 0;
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": received request from the client:\n",(char*)"received request from the client:",(SDL_Color){255,255,255,0},main_color0});
                            }
                        break;

                        case 5:
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"received disconnect signal from the client\n",0,0});
                                #endif
                                variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
                                variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
                                variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                                          &variables->THREAD_variables->server_structure);

                                main_color0.r = 168; main_color0.g = 168;
                                main_color0.b = 0; main_color0.a = 0;
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": received information from the client:\n",(char*)"received information from the client:",(SDL_Color){255,255,255,0},main_color0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":    client disconnected;\n",(char*)"    client disconnected;",(SDL_Color){168,0,0,0},{0,0,0,255},0});

                                if(variables->THREAD_variables->how_much_fps_pass_without_red_diode>=1)  variables->THREAD_variables->diode_red_counter = 2;

                                variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({1});
                                variables->THREAD_variables->window0_state = 1;
                                this->reset_all_server_state_variables(variables->THREAD_variables);
                                variables->THREAD_variables->active_thread = 0;
                                continue;
                            }
                        break;

                        case 6: //sended change of requested_quality from the client;
                            {
                                variables->THREAD_variables->priority_number = 142;
                                variables->THREAD_variables->server_operation[variables->THREAD_variables->priority_number] = 1;
                                variables->THREAD_variables->client_first_send_request = 2; //receive and send return code;
                                main_color0.r = 168; main_color0.g = 168;
                                main_color0.b = 0; main_color0.a = 0;
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":received request from the client:\n",(char*)"received request from the client:",(SDL_Color){255,255,255,0},main_color0});
                            }
                        break;

                        default:
                            {
                                if(variables->THREAD_variables->how_much_fps_pass_without_red_diode>=1)  variables->THREAD_variables->diode_red_counter = 2;
                                uint8_t buffor_code = 129;
                                variables->THREAD_variables->server.send_to_client(&buffor_code,1,&variables->THREAD_variables->server_structure);
                                #ifdef MAIN_PROGRAM0_DEBUG
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"129 signal has been sended;\n",0,0});
                                #endif
                                variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
                                variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
                                variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                                          &variables->THREAD_variables->server_structure);
                                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1)  variables->THREAD_variables->diode_blue_counter = 2;

                                background.r = 168; background.g = 0; background.b = 0; background.a = 0;
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": connection has been rejected;\n",(char*)"connection has been rejected;",(SDL_Color){255,255,255,0},background,0});

                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(126);
                                sprintf(debug_buffor,"wrong request sended from the client: %zd\n",buffor0_static[0]);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wrong code received from the client:\n",(char*)"wrong code received from the client:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                char* buffor0 = (char*)malloc(32);
                                char* buffor1 = (char*)malloc(32);
                                sprintf(buffor0,"    code: %zd;",buffor0_static[0]);
                                sprintf(buffor1,":    code: %zd;\n",buffor0_static[0]);
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                                variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({1});
                                variables->THREAD_variables->window0_state = 1;
                                this->reset_all_server_state_variables(variables->THREAD_variables);
                                variables->THREAD_variables->active_thread = 0;
                                continue;
                            }
                        break;

                    }
                }
                if(WSAGetLastError()!=WSAEWOULDBLOCK&&(error_status==0||error_status==-1)) //if there was connection error;
                {
                    if(variables->THREAD_variables->do_client_is_rejecting==1||variables->THREAD_variables->do_server_is_destroying==1) //if "reject" or "disconnect" event has been executed in the main program;
                    {
                        variables->THREAD_variables->do_client_is_rejecting = 0;
                        variables->THREAD_variables->do_server_is_destroying = 0;
                        this->reset_all_server_state_variables(variables->THREAD_variables);
                        variables->THREAD_variables->active_thread = 0;
                        continue;
                    }
                    error_status = WSAGetLastError();

                    uint8_t buffor_code = 129;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"129 signal has been sended;\n",0,0});
                    #endif
                    variables->THREAD_variables->server.send_to_client(&buffor_code,1,&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                              &variables->THREAD_variables->server_structure);

                    background.r = 168; background.g = 0; background.b = 0; background.a = 0;
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": connection has been lost;\n",(char*)"connection has been lost;",(SDL_Color){255,255,255,0},background,0});

                    if(variables->THREAD_variables->how_much_fps_pass_without_red_diode>=1)  variables->THREAD_variables->diode_red_counter = 2;

                    char* buffor0 = (char*)malloc(64);
                    sprintf(buffor0,"    winsock error: %d;",error_status);
                    char* buffor1 = (char*)malloc(64);
                    sprintf(buffor1,":   winsock error: %d;\n",error_status);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){255,0,0,0},{0,0,0,255},1});
                    variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({1});
                    variables->THREAD_variables->window0_state = 1;
                    this->reset_all_server_state_variables(variables->THREAD_variables);
                    variables->THREAD_variables->active_thread = 0;
                    continue;
                }
            }

            //server_operation[codes]:
        //  [0] - send message to a client; [127] receive
        //  [1] - send refresh; [128] receive
        //  [2] - send change max_fps [129] receive
        //  [3] - send change max_quality [130] receive
        //  [4] - send change screen_width [131] receive
        //  [5] - send change screen_height [132] receive
        //  [6] - send change hash_activate [133] receive
        //  [7] - send change hash_state [134] receive
        //  [8] - accept connection [135] receive
        //  [9] - send response to change of requested_fps from the client; comes from [136];
        //  [11] - send response to change of requested_quality from the client; comes from [138];
        //  [12] - send frame of your screen to the client; [139] receive;
        //  [13] - send pause status and/or pause image to the client; [140] receive;
        //  [14] - send change max_shared_loss [141] receive
        //  [15] - send response to change of requested_loss from the client; comes from [142]
        //  [128] - receive refresh response from client from operation_code; comes from [1]
        //  [136] - receive requested_fps from the client if was sended to you; send to [9] after all;
        //  [137] - receive message from the client if was sended to you;
        //  [138] - receive requested_quality from the client if was sended to you; send to [11] after all;
        //  [139] - receive response that confirmes that screen frame has been delivered; comes from [12];
        //  [140] - receive response that confirmes that pause image has been delivered; comes from [13];
        //  [142] - receive requested_loss from the client if was sended to you; send to [15] after all;

        //receive codes are always: 127+send_code
        //represented order of codes aren't for flex; if someone want to add for example to send code [6] receive request for client,
            //then u have place for this operation: [133]; 'cause send_code == 6, so receive_code == 127+send_code;

        //is_server_busy codes:
        //  codes+1;

        //printf("%zd\n",variables->THREAD_variables->server_operation[13]);

            if(((variables->THREAD_variables->is_server_busy==0)&&(variables->THREAD_variables->priority_number==-1)&&(variables->THREAD_variables->window0_state==3)
               &&(variables->THREAD_variables->wait_for_client_request==0))) //send frame/pause/unpause
            {
                static uint8_t help_data[5];

                if(variables->THREAD_variables->is_screen_sharing_paused==0&&variables->THREAD_variables->should_be_next_frame==1&&variables->THREAD_variables->server_operation[13]==0)
                {
                    variables->THREAD_variables->server_operation[12] = 1; //if there's not pause, then try send frame of screen;
                }
                if(variables->THREAD_variables->requested_loss==0) this->THREAD_BACKGROUND_send_data_to_client_tool1(variables,variables->THREAD_variables->main_frame_data,help_data);
                else this->THREAD_BACKGROUND_send_data_to_client_tool1(variables,variables->THREAD_variables->main_frame_data_jpeg,help_data);
                this->THREAD_BACKGROUND_receive_data_to_client_tool1(variables,buffor0_static,help_data);

                variables->THREAD_variables->server_operation[12] = 0;
            }

            if(variables->THREAD_variables->client_first_send_request!=0)
            {
                this->THREAD_receive_data_to_client_tool0(variables,log_buffor0,log_buffor1,buffor0_static);
                this->THREAD_send_data_to_client_tool0(variables,log_buffor0,log_buffor1,buffor0_static);

            }
            else
            {
                this->THREAD_send_data_to_client_tool0(variables,log_buffor0,log_buffor1,buffor0_static);
                this->THREAD_receive_data_to_client_tool0(variables,log_buffor0,log_buffor1,buffor0_static);
            }

        }

        variables->THREAD_variables->active_thread = 0;
        if(frame_data_is_to_delocate==1)
        {
            while(variables->THREAD_variables->frame_data_should_be_displaying==1) SDL_Delay(1);   //thread lock
            free(variables->THREAD_variables->main_frame_data);
            if(variables->THREAD_variables->operation_on_data_frame==1||variables->THREAD_variables->operation_on_data_frame==3)
            {
                tj3Free(variables->THREAD_variables->main_frame_data_jpeg);
            }
            frame_data_is_to_delocate = 0;
        }



    }

    return NULL;
}

    //SEND_BACKGROUND BLOCK
//========================================================================================================================================
void Server_Menu::THREAD_BACKGROUND_send_data_to_client_tool1(THREAD_server_menu_struct_variables* variables,const uint8_t* const data_pointer,uint8_t* function_help_data)
{
    static uint32_t needed_bytes_to_send_receive;
    static SDL_Color background;
    static int error_status;
    static uint32_t how_much_data_is_needed_right_now;
    static uint8_t* second_data_pointer;
    static uint8_t actual_code;

    if(variables->THREAD_variables->server_operation[13]==1) //send pause info and/or pause image
    {
        variables->THREAD_variables->active_thread = 0;
        actual_code = 13;
        variables->THREAD_variables->timeout0 = SDL_GetTicks();
        variables->THREAD_variables->is_server_busy = 14;

        uint32_t size_of_compressed_data;

        if(variables->THREAD_variables->is_screen_sharing_paused==1)
        {
            function_help_data[4] = 1;
            #ifdef MAIN_PROGRAM0_DEBUG
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're sending pause image;\n",0,0});
            #endif

            if(variables->THREAD_global_variables->universal_tool0->compare_data((uint8_t*)"blank",variables->THREAD_variables->pause_image_path,6)==0)
            {
                size_of_compressed_data = (64*64*4)+6;
                second_data_pointer = (uint8_t*)malloc(size_of_compressed_data);
                for(uint32_t i = 0; i!=size_of_compressed_data-6; i+=4)
                {
                    *(uint32_t*)((uint8_t*)second_data_pointer+6+i) = 0x00000000;
                }

            }
            else
            {
                uint32_t size_of_file = variables->THREAD_global_variables->universal_tool0->file_size((const char*)variables->THREAD_variables->pause_image_path);
                second_data_pointer = (uint8_t*)malloc(size_of_file+6);
                FILE* file = fopen((const char*)variables->THREAD_variables->pause_image_path,"rb");
                fread(second_data_pointer+6,size_of_file,1,file);
                fclose(file);
                size_of_compressed_data = size_of_file+6;
            }

            second_data_pointer[0] = 9;
            second_data_pointer[1] = 1;
            *(uint32_t*)((uint8_t*)second_data_pointer+2) = size_of_compressed_data-6;


            if(variables->THREAD_variables->activate_hash[0]=='y')
            {
                uint32_t hash_seed_counter = 0;
                uint8_t* hash_seed = (uint8_t*)malloc(257);
                variables->THREAD_global_variables->universal_tool0->memset_custom<uint8_t>(hash_seed,0,257);
                strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash0); strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash1);
                strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash2); strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash3);
                hash_seed_counter = variables->THREAD_global_variables->universal_tool0->count_string_chars((const char*)hash_seed);
                variables->THREAD_global_variables->universal_tool0->hash0_32bit(second_data_pointer+6,hash_seed,size_of_compressed_data-6,hash_seed_counter);
                free(hash_seed);
            }


            #ifdef MAIN_PROGRAM0_DEBUG
            char* debug_buffor = (char*)malloc(128);
            sprintf(debug_buffor,"size of pause image array pixel = %zdB\n",size_of_compressed_data-6);
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
            #endif

            *(uint32_t*)function_help_data = size_of_compressed_data; //for receive purpose; this value will be used in receive function to check if client received full data;
        }
        else
        {
            function_help_data[4] = 0;
            #ifdef MAIN_PROGRAM0_DEBUG
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're sending pause info;\n",0,0});
            #endif
            second_data_pointer = (uint8_t*)malloc(2);
            second_data_pointer[0] = 9;
            second_data_pointer[1] = 0;
            size_of_compressed_data = 2;
        }

        needed_bytes_to_send_receive = size_of_compressed_data;
        how_much_data_is_needed_right_now = needed_bytes_to_send_receive;


    }
    else if(variables->THREAD_variables->server_operation[12]==1) //send frame (this must be checked at the end cause this variable is always selected)
    {
        variables->THREAD_variables->active_thread = 0;
        actual_code = 12;
        variables->THREAD_variables->timeout0 = SDL_GetTicks();
        variables->THREAD_variables->is_server_busy = 13;
        variables->THREAD_variables->should_be_next_frame = 0;

        #ifdef MAIN_PROGRAM0_DEBUG
        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're sending frame of your screen;\n",0,0});
        #endif


        uint32_t size_of_compressed_data;

        if(variables->THREAD_variables->operation_on_data_frame==2) //no compression;
        {

            uint32_t size_of_raw_data = variables->THREAD_variables->width_of_actual_frame*variables->THREAD_variables->height_of_actual_frame*3;

            //(SIZEOF(data_in)+(SIZEOF(data_in)/3)) == max size of compressed data;
            second_data_pointer = (uint8_t*)malloc(size_of_raw_data+(size_of_raw_data/3)+11);
            size_of_compressed_data = variables->THREAD_global_variables->universal_tool0->compress_per3bytes_rgb_data(data_pointer,second_data_pointer+11,size_of_raw_data);
            #ifdef MAIN_PROGRAM0_DEBUG
            char* debug_buffor = (char*)malloc(128);
            sprintf(debug_buffor,"size of compressed data throught custom method = %zdB\n",size_of_compressed_data);
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
            #endif

        }
        else                                                        //with compression;
        {
            second_data_pointer = (uint8_t*)malloc(variables->THREAD_variables->size_of_main_frame_data_jpeg+11);
            memcpy(second_data_pointer+11,data_pointer,variables->THREAD_variables->size_of_main_frame_data_jpeg);
            size_of_compressed_data = variables->THREAD_variables->size_of_main_frame_data_jpeg;
            #ifdef MAIN_PROGRAM0_DEBUG
            char* debug_buffor = (char*)malloc(128);
            sprintf(debug_buffor,"size of compressed data throught jpeg method = %zdB\n",variables->THREAD_variables->size_of_main_frame_data_jpeg);
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
            #endif
        }
        second_data_pointer[0] = 10;
        *((uint32_t*)((uint8_t*)second_data_pointer+1)) = size_of_compressed_data; //size_of_compressed_pixel_array_without_first_5_bytes
        *((uint16_t*)((uint8_t*)second_data_pointer+5)) = variables->THREAD_variables->width_of_actual_frame;
        *((uint16_t*)((uint8_t*)second_data_pointer+7)) = variables->THREAD_variables->height_of_actual_frame;
        *((uint8_t*)((uint8_t*)second_data_pointer+9)) = variables->THREAD_variables->quality_of_actual_frame;
        *((uint8_t*)((uint8_t*)second_data_pointer+10)) = variables->THREAD_variables->hash_active_of_actual_frame;
        size_of_compressed_data+=11;

        needed_bytes_to_send_receive = size_of_compressed_data;
        how_much_data_is_needed_right_now = needed_bytes_to_send_receive;

        *(uint32_t*)function_help_data = size_of_compressed_data; //for receive purpose; this value will be used in receive function to check if client received full data;

        if(variables->THREAD_variables->activate_hash[0]=='y')
        {
            uint32_t hash_seed_counter = 0;
            uint8_t* hash_seed = (uint8_t*)malloc(257);
            variables->THREAD_global_variables->universal_tool0->memset_custom<uint8_t>(hash_seed,0,257);
            strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash0); strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash1);
            strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash2); strcat((char*)hash_seed,(const char*)variables->THREAD_variables->hash3);
            hash_seed_counter = variables->THREAD_global_variables->universal_tool0->count_string_chars((const char*)hash_seed);
            variables->THREAD_global_variables->universal_tool0->hash0_32bit(second_data_pointer+11,hash_seed,size_of_compressed_data-11,hash_seed_counter);
            free(hash_seed);
        }


    }
    else return;

    static uint32_t failed_attempts;
    failed_attempts = 0;
    for(;;)
    {
        if(SDL_GetTicks()-variables->THREAD_variables->timeout0>=variables->THREAD_global_variables->inactive_timeout_in_ms) //sending information to client about reached limit;
        {
            uint8_t buffor_code = 128;
            variables->THREAD_variables->server.send_to_client(&buffor_code,1,&variables->THREAD_variables->server_structure);
            #ifdef MAIN_PROGRAM0_DEBUG
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"128 signal has been sended; | THREAD_BACKGROUND_send_data_to_client_tool1\n",0,0});
            #endif
            buffor_code = 129;
            variables->THREAD_variables->server.send_to_client(&buffor_code,1,&variables->THREAD_variables->server_structure);
            #ifdef MAIN_PROGRAM0_DEBUG
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"129 signal has been sended; | THREAD_BACKGROUND_send_data_to_client_tool1\n",0,0});
            #endif
            variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
            variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
            variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                      &variables->THREAD_variables->server_structure);

            background.r = 168; background.g = 0; background.b = 0; background.a = 0;
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": connection has been rejected;\n",(char*)"connection has been rejected;",(SDL_Color){255,255,255,0},background,0});
            #ifdef MAIN_PROGRAM0_DEBUG
            char* debug_buffor = (char*)malloc(512);
            sprintf(debug_buffor,"    sending data error: inactivity session timeout reached his limit: %zdms\n    data from the server wasn't sended in complete piece: %dbytes received from %zd needed;\n",
            variables->THREAD_global_variables->inactive_timeout_in_ms,needed_bytes_to_send_receive-how_much_data_is_needed_right_now,needed_bytes_to_send_receive);
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
            #endif

            if(actual_code==13)
            {
                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1)  variables->THREAD_variables->diode_blue_counter = 2;
                if(variables->THREAD_variables->is_screen_sharing_paused==1)
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to send pause image:\n",(char*)"wasn't able to send pause image:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                }
                else variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to send pause info:\n",(char*)"wasn't able to send pause info:",(SDL_Color){168,0,0,0},{0,0,0,255},0});

                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
            }
            else if(actual_code==12)
            {
                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1)  variables->THREAD_variables->diode_blue_counter = 2;
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to send screen frame:\n",(char*)"wasn't able to send screen frame:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
            }

            variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({1});
            variables->THREAD_variables->window0_state = 1;
            this->reset_all_server_state_variables(variables->THREAD_variables);
            variables->THREAD_variables->active_thread = 0;
            free(second_data_pointer);
            return;
        }
        error_status = variables->THREAD_variables->server.send_to_client(second_data_pointer+(needed_bytes_to_send_receive-how_much_data_is_needed_right_now),how_much_data_is_needed_right_now,&variables->THREAD_variables->server_structure);
        if(error_status!=-1) how_much_data_is_needed_right_now-=error_status;
        if(WSAGetLastError()!=WSAEWOULDBLOCK&&error_status==-1) //if there was connection error;
        {
            if(variables->THREAD_variables->do_client_is_rejecting==1||variables->THREAD_variables->do_server_is_destroying==1) //if "reject" or "disconnect" event has been executed in the main program;
            {
                variables->THREAD_variables->do_client_is_rejecting = 0;
                variables->THREAD_variables->do_server_is_destroying = 0;
                this->reset_all_server_state_variables(variables->THREAD_variables);
                variables->THREAD_variables->active_thread = 0;
                return;
            }
            error_status = WSAGetLastError();

            uint8_t buffor_code = 129;
            variables->THREAD_variables->server.send_to_client(&buffor_code,1,&variables->THREAD_variables->server_structure);
            #ifdef MAIN_PROGRAM0_DEBUG
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"129 signal has been sended; | THREAD_BACKGROUND_send_data_to_client_tool1\n",0,0});
            #endif
            variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
            variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
            variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                      &variables->THREAD_variables->server_structure);

            background.r = 168; background.g = 0; background.b = 0; background.a = 0;
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": connection has been lost;\n",(char*)"connection has been lost;",(SDL_Color){255,255,255,0},background,0});

            if(actual_code==13)
            {
                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1)  variables->THREAD_variables->diode_blue_counter = 2;
                #ifdef MAIN_PROGRAM0_DEBUG
                char* debug_buffor = (char*)malloc(128);
                sprintf(debug_buffor,"you've been failed to send frame to the client; winsock error: %d\n",error_status);
                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                #endif
                if(variables->THREAD_variables->is_screen_sharing_paused==1)
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sending pause image failed:\n",(char*)"sending pause image failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                }
                else variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sending pause info failed:\n",(char*)"sending pause info failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
            }
            else if(actual_code==12)
            {
                    if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1)  variables->THREAD_variables->diode_blue_counter = 2;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    char* debug_buffor = (char*)malloc(128);
                    sprintf(debug_buffor,"you've been failed to send frame to the client; winsock error: %d\n",error_status);
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                    #endif
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sending screen frame failed:\n",(char*)"sending screen frame failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
            }


            char* buffor0 = (char*)malloc(64);
            sprintf(buffor0,"    winsock error: %d;",error_status);
            char* buffor1 = (char*)malloc(64);
            sprintf(buffor1,":   winsock error: %d;\n",error_status);
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){255,0,0,0},{0,0,0,255},1});
            variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({1});
            variables->THREAD_variables->window0_state = 1;
            this->reset_all_server_state_variables(variables->THREAD_variables);
            variables->THREAD_variables->active_thread = 0;
            free(second_data_pointer);
            return;
        }

        if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1&&error_status!=-1)
        {
            variables->THREAD_variables->diode_blue_counter = 1;
        }

        if(failed_attempts==50)
        {
            if(error_status==-1) SDL_Delay(1); //this line may slow down screen sharing (to check); but for sure it 'causing low using of processor when there is some problem to send/receive data;
            variables->THREAD_variables->active_thread = 0; //fixes freezing bug from window0;
        }
        else failed_attempts++;

        if(how_much_data_is_needed_right_now==0) break; //if all data needed has been sended;
    }

    if(actual_code==13)
    {
        variables->THREAD_variables->server_operation[13] = 0;
        variables->THREAD_variables->server_operation[140] = 1;
        #ifdef MAIN_PROGRAM0_DEBUG
        if(variables->THREAD_variables->is_screen_sharing_paused==1) variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"pause image sended\n",0,0});
        else variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"pause info sended\n",0,0});
        #endif
    }
    else if(actual_code==12)
    {
        variables->THREAD_variables->server_operation[12] = 0;
        #ifdef MAIN_PROGRAM0_DEBUG
        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"frame of the screen sended\n",0,0});
        #endif
        variables->THREAD_variables->server_operation[139] = 1;  //frame send response;
    }


    variables->THREAD_variables->timeout0 = SDL_GetTicks();
    variables->THREAD_variables->is_server_busy = 0;
    free(second_data_pointer);

    return;
}

    //RECEIVE_BACKGROUND BLOCK
//========================================================================================================================================
void Server_Menu::THREAD_BACKGROUND_receive_data_to_client_tool1(THREAD_server_menu_struct_variables* variables,uint8_t* data_pointer,uint8_t* function_help_data)
{
    static uint32_t needed_bytes_to_send_receive;
    static SDL_Color background;
    static int error_status;
    static uint32_t how_much_data_is_needed_right_now;
    static uint8_t actual_code;

    if(variables->THREAD_variables->server_operation[140]==1) //send pause info and/or pause image
    {
        variables->THREAD_variables->active_thread = 0;
        actual_code = 140;
        variables->THREAD_variables->timeout0 = SDL_GetTicks();
        variables->THREAD_variables->is_server_busy = 141;

        needed_bytes_to_send_receive = 4;
        how_much_data_is_needed_right_now = needed_bytes_to_send_receive;

        #ifdef MAIN_PROGRAM0_DEBUG
        if(variables->THREAD_variables->is_screen_sharing_paused==1) variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're waiting for confirmation of pause image\n",0,0});
        else variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're waiting for confirmation of pause info;\n",0,0});
        #endif

    }
    else if(variables->THREAD_variables->server_operation[139]==1)
    {
        variables->THREAD_variables->active_thread = 0;
        actual_code = 139;
        variables->THREAD_variables->timeout0 = SDL_GetTicks();
        variables->THREAD_variables->is_server_busy = 140;

        #ifdef MAIN_PROGRAM0_DEBUG
        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're waiting for confirmation of sended frame;\n",0,0});
        #endif

        needed_bytes_to_send_receive = 5;
        how_much_data_is_needed_right_now = needed_bytes_to_send_receive;

    }
    else return;

    static uint32_t failed_attempts;
    failed_attempts = 0;
    for(;;)
    {
        if(SDL_GetTicks()-variables->THREAD_variables->timeout0>=variables->THREAD_global_variables->inactive_timeout_in_ms) //sending information to client about reached limit;
        {
            uint8_t buffor_code = 128;
            variables->THREAD_variables->server.send_to_client(&buffor_code,1,&variables->THREAD_variables->server_structure);
            #ifdef MAIN_PROGRAM0_DEBUG
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"128 signal has been sended; | THREAD_BACKGROUND_receive_data_to_client_tool1\n",0,0});
            #endif
            buffor_code = 129;
            variables->THREAD_variables->server.send_to_client(&buffor_code,1,&variables->THREAD_variables->server_structure);
            #ifdef MAIN_PROGRAM0_DEBUG
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"129 signal has been sended; | THREAD_BACKGROUND_receive_data_to_client_tool1\n",0,0});
            #endif
            variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
            variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
            variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                      &variables->THREAD_variables->server_structure);

            background.r = 168; background.g = 0; background.b = 0; background.a = 0;
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": connection has been lost;\n",(char*)"connection has been lost;",(SDL_Color){255,255,255,0},background,0});

            #ifdef MAIN_PROGRAM0_DEBUG
            char* debug_buffor = (char*)malloc(512);
            sprintf(debug_buffor,"    receiving data error: inactivity session timeout reached his limit: %zdms\n    data from the server wasn't sended in complete piece: %dbytes received from %zd needed;\n",
            variables->THREAD_global_variables->inactive_timeout_in_ms,needed_bytes_to_send_receive-how_much_data_is_needed_right_now,needed_bytes_to_send_receive);
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
            #endif

            if(actual_code==140)
            {
                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1)  variables->THREAD_variables->diode_blue_counter = 2;
                if(function_help_data[4]==1) variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to receive pause img response:\n",(char*)"wasn't able to receive pause img response:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                else variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to receive pause inf response:\n",(char*)"wasn't able to receive pause info response:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
            }
            else if(actual_code==139)
            {
                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1)  variables->THREAD_variables->diode_blue_counter = 2;
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to receive screen frame response:\n",(char*)"wasn't able to receive screen frame response:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
            }

            variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({1});
            variables->THREAD_variables->window0_state = 1;
            this->reset_all_server_state_variables(variables->THREAD_variables);
            variables->THREAD_variables->active_thread = 0;
            return;
        }
        error_status = variables->THREAD_variables->server.recv_from_client(data_pointer+(needed_bytes_to_send_receive-how_much_data_is_needed_right_now),how_much_data_is_needed_right_now,&variables->THREAD_variables->server_structure);
        if(error_status!=-1) {how_much_data_is_needed_right_now-=error_status; }
        if(WSAGetLastError()!=WSAEWOULDBLOCK&&(error_status==0||error_status==-1)) //if there was connection error;
        {
            if(variables->THREAD_variables->do_client_is_rejecting==1||variables->THREAD_variables->do_server_is_destroying==1) //if "reject" or "disconnect" event has been executed in the main program;
            {
                variables->THREAD_variables->do_client_is_rejecting = 0;
                variables->THREAD_variables->do_server_is_destroying = 0;
                this->reset_all_server_state_variables(variables->THREAD_variables);
                variables->THREAD_variables->active_thread = 0;
                return;
            }
            error_status = WSAGetLastError();

            uint8_t buffor_code = 129;
            variables->THREAD_variables->server.send_to_client(&buffor_code,1,&variables->THREAD_variables->server_structure);
            #ifdef MAIN_PROGRAM0_DEBUG
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"128 signal has been sended; | THREAD_BACKGROUND_receive_data_to_client_tool1\n",0,0});
            #endif
            variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
            variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
            variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                      &variables->THREAD_variables->server_structure);

            background.r = 168; background.g = 0; background.b = 0; background.a = 0;
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": connection has been lost;\n",(char*)"connection has been lost;",(SDL_Color){255,255,255,0},background,0});

            if(actual_code==140)
            {
                    if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1)  variables->THREAD_variables->diode_blue_counter = 2;
                    if(function_help_data[4]==1)
                    {
                        #ifdef MAIN_PROGRAM0_DEBUG
                        char* debug_buffor = (char*)malloc(256);
                        sprintf(debug_buffor,"you've been failed to receive pause image response from the client; winsock error: %d\n",error_status);
                        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                        #endif
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": receiving pause image response failed:\n",(char*)"receiving pause image response failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                    }
                    else
                    {
                        #ifdef MAIN_PROGRAM0_DEBUG
                        char* debug_buffor = (char*)malloc(256);
                        sprintf(debug_buffor,"you've been failed to receive pause info response from the client; winsock error: %d\n",error_status);
                        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                        #endif
                        variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": receiving pause info response failed:\n",(char*)"receiving pause info response failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                    }

            }
            else if(actual_code==139)
            {
                    if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1)  variables->THREAD_variables->diode_blue_counter = 2;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    char* debug_buffor = (char*)malloc(256);
                    sprintf(debug_buffor,"you've been failed to receive screen frame response from the client; winsock error: %d\n",error_status);
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                    #endif
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": receiving screen frame response failed:\n",(char*)"receiving screen frame response failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
            }


            char* buffor0 = (char*)malloc(64);
            sprintf(buffor0,"    winsock error: %d;",error_status);
            char* buffor1 = (char*)malloc(64);
            sprintf(buffor1,":   winsock error: %d;\n",error_status);
            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){255,0,0,0},{0,0,0,255},1});
            variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({1});
            variables->THREAD_variables->window0_state = 1;
            this->reset_all_server_state_variables(variables->THREAD_variables);
            variables->THREAD_variables->active_thread = 0;
            return;
        }

        if(variables->THREAD_variables->how_much_fps_pass_without_red_diode>=1&&error_status>0)
        {
            variables->THREAD_variables->diode_red_counter = 1;
        }

        if(failed_attempts==50)
        {
            if(error_status==-1) SDL_Delay(1); //this line may slow down screen sharing (to check); but for sure it 'causing low using of processor when there is some problem to send/receive data;
            variables->THREAD_variables->active_thread = 0; //fixes freezing bug from window0;
        }
        else failed_attempts++;

        if(how_much_data_is_needed_right_now==0) break; //if all data needed has been sended;
    }

    if(actual_code==140)
    {
        variables->THREAD_variables->server_operation[140] = 0;

        #ifdef MAIN_PROGRAM0_DEBUG
        if(function_help_data[4]==1) //if pause
        {
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"response from sended pause image received\n",0,0});

            if(*(uint32_t*)((uint8_t*)function_help_data)!=*(uint32_t*)((uint8_t*)data_pointer)) //if client doesn't received full frame;
            {
                char* debug_buffor = (char*)malloc(256);
                sprintf(debug_buffor,"client doesn't receive full data:\nclient should receive: %zd\nclient received: %zd\n",*(uint32_t*)((uint8_t*)function_help_data),*(uint32_t*)((uint8_t*)data_pointer));
                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});

            }
        }
        else
        {
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"response from sended pause info received\n",0,0});
        }
        #endif
    }
    else if(actual_code==139)
    {
        variables->THREAD_variables->server_operation[139] = 0;
        #ifdef MAIN_PROGRAM0_DEBUG
        variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"response from sended frame received\n",0,0});

        if(*(uint32_t*)((uint8_t*)function_help_data)!=*(uint32_t*)((uint8_t*)data_pointer)) //if client doesn't received full frame;
        {
            char* debug_buffor = (char*)malloc(256);
            sprintf(debug_buffor,"client doesn't receive full data:\nclient should receive: %zd\nclient received: %zd\n",*(uint32_t*)((uint8_t*)function_help_data),*(uint32_t*)((uint8_t*)data_pointer));
            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});

        }
        #endif
        if(*(uint8_t*)((uint8_t*)data_pointer+4)==1) variables->THREAD_variables->wait_for_client_request = 1;

    }

    variables->THREAD_variables->timeout0 = SDL_GetTicks();
    variables->THREAD_variables->is_server_busy = 0;

    return;
}

void Server_Menu::THREAD_send_data_to_client_tool0(THREAD_server_menu_struct_variables* variables,char* log_buffor0,char* log_buffor1,uint8_t* buffor0_static)
{
    static int32_t needed_bytes_to_send_receive;
    static SDL_Color background;
    static uint8_t* pointer_to_existing_data;
    static int error_status;
    static uint32_t how_much_data_is_needed_right_now;

    //SEND
//========================================================================================================================================
    for(int counter0 = 0; counter0!=variables->THREAD_variables->SIZE_OF_OPERATION_ARRAY-128+1; counter0++)
    {
        if(variables->THREAD_variables->server_operation[counter0]==1&&(variables->THREAD_variables->is_server_busy==counter0+1||variables->THREAD_variables->is_server_busy==0)) //variables->THREAD_variables->is_server_busy==0 means that server isn't busy;
        {
            if(variables->THREAD_variables->state_of_waiting_for_client==0)
            {
                if(variables->THREAD_variables->priority_number!=-1&&variables->THREAD_variables->priority_number!=counter0) continue;
                variables->THREAD_variables->is_server_busy = counter0+1;
                switch(counter0) //server_operation code
                {
                    case 0: //sending message
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're sending message now;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 67;
                            variables->THREAD_global_variables->universal_tool0->memset_custom(buffor0_static,'\0',67);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char(": failed to send full message to the client;\n",log_buffor0);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char("failed to send full message to the client;",log_buffor1);

                            buffor0_static[0] = 2;
                            for(int i = 0; variables->THREAD_variables->message0[i]!='\0'; i++) buffor0_static[i+1] = variables->THREAD_variables->message0[i];
                            for(int i = 0; variables->THREAD_variables->message1[i]!='\0'; i++) buffor0_static[i+34] = variables->THREAD_variables->message1[i];

                            pointer_to_existing_data = buffor0_static; //128 size;
                        }
                    break;

                    case 1: //sending refresh signal
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're sending refresh signal now;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 1;
                            buffor0_static[0] = 100;
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char(": failed to send refresh signal;\n",log_buffor0);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char("failed to send refresh signal;",log_buffor1);

                            pointer_to_existing_data = buffor0_static; //128 size;
                        }
                    break;

                    case 2: //change max fps;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're sending new value of max_fps now;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 3;
                            buffor0_static[0] = 3;
                            *(uint16_t*)(buffor0_static+1) = variables->THREAD_global_variables->universal_tool0->string_to_int32((const char*)variables->THREAD_variables->max_shared_fps);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char(": failed to send max_fps variable;\n",log_buffor0);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char("failed to send max_fps variable;",log_buffor1);

                            pointer_to_existing_data = buffor0_static; //128 size;
                        }
                    break;

                    case 3: //change max quality;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're sending new value of max_quality now;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 2;
                            buffor0_static[0] = 4;
                            *(uint8_t*)(buffor0_static+1) = variables->THREAD_global_variables->universal_tool0->string_to_int32((const char*)variables->THREAD_variables->max_shared_quality);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char(": failed to send max_quality variable;\n",log_buffor0);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char("failed to send max_quality variable;",log_buffor1);

                            pointer_to_existing_data = buffor0_static; //128 size;
                        }break;

                    case 4: //change screen_width
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're sending new value of screen_width now;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 3;
                            buffor0_static[0] = 5;
                            *(uint16_t*)(buffor0_static+1) = variables->THREAD_global_variables->universal_tool0->string_to_int32((const char*)variables->THREAD_variables->screen_width_share);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char(": failed to send screen_width variable;\n",log_buffor0);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char("failed to send screen_width variable;",log_buffor1);

                            pointer_to_existing_data = buffor0_static; //128 size;
                        }break;

                    case 5: //change screen_height
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're sending new value of screen_height now;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 3;
                            buffor0_static[0] = 6;
                            *(uint16_t*)(buffor0_static+1) = variables->THREAD_global_variables->universal_tool0->string_to_int32((const char*)variables->THREAD_variables->screen_height_share);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char(": failed to send screen_height variable;\n",log_buffor0);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char("failed to send screen_height variable;",log_buffor1);

                            pointer_to_existing_data = buffor0_static; //128 size;
                        }break;

                    case 6: //change hash_activate
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're sending new value of hash_activate now;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 2;
                            buffor0_static[0] = 7;
                            *(uint8_t*)(buffor0_static+1) = (variables->THREAD_variables->activate_hash[0]=='y') ? 1 : 0;
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char(": failed to send hash_activate variable;\n",log_buffor0);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char("failed to send hash_activate variable;",log_buffor1);

                            pointer_to_existing_data = buffor0_static; //128 size;
                        }break;

                    case 7: //change hash state
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're sending information about changed hash now;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 1;
                            buffor0_static[0] = 8;
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char(": failed to send hash information;\n",log_buffor0);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char("failed to send hash information;",log_buffor1);

                            pointer_to_existing_data = buffor0_static; //128 size;
                        }break;

                        case 8: //connection accepted
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're accepting connection with the client now;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 2;
                            buffor0_static[0] = 1; buffor0_static[1] = 1;
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char(": failed to accept connection;\n",log_buffor0);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char("failed to accept connection;",log_buffor1);

                            pointer_to_existing_data = buffor0_static; //128 size;
                        }break;

                        case 9: //send response to requested_fps
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're sending response to requested_fps to the client now;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 1;
                            buffor0_static[0] = variables->THREAD_variables->buffor_to_response_code;
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char(": failed to send requested_fps response;\n",log_buffor0);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char("failed to send requested_fps response;",log_buffor1);

                            pointer_to_existing_data = buffor0_static; //128 size;
                        }break;

                        case 11: //send response to requested_quality
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're sending response to requested_quality to the client now;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 1;
                            buffor0_static[0] = variables->THREAD_variables->buffor_to_response_code;
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char(": failed to send requested_quality response;\n",log_buffor0);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char("failed to send requested_quality response;",log_buffor1);

                            pointer_to_existing_data = buffor0_static; //128 size;
                        }break;

                        case 14: //change max_shared_loss
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're sending new value of max_shared_loss now;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 2;
                            buffor0_static[0] = 11;
                            *(uint8_t*)(buffor0_static+1) = variables->THREAD_variables->max_shared_loss_int;
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char(": failed to send max_loss variable;\n",log_buffor0);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char("failed to send max_loss variable;",log_buffor1);

                            pointer_to_existing_data = buffor0_static; //128 size;
                        }break;

                        case 15: //send response to requested_loss
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're sending response to requested_loss to the client now;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 1;
                            buffor0_static[0] = variables->THREAD_variables->buffor_to_response_code;
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char(": failed to send requested_loss response;\n",log_buffor0);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char("failed to send requested_loss response;",log_buffor1);

                            pointer_to_existing_data = buffor0_static; //128 size;
                        }break;


                    default: variables->THREAD_variables->is_server_busy = 0; return;
                }


                error_status = variables->THREAD_variables->server.send_to_client(pointer_to_existing_data,needed_bytes_to_send_receive,&variables->THREAD_variables->server_structure);
                if(error_status!=needed_bytes_to_send_receive) //if data wasn't sended in one piece;
                {
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){log_buffor0,log_buffor1,(SDL_Color){168,0,0,0},{0,0,0,255},1});
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":    retries are performed\n",(char*)"    retries are performed;",(SDL_Color){0,0,0,0},{0,0,0,255},0});
                    if(error_status!=-1)
                    {
                        variables->THREAD_variables->diode_blue_counter = 2;
                        how_much_data_is_needed_right_now = needed_bytes_to_send_receive-error_status;
                    }
                    else
                    {
                        variables->THREAD_variables->diode_blue_counter = 0;
                        how_much_data_is_needed_right_now = needed_bytes_to_send_receive;
                    }

                    variables->THREAD_variables->state_of_waiting_for_client = 1;
                    variables->THREAD_variables->timeout0 = SDL_GetTicks();
                }
                else variables->THREAD_variables->state_of_waiting_for_client = 2; //if all data needed has been sended;
            }
            if(variables->THREAD_variables->state_of_waiting_for_client==1) //if data wasn't send in one piece;
            {
                background.r = 168; background.g = 0; background.b = 0; background.a = 0;

                if(SDL_GetTicks()-variables->THREAD_variables->timeout0>=variables->THREAD_global_variables->inactive_timeout_in_ms) //sending information to client about reached limit
                {
                    uint8_t buffor_code = 128;
                    variables->THREAD_variables->server.send_to_client(&buffor_code,1,&variables->THREAD_variables->server_structure);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"128 signal has been sended; | THREAD_send_data_to_client_tool0\n",0,0});
                    #endif
                    buffor_code = 129;
                    variables->THREAD_variables->server.send_to_client(&buffor_code,1,&variables->THREAD_variables->server_structure);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"129 signal has been sended; | THREAD_send_data_to_client_tool0\n",0,0});
                    #endif
                    variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                              &variables->THREAD_variables->server_structure);

                    background.r = 168; background.g = 0; background.b = 0; background.a = 0;
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": connection has been lost;\n",(char*)"connection has been lost;",(SDL_Color){255,255,255,0},background,0});

                    #ifdef MAIN_PROGRAM0_DEBUG
                    char* debug_buffor = (char*)malloc(512);
                    sprintf(debug_buffor,"    sending data failed: inactivity session timeout reached his limit: %zdms\n    your data wasn't sended to a client in complete piece: %dbytes sended from %d needed;\n",
                    variables->THREAD_global_variables->inactive_timeout_in_ms,needed_bytes_to_send_receive-how_much_data_is_needed_right_now,needed_bytes_to_send_receive);
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                    #endif

                    if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1)  variables->THREAD_variables->diode_blue_counter = 2;

                    switch(counter0)
                    {
                        case 0:  //sending message
                            {
                                //
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to send complete message:\n",(char*)"wasn't able to send complete message:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                                //
                            }
                        break;

                        case 1: //sending refresh signal
                            {
                                //
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to send refresh signal:\n",(char*)"wasn't able to send refresh signal:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                                //
                            }
                        break;


                        case 2: //change max fps;
                            {
                                //
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to send new max_fps:\n",(char*)"wasn't able to send new max_fps:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                                //
                            }
                        break;

                        case 3: //change max quality;
                            {
                                //
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to send new max_quality:\n",(char*)"wasn't able to send new max_quality:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                                //
                            }
                        break;

                        case 4: //change screen_width
                            {
                                //
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to send new screen_width:\n",(char*)"wasn't able to send new screen_width:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                                //
                            }
                        break;

                        case 5: //change screen_height
                            {
                                //
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to send new screen_height:\n",(char*)"wasn't able to send new screen_height:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                                //
                            }
                        break;

                        case 6: //change hash_activate
                            {
                                //
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to send new hash_activate:\n",(char*)"wasn't able to send new hash_activate:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                                //
                            }
                        break;

                        case 7: //change hash state
                            {
                                //
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to send hash information:\n",(char*)"wasn't able to send hash information:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                                //
                            }
                        break;

                        case 8: //accept connection with the client;
                            {
                                //
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to accept connection:\n",(char*)"wasn't able to accept connection:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                                //
                            }
                        break;

                        case 9: //send response to requested_fps
                            {
                                //
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to send requested response:\n",(char*)"wasn't able to send requested response:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                                //
                            }
                        break;

                        case 11: //send response to requested_quality
                            {
                                //
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to send requested response:\n",(char*)"wasn't able to send requested response:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                                //
                            }
                        break;

                        case 14: //send new value of mas_shared_loss
                            {
                                //
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to send new max_loss:\n",(char*)"wasn't able to send new max_loss:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                                //
                            }
                        break;

                        case 15: //send response to requested_loss
                            {
                                //
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": wasn't able to send requested response:\n",(char*)"wasn't able to send requested response:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                                //
                            }
                        break;


                        default: break;
                    }

                    variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({1});
                    variables->THREAD_variables->window0_state = 1;
                    this->reset_all_server_state_variables(variables->THREAD_variables);
                    variables->THREAD_variables->client_first_send_request = 0;
                    variables->THREAD_variables->active_thread = 0;
                    break;
                }
                error_status = variables->THREAD_variables->server.send_to_client(pointer_to_existing_data+(needed_bytes_to_send_receive-how_much_data_is_needed_right_now),how_much_data_is_needed_right_now,&variables->THREAD_variables->server_structure);
                if(error_status!=-1) how_much_data_is_needed_right_now-=error_status;
                if(WSAGetLastError()!=WSAEWOULDBLOCK&&error_status==-1) //if there was connection error;
                {
                    if(variables->THREAD_variables->do_client_is_rejecting==1||variables->THREAD_variables->do_server_is_destroying==1) //if "reject" or "disconnect" event has been executed in the main program;
                    {
                        variables->THREAD_variables->do_client_is_rejecting = 0;
                        variables->THREAD_variables->do_server_is_destroying = 0;
                        this->reset_all_server_state_variables(variables->THREAD_variables);
                        variables->THREAD_variables->active_thread = 0;
                        return;
                    }
                    error_status = WSAGetLastError();

                    uint8_t buffor_code = 129;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"129 signal has been sended; | THREAD_send_data_to_client_tool0\n",0,0});
                    #endif
                    variables->THREAD_variables->server.send_to_client(&buffor_code,1,&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                              &variables->THREAD_variables->server_structure);

                    background.r = 168; background.g = 0; background.b = 0; background.a = 0;
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": connection has been lost;\n",(char*)"connection has been lost;",(SDL_Color){255,255,255,0},background,0});

                    if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1)  variables->THREAD_variables->diode_blue_counter = 2;

                    switch(counter0)
                    {
                        case 0:  //sending message
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(256);
                                sprintf(debug_buffor,"you've been failed to send data to the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sending message failed:\n",(char*)"sending message failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;

                        case 1: //sending refresh signal
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(256);
                                sprintf(debug_buffor,"you've been failed to send data to the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sending refresh signal failed:\n",(char*)"sending refresh signal failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;

                        case 2: //change max fps;
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(256);
                                sprintf(debug_buffor,"you've been failed to send data to the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sending new max_fps failed:\n",(char*)"sending new max_fps failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;

                        case 3: //change max quality;
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(256);
                                sprintf(debug_buffor,"you've been failed to send data to the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sending new max_quality failed:\n",(char*)"sending new max_quality failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;

                        case 4: //change screen_width;
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(256);
                                sprintf(debug_buffor,"you've been failed to send data to the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sending new screen_width failed:\n",(char*)"sending new screen_width failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;

                        case 5: //change screen_height;
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(256);
                                sprintf(debug_buffor,"you've been failed to send data to the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sending new screen_height failed:\n",(char*)"sending new screen_height failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;

                        case 6: //change hash_activate;
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(256);
                                sprintf(debug_buffor,"you've been failed to send data to the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sending new hash_activate failed:\n",(char*)"sending new hash_activate failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;

                        case 7: //change hash state;
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(256);
                                sprintf(debug_buffor,"you've been failed to send data to the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sending hash information failed:\n",(char*)"sending hash information failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;

                        case 8: //accept connection with the client;
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(256);
                                sprintf(debug_buffor,"you've been failed to send data to the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": accept connection failed:\n",(char*)"accept connection failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;


                        case 9: //send response to requested_fps;
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(256);
                                sprintf(debug_buffor,"you've been failed to send data to the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sending requested_fps response failed:\n",(char*)"sending requested_fps response failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;

                        case 11: //send response to requested_quality;
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(256);
                                sprintf(debug_buffor,"you've been failed to send data to the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sending requested_quality response failed:\n",(char*)"sending requested_quality response failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;

                        case 14: //send new value of max_shared_loss
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(256);
                                sprintf(debug_buffor,"you've been failed to send data to the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sending new max_loss failed:\n",(char*)"sending new max_loss failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;

                        case 15: //send response to requested_loss
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(256);
                                sprintf(debug_buffor,"you've been failed to send data to the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sending requested_loss response failed:\n",(char*)"sending requested_loss response failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;

                        default: break;
                    }

                    char* buffor0 = (char*)malloc(64);
                    sprintf(buffor0,"    winsock error: %d;",error_status);
                    char* buffor1 = (char*)malloc(64);
                    sprintf(buffor1,":   winsock error: %d;\n",error_status);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){255,0,0,0},{0,0,0,255},1});
                    variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({1});
                    variables->THREAD_variables->window0_state = 1;
                    this->reset_all_server_state_variables(variables->THREAD_variables);
                    variables->THREAD_variables->client_first_send_request = 0;
                    variables->THREAD_variables->active_thread = 0;
                    break;
                }
                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1&&error_status!=-1)
                {
                    if(how_much_data_is_needed_right_now==0) variables->THREAD_variables->diode_blue_counter = 2;
                    else variables->THREAD_variables->diode_blue_counter = 1;
                }

                if(how_much_data_is_needed_right_now==0) variables->THREAD_variables->state_of_waiting_for_client = 2; //if all data needed has been sended;

            }
            if(variables->THREAD_variables->state_of_waiting_for_client==2) //if all data needed has been sended;
            {
                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1&&error_status!=-1)  variables->THREAD_variables->diode_blue_counter = 2;

                variables->THREAD_variables->state_of_waiting_for_client = 0;
                variables->THREAD_variables->is_server_busy = 0;
                variables->THREAD_variables->server_operation[counter0] = 0;
                variables->THREAD_variables->priority_number = -1;
                switch(counter0)
                {
                    case 0:  //sending message
                        {

                            #ifdef MAIN_PROGRAM0_DEBUG
                            char* debug_buffor = (char*)malloc(256);
                            sprintf(debug_buffor,"    sended message to the client:\n"
                                    "        %s\n"
                                    "        %s\n",
                            (const char*)pointer_to_existing_data+1,
                            (const char*)pointer_to_existing_data+34);
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                            #endif

                            background.r = 0; background.g = 0; background.b = 168; background.a = 0;
                            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": sended message to the client:\n",(char*)"sended message to the client:",(SDL_Color){255,255,255,0},background,0});
                            if(pointer_to_existing_data[1]!='\0'||pointer_to_existing_data[34]!='\0')
                            {
                                char* buffor0;
                                char* buffor1;
                                if(pointer_to_existing_data[1]!='\0')
                                {
                                    buffor0 = (char*)malloc(64);
                                    buffor1 = (char*)malloc(64);
                                    sprintf(buffor0,"    %s",(const char*)pointer_to_existing_data+1);
                                    sprintf(buffor1,":    %s\n",(const char*)pointer_to_existing_data+1);
                                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                                }
                                if(pointer_to_existing_data[34]!='\0')
                                {
                                    buffor0 = (char*)malloc(64);
                                    buffor1 = (char*)malloc(64);
                                    sprintf(buffor0,"    %s",(const char*)pointer_to_existing_data+34);
                                    sprintf(buffor1,":    %s\n",(const char*)pointer_to_existing_data+34);
                                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                                }
                            }
                        }
                    break;

                    case 1:  //sending refresh signal
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"refresh signal sended;\n",0,0});
                            #endif
                            variables->THREAD_variables->server_operation[128] = 1;  //refresh signal receive response;

                        }
                    break;

                    case 2:  //change max fps;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"changes of max_fps sended;\n",0,0});
                            #endif
                            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": changes sended to the client;\n",(char*)"changes sended to the client;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                        }
                    break;

                    case 3:  //change max quality;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"changes of max_quality sended;\n",0,0});
                            #endif
                           variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": changes sended to the client;\n",(char*)"changes sended to the client;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                        }
                    break;

                    case 4:  //change screen_width;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"changes of screen_width sended;\n",0,0});
                            #endif
                            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": changes sended to the client;\n",(char*)"changes sended to the client;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                        }
                    break;

                    case 5:  //change screen_height;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"changes of screen_height sended;\n",0,0});
                            #endif
                            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": changes sended to the client;\n",(char*)"changes sended to the client;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                        }
                    break;

                    case 6:  //change hash_activate;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"changes of hash_activate sended;\n",0,0});
                            #endif
                            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": changes sended to the client;\n",(char*)"changes sended to the client;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                        }
                    break;

                    case 7:  //change hash state;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"changes of hash information sended;\n",0,0});
                            #endif
                            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": information sended to the client;\n",(char*)"information sended to the client;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                        }
                    break;

                    case 8:  //accept connection with the client;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"connection accepted;\n",0,0});
                            #endif
                            background.r = 0; background.g = 168;
                            background.b = 0; background.a = 0;
                            variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({3});
                            variables->THREAD_variables->window0_state = 3;
                            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": connection accepted;\n",(char*)"connection accepted;",(SDL_Color){255,255,255,0},background,0});
                            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": ScreenSharing has been paused;\n",(char*)"ScreenSharing has been paused;",(SDL_Color){0,0,0,0},{0,0,0,255},0});

                        }
                    break;

                    case 9: //send response to requested_fps
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"requested_fps response sended;\n",0,0});
                                #endif
                                 variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": requested_fps response sended;\n",(char*)"requested_fps response sended;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                                 variables->THREAD_variables->wait_for_client_request = 0; //important;
                            }
                        break;

                    case 11: //send response to requested_quality
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"requested_quality response sended;\n",0,0});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": requested_quality response sended;\n",(char*)"requested_quality response sended;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                                variables->THREAD_variables->wait_for_client_request = 0; //important;
                            }
                        break;

                    case 14:  //change max_shared_loss
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"changes of max_shared_loss sended;\n",0,0});
                            #endif
                            variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": changes sended to the client;\n",(char*)"changes sended to the client;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                        }
                    break;

                    case 15: //send response to requested_loss
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"requested_loss response sended;\n",0,0});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": requested_loss response sended;\n",(char*)"requested_loss response sended;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                                variables->THREAD_variables->wait_for_client_request = 0; //important;
                            }
                    break;

                    default: break;
                }

                if(variables->THREAD_variables->client_first_send_request!=0) variables->THREAD_variables->client_first_send_request--;
                if(variables->THREAD_variables->wait_for_client_request==0) variables->THREAD_variables->timeout0 = SDL_GetTicks(); //if client tell to "stop screen sharing and wait for my request"
                break;
            }
            break;
        }
    }
    return;
}
void Server_Menu::THREAD_receive_data_to_client_tool0(THREAD_server_menu_struct_variables* variables,char* log_buffor0,char* log_buffor1,uint8_t* buffor0_static)
{

    static uint32_t needed_bytes_to_send_receive;
    static SDL_Color background;
    static uint8_t* pointer_to_existing_data;
    static int error_status;
    static uint32_t how_much_data_is_needed_right_now;


        //RECEIVE
//========================================================================================================================================
    for(int counter0 = 127; counter0!=variables->THREAD_variables->SIZE_OF_OPERATION_ARRAY; counter0++)
    {
        if(variables->THREAD_variables->server_operation[counter0]==1&&(variables->THREAD_variables->is_server_busy==counter0+1||variables->THREAD_variables->is_server_busy==0)) //variables->THREAD_variables->is_server_busy==0 means that server isn't busy;
        {
            if(variables->THREAD_variables->state_of_waiting_for_client==0)
            {
                //printf("\n%zd %zd %zd",variables->THREAD_variables->server_operation[counter0],variables->THREAD_variables->is_server_busy,counter0);
                if(variables->THREAD_variables->priority_number!=-1&&variables->THREAD_variables->priority_number!=counter0) continue;
                variables->THREAD_variables->is_server_busy = counter0+1;
                variables->THREAD_variables->timeout0 = SDL_GetTicks();
                background.r = 168; background.g = 0; background.b = 0; background.a = 0;

                switch(counter0) //server_operation code
                {
                    case 128: //refresh signal receive response;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're receiving response after sending refresh signal;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 1;
                            how_much_data_is_needed_right_now = needed_bytes_to_send_receive;;

                            pointer_to_existing_data = buffor0_static;
                        }
                    break;

                    case 136: //receive request change requested_fps from the client;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're receiving request \"change requested_fps\" from the client;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 2;
                            how_much_data_is_needed_right_now = needed_bytes_to_send_receive;;

                            pointer_to_existing_data = buffor0_static;
                        }
                    break;

                    case 137: //receive message from the client;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're receiving message from the client;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 66;
                            how_much_data_is_needed_right_now = needed_bytes_to_send_receive;;

                            pointer_to_existing_data = buffor0_static;
                        }
                    break;

                    case 138: //receive request change requested_quality from the client;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're receiving request \"change requested_quality\" from the client;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 1;
                            how_much_data_is_needed_right_now = needed_bytes_to_send_receive;;

                            pointer_to_existing_data = buffor0_static;
                        }
                    break;

                    case 142: //receive request change requested_loss from the client;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"you're receiving request \"change requested_loss\" from the client;\n",0,0});
                            #endif
                            needed_bytes_to_send_receive = 1;
                            how_much_data_is_needed_right_now = needed_bytes_to_send_receive;;

                            pointer_to_existing_data = buffor0_static;
                        }
                    break;

                    default: variables->THREAD_variables->is_server_busy = 0; return;
                }
                variables->THREAD_variables->state_of_waiting_for_client = 1;
            }

            if(variables->THREAD_variables->state_of_waiting_for_client==1)
            {
                if(SDL_GetTicks()-variables->THREAD_variables->timeout0>=variables->THREAD_global_variables->inactive_timeout_in_ms) //sending information to client about reached limit;
                {
                    uint8_t buffor_code = 128;
                    variables->THREAD_variables->server.send_to_client(&buffor_code,1,&variables->THREAD_variables->server_structure);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"128 signal has been sended; | THREAD_receive_data_to_client_tool0\n",0,0});
                    #endif
                    buffor_code = 129;
                    variables->THREAD_variables->server.send_to_client(&buffor_code,1,&variables->THREAD_variables->server_structure);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"129 signal has been sended; | THREAD_receive_data_to_client_tool0\n",0,0});
                    #endif
                    variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                              &variables->THREAD_variables->server_structure);

                    background.r = 168; background.g = 0; background.b = 0; background.a = 0;
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": connection has been lost;\n",(char*)"connection has been lost;",(SDL_Color){255,255,255,0},background,0});

                    #ifdef MAIN_PROGRAM0_DEBUG
                    char* debug_buffor = (char*)malloc(512);
                    sprintf(debug_buffor,"    receive data error: inactivity session timeout reached his limit: %zdms\n    data from the client wasn't sended in complete piece: %dbytes received from %zd needed;\n",
                    variables->THREAD_global_variables->inactive_timeout_in_ms,needed_bytes_to_send_receive-how_much_data_is_needed_right_now,needed_bytes_to_send_receive);
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                    #endif

                    switch(counter0)
                    {
                        case 128: //refresh signal receive response;
                            {
                                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1&&error_status!=-1)  variables->THREAD_variables->diode_blue_counter = 2;
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": client wasn't able to send response:\n",(char*)"client wasn't able to send response:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                            }
                        break;

                        case 136: //receive request change requested_fps from the client;
                            {
                                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1&&error_status!=-1)  variables->THREAD_variables->diode_blue_counter = 2;
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": client wasn't able to send request:\n",(char*)"client wasn't able to send request:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                            }
                        break;

                        case 137: //receive message from the client;
                            {
                                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1&&error_status!=-1)  variables->THREAD_variables->diode_blue_counter = 2;
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": client wasn't able to send message:\n",(char*)"client wasn't able to send message:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                            }
                        break;

                        case 138: //receive request change requested_quality from the client;
                            {
                                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1&&error_status!=-1)  variables->THREAD_variables->diode_blue_counter = 2;
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": client wasn't able to send request:\n",(char*)"client wasn't able to send request:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                            }
                        break;

                        case 142: //receive request change requested_loss from the client;
                            {
                                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1&&error_status!=-1)  variables->THREAD_variables->diode_blue_counter = 2;
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": client wasn't able to send request:\n",(char*)"client wasn't able to send request:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":   inactivity timeout reached;\n",(char*)"    inactivity timeout reached;",(SDL_Color){0,0,168,0},{0,0,0,255},0});
                            }
                        break;

                        default: break;
                    }

                    variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({1});
                    variables->THREAD_variables->window0_state = 1;
                    this->reset_all_server_state_variables(variables->THREAD_variables);
                    variables->THREAD_variables->client_first_send_request = 0;
                    variables->THREAD_variables->active_thread = 0;
                    break;
                }
                error_status = variables->THREAD_variables->server.recv_from_client(pointer_to_existing_data+(needed_bytes_to_send_receive-how_much_data_is_needed_right_now),how_much_data_is_needed_right_now,&variables->THREAD_variables->server_structure);
                if(error_status!=-1) how_much_data_is_needed_right_now-=error_status;
                if(WSAGetLastError()!=WSAEWOULDBLOCK&&(error_status==0||error_status==-1)) //if there was connection error;
                {
                    if(variables->THREAD_variables->do_client_is_rejecting==1||variables->THREAD_variables->do_server_is_destroying==1) //if "reject" or "disconnect" event has been executed in the main program;
                    {
                        variables->THREAD_variables->do_client_is_rejecting = 0;
                        variables->THREAD_variables->do_server_is_destroying = 0;
                        this->reset_all_server_state_variables(variables->THREAD_variables);
                        variables->THREAD_variables->active_thread = 0;
                        return;
                    }
                    error_status = WSAGetLastError();

                    uint8_t buffor_code = 129;
                    variables->THREAD_variables->server.send_to_client(&buffor_code,1,&variables->THREAD_variables->server_structure);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"129 signal has been sended; | THREAD_receive_data_to_client_tool0\n",0,0});
                    #endif
                    variables->THREAD_variables->server.reject_client(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.destroy_server(&variables->THREAD_variables->server_structure);
                    variables->THREAD_variables->server.create_server((const char*)variables->THREAD_variables->local_ip,(const char*)variables->THREAD_variables->local_port,
                                                              &variables->THREAD_variables->server_structure);

                    background.r = 168; background.g = 0; background.b = 0; background.a = 0;
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": connection has been lost;\n",(char*)"connection has been lost;",(SDL_Color){255,255,255,0},background,0});

                    switch(counter0)
                    {
                        case 128: //refresh signal receive response;
                            {
                                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1)  variables->THREAD_variables->diode_blue_counter = 2;
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(128);
                                sprintf(debug_buffor,"you've been failed to receive data from the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": receive refresh signal response failed:\n",(char*)"receive refresh signal response failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;

                        case 136: //receive request change requested_fps from the client;
                            {
                                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1)  variables->THREAD_variables->diode_blue_counter = 2;
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(128);
                                sprintf(debug_buffor,"you've been failed to receive data from the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": receiving change requested_fps failed:\n",(char*)"receiving change requested_fps failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;

                        case 137: //receive message from the client;
                            {
                                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1)  variables->THREAD_variables->diode_blue_counter = 2;
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(128);
                                sprintf(debug_buffor,"you've been failed to receive data from the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": receiving message failed:\n",(char*)"receiving message failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;

                        case 138: //receive request change requested_quality from the client;
                            {
                                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1)  variables->THREAD_variables->diode_blue_counter = 2;
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(128);
                                sprintf(debug_buffor,"you've been failed to receive data from the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": receiving change requested_quality failed:\n",(char*)"receiving change requested_quality failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;

                        case 142: //receive request change requested_loss from the client;
                            {
                                if(variables->THREAD_variables->how_much_fps_pass_without_blue_diode>=1)  variables->THREAD_variables->diode_blue_counter = 2;
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(128);
                                sprintf(debug_buffor,"you've been failed to receive data from the client; winsock error: %d\n",error_status);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                                #endif
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": receiving change requested_loss failed:\n",(char*)"receiving change requested_loss failed:",(SDL_Color){168,0,0,0},{0,0,0,255},0});
                            }
                        break;


                        default: break;
                    }

                    char* buffor0 = (char*)malloc(64);
                    sprintf(buffor0,"    winsock error: %d;",error_status);
                    char* buffor1 = (char*)malloc(64);
                    sprintf(buffor1,":   winsock error: %d;\n",error_status);
                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){255,0,0,0},{0,0,0,255},1});
                    variables->THREAD_variables->thread_vector_reset_windows_request[0].push_back({1});
                    variables->THREAD_variables->window0_state = 1;
                    this->reset_all_server_state_variables(variables->THREAD_variables);
                    variables->THREAD_variables->client_first_send_request = 0;
                    variables->THREAD_variables->active_thread = 0;
                    break;
                }
                if(variables->THREAD_variables->how_much_fps_pass_without_red_diode>=1&&error_status>0)
                {
                    if(how_much_data_is_needed_right_now==0) variables->THREAD_variables->diode_red_counter = 2;
                    else variables->THREAD_variables->diode_red_counter = 1;

                }

                if(how_much_data_is_needed_right_now==0) variables->THREAD_variables->state_of_waiting_for_client = 2; //if all data needed has been sended;
            }

            if(variables->THREAD_variables->state_of_waiting_for_client==2) //received all of the data;
            {
                variables->THREAD_variables->priority_number = -1;
                switch(counter0)
                {
                    case 128: //refresh signal receive response;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"refresh singal response received from the client;\n",0,0});
                            #endif
                            if(variables->THREAD_variables->how_much_fps_pass_without_red_diode>=1)  variables->THREAD_variables->diode_red_counter = 2;
                            if(pointer_to_existing_data[0]!=100)
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(64);
                                sprintf(debug_buffor,"wrong data received from the client: %d\n",pointer_to_existing_data[0]);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                                #endif

                                char* buffor0 = (char*)malloc(64);
                                char* buffor1 = (char*)malloc(64);

                                sprintf(buffor0,"received unkown code: %zd;",pointer_to_existing_data[0]);
                                sprintf(buffor1,": received unkown code: %zd;\n",pointer_to_existing_data[0]);
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                            }
                        }
                    break;

                    case 136: //receive request change requested_fps from the client;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"change requested_fps received from the client;\n",0,0});
                            #endif
                            if(variables->THREAD_variables->how_much_fps_pass_without_red_diode>=1)  variables->THREAD_variables->diode_red_counter = 2;
                            while(variables->THREAD_variables->wait_before_changing_loss_quality_fps0==1) {SDL_Delay(1);}                                                //thread locks
                            int max_shared_fps_int = variables->THREAD_global_variables->universal_tool0->string_to_int32((const char*)variables->THREAD_variables->max_shared_fps);
                            if(*(uint16_t*)pointer_to_existing_data>max_shared_fps_int)
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(64);
                                sprintf(debug_buffor,"received requested_fps is too big: %zd\n",*(uint16_t*)pointer_to_existing_data);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                                #endif

                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": received requested_fps is too big;\n",(char*)"received requested_fps is too big;",(SDL_Color){0,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->buffor_to_response_code = 1;
                            }
                            else if(*(uint16_t*)pointer_to_existing_data<1)
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(64);
                                sprintf(debug_buffor,"received requested_fps is too small: %zd\n",*(uint16_t*)pointer_to_existing_data);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                                #endif

                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": received requested_fps is too small;\n",(char*)"received requested_fps is too small;",(SDL_Color){0,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->buffor_to_response_code = 2;
                            }
                            else
                            {
                                    variables->THREAD_variables->requested_fps = *(uint16_t*)pointer_to_existing_data;
                                    char* buffor0 = (char*)malloc(64);
                                    char* buffor1 = (char*)malloc(64);

                                    variables->THREAD_variables->thread_vector_update_window0_state2_state3.push_back({1});

                                    sprintf(buffor0,"client changed requested_fps to: %zd;",*(uint16_t*)pointer_to_existing_data);
                                    sprintf(buffor1,": client changed requested_fps to: %zd;\n",*(uint16_t*)pointer_to_existing_data);
                                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                                    variables->THREAD_variables->buffor_to_response_code = 0;

                            }
                            //if client send first request then u have set options like this:
                            variables->THREAD_variables->priority_number = 9;
                            variables->THREAD_variables->server_operation[9] = 1;
                            variables->THREAD_variables->client_first_send_request--;
                        }
                    break;

                    case 137: //receive message from the client;
                        {
                            char* buffor0;
                            char* buffor1;
                            pointer_to_existing_data[32] = '\0';
                            pointer_to_existing_data[65] = '\0';

                            #ifdef MAIN_PROGRAM0_DEBUGw
                            char* debug_buffor = (char*)malloc(256);
                            sprintf(debug_buffor,"received message from the client:\n    %s\n    %s\n",(const char*)pointer_to_existing_data,(const char*)pointer_to_existing_data+33);
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                            #endif

                            bool shrink_message0 = this->shrink_string_to_fit_the_size(variables->THREAD_global_variables->main_ttf,(char*)pointer_to_existing_data,210);
                            bool shrink_message1 = this->shrink_string_to_fit_the_size(variables->THREAD_global_variables->main_ttf,(char*)&pointer_to_existing_data[33],210);

                            if(pointer_to_existing_data[0]!='\0')
                            {
                                buffor0 = (char*)malloc(64);
                                buffor1 = (char*)malloc(64);
                                sprintf(buffor0,"    %s",(const char*)pointer_to_existing_data);
                                sprintf(buffor1,":   %s\n",(const char*)pointer_to_existing_data);
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                            }
                            if(pointer_to_existing_data[33]!='\0')
                            {
                                buffor0 = (char*)malloc(64);
                                buffor1 = (char*)malloc(64);
                                sprintf(buffor0,"    %s",(const char*)((uint8_t*)pointer_to_existing_data+33));
                                sprintf(buffor1,":   %s\n",(const char*)((uint8_t*)pointer_to_existing_data+33));
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                            }
                            if(shrink_message0||shrink_message1)
                            {
                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)":  message had to be truncated;\n",(char*)"message had to be truncated;",(SDL_Color){0,0,0,0},{0,0,0,255},1});
                            }

                            variables->THREAD_global_variables->universal_tool0->const_char_to_char((const char*)pointer_to_existing_data,(char*)variables->THREAD_variables->message0_client);
                            variables->THREAD_global_variables->universal_tool0->const_char_to_char((const char*)pointer_to_existing_data+33,(char*)variables->THREAD_variables->message1_client);

                            variables->THREAD_variables->thread_vector_update_window0_state2_state3.push_back({3});
                            variables->THREAD_variables->thread_vector_update_window0_state2_state3.push_back({4});

                            variables->THREAD_variables->wait_for_client_request = 0; //important;
                            //if client send first request (and you don't have to response) then u have set options like this:
                            variables->THREAD_variables->client_first_send_request--;
                        }
                    break;

                    case 138: //receive request change requested_quality from the client;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"change requested_quality received from the client;\n",0,0});
                            #endif
                            if(variables->THREAD_variables->how_much_fps_pass_without_red_diode>=1)  variables->THREAD_variables->diode_red_counter = 2;
                            while(variables->THREAD_variables->wait_before_changing_loss_quality_fps0==1) {SDL_Delay(1);}                                                //thread locks
                            int max_shared_quality_int = variables->THREAD_global_variables->universal_tool0->string_to_int32((const char*)variables->THREAD_variables->max_shared_quality);
                            if(*(uint8_t*)pointer_to_existing_data>max_shared_quality_int)
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(128);
                                sprintf(debug_buffor,"received requested_quality is too big: %zd\n",*(uint8_t*)pointer_to_existing_data);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                                #endif

                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": received requested_quality is too big;\n",(char*)"received requested_quality is too big;",(SDL_Color){0,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->buffor_to_response_code = 1;
                            }
                            else if(*(uint8_t*)pointer_to_existing_data<1)
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(128);
                                sprintf(debug_buffor,"received requested_quality is too small: %zd\n",*(uint8_t*)pointer_to_existing_data);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                                #endif

                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": received requested_quality is too small;\n",(char*)"received requested_quality is too small;",(SDL_Color){0,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->buffor_to_response_code = 2;
                            }
                            else
                            {
                                    variables->THREAD_variables->requested_quality = *(uint8_t*)pointer_to_existing_data;

                                    char* buffor0 = (char*)malloc(64);
                                    char* buffor1 = (char*)malloc(64);

                                    variables->THREAD_variables->thread_vector_update_window0_state2_state3.push_back({2});

                                    sprintf(buffor0,"client changed requested_quality to: %zd;",*(uint8_t*)pointer_to_existing_data);
                                    sprintf(buffor1,": client changed requested_quality to: %zd;\n",*(uint8_t*)pointer_to_existing_data);
                                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                                    variables->THREAD_variables->buffor_to_response_code = 0;

                            }
                            //if client send first request then u have set options like this:
                            variables->THREAD_variables->priority_number = 11;
                            variables->THREAD_variables->server_operation[11] = 1;
                            variables->THREAD_variables->client_first_send_request--;
                        }
                    break;

                    case 142: //receive request change requested_loss from the client;
                        {
                            #ifdef MAIN_PROGRAM0_DEBUG
                            variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)"change requested_loss received from the client;\n",0,0});
                            #endif
                            if(variables->THREAD_variables->how_much_fps_pass_without_red_diode>=1)  variables->THREAD_variables->diode_red_counter = 2;
                            while(variables->THREAD_variables->wait_before_changing_loss_quality_fps0==1) {SDL_Delay(1);}                                                //thread locks
                            if(*(uint8_t*)pointer_to_existing_data>variables->THREAD_variables->max_shared_loss_int)
                            {
                                #ifdef MAIN_PROGRAM0_DEBUG
                                char* debug_buffor = (char*)malloc(128);
                                sprintf(debug_buffor,"received requested_loss is too big: %zd\n",*(uint8_t*)pointer_to_existing_data);
                                variables->THREAD_variables->thread_vector_stdout_stderr[0].push_back((Server_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                                #endif

                                variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){(char*)": received requested_loss is too big;\n",(char*)"received requested_loss is too big;",(SDL_Color){0,0,0,0},{0,0,0,255},0});
                                variables->THREAD_variables->buffor_to_response_code = 1;
                            }
                            else
                            {
                                    variables->THREAD_variables->requested_loss = *(uint8_t*)pointer_to_existing_data;

                                    char* buffor0 = (char*)malloc(64);
                                    char* buffor1 = (char*)malloc(64);

                                    variables->THREAD_variables->thread_vector_update_window0_state2_state3.push_back({5});

                                    sprintf(buffor0,"client changed requested_loss to: %zd;",*(uint8_t*)pointer_to_existing_data);
                                    sprintf(buffor1,": client changed requested_loss to: %zd;\n",*(uint8_t*)pointer_to_existing_data);
                                    variables->THREAD_variables->thread_vector_logs_request[0].push_back((Server_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){0,0,0,0},{0,0,0,255},1});
                                    variables->THREAD_variables->buffor_to_response_code = 0;

                            }
                            //if client send first request then u have set options like this:
                            variables->THREAD_variables->priority_number = 15;
                            variables->THREAD_variables->server_operation[15] = 1;
                            variables->THREAD_variables->client_first_send_request--;
                        }
                    break;

                    default: break;
                }
                variables->THREAD_variables->state_of_waiting_for_client = 0;
                variables->THREAD_variables->is_server_busy = 0;
                variables->THREAD_variables->server_operation[counter0] = 0;
                if(variables->THREAD_variables->wait_for_client_request==0) variables->THREAD_variables->timeout0 = SDL_GetTicks(); //if client tell to "stop screen sharing and wait for my request"
                variables->THREAD_variables->active_thread = 0;
            }
            break;
        }
    }
    return;
}
