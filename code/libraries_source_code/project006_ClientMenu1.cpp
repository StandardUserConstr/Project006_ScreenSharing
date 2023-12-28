#include "../libraries/project006_main_program_headers0.h"


void Client_Menu::client_animation0(Client_Menu_Variables* variables,bool mode)
{

    static uint32_t actual_frame = 0;
    if(mode==0)
    {
        variables->timer0_0 = SDL_GetTicks();
        if(variables->timer0_0>=variables->timer0_1+200)
        {
            actual_frame++;
            if(actual_frame==10) actual_frame = 0;
            variables->timer0_1 = SDL_GetTicks();
        }
    }
    else
    {
        variables->timer0_0 = SDL_GetTicks();
        if(variables->timer0_0>=variables->timer0_1+400)
        {
            actual_frame++;
            if(actual_frame==10) actual_frame = 0;
            variables->timer0_1 = SDL_GetTicks();
        }

    }
    SDL_RenderCopy(this->global_variables->render,variables->animation0[actual_frame],NULL,&variables->rect_window0_animation);
    return;
}

void Client_Menu::do_prepared_textboxes(SDL_Event* event,Client_Menu_Variables* variables)
{
    if(variables->window0_state==0||variables->VARIABLE_do_prepared_textboxes_FORCE_TO_RESET_TO_0==1)
    {
        for(int i = 0; i!=variables->COUNT_OF_TEXBOXES; i++) variables->textbox_variables[i]->TextBox(event,variables->textbox_data[i],variables->textbox_settings0[i],0);
        for(int i = 5; i!=10; i++)
        {
            if(this->shrink_string_to_fit_the_size(variables->ThreadFriendly_global_variables->main_ttf,(char*)variables->textbox_data[i],562)!=0) //password/hash
            {
                variables->textbox_variables[i]->update_textbox();
                SDL_Event clear_event;
                variables->textbox_variables[i]->TextBox(&clear_event,variables->textbox_data[i],variables->textbox_settings0[i],0);
            }

        }
        if(this->shrink_string_to_fit_the_size(variables->ThreadFriendly_global_variables->main_ttf,(char*)variables->textbox_data[10],206)!=0)//message0
        {
            variables->textbox_variables[10]->update_textbox();
            SDL_Event clear_event;
            variables->textbox_variables[10]->TextBox(&clear_event,variables->textbox_data[10],variables->textbox_settings0[10],0);

        }
        if(this->shrink_string_to_fit_the_size(variables->ThreadFriendly_global_variables->main_ttf,(char*)variables->textbox_data[11],206)!=0)//message1
        {
            variables->textbox_variables[11]->update_textbox();
            SDL_Event clear_event;
            variables->textbox_variables[11]->TextBox(&clear_event,variables->textbox_data[11],variables->textbox_settings0[11],0);

        }
        variables->VARIABLE_do_prepared_textboxes_FORCE_TO_RESET_TO_0 = 0;
    }
    else if(variables->window0_state==1)
    {
        for(int i = 6; i!=10; i++) variables->textbox_variables[i]->TextBox(event,variables->textbox_data[i],variables->textbox_settings0[i],0);
        for(int i = 12; i!=variables->COUNT_OF_TEXBOXES; i++) variables->textbox_variables[i]->TextBox(event,variables->textbox_data[i],variables->textbox_settings0[i],0);

        for(int i = 6; i!=10; i++)
        {
            if(this->shrink_string_to_fit_the_size(variables->ThreadFriendly_global_variables->main_ttf,(char*)variables->textbox_data[i],562)!=0) //hash
            {
                variables->textbox_variables[i]->update_textbox();
                SDL_Event clear_event;
                variables->textbox_variables[i]->TextBox(&clear_event,variables->textbox_data[i],variables->textbox_settings0[i],0);
            }

        }
    }
    else
    {
        for(int i = 2; i!=5; i++) variables->textbox_variables[i]->TextBox(event,variables->textbox_data[i],variables->textbox_settings0[i],0);
        for(int i = 6; i!=variables->COUNT_OF_TEXBOXES; i++) variables->textbox_variables[i]->TextBox(event,variables->textbox_data[i],variables->textbox_settings0[i],0);

        for(int i = 6; i!=10; i++)
        {
            if(this->shrink_string_to_fit_the_size(variables->ThreadFriendly_global_variables->main_ttf,(char*)variables->textbox_data[i],562)!=0) //hash
            {
                variables->textbox_variables[i]->update_textbox();
                SDL_Event clear_event;
                variables->textbox_variables[i]->TextBox(&clear_event,variables->textbox_data[i],variables->textbox_settings0[i],0);
            }

        }
        if(this->shrink_string_to_fit_the_size(variables->ThreadFriendly_global_variables->main_ttf,(char*)variables->textbox_data[10],206)!=0)//message0
        {
            variables->textbox_variables[10]->update_textbox();
            SDL_Event clear_event;
            variables->textbox_variables[10]->TextBox(&clear_event,variables->textbox_data[10],variables->textbox_settings0[10],0);

        }
        if(this->shrink_string_to_fit_the_size(variables->ThreadFriendly_global_variables->main_ttf,(char*)variables->textbox_data[11],206)!=0)//message1
        {
            variables->textbox_variables[11]->update_textbox();
            SDL_Event clear_event;
            variables->textbox_variables[11]->TextBox(&clear_event,variables->textbox_data[11],variables->textbox_settings0[11],0);

        }
    }

    //decide which data after losing focus/unclick should be saved to file/displayed in logs and possibly whether information should be sended to client or not;
    int i = 0;
    for(;;) //u can change multiple variables at one time so it's necessary to make this loop;
    {
        for(; i!=variables->COUNT_OF_TEXBOXES; i++) if(variables->textbox_variables[i]->do_data_should_be_safed()==1) break;

         if(i==variables->COUNT_OF_TEXBOXES) break;

        switch(i)
        {
            case 0:
                {
                    if(variables->ThreadFriendly_global_variables->universal_tool0->compare_data(variables->textbox_data[i],variables->server_ip,15)==0) break;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    server_ip changed\n",0,0});
                    #endif
                    uint32_t server_ip_new_int;
                    if(convert_IPv4_from_string_to_uint32((const char*)variables->textbox_data[i],&server_ip_new_int)!=0)
                    {
                        memcpy(variables->textbox_data[i],variables->server_ip,15);
                        #ifdef MAIN_PROGRAM0_DEBUG
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    server_ip has bad syntax\n",0,0});
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                        #endif
                        variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": server_ip: wrong format\n",(char*)"server_ip: wrong format",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        variables->textbox_variables[i]->update_textbox();
                        SDL_Event clear_event;
                        variables->textbox_variables[i]->TextBox(&clear_event,variables->textbox_data[i],variables->textbox_settings0[i],0);
                        break;
                    }
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    config changed\n",0,0});
                    #endif
                    //clear textbox_data 'cause textbox() didn't clearing; it's only adding char '\0'; it's not necessary to clear but just for calm head and clear config purpose;
                    int counter = 0;
                    for(; variables->textbox_data[i][counter]!='\0'; counter++) {}
                    for(; counter!=15; counter++) variables->textbox_data[i][counter] = '\0';

                    memcpy(variables->server_ip,variables->textbox_data[i],15);
                    variables->server_ip[15] = '\r'; variables->server_ip[16] = '\n';
                    variables->ThreadFriendly_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->server_ip,17,": ",variables->client_base_position_in_config,(i+1)*64);
                    variables->server_ip[15] = '\0'; variables->server_ip[16] = '\0';

                    char* buffor0 = (char*)malloc(64);
                    strcpy(buffor0,": ");
                    strcat(buffor0,"local_server_ip: ");
                    strcat(buffor0,(const char*)variables->textbox_data[i]);
                    strcat(buffor0,";\n");
                    char* buffor1 = (char*)malloc(64);
                    strcpy(buffor1,"local_server_ip: ");
                    strcat(buffor1,(const char*)variables->textbox_data[i]);
                    strcat(buffor1,";");

                    variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor0,buffor1,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});

                    SDL_DestroyTexture(variables->window0_state0_text_texture[0]);
                    SDL_Surface* surface_temporary_ttf;
                    surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,(const char*)variables->server_ip,(SDL_Color){0,0,0,0});
                    variables->window0_state0_text_texture[0] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
                    SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state0_text_texture[0]);
                    variables->rect_window0_state0_text_texture[0].x = 403; variables->rect_window0_state0_text_texture[0].y = 82;
                    SDL_FreeSurface(surface_temporary_ttf);


                }
            break;

            case 1:
                {
                    int size_of_textbox_data = 5;
                    if(variables->ThreadFriendly_global_variables->universal_tool0->compare_data(variables->textbox_data[i],variables->server_port,size_of_textbox_data)==0) break;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    server_port changed\n",0,0});
                    #endif
                    uint32_t server_port = variables->ThreadFriendly_global_variables->universal_tool0->string_to_int32((const char*)variables->textbox_data[i]);
                    if(server_port==0||server_port>65535||variables->textbox_data[i][0]=='0')
                    {
                        memcpy(variables->textbox_data[i],variables->server_port,size_of_textbox_data);
                        #ifdef MAIN_PROGRAM0_DEBUG
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    server_port is higher or lower than allowed or wrong format\n",0,0});
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                        #endif
                        if(server_port==0)
                        {
                            variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": server_port: can't be 0\n",(char*)"server_port: can't be 0",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        }
                        else if(server_port>65535) variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": server_port: can't be higher than 65535\n",(char*)"server_port: can't be higher than 65535",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        else variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": server_port: wrong format\n",(char*)"server_port: wrong format",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        variables->textbox_variables[i]->update_textbox();
                        SDL_Event clear_event;
                        variables->textbox_variables[i]->TextBox(&clear_event,variables->textbox_data[i],variables->textbox_settings0[i],0);
                        break;
                    }

                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    config changed\n",0,0});
                    #endif
                    //clear textbox_data 'cause textbox() didn't clearing; it's only adding char '\0';
                    int counter = 0;
                    for(; variables->textbox_data[i][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->textbox_data[i][counter] = '\0';

                    memcpy(variables->server_port,variables->textbox_data[i],size_of_textbox_data);
                    variables->server_port[size_of_textbox_data] = '\r'; variables->server_port[size_of_textbox_data+1] = '\n';
                    variables->ThreadFriendly_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->server_port,size_of_textbox_data+2,"port: ",variables->client_base_position_in_config,(i+1)*64);
                    variables->server_port[size_of_textbox_data] = '\0'; variables->server_port[size_of_textbox_data+1] = '\0';

                    char* buffor0 = (char*)malloc(64);
                    strcpy(buffor0,": ");
                    strcat(buffor0,"server_port: ");
                    strcat(buffor0,(const char*)variables->textbox_data[i]);
                    strcat(buffor0,";\n");
                    char* buffor1 = (char*)malloc(64);
                    strcpy(buffor1,"server_port: ");
                    strcat(buffor1,(const char*)variables->textbox_data[i]);
                    strcat(buffor1,";");

                    variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor0,buffor1,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});

                    SDL_DestroyTexture(variables->window0_state0_text_texture[1]);
                    SDL_Surface* surface_temporary_ttf;
                    surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,(const char*)variables->server_port,(SDL_Color){0,0,0,0});
                    variables->window0_state0_text_texture[1] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
                    SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state0_text_texture[1]);
                    variables->rect_window0_state0_text_texture[1].x = 403; variables->rect_window0_state0_text_texture[1].y = 98;
                    SDL_FreeSurface(surface_temporary_ttf);
                }
            break;

            case 2:
                {
                    int size_of_textbox_data = 3;
                    if(variables->ThreadFriendly_global_variables->universal_tool0->compare_data(variables->textbox_data[i],variables->requested_fps,size_of_textbox_data)==0) break;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    requested_fps changed\n",0,0});
                    #endif
                    bool send_signal_or_not = 0;
                    if(variables->window1_state==2)
                    {
                        send_signal_or_not = 1;
                        for(size_t i = 0; i!=variables->thread_vector_send_receive[0].size(); i++)
                        {
                            if(variables->thread_vector_send_receive[0][i].operation_code==2)
                            {
                                send_signal_or_not = 0;
                                break;
                            }
                        }
                    }

                    uint32_t requested_fps = variables->ThreadFriendly_global_variables->universal_tool0->string_to_int32((const char*)variables->textbox_data[i]);
                    if(requested_fps==0||requested_fps>480||variables->textbox_data[i][0]=='0'||(variables->window1_state==2&&(requested_fps>variables->max_shared_fps_int||send_signal_or_not==0)))
                    {
                        #ifdef MAIN_PROGRAM0_DEBUG
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    requested_fps is higher or lower thand allowed or wrong format or requested_fps is higher than max_shared_fps\n",0,0});
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                        #endif
                        if(requested_fps<1)
                        {
                            variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_fps: can't be 0;\n",(char*)"requested_fps: can't be 0;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        }
                        else if(requested_fps>480) variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_fps: higher than 480;\n",(char*)"requested_fps: higher than 480;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        else if(variables->window1_state==2&&requested_fps>variables->max_shared_fps_int) variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_fps: higher than max_fps;\n",(char*)"requested_fps: higher than max_fps;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        else if(variables->textbox_data[i][0]=='0') variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_fps: wrong format;\n",(char*)"requested_fps: wrong format;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        else variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_fps: is already in the queue;\n",(char*)"requested_fps: is already in the queue;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        variables->textbox_variables[i]->update_textbox();
                        SDL_Event clear_event;
                        memcpy(variables->textbox_data[i],variables->requested_fps,size_of_textbox_data);
                        variables->textbox_variables[i]->TextBox(&clear_event,variables->textbox_data[i],variables->textbox_settings0[i],0);
                        break;
                    }
                    variables->requested_fps_int = requested_fps;

                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    config changed\n",0,0});
                    #endif
                    //clear textbox_data 'cause textbox() didn't clearing; it's only adding char '\0';
                    int counter = 0;
                    for(; variables->textbox_data[i][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->textbox_data[i][counter] = '\0';

                    memcpy(variables->requested_fps,variables->textbox_data[i],size_of_textbox_data);
                    variables->requested_fps[size_of_textbox_data] = '\r'; variables->requested_fps[size_of_textbox_data+1] = '\n';
                    variables->ThreadFriendly_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->requested_fps,size_of_textbox_data+2,"\nrequested fps: ",variables->client_base_position_in_config,(i+1)*64);
                    variables->requested_fps[size_of_textbox_data] = '\0'; variables->requested_fps[size_of_textbox_data+1] = '\0';

                    char* buffor0 = (char*)malloc(64);
                    strcpy(buffor0,": ");
                    strcat(buffor0,"requested_fps: ");
                    strcat(buffor0,(const char*)variables->textbox_data[i]);
                    strcat(buffor0,";\n");
                    char* buffor1 = (char*)malloc(64);
                    strcpy(buffor1,"requested_fps: ");
                    strcat(buffor1,(const char*)variables->textbox_data[i]);
                    strcat(buffor1,";");

                    variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor0,buffor1,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});

                    SDL_DestroyTexture(variables->window0_state0_text_texture[3]);
                    SDL_Surface* surface_temporary_ttf;
                    surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,(const char*)variables->requested_fps,(SDL_Color){0,0,0,0});
                    variables->window0_state0_text_texture[3] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
                    SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state0_text_texture[3]);
                    variables->rect_window0_state0_text_texture[3].x = 403; variables->rect_window0_state0_text_texture[3].y = 130;
                    SDL_FreeSurface(surface_temporary_ttf);

                    #ifdef MAIN_PROGRAM0_DEBUG
                    bool which_fps;
                    #endif
                    if(variables->requested_fps_int>=variables->ThreadFriendly_global_variables->main_menu_fps) {variables->ThreadFriendly_global_variables->sdl_universal_tool0->change_fps(variables->requested_fps_int);
                    #ifdef MAIN_PROGRAM0_DEBUG
                    which_fps = 0;
                    #endif
                    }
                    else {variables->ThreadFriendly_global_variables->sdl_universal_tool0->change_fps(variables->ThreadFriendly_global_variables->main_menu_fps);
                    #ifdef MAIN_PROGRAM0_DEBUG
                     which_fps = 1;
                     #endif
                     }

                    #ifdef MAIN_PROGRAM0_DEBUG
                    char* debug_buffor = (char*)malloc(64);
                    if(which_fps==0) sprintf(debug_buffor,"    fps changed to %zd\n",variables->requested_fps_int);
                    else sprintf(debug_buffor,"    fps changed to %zd\n",variables->ThreadFriendly_global_variables->main_menu_fps);

                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)debug_buffor,0,1});
                    #endif

                    //send winsock signal to the server about change;
                    if(send_signal_or_not==1)
                    {
                        variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){2});
                        #ifdef MAIN_PROGRAM0_DEBUG
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"change requested_fps signal is ready to be sended;\n",0,0});
                        #endif
                    }
                }
            break;

            case 3:
                {
                    int size_of_textbox_data = 2;
                    if(variables->ThreadFriendly_global_variables->universal_tool0->compare_data(variables->textbox_data[i],variables->requested_quality,size_of_textbox_data)==0) break;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    requested_quality changed\n",0,0});
                    #endif
                    bool send_signal_or_not = 0;
                    if(variables->window1_state==2)
                    {
                        send_signal_or_not = 1;
                        for(size_t i = 0; i!=variables->thread_vector_send_receive[0].size(); i++)
                        {
                            if(variables->thread_vector_send_receive[0][i].operation_code==3)
                            {
                                send_signal_or_not = 0;
                                break;
                            }
                        }
                    }

                    uint32_t requested_quality = variables->ThreadFriendly_global_variables->universal_tool0->string_to_int32((const char*)variables->textbox_data[i]);
                    if(requested_quality==0||requested_quality>10||variables->textbox_data[i][0]=='0'||(variables->window1_state==2&&(requested_quality>variables->max_shared_quality_int||send_signal_or_not==0)))
                    {
                        #ifdef MAIN_PROGRAM0_DEBUG
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    requested_quality is higher or lower thand allowed or wrong format or higher than max_shared_quality\n",0,0});
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                        #endif
                        if(requested_quality==0)
                        {
                            variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_quality: can't be 0;\n",(char*)"requested_quality: can't be 0;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        }
                        else if(requested_quality>10) variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_quality: higher than 10;\n",(char*)"requested_quality: higher than 10;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        else if(variables->textbox_data[i][0]=='0') variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_quality: wrong format;\n",(char*)"requested_quality: wrong format;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        else if(variables->window1_state==2&&(requested_quality>variables->max_shared_quality_int)) variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_quality: higher than max_quality;\n",(char*)"requested_quality: higher than max_quality;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        else variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_quality: is already in the queue;\n",(char*)"requested_quality: is already in the queue;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        variables->textbox_variables[i]->update_textbox();
                        SDL_Event clear_event;
                        memcpy(variables->textbox_data[i],variables->requested_quality,size_of_textbox_data);
                        variables->textbox_variables[i]->TextBox(&clear_event,variables->textbox_data[i],variables->textbox_settings0[i],0);
                        break;
                    }
                    variables->requested_quality_int = requested_quality;

                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    config changed\n",0,0});
                    #endif
                    //clear textbox_data 'cause textbox() didn't clearing; it's only adding char '\0';
                    int counter = 0;
                    for(; variables->textbox_data[i][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->textbox_data[i][counter] = '\0';

                    memcpy(variables->requested_quality,variables->textbox_data[i],size_of_textbox_data);
                    variables->requested_quality[size_of_textbox_data] = '\r'; variables->requested_quality[size_of_textbox_data+1] = '\n';
                    variables->ThreadFriendly_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->requested_quality,size_of_textbox_data+2,"\nrequested quality: ",variables->client_base_position_in_config,(i+1)*64);
                    variables->requested_quality[size_of_textbox_data] = '\0'; variables->requested_quality[size_of_textbox_data+1] = '\0';

                    char* buffor0 = (char*)malloc(64);
                    strcpy(buffor0,": ");
                    strcat(buffor0,"requested_quality: ");
                    strcat(buffor0,(const char*)variables->textbox_data[i]);
                    strcat(buffor0,";\n");
                    char* buffor1 = (char*)malloc(64);
                    strcpy(buffor1,"requested_quality: ");
                    strcat(buffor1,(const char*)variables->textbox_data[i]);
                    strcat(buffor1,";");

                    variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor0,buffor1,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});

                    SDL_DestroyTexture(variables->window0_state0_text_texture[4]);
                    SDL_Surface* surface_temporary_ttf;
                    surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,(const char*)variables->requested_quality,(SDL_Color){0,0,0,0});
                    variables->window0_state0_text_texture[4] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
                    SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state0_text_texture[4]);
                    variables->rect_window0_state0_text_texture[4].x = 403; variables->rect_window0_state0_text_texture[4].y = 146;
                    SDL_FreeSurface(surface_temporary_ttf);

                    //przy quality uwzglednij pause_image i fullscreen;
                    if((variables->is_screen_sharing_paused==0&&variables->window0_state==3))
                    {
                        int32_t preview_width = (variables->screen_width_share_int*0.1)*variables->requested_quality_int;
                        if(preview_width<64) preview_width = 64;
                        int32_t preview_height = (variables->screen_height_share_int*0.1)*variables->requested_quality_int;
                        if(preview_height<64) preview_height = 64;
                        char buffor_width[5] = {'\0','\0','\0','\0','\0'};
                        char buffor_height[5] = {'\0','\0','\0','\0','\0'};
                        variables->ThreadFriendly_global_variables->universal_tool0->uint32_to_string(preview_width,buffor_width);
                        variables->ThreadFriendly_global_variables->universal_tool0->uint32_to_string(preview_height,buffor_height);
                        memcpy(variables->textbox_data[12],buffor_width,5);
                        memcpy(variables->textbox_data[13],buffor_height,5);
                        SDL_Event clear_event;
                        variables->textbox_variables[12]->update_textbox(); variables->textbox_variables[13]->update_textbox();
                        variables->textbox_variables[12]->TextBox(&clear_event,variables->textbox_data[12],variables->textbox_settings0[12],0);
                        variables->textbox_variables[13]->TextBox(&clear_event,variables->textbox_data[13],variables->textbox_settings0[13],0);

                        buffor0 = (char*)malloc(32);
                        strcpy(buffor0,": ");
                        strcat(buffor0,"screen_width_preview: ");
                        strcat(buffor0,(const char*)variables->textbox_data[12]);
                        strcat(buffor0,"\n");
                        buffor1 = (char*)malloc(32);
                        strcpy(buffor1,"screen_width_preview: ");
                        strcat(buffor1,(const char*)variables->textbox_data[12]);
                        strcat(buffor1,";");
                        variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor0,buffor1,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});

                        buffor0 = (char*)malloc(32);
                        strcpy(buffor0,": ");
                        strcat(buffor0,"screen_height_preview: ");
                        strcat(buffor0,(const char*)variables->textbox_data[13]);
                        strcat(buffor0,"\n");
                        buffor1 = (char*)malloc(32);
                        strcpy(buffor1,"screen_height_preview: ");
                        strcat(buffor1,(const char*)variables->textbox_data[13]);
                        strcat(buffor1,";");
                        variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor0,buffor1,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});

                        variables->screen_width_preview = preview_width;
                        variables->screen_height_preview = preview_height;

                        if(variables->window2_is_fullscreen==0)
                        {
                            variables->window2_hittest.h = variables->screen_height_preview;
                            variables->window2_hittest.w = variables->screen_width_preview-55;
                        }
                        variables->rect_window2_bar = (SDL_Rect){(int)variables->screen_width_preview-54,0,54,19};
                        if(variables->window2_minimalize==1) //anty SDL2 bug;
                        {
                            variables->window2_minimalize = 0;
                            SDL_RestoreWindow(variables->window2);
                        }
                        SDL_SetWindowSize(variables->window2,variables->screen_width_preview,variables->screen_height_preview);
                    }
                    else if((variables->is_screen_sharing_paused==1&&variables->window0_state==3))
                    {
                        int32_t preview_width = (variables->screen_width_share_int*0.1)*variables->requested_quality_int;
                        if(preview_width<64) preview_width = 64;
                        int32_t preview_height = (variables->screen_height_share_int*0.1)*variables->requested_quality_int;
                        if(preview_height<64) preview_height = 64;
                        variables->buffor_for_screen_width_preview = preview_width;
                        variables->buffor_for_screen_height_preview = preview_height;

                    }


                    //send winsock signal to the server about change;
                    if(send_signal_or_not==1)
                    {
                        variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){3});
                        #ifdef MAIN_PROGRAM0_DEBUG
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"change requested_quality signal is ready to be sended;\n",0,0});
                        #endif
                    }
                }
            break;

            case 4:
                {
                    int size_of_textbox_data = 3;
                    if(variables->ThreadFriendly_global_variables->universal_tool0->compare_data(variables->textbox_data[i],variables->requested_loss,size_of_textbox_data)==0) break;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    requested_loss changed\n",0,0});
                    #endif
                    bool send_signal_or_not = 0;
                    if(variables->window1_state==2)
                    {
                        send_signal_or_not = 1;
                        for(size_t i = 0; i!=variables->thread_vector_send_receive[0].size(); i++)
                        {
                            if(variables->thread_vector_send_receive[0][i].operation_code==5)
                            {
                                send_signal_or_not = 0;
                                break;
                            }
                        }
                    }

                    uint32_t requested_loss = variables->ThreadFriendly_global_variables->universal_tool0->string_to_int32((const char*)variables->textbox_data[i]);
                    if(requested_loss>100||(variables->textbox_data[i][0]=='0'&&variables->textbox_data[i][1]!='\0')||(variables->window1_state==2&&(requested_loss>variables->max_shared_loss_int||send_signal_or_not==0)))
                    {

                        #ifdef MAIN_PROGRAM0_DEBUG
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    requested_loss is higher than allowed or wrong format or higher than max_shared_loss\n",0,0});
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                        #endif
                        if(requested_loss>100)
                        {
                            variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_loss: higher than 100;\n",(char*)"requested_loss: higher than 100;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        }
                        else if(variables->textbox_data[i][0]=='0'&&variables->textbox_data[i][1]!='\0') variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_loss: wrong format;\n",(char*)"requested_loss: wrong format;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        else if(variables->window1_state==2&&(requested_loss>variables->max_shared_loss_int)) variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_loss: higher than max_loss;\n",(char*)"requested_loss: higher than max_loss;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        else variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": requested_loss: is already in the queue;\n",(char*)"requested_loss: is already in the queue;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        variables->textbox_variables[i]->update_textbox();
                        SDL_Event clear_event;
                        memcpy(variables->textbox_data[i],variables->requested_loss,size_of_textbox_data);
                        variables->textbox_variables[i]->TextBox(&clear_event,variables->textbox_data[i],variables->textbox_settings0[i],0);
                        break;
                    }
                    variables->requested_loss_int = requested_loss;

                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    config changed\n",0,0});
                    #endif
                    //clear textbox_data 'cause textbox() didn't clearing; it's only adding char '\0';
                    int counter = 0;
                    for(; variables->textbox_data[i][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->textbox_data[i][counter] = '\0';

                    memcpy(variables->requested_loss,variables->textbox_data[i],size_of_textbox_data);
                    variables->requested_loss[size_of_textbox_data] = '\r'; variables->requested_loss[size_of_textbox_data+1] = '\n';
                    variables->ThreadFriendly_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->requested_loss,size_of_textbox_data+2,"\nrequested loss: ",variables->client_base_position_in_config,(i+1)*64);
                    variables->requested_loss[size_of_textbox_data] = '\0'; variables->requested_loss[size_of_textbox_data+1] = '\0';

                    char* buffor0 = (char*)malloc(64);
                    strcpy(buffor0,": ");
                    strcat(buffor0,"requested_loss: ");
                    if(requested_loss==0) strcat(buffor0,"disabled");
                    else strcat(buffor0,(const char*)variables->textbox_data[i]);
                    strcat(buffor0,";\n");

                    char* buffor1 = (char*)malloc(64);
                    strcpy(buffor1,"requested_loss: ");
                    if(requested_loss==0) strcat(buffor1,"disabled");
                    else strcat(buffor1,(const char*)variables->textbox_data[i]);
                    strcat(buffor1,";");

                    variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor0,buffor1,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});

                    SDL_DestroyTexture(variables->window0_state0_text_texture[5]);
                    SDL_Surface* surface_temporary_ttf;
                    surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,(const char*)variables->requested_loss,(SDL_Color){0,0,0,0});
                    variables->window0_state0_text_texture[5] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
                    SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state0_text_texture[5]);
                    variables->rect_window0_state0_text_texture[5].x = 403; variables->rect_window0_state0_text_texture[5].y = 162;
                    SDL_FreeSurface(surface_temporary_ttf);

                    //send winsock signal to the server about change;
                    if(send_signal_or_not==1)
                    {
                        variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){5});
                        #ifdef MAIN_PROGRAM0_DEBUG
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"change requested_loss signal is ready to be sended;\n",0,0});
                        #endif
                    }
                }
            break;

            case 5:
                {
                    int size_of_textbox_data = 64;
                    if(variables->ThreadFriendly_global_variables->universal_tool0->compare_data(variables->textbox_data[i],variables->password,size_of_textbox_data)==0) break;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    password changed\n",0,0});
                    #endif

                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    config changed\n",0,0});
                    #endif
                    //clear textbox_data 'cause textbox() didn't clearing; it's only adding char '\0';
                    int counter = 0;
                    for(; variables->textbox_data[i][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->textbox_data[i][counter] = '\0';

                    memcpy(variables->password,variables->textbox_data[i],size_of_textbox_data);
                    variables->password[size_of_textbox_data] = '\r'; variables->password[size_of_textbox_data+1] = '\n';
                    variables->ThreadFriendly_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->password,size_of_textbox_data+2,"\npassword: ",variables->client_base_position_in_config,(i+1)*64);
                    variables->password[size_of_textbox_data] = '\0'; variables->password[size_of_textbox_data+1] = '\0';

                    char* buffor0 = (char*)malloc(32);
                    strcpy(buffor0,": password: changed;\n");
                    char* buffor1 = (char*)malloc(32);
                    strcpy(buffor1,"password: changed;");

                    variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor0,buffor1,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                }
            break;

            case 6:
                {
                    int size_of_textbox_data = 64;
                    if(variables->ThreadFriendly_global_variables->universal_tool0->compare_data(variables->textbox_data[i],variables->hash0,size_of_textbox_data)==0) break;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    hash0 changed\n",0,0});
                    #endif
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    config changed\n",0,0});
                    #endif
                    //clear textbox_data 'cause textbox() didn't clearing; it's only adding char '\0';
                    int counter = 0;
                    for(; variables->textbox_data[i][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->textbox_data[i][counter] = '\0';

                    memcpy(variables->hash0,variables->textbox_data[i],size_of_textbox_data);
                    variables->hash0[size_of_textbox_data] = '\r'; variables->hash0[size_of_textbox_data+1] = '\n';
                    variables->ThreadFriendly_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->hash0,size_of_textbox_data+2,"\nhash0: ",variables->client_base_position_in_config,(i+1)*64);
                    variables->hash0[size_of_textbox_data] = '\0'; variables->hash0[size_of_textbox_data+1] = '\0';

                    char* buffor0 = (char*)malloc(32);
                    strcpy(buffor0,": hash0: changed;\n");
                    char* buffor1 = (char*)malloc(32);
                    strcpy(buffor1,"hash0: changed;");

                    variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor0,buffor1,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                }
            break;

            case 7:
                {
                    int size_of_textbox_data = 64;
                    if(variables->ThreadFriendly_global_variables->universal_tool0->compare_data(variables->textbox_data[i],variables->hash1,size_of_textbox_data)==0) break;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    hash1 changed\n",0,0});
                    #endif
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    config changed\n",0,0});
                    #endif
                    //clear textbox_data 'cause textbox() didn't clearing; it's only adding char '\0';
                    int counter = 0;
                    for(; variables->textbox_data[i][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->textbox_data[i][counter] = '\0';

                    memcpy(variables->hash1,variables->textbox_data[i],size_of_textbox_data);
                    variables->hash1[size_of_textbox_data] = '\r'; variables->hash1[size_of_textbox_data+1] = '\n';
                    variables->ThreadFriendly_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->hash1,size_of_textbox_data+2,"\nhash1: ",variables->client_base_position_in_config,(i+1)*64);
                    variables->hash1[size_of_textbox_data] = '\0'; variables->hash1[size_of_textbox_data+1] = '\0';

                    char* buffor0 = (char*)malloc(32);
                    strcpy(buffor0,": hash1: changed;\n");
                    char* buffor1 = (char*)malloc(32);
                    strcpy(buffor1,"hash1: changed;");

                    variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor0,buffor1,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                }
            break;

            case 8:
                {
                    int size_of_textbox_data = 64;
                    if(variables->ThreadFriendly_global_variables->universal_tool0->compare_data(variables->textbox_data[i],variables->hash2,size_of_textbox_data)==0) break;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    hash2 changed\n",0,0});
                    #endif
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    config changed\n",0,0});
                    #endif
                    //clear textbox_data 'cause textbox() didn't clearing; it's only adding char '\0';
                    int counter = 0;
                    for(; variables->textbox_data[i][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->textbox_data[i][counter] = '\0';

                    memcpy(variables->hash2,variables->textbox_data[i],size_of_textbox_data);
                    variables->hash2[size_of_textbox_data] = '\r'; variables->hash2[size_of_textbox_data+1] = '\n';
                    variables->ThreadFriendly_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->hash2,size_of_textbox_data+2,"\nhash2: ",variables->client_base_position_in_config,(i+1)*64);
                    variables->hash2[size_of_textbox_data] = '\0'; variables->hash2[size_of_textbox_data+1] = '\0';

                    char* buffor0 = (char*)malloc(32);
                    strcpy(buffor0,": hash2: changed;\n");
                    char* buffor1 = (char*)malloc(32);
                    strcpy(buffor1,"hash2: changed;");

                    variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor0,buffor1,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                }
            break;

            case 9:
                {
                    int size_of_textbox_data = 64;
                    if(variables->ThreadFriendly_global_variables->universal_tool0->compare_data(variables->textbox_data[i],variables->hash3,size_of_textbox_data)==0) break;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    hash3 changed\n",0,0});
                    #endif
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    config changed\n",0,0});
                    #endif
                    //clear textbox_data 'cause textbox() didn't clearing; it's only adding char '\0';
                    int counter = 0;
                    for(; variables->textbox_data[i][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->textbox_data[i][counter] = '\0';

                    memcpy(variables->hash3,variables->textbox_data[i],size_of_textbox_data);
                    variables->hash3[size_of_textbox_data] = '\r'; variables->hash3[size_of_textbox_data+1] = '\n';
                    variables->ThreadFriendly_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->hash3,size_of_textbox_data+2,"\nhash3: ",variables->client_base_position_in_config,(i+1)*64);
                    variables->hash3[size_of_textbox_data] = '\0'; variables->hash3[size_of_textbox_data+1] = '\0';

                    char* buffor0 = (char*)malloc(32);
                    strcpy(buffor0,": hash3: changed;\n");
                    char* buffor1 = (char*)malloc(32);
                    strcpy(buffor1,"hash3: changed;");

                    variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor0,buffor1,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                }
            break;

            case 10:
                {
                    int size_of_textbox_data = 32;
                    if(variables->ThreadFriendly_global_variables->universal_tool0->compare_data(variables->textbox_data[i],variables->message0,size_of_textbox_data)==0) break;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    message0 changed\n",0,0});
                    #endif
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    config changed\n",0,0});
                    #endif
                    //clear textbox_data 'cause textbox() didn't clearing; it's only adding char '\0';
                    int counter = 0;
                    for(; variables->textbox_data[i][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->textbox_data[i][counter] = '\0';

                    memcpy(variables->message0,variables->textbox_data[i],size_of_textbox_data);
                    variables->message0[size_of_textbox_data] = '\r'; variables->message0[size_of_textbox_data+1] = '\n';
                    variables->ThreadFriendly_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->message0,size_of_textbox_data+2,"\nmessage0: ",variables->client_base_position_in_config,(i+1)*64);
                    variables->message0[size_of_textbox_data] = '\0'; variables->message0[size_of_textbox_data+1] = '\0';

                    /*char* buffor0 = (char*)malloc(32);
                    strcpy(buffor0,": message0: changed;\n");
                    char* buffor1 = (char*)malloc(32);
                    strcpy(buffor1,"message0: changed;");

                    variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor0,buffor1,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});*/

                    SDL_DestroyTexture(variables->window0_state0_text_texture[6]);
                    SDL_Surface* surface_temporary_ttf;
                    surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,(const char*)variables->message0,(SDL_Color){0,0,0,0});
                    variables->window0_state0_text_texture[6] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
                    SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state0_text_texture[6]);
                    variables->rect_window0_state0_text_texture[6].x = 284; variables->rect_window0_state0_text_texture[6].y = 196;
                    SDL_FreeSurface(surface_temporary_ttf);
                }
            break;

            case 11:
                {
                    int size_of_textbox_data = 32;
                    if(variables->ThreadFriendly_global_variables->universal_tool0->compare_data(variables->textbox_data[i],variables->message1,size_of_textbox_data)==0) break;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    message1 changed\n",0,0});
                    #endif
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    config changed\n",0,0});
                    #endif
                    //clear textbox_data 'cause textbox() didn't clearing; it's only adding char '\0';
                    int counter = 0;
                    for(; variables->textbox_data[i][counter]!='\0'; counter++) {}
                    for(; counter!=size_of_textbox_data; counter++) variables->textbox_data[i][counter] = '\0';

                    memcpy(variables->message1,variables->textbox_data[i],size_of_textbox_data);
                    variables->message1[size_of_textbox_data] = '\r'; variables->message1[size_of_textbox_data+1] = '\n';
                    variables->ThreadFriendly_global_variables->universal_tool0->advanced_write_to_file0("config",(const char*)variables->message1,size_of_textbox_data+2,"\nmessage1: ",variables->client_base_position_in_config,(i+1)*64);
                    variables->message1[size_of_textbox_data] = '\0'; variables->message1[size_of_textbox_data+1] = '\0';

                    /*char* buffor0 = (char*)malloc(32);
                    strcpy(buffor0,": message1: changed;\n");
                    char* buffor1 = (char*)malloc(32);
                    strcpy(buffor1,"message1: changed;");

                    variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor0,buffor1,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});*/

                    SDL_DestroyTexture(variables->window0_state0_text_texture[7]);
                    SDL_Surface* surface_temporary_ttf;
                    surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,(const char*)variables->message1,(SDL_Color){0,0,0,0});
                    variables->window0_state0_text_texture[7] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
                    SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state0_text_texture[7]);
                    variables->rect_window0_state0_text_texture[7].x = 284; variables->rect_window0_state0_text_texture[7].y = 212;
                    SDL_FreeSurface(surface_temporary_ttf);

                }
            break;

            case 12:
                {
                    int size_of_textbox_data = 4;
                    char buffor[6] = {'\0','\0','\0','\0','\0','\0'};
                    variables->ThreadFriendly_global_variables->universal_tool0->uint32_to_string(variables->screen_width_preview,buffor);
                    if(variables->ThreadFriendly_global_variables->universal_tool0->compare_data(variables->textbox_data[i],(uint8_t*)buffor,size_of_textbox_data)==0) break;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    screen_width_preview changed\n",0,0});
                    #endif
                    uint32_t screen_width_preview = variables->ThreadFriendly_global_variables->universal_tool0->string_to_int32((const char*)variables->textbox_data[i]);
                    if(screen_width_preview<64||variables->textbox_data[i][0]=='0')
                    {
                        memcpy(variables->textbox_data[i],buffor,size_of_textbox_data);
                        #ifdef MAIN_PROGRAM0_DEBUG
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    screen_width_preview is lower than allowed or wrong format\n",0,0});
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                        #endif
                        if(screen_width_preview<64) variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": screen_width_preview: lower than 64;\n",(char*)"screen_width_preview: lower than 64;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        else variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": screen_width_preview: wrong format;\n",(char*)"screen_width_preview: wrong format;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        variables->textbox_variables[i]->update_textbox();
                        SDL_Event clear_event;
                        variables->textbox_variables[i]->TextBox(&clear_event,variables->textbox_data[i],variables->textbox_settings0[i],0);
                        break;
                    }
                    variables->screen_width_preview = screen_width_preview;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    config changed\n",0,0});
                    #endif

                    if(variables->window2_is_fullscreen==0)
                    {
                        variables->window2_hittest.h = variables->screen_height_preview;
                        variables->window2_hittest.w = variables->screen_width_preview-55;
                    }
                    variables->rect_window2_bar = (SDL_Rect){(int)variables->screen_width_preview-54,0,54,19};
                    if(variables->window2_minimalize==1) //anty SDL2 bug;
                    {
                        variables->window2_minimalize = 0;
                        SDL_RestoreWindow(variables->window2);
                    }
                    SDL_SetWindowSize(variables->window2,variables->screen_width_preview,variables->screen_height_preview);


                    char* buffor0 = (char*)malloc(32);
                    strcpy(buffor0,": ");
                    strcat(buffor0,"screen_width_preview: ");
                    strcat(buffor0,(const char*)variables->textbox_data[i]);
                    strcat(buffor0,";\n");
                    char* buffor1 = (char*)malloc(32);
                    strcpy(buffor1,"screen_width_preview: ");
                    strcat(buffor1,(const char*)variables->textbox_data[i]);
                    strcat(buffor1,";");

                    variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor0,buffor1,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                }
            break;

            case 13:
                {
                    int size_of_textbox_data = 4;
                    char buffor[6] = {'\0','\0','\0','\0','\0','\0'};
                    variables->ThreadFriendly_global_variables->universal_tool0->uint32_to_string(variables->screen_height_preview,buffor);
                    if(variables->ThreadFriendly_global_variables->universal_tool0->compare_data(variables->textbox_data[i],(uint8_t*)buffor,size_of_textbox_data)==0) break;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    screen_height_preview changed\n",0,0});
                    #endif
                    uint32_t screen_height_preview = variables->ThreadFriendly_global_variables->universal_tool0->string_to_int32((const char*)variables->textbox_data[i]);
                    if(screen_height_preview<64||variables->textbox_data[i][0]=='0')
                    {
                        memcpy(variables->textbox_data[i],buffor,size_of_textbox_data);
                        #ifdef MAIN_PROGRAM0_DEBUG
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    screen_height_preview is lower than allowed or wrong format\n",0,0});
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                        #endif
                        if(screen_height_preview<64) variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": screen_height_preview: lower than 64;\n",(char*)"screen_height_preview: lower than 64;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        else variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": screen_height_preview: wrong format;\n",(char*)"screen_height_preview: wrong format;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                        variables->textbox_variables[i]->update_textbox();
                        SDL_Event clear_event;
                        variables->textbox_variables[i]->TextBox(&clear_event,variables->textbox_data[i],variables->textbox_settings0[i],0);
                        break;
                    }
                    variables->screen_height_preview = screen_height_preview;
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    config changed\n",0,0});
                    #endif

                    if(variables->window2_is_fullscreen==0)
                    {
                        variables->window2_hittest.h = variables->screen_height_preview;
                        variables->window2_hittest.w = variables->screen_width_preview-55;
                    }
                    variables->rect_window2_bar = (SDL_Rect){(int)variables->screen_width_preview-54,0,54,19};
                    if(variables->window2_minimalize==1) //anty SDL2 bug;
                    {
                        variables->window2_minimalize = 0;
                        SDL_RestoreWindow(variables->window2);
                    }
                    SDL_SetWindowSize(variables->window2,variables->screen_width_preview,variables->screen_height_preview);


                    char* buffor0 = (char*)malloc(32);
                    strcpy(buffor0,": ");
                    strcat(buffor0,"screen_height_preview: ");
                    strcat(buffor0,(const char*)variables->textbox_data[i]);
                    strcat(buffor0,";\n");
                    char* buffor1 = (char*)malloc(32);
                    strcpy(buffor1,"screen_height_preview: ");
                    strcat(buffor1,(const char*)variables->textbox_data[i]);
                    strcat(buffor1,";");

                    variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor0,buffor1,(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},1});
                }
            break;

            default: break;

        }

        i++;
    }

    return;
}

void Client_Menu::save_logs_to_file_and_create_texture(Client_Menu_Variables* variables,const char* what_save_to_file,const char* logs_string_text,SDL_Color color_of_text,SDL_Color color_of_background)
{
    variables->logs_file = fopen("files/client_logs.txt","a+b");
    uint32_t buffor_size = variables->ThreadFriendly_global_variables->universal_tool0->count_string_chars(what_save_to_file);
    time_t date = time(NULL);
    char* time_buffor = ctime(&date);
    uint32_t time_buffor_size = variables->ThreadFriendly_global_variables->universal_tool0->count_string_chars(time_buffor);
    time_buffor_size--;
    time_buffor[time_buffor_size] = '\0';
    char result[buffor_size+time_buffor_size+1];
    strcpy(result,time_buffor);
    strcat(result,what_save_to_file);
    fwrite(result,1,buffor_size+time_buffor_size,variables->logs_file);
    fclose(variables->logs_file);

    if((uint32_t)variables->y_logs_position==variables->H_SIZE_OF_LOGS)
    {
        #ifdef MAIN_PROGRAM0_DEBUG
        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs space reached his limits; one log line has been cut off\n",0,0});
        #endif
        SDL_Surface* text;
        if(color_of_background.a==255)
        {
           text = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,logs_string_text,color_of_text);
        }
        else
        {
            text = TTF_RenderUTF8_LCD(variables->ThreadFriendly_global_variables->main_ttf,logs_string_text,color_of_text,color_of_background);
        }
        SDL_Surface* copy_surface = SDL_CreateRGBSurface(0,240,variables->H_SIZE_OF_LOGS,32,0x00FF0000,0x0000FF00,0x000000FF,0xFF000000);
        SDL_Rect rect_combine_dst = {0,0,0,0};
        SDL_Rect rect_combine_src = {0,13,240,(int)variables->H_SIZE_OF_LOGS};
        SDL_BlitSurface(variables->main_logs_surface,&rect_combine_src,copy_surface,&rect_combine_dst);
        rect_combine_dst.y = variables->H_SIZE_OF_LOGS-13;
        SDL_BlitSurface(text,NULL,copy_surface,&rect_combine_dst);
        SDL_FreeSurface(variables->main_logs_surface);
        variables->main_logs_surface = copy_surface;

        SDL_DestroyTexture(variables->main_logs_texture);
        SDL_FreeSurface(text);
        variables->main_logs_texture = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,variables->main_logs_surface);
    }
    else
    {
        SDL_Surface* text;

        if(color_of_background.a==255)
        {
           text = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,logs_string_text,color_of_text);
        }
        else
        {
            text = TTF_RenderUTF8_LCD(variables->ThreadFriendly_global_variables->main_ttf,logs_string_text,color_of_text,color_of_background);
        }

        variables->ThreadFriendly_global_variables->sdl_universal_tool0->combine_surfaces(0,variables->y_logs_position,text,variables->main_logs_surface);
        SDL_DestroyTexture(variables->main_logs_texture);
        SDL_FreeSurface(text);
        variables->main_logs_texture = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,variables->main_logs_surface);

        variables->y_logs_position+=13;
        if(variables->y_logs_position>variables->H_MAX_OF_DISPLAY-1)
        {
            variables->rect_logs_src.y+=13;
        }
    }

    return;
}
void Client_Menu::reset_window0_and_window1_to_state0_or_1_or_2_or_3(Client_Menu_Variables* variables,uint8_t state0_or_1_or_2_or_3)
{
    SDL_Color main_color;
    SDL_Color main_color1;

    if(state0_or_1_or_2_or_3==2||state0_or_1_or_2_or_3==3)
    {
        this->force_update_textboes(variables); //unselecting text if selecting and updates containters like max_shared_loss, max_shared_quality and etc.

        main_color.r = 0; main_color.g = 0;
        main_color.b = 0; main_color.a = 0;

        if(state0_or_1_or_2_or_3==2)
        {
            main_color1.r = 135; main_color1.g = 136;
            main_color1.b = 143; main_color1.a = 0;

            variables->window0_state = 2;
            variables->window1_state = 2;
        }
        else
        {
            main_color1.r = 0; main_color1.g = 0;
            main_color1.b = 0; main_color1.a = 0;

            variables->window0_state = 3;
        }

        char buffor0[33];
        for(int i = 0; i!=variables->COUNT_OF_WINDOW0_STATE2_3_TEXT_TEXTURE; i++) SDL_DestroyTexture(variables->window0_state2_3_text_texture[i]);
        SDL_Surface* surface_temporary_ttf;

        surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,(const char*)variables->server_ip,main_color1);
        variables->window0_state2_3_text_texture[0] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[0]);
        variables->rect_window0_state2_3_text_texture[0].x = 403; variables->rect_window0_state2_3_text_texture[0].y = 82;
        SDL_FreeSurface(surface_temporary_ttf);

        variables->ThreadFriendly_global_variables->universal_tool0->uint32_to_string(variables->max_shared_fps_int,buffor0);
        surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,(const char*)buffor0,main_color1);
        variables->window0_state2_3_text_texture[1] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[1]);
        variables->rect_window0_state2_3_text_texture[1].x = 403; variables->rect_window0_state2_3_text_texture[1].y = 98;
        SDL_FreeSurface(surface_temporary_ttf);

        variables->ThreadFriendly_global_variables->universal_tool0->uint32_to_string(variables->max_shared_quality_int,buffor0);
        surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,(const char*)buffor0,main_color1);
        variables->window0_state2_3_text_texture[2] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[2]);
        variables->rect_window0_state2_3_text_texture[2].x = 403; variables->rect_window0_state2_3_text_texture[2].y = 114;
        SDL_FreeSurface(surface_temporary_ttf);

        variables->ThreadFriendly_global_variables->universal_tool0->uint32_to_string(variables->max_shared_loss_int,buffor0);
        surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,(const char*)buffor0,main_color1);
        variables->window0_state2_3_text_texture[3] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[3]);
        variables->rect_window0_state2_3_text_texture[3].x = 403; variables->rect_window0_state2_3_text_texture[3].y = 130;
        SDL_FreeSurface(surface_temporary_ttf);

        variables->ThreadFriendly_global_variables->universal_tool0->uint32_to_string(variables->screen_width_share_int,buffor0);
        surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,(const char*)buffor0,main_color1);
        variables->window0_state2_3_text_texture[4] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[4]);
        variables->rect_window0_state2_3_text_texture[4].x = 403; variables->rect_window0_state2_3_text_texture[4].y = 146;
        SDL_FreeSurface(surface_temporary_ttf);

        variables->ThreadFriendly_global_variables->universal_tool0->uint32_to_string(variables->screen_height_share_int,buffor0);
        surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,(const char*)buffor0,main_color1);
        variables->window0_state2_3_text_texture[5] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[5]);
        variables->rect_window0_state2_3_text_texture[5].x = 403; variables->rect_window0_state2_3_text_texture[5].y = 162;
        SDL_FreeSurface(surface_temporary_ttf);

        if(variables->server_password_required==1) surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,"yes",main_color1);
        else surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,"no",main_color1);
        variables->window0_state2_3_text_texture[6] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[6]);
        variables->rect_window0_state2_3_text_texture[6].x = 403; variables->rect_window0_state2_3_text_texture[6].y = 178;
        SDL_FreeSurface(surface_temporary_ttf);

        if(variables->server_hash_activate==1) surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,"yes",main_color1);
        else surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,"no",main_color1);
        variables->window0_state2_3_text_texture[7] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[7]);
        variables->rect_window0_state2_3_text_texture[7].x = 403; variables->rect_window0_state2_3_text_texture[7].y = 194;
        SDL_FreeSurface(surface_temporary_ttf);

        surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,(const char*)variables->message0_server,main_color1);
        variables->window0_state2_3_text_texture[8] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[8]);
        variables->rect_window0_state2_3_text_texture[8].x = 284; variables->rect_window0_state2_3_text_texture[8].y = 229;
        SDL_FreeSurface(surface_temporary_ttf);

        surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,(const char*)variables->message1_server,main_color1);
        variables->window0_state2_3_text_texture[9] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[9]);
        variables->rect_window0_state2_3_text_texture[9].x = 284; variables->rect_window0_state2_3_text_texture[9].y = 245;
        SDL_FreeSurface(surface_temporary_ttf);

        if(state0_or_1_or_2_or_3==2)
        {
            for(int i = 2; i!=5; i++) variables->textbox_settings0[i]->solid_text_color = main_color;
            variables->textbox_settings0[10]->solid_text_color = main_color;
            variables->textbox_settings0[11]->solid_text_color = main_color;
            for(int i = 2; i!=5; i++) variables->textbox_variables[i]->update_textbox();
            variables->textbox_variables[10]->update_textbox();
            variables->textbox_variables[11]->update_textbox();

            SDL_Event clear_event;
            for(int i = 2; i!=5; i++) variables->textbox_variables[i]->TextBox(&clear_event,variables->textbox_data[i],variables->textbox_settings0[i],0);
            variables->textbox_variables[10]->TextBox(&clear_event,variables->textbox_data[10],variables->textbox_settings0[10],0);
            variables->textbox_variables[11]->TextBox(&clear_event,variables->textbox_data[11],variables->textbox_settings0[11],0);
        }


    }
    else
    {
        this->force_update_textboes(variables); //unselecting text if selecting and updates containters like max_shared_loss, max_shared_quality and etc.

        if(state0_or_1_or_2_or_3==1)
        {
            main_color.r = 135; main_color.g = 136;
            main_color.b = 143; main_color.a = 0;

            variables->window0_state = 1;
            variables->window1_state = 1;

        }
        else if(state0_or_1_or_2_or_3==0)
        {
            main_color.r = 0; main_color.g = 0;
            main_color.b = 0; main_color.a = 0;


            variables->window0_state = 0;
            variables->window1_state = 0;
        }

        for(int i = 0; i!=variables->COUNT_OF_WINDOW0_STATE0_TEXT_TEXTURE; i++) SDL_DestroyTexture(variables->window0_state0_text_texture[i]);
        SDL_Surface* surface_temporary_ttf;

        surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)variables->server_ip,main_color);
        variables->window0_state0_text_texture[0] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state0_text_texture[0]);
        variables->rect_window0_state0_text_texture[0].x = 403; variables->rect_window0_state0_text_texture[0].y = 82;
        SDL_FreeSurface(surface_temporary_ttf);
        surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)variables->server_port,main_color);
        variables->window0_state0_text_texture[1] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state0_text_texture[1]);
        variables->rect_window0_state0_text_texture[1].x = 403; variables->rect_window0_state0_text_texture[1].y = 98;
        SDL_FreeSurface(surface_temporary_ttf);
        surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)variables->public_ip_string,main_color);
        variables->window0_state0_text_texture[2] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state0_text_texture[2]);
        variables->rect_window0_state0_text_texture[2].x = 403; variables->rect_window0_state0_text_texture[2].y = 114;
        SDL_FreeSurface(surface_temporary_ttf);
        surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)variables->requested_fps,main_color);
        variables->window0_state0_text_texture[3] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state0_text_texture[3]);
        variables->rect_window0_state0_text_texture[3].x = 403; variables->rect_window0_state0_text_texture[3].y = 130;
        SDL_FreeSurface(surface_temporary_ttf);
        surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)variables->requested_quality,main_color);
        variables->window0_state0_text_texture[4] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state0_text_texture[4]);
        variables->rect_window0_state0_text_texture[4].x = 403; variables->rect_window0_state0_text_texture[4].y = 146;
        SDL_FreeSurface(surface_temporary_ttf);
        surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)variables->requested_loss,main_color);
        variables->window0_state0_text_texture[5] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state0_text_texture[5]);
        variables->rect_window0_state0_text_texture[5].x = 403; variables->rect_window0_state0_text_texture[5].y = 162;
        SDL_FreeSurface(surface_temporary_ttf);
        surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)variables->message0,main_color);
        variables->window0_state0_text_texture[6] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state0_text_texture[6]);
        variables->rect_window0_state0_text_texture[6].x = 284; variables->rect_window0_state0_text_texture[6].y = 196;
        SDL_FreeSurface(surface_temporary_ttf);
        surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)variables->message1,main_color);
        variables->window0_state0_text_texture[7] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state0_text_texture[7]);
        variables->rect_window0_state0_text_texture[7].x = 284; variables->rect_window0_state0_text_texture[7].y = 212;
        SDL_FreeSurface(surface_temporary_ttf);

        for(int i = 0; i!=6; i++) variables->textbox_settings0[i]->solid_text_color = main_color;
        variables->textbox_settings0[10]->solid_text_color = main_color;
        variables->textbox_settings0[11]->solid_text_color = main_color;
        for(int i = 0; i!=6; i++) variables->textbox_variables[i]->update_textbox();
        variables->textbox_variables[10]->update_textbox();
        variables->textbox_variables[11]->update_textbox();

        SDL_Event clear_event;
        for(int i = 0; i!=6; i++) variables->textbox_variables[i]->TextBox(&clear_event,variables->textbox_data[i],variables->textbox_settings0[i],0);
        variables->textbox_variables[10]->TextBox(&clear_event,variables->textbox_data[10],variables->textbox_settings0[10],0);
        variables->textbox_variables[11]->TextBox(&clear_event,variables->textbox_data[11],variables->textbox_settings0[11],0);
    }

    return;
}

void Client_Menu::force_update_textboes(Client_Menu_Variables* variables)
{
    variables->window1_animation = 0;
    variables->window1_mouse_state = 0;
    variables->window0_animation = 0;
    variables->window0_mouse_state = 0;

    SDL_Event clear_event;                          // if something in textboxes changed and difference in variables wasn't updated;
    clear_event.type = SDL_MOUSEMOTION;          //
    clear_event.motion.x = 0;                       //
    clear_event.motion.y = 100;                     //
    variables->VARIABLE_do_prepared_textboxes_FORCE_TO_RESET_TO_0 = 1;
    do_prepared_textboxes(&clear_event,variables);  //
    clear_event.type = SDL_MOUSEBUTTONUP;         //
    variables->VARIABLE_do_prepared_textboxes_FORCE_TO_RESET_TO_0 = 1;
    do_prepared_textboxes(&clear_event,variables);  //
    clear_event.type = SDL_MOUSEBUTTONDOWN;           //
    variables->VARIABLE_do_prepared_textboxes_FORCE_TO_RESET_TO_0 = 1;
    do_prepared_textboxes(&clear_event,variables);  //
    clear_event.type = SDL_MOUSEBUTTONUP;           //
    variables->VARIABLE_do_prepared_textboxes_FORCE_TO_RESET_TO_0 = 1;
    do_prepared_textboxes(&clear_event,variables);  //
    return;
}

void Client_Menu::client_unpack_vectors(Client_Menu_Variables* variables)
{
    //variables->thread_vector_logs_request[0].push_back((MAIN_PROGRAM::vector_log_request_from_thread){(char*)"logs: 1234","1234",(SDL_Color){0,0,0,0},NULL});

    int last_array_index_of_reset_window = variables->thread_vector_reset_windows_request->size();
    if(last_array_index_of_reset_window!=0)
    {
        this->reset_window0_and_window1_to_state0_or_1_or_2_or_3(variables,variables->thread_vector_reset_windows_request[0][last_array_index_of_reset_window-1].state0_or_1_or_2_or_3);
        variables->thread_vector_reset_windows_request->clear();
    }

    int last_array_index_of_log = variables->thread_vector_logs_request->size();
    if(last_array_index_of_log!=0)
    {
        for(int i = 0; i!=last_array_index_of_log; i++)
        {
            this->save_logs_to_file_and_create_texture(variables,
                                                                variables->thread_vector_logs_request[0][i].what_save_to_file,
                                                                variables->thread_vector_logs_request[0][i].logs_string_text,
                                                                variables->thread_vector_logs_request[0][i].color_of_text,
                                                                variables->thread_vector_logs_request[0][i].color_of_background);

            if(variables->thread_vector_logs_request[0][i].free_memory_from_first_two_arg_or_not==1)
            {
                free(variables->thread_vector_logs_request[0][i].what_save_to_file);
                free(variables->thread_vector_logs_request[0][i].logs_string_text);
            }

            last_array_index_of_log = variables->thread_vector_logs_request->size(); //variable may change in another thread so better is to update it each time;
        }
        variables->thread_vector_logs_request->clear();
    }

    int last_array_index_of_window0_state2_state3 = variables->thread_vector_update_window0_state2_state3.size();
    if(last_array_index_of_window0_state2_state3!=0)
    {
        char buffor0[33];
        SDL_Surface* surface_temporary_ttf;
        SDL_Color main_color1;
        if(variables->window0_state==2)
        {
            main_color1.r = 135; main_color1.g = 136;
            main_color1.b = 143; main_color1.a = 0;
        }
        else
        {
            main_color1.r = 0; main_color1.g = 0;
            main_color1.b = 0; main_color1.a = 0;
        }
        for(int i = 0; i!=last_array_index_of_window0_state2_state3; i++)
        {
            switch(variables->thread_vector_update_window0_state2_state3[i].which_texture_to_change)
            {
                /*case 0: //this is server public ip
                    {

                    }
                break;*/

                case 1:
                    {


                        SDL_DestroyTexture(variables->window0_state2_3_text_texture[1]);

                        this->global_variables->universal_tool0->uint32_to_string(variables->max_shared_fps_int,buffor0);
                        surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)buffor0,main_color1);
                        variables->window0_state2_3_text_texture[1] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
                        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[1]);
                        variables->rect_window0_state2_3_text_texture[1].x = 403; variables->rect_window0_state2_3_text_texture[1].y = 98;
                        SDL_FreeSurface(surface_temporary_ttf);

                        SDL_Event event_clear;
                        variables->textbox_variables[2]->TextBox(&event_clear,variables->textbox_data[2],variables->textbox_settings0[2],0);
                    }
                break;

                case 2:
                    {
                            SDL_DestroyTexture(variables->window0_state2_3_text_texture[2]);

                            this->global_variables->universal_tool0->uint32_to_string(variables->max_shared_quality_int,buffor0);
                            SDL_Surface* surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)buffor0,main_color1);
                            variables->window0_state2_3_text_texture[2] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
                            SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[2]);
                            variables->rect_window0_state2_3_text_texture[2].x = 403; variables->rect_window0_state2_3_text_texture[2].y = 114;
                            SDL_FreeSurface(surface_temporary_ttf);

                            SDL_Event event_clear;
                            variables->textbox_variables[3]->TextBox(&event_clear,variables->textbox_data[3],variables->textbox_settings0[3],0);
                    }
                break;

                case 3:
                    {
                            SDL_DestroyTexture(variables->window0_state2_3_text_texture[3]);

                            this->global_variables->universal_tool0->uint32_to_string(variables->max_shared_loss_int,buffor0);
                            SDL_Surface* surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)buffor0,main_color1);
                            variables->window0_state2_3_text_texture[3] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
                            SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[3]);
                            variables->rect_window0_state2_3_text_texture[3].x = 403; variables->rect_window0_state2_3_text_texture[3].y = 130;
                            SDL_FreeSurface(surface_temporary_ttf);

                            SDL_Event event_clear;
                            variables->textbox_variables[4]->TextBox(&event_clear,variables->textbox_data[4],variables->textbox_settings0[4],0);
                    }
                break;

                case 4:
                    {
                            SDL_DestroyTexture(variables->window0_state2_3_text_texture[4]);

                            this->global_variables->universal_tool0->uint32_to_string(variables->screen_width_share_int,buffor0);
                            SDL_Surface* surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)buffor0,main_color1);
                            variables->window0_state2_3_text_texture[4] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
                            SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[4]);
                            variables->rect_window0_state2_3_text_texture[4].x = 403; variables->rect_window0_state2_3_text_texture[4].y = 146;
                            SDL_FreeSurface(surface_temporary_ttf);
                    }
                break;

                case 5:
                    {
                            SDL_DestroyTexture(variables->window0_state2_3_text_texture[5]);

                            this->global_variables->universal_tool0->uint32_to_string(variables->screen_height_share_int,buffor0);
                            SDL_Surface* surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)buffor0,main_color1);
                            variables->window0_state2_3_text_texture[5] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
                            SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[5]);
                            variables->rect_window0_state2_3_text_texture[5].x = 403; variables->rect_window0_state2_3_text_texture[5].y = 162;
                            SDL_FreeSurface(surface_temporary_ttf);
                    }
                break;

                case 6:
                    {
                            SDL_DestroyTexture(variables->window0_state2_3_text_texture[6]);

                            if(variables->server_password_required==1) surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,"yes",main_color1);
                            else surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,"no",main_color1);
                            variables->window0_state2_3_text_texture[6] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
                            SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[6]);
                            variables->rect_window0_state2_3_text_texture[6].x = 403; variables->rect_window0_state2_3_text_texture[6].y = 178;
                            SDL_FreeSurface(surface_temporary_ttf);

                    }
                break;

                case 7:
                    {
                        SDL_DestroyTexture(variables->window0_state2_3_text_texture[7]);

                        if(variables->server_hash_activate==1) surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,"yes",main_color1);
                        else surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,"no",main_color1);
                        variables->window0_state2_3_text_texture[7] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
                        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[7]);
                        variables->rect_window0_state2_3_text_texture[7].x = 403; variables->rect_window0_state2_3_text_texture[7].y = 194;
                        SDL_FreeSurface(surface_temporary_ttf);
                    }
                break;

                case 8:
                    {
                        SDL_DestroyTexture(variables->window0_state2_3_text_texture[8]);

                        surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,(const char*)variables->message0_server,main_color1);
                        variables->window0_state2_3_text_texture[8] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
                        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[8]);
                        variables->rect_window0_state2_3_text_texture[8].x = 284; variables->rect_window0_state2_3_text_texture[8].y = 229;
                        SDL_FreeSurface(surface_temporary_ttf);
                    }
                break;

                case 9:
                    {
                        SDL_DestroyTexture(variables->window0_state2_3_text_texture[9]);

                        surface_temporary_ttf = TTF_RenderUTF8_Solid(variables->ThreadFriendly_global_variables->main_ttf,(const char*)variables->message1_server,main_color1);
                        variables->window0_state2_3_text_texture[9] = SDL_CreateTextureFromSurface(variables->ThreadFriendly_global_variables->render,surface_temporary_ttf);
                        SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state2_3_text_texture[9]);
                        variables->rect_window0_state2_3_text_texture[9].x = 284; variables->rect_window0_state2_3_text_texture[9].y = 245;
                        SDL_FreeSurface(surface_temporary_ttf);
                    }
                break;

                default:
                    {
                        #ifdef MAIN_PROGRAM0_DEBUG
                        printf_error_args("wrong variable \"which_texture_to_change\"in function Client_Menu::client_unpack_vectors: %zd\n",
                                          variables->thread_vector_update_window0_state2_state3[i].which_texture_to_change);
                        #endif
                    }
                break;

            }
            last_array_index_of_window0_state2_state3 = variables->thread_vector_update_window0_state2_state3.size(); //variable may change in another thread so better is to update it each time;
        }
        variables->thread_vector_update_window0_state2_state3.clear();
    }

    int last_array_index_of_stdout_stderr = variables->thread_vector_stdout_stderr->size();
    if(last_array_index_of_stdout_stderr!=0)
    {
        for(int i = 0; i!=last_array_index_of_stdout_stderr; i++)
        {
            if(variables->thread_vector_stdout_stderr[0][i].stdout_or_stderr==0)
            {
                printf((const char*)variables->thread_vector_stdout_stderr[0][i].buffor);
            }
            else
            {
                printf_error((const char*)variables->thread_vector_stdout_stderr[0][i].buffor);
            }

            if(variables->thread_vector_stdout_stderr[0][i].free_memory==1)
            {
                free(variables->thread_vector_stdout_stderr[0][i].buffor);
            }

            last_array_index_of_stdout_stderr = variables->thread_vector_stdout_stderr->size();
        }
        variables->thread_vector_stdout_stderr->clear();
    }


    return;
}
