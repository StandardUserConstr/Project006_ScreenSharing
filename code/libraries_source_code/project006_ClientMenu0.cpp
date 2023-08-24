#include "../libraries/project006_main_program_headers0.h"

void Client_Menu::event_client_menu(Client_Menu_Variables* variables)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type)
    {
        case SDL_WINDOWEVENT:
            if(event.window.event==SDL_WINDOWEVENT_CLOSE)
            {
                if(event.window.windowID==variables->window0_ID)
                {
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    close event on window0: program is closing\n",0,0});
                    #endif

                    variables->return_value = 1;
                    this->close_program = 1;
                }
                else if(event.window.windowID==variables->window1_ID)
                {
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    close event on window1: window1 is hidden\n",0,0});
                    #endif

                    SDL_HideWindow(variables->window1);
                    variables->window1_hide = 1;
                }
                else if(event.window.windowID==variables->window2_ID)
                {
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    close event on window2: window2 is hidden\n",0,0});
                    #endif

                    variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": preview window has been hidden;\n",(char*)"preview window has been hidden;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                    SDL_HideWindow(variables->window2);
                    variables->window2_hide = 1;
                }
            }
            else if(event.window.event==SDL_WINDOWEVENT_FOCUS_GAINED)
            {
                if(event.window.windowID==variables->window0_ID)
                {
                    #ifdef MAIN_PROGRAM0_DEBUG
                    if(variables->window0_display==0) variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    focus gained event on window0: window0 is showing\n",0,0});
                    #endif
                    variables->window0_display = 1;
                }
                else if(event.window.windowID==variables->window1_ID)
                {
                    #ifdef MAIN_PROGRAM0_DEBUG
                    if(variables->window1_minimalize==1)
                    {
                        variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    focus gained on window1: window1 is showing\n",0,0});
                    }
                    #endif
                    variables->window1_minimalize = 0;
                }
                else if(event.window.windowID==variables->window2_ID)
                {
                    #ifdef MAIN_PROGRAM0_DEBUG
                    if(variables->window2_minimalize==1) variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    focus gained on window2: window2 is showing\n",0,0});
                    #endif
                    variables->window2_minimalize = 0;
                    variables->bar_animation_opacity = 1;
                }
            }
        break;
    }

    if((SDL_GetWindowFlags(this->global_variables->window)&SDL_WINDOW_INPUT_FOCUS)!=0)
    {
        do
        {
            switch(event.type)
            {

                case SDL_MOUSEBUTTONDOWN:
                    {
                        if(event.button.button==SDL_BUTTON_LEFT)
                        {
                            if(event.motion.y>=5&&event.motion.y<=19)
                            {
                                if(event.motion.x>=447&&event.motion.x<=463)
                                {
                                    variables->window0_mouse_state = 1;
                                    variables->window0_animation = 1;
                                }
                                else if(event.motion.x>=473&&event.motion.x<=489)
                                {
                                    variables->window0_mouse_state = 2;
                                    variables->window0_animation = 2;
                                }
                                else if(event.motion.x>=491&&event.motion.x<=507)
                                {
                                    variables->window0_mouse_state = 3;
                                    variables->window0_animation = 3;
                                }
                                else
                                {
                                    variables->window0_mouse_state = 0;
                                    variables->window0_animation = 0;
                                }
                            }
                            else if(event.motion.y>=377&&event.motion.y<=400)
                            {
                                if(variables->window0_state==0)
                                {
                                    if(event.motion.x>=392&&event.motion.x<=506)
                                    {
                                        variables->window0_mouse_state = 4;
                                        variables->window0_animation = 4;
                                    }
                                    else
                                    {
                                        variables->window0_mouse_state = 0;
                                        variables->window0_animation = 0;
                                    }

                                }
                                else
                                {
                                    if(event.motion.x>=284&&event.motion.x<=388)
                                    {
                                        variables->window0_mouse_state = 5;
                                        variables->window0_animation = 5;
                                    }
                                    else
                                    {
                                        variables->window0_mouse_state = 0;
                                        variables->window0_animation = 0;
                                    }
                                }

                            }
                            else
                            {
                                variables->window0_mouse_state = 0;
                                variables->window0_animation = 0;
                            }
                        }
                        else
                        {
                            variables->window0_mouse_state = 0;
                            variables->window0_animation = 0;
                        }
                    }
                break;

                case SDL_MOUSEMOTION:
                    {
                        if(event.motion.windowID==variables->window1_ID)
                        {
                            variables->beam_is_unlock = 1;
                            this->do_prepared_textboxes(&event,variables);
                        }
                        else variables->beam_is_unlock = 0;

                        if(variables->window0_mouse_state!=0)
                        {
                            switch(variables->window0_mouse_state)
                            {
                                case 1:
                                    {
                                        if(!((event.motion.y>=5&&event.motion.y<=19)&&(event.motion.x>=447&&event.motion.x<=463)))
                                        {
                                            variables->window0_animation = 0;
                                        }
                                        else variables->window0_animation = 1;
                                    }
                                break;

                                case 2:
                                    {
                                        if(!((event.motion.y>=5&&event.motion.y<=19)&&(event.motion.x>=473&&event.motion.x<=489)))
                                        {
                                            variables->window0_animation = 0;
                                        }
                                        else variables->window0_animation = 2;
                                    }
                                break;

                                case 3:
                                    {
                                        if(!((event.motion.y>=5&&event.motion.y<=19)&&(event.motion.x>=491&&event.motion.x<=507)))
                                        {
                                            variables->window0_animation = 0;
                                        }
                                        else variables->window0_animation = 3;
                                    }
                                break;

                                case 4:
                                    {
                                        if(!((event.motion.y>=377&&event.motion.y<=400)&&(event.motion.x>=392&&event.motion.x<=506)))
                                        {
                                            variables->window0_animation = 0;
                                        }
                                        else variables->window0_animation = 4;
                                    }
                                break;

                                case 5:
                                    {
                                        if(!((event.motion.y>=377&&event.motion.y<=400)&&(event.motion.x>=284&&event.motion.x<=388)))
                                        {
                                            variables->window0_animation = 0;
                                        }
                                        else variables->window0_animation = 5;
                                    }
                                break;


                            }
                        }
                    }
                break;

                case SDL_MOUSEBUTTONUP:
                    {
                        if(variables->window0_mouse_state!=0&&event.button.button==SDL_BUTTON_LEFT)
                        {
                            switch(variables->window0_mouse_state)
                            {
                                //DISPLAY_HIDE_WINDOW1
                                case 1:
                                    {
                                        if(((event.motion.y>=5&&event.motion.y<=19)&&(event.motion.x>=447&&event.motion.x<=463)))
                                        {

                                            if(variables->window1_hide==1)
                                            {
                                                #ifdef MAIN_PROGRAM0_DEBUG
                                                variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    display window1 event: window1 shown\n",0,0});
                                                #endif
                                                SDL_RestoreWindow(variables->window1);
                                                SDL_ShowWindow(variables->window1);
                                                variables->window1_hide = 0;
                                                variables->window1_minimalize = 0;

                                            }
                                            else
                                            {
                                                #ifdef MAIN_PROGRAM0_DEBUG
                                                variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    display window1 event: window1 hidden\n",0,0});
                                                #endif
                                                SDL_HideWindow(variables->window1);
                                                variables->window1_hide = 1;
                                                //SDL_RestoreWindow(variables->window1);
                                            }
                                        }
                                    }
                                break;

                                //MINIMALIZE_WINDOW0
                                case 2:
                                    {
                                        if(((event.motion.y>=5&&event.motion.y<=19)&&(event.motion.x>=473&&event.motion.x<=489)))
                                        {
                                            #ifdef MAIN_PROGRAM0_DEBUG
                                            variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    minimize window0 event: window0 minimized\n",0,0});
                                            #endif
                                            SDL_MinimizeWindow(this->global_variables->window);
                                            variables->window0_display = 0;
                                        }
                                    }
                                break;

                                //CLOSE_WINDOW0
                                case 3:
                                    {
                                        if(((event.motion.y>=5&&event.motion.y<=19)&&(event.motion.x>=491&&event.motion.x<=507)))
                                        {
                                            #ifdef MAIN_PROGRAM0_DEBUG
                                            variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    close window0 event: window0 is closing\n",0,0});
                                            #endif
                                            variables->return_value = 1;
                                            this->close_program = 1;
                                        }
                                    }
                                break;

                                //START_CLIENT_BUTTON_WINDOW0
                                case 4:
                                    {
                                        if(((event.motion.y>=377&&event.motion.y<=400)&&(event.motion.x>=392&&event.motion.x<=506)))
                                        {
                                            if(variables->public_ip_int==0)
                                            {
                                                #ifdef MAIN_PROGRAM0_DEBUG
                                                variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    window0 state0 event: error\n",1,0});
                                                variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                                                #endif
                                                SDL_Color background = (SDL_Color){255,255,255,0};
                                                variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": refresh your public ip before trying to connect;\n",(char*)"refresh your public ip before trying to connect;",(SDL_Color){0,0,0,0},background,0});
                                            }
                                            else
                                            {
                                                //create client, send signal to another thread to start tryting to connect to the server;
                                                SDL_Event clear_event;                          // if something in textboxes changed and difference in variables wasn't updated;
                                                clear_event.type = SDL_MOUSEMOTION;          //
                                                clear_event.motion.x = 0;                       //
                                                clear_event.motion.y = 100;                     //
                                                variables->VARIABLE_do_prepared_textboxes_FORCE_TO_RESET_TO_0 = 1;
                                                this->do_prepared_textboxes(&clear_event,variables);  //
                                                clear_event.type = SDL_MOUSEBUTTONUP;         //
                                                variables->VARIABLE_do_prepared_textboxes_FORCE_TO_RESET_TO_0 = 1;
                                                this->do_prepared_textboxes(&clear_event,variables);  //
                                                clear_event.type = SDL_MOUSEBUTTONDOWN;           //
                                                variables->VARIABLE_do_prepared_textboxes_FORCE_TO_RESET_TO_0 = 1;
                                                this->do_prepared_textboxes(&clear_event,variables);  //
                                                //this->force_update_textboes(variables);
                                                int error = variables->client.create_client((const char*)variables->server_ip,(const char*)variables->server_port,&variables->client_structure);
                                                if(error!=0)
                                                {
                                                    #ifdef MAIN_PROGRAM0_DEBUG
                                                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    window0 state0 event: error\n",1,0});
                                                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                                                    #endif

                                                    variables->client.close_client(&variables->client_structure);

                                                    SDL_Color background = (SDL_Color){168,0,0,0};
                                                    char* buffor0;
                                                    char* buffor1;
                                                    #ifdef MAIN_PROGRAM0_DEBUG
                                                    buffor0 = (char*)malloc(128);
                                                    sprintf(buffor0,"ERROR: failed to create the client; winsock error: %d\n\n",error);
                                                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)buffor0,1,1});
                                                    #endif
                                                    variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": failed to create the client;\n",(char*)"failed to create the client;",(SDL_Color){255,255,255,0},background,0});
                                                    buffor0 = (char*)malloc(64);
                                                    sprintf(buffor0,"    winsock error: %d;",error);
                                                    buffor1 = (char*)malloc(64);
                                                    sprintf(buffor1,":   winsock error: %d;\n",error);
                                                    variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){buffor1,buffor0,(SDL_Color){255,0,0,0},(SDL_Color){0,0,0,255},1});
                                                    break;
                                                }
                                                #ifdef MAIN_PROGRAM0_DEBUG
                                                variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    window0 state0 event: client is created\n",0,0});
                                                variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                                                #endif


                                                variables->thread_vector_reset_windows_request[0].push_back({1});
                                                variables->diode_blue_counter = 2;
                                                variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client has been created;\n",(char*)"client has been created;",(SDL_Color){0,168,0,0},(SDL_Color){0,0,0,255},0});
                                                variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client is trying to connect to the server;\n",(char*)"client is trying to connect to the server;",(SDL_Color){0,0,168,0},(SDL_Color){0,0,0,255},0});
                                                //important lines for THREAD:
                                                //    variables->client.create_client();
                                                //    variables->thread_vector_reset_windows_request[0].push_back({1});
                                            }

                                        }
                                    }
                                break;

                                //STOP_CLIENT_BUTTON_WINDOW0
                                case 5:
                                    {
                                        if(((event.motion.y>=377&&event.motion.y<=400)&&(event.motion.x>=284&&event.motion.x<=388)))
                                        {
                                            #ifdef MAIN_PROGRAM0_DEBUG
                                            variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    window0 state1|2|3 event: client is destroyed\n",0,0});
                                            variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                                            #endif

                                            if(variables->client_structure.connected_with_the_server==1) //if connected with the server
                                            {
                                                variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client has been disconnected\n",(char*)"client has been disconnected;",(SDL_Color){168,0,0,0},(SDL_Color){0,0,0,255},0});
                                                variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client has been destroyed;\n",(char*)"client has been destroyed;",(SDL_Color){168,0,0,0},(SDL_Color){0,0,0,255},0});
                                                variables->client_is_trying_to_disconnect = 1;
                                                variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){4}); //disconnect
                                                while(variables->client_is_trying_to_disconnect==1) SDL_Delay(1);     //thread lock (waiting for client to send disconnect signal and reset window with variables and close client);
                                                variables->window0_state = 0;
                                                variables->thread_vector_reset_windows_request[0].push_back({0});
                                            }
                                            else
                                            {
                                                variables->client_is_trying_to_disconnect = 1;
                                                while(variables->client_is_trying_to_disconnect==1) SDL_Delay(1);     //thread lock (waiting for client to reset window with variables and close client);
                                                variables->window0_state = 0;
                                                variables->thread_vector_reset_windows_request[0].push_back({0});
                                                variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": client has been destroyed;\n",(char*)"client has been destroyed;",(SDL_Color){168,0,0,0},(SDL_Color){0,0,0,255},0});
                                                //variables->client.close_client(&variables->client_structure);
                                                //variables->thread_vector_receive[0].clear();
                                                //variables->thread_vector_send_receive[0].clear();
                                            }

                                        }
                                    }
                                break;

                            }
                        }
                        variables->window0_mouse_state = 0;
                        variables->window0_animation = 0;
                    }
                break;

                case SDL_MOUSEWHEEL:
                    {
                        int x,y;
                        SDL_GetMouseState(&x,&y);
                        if(((y>=33&&y<=variables->H_MAX_OF_DISPLAY+59)&&(x>=9&&x<=267)))
                        {
                            if(event.wheel.y>0)// scroll up
                            {

                                if(variables->rect_logs_src.y!=0)
                                {
                                    variables->rect_logs_src.y-=39;
                                    if(variables->rect_logs_src.y<0) variables->rect_logs_src.y = 0;
                                }

                            }
                            else
                            {
                                if(variables->y_logs_position-variables->rect_logs_src.y>variables->H_MAX_OF_DISPLAY-1)
                                {
                                    variables->rect_logs_src.y+=39;
                                    if(variables->y_logs_position-variables->rect_logs_src.y<variables->H_MAX_OF_DISPLAY-1) variables->rect_logs_src.y-=13;
                                    if(variables->y_logs_position-variables->rect_logs_src.y<variables->H_MAX_OF_DISPLAY-1) variables->rect_logs_src.y-=13;
                                }

                            }
                        }

                    }break;

            }
        }while(SDL_PollEvent(&event));

    }
    else if(((SDL_GetWindowFlags(variables->window1)&SDL_WINDOW_INPUT_FOCUS)!=0))
    {
        do
        {
            this->do_prepared_textboxes(&event,variables);  //textbox_events
            switch(event.type)
            {
                    case SDL_MOUSEBUTTONDOWN:
                    {
                        if(event.button.button==SDL_BUTTON_LEFT)
                        {
                            if(event.motion.y>=94&&event.motion.y<=117&&event.motion.x>=170&&event.motion.x<=245)
                            {
                                    variables->window1_mouse_state = 1;
                                    variables->window1_animation = 1;
                            }
                            else if(event.motion.y>=7&&event.motion.y<=20)
                            {
                                if(event.motion.x>=568&&event.motion.x<=584)
                                {
                                    variables->window1_mouse_state = 2;
                                    variables->window1_animation = 2;
                                }
                                else if((event.motion.x>=586&&event.motion.x<=602))
                                {
                                    variables->window1_mouse_state = 3;
                                    variables->window1_animation = 3;
                                }
                                else
                                {
                                    variables->window1_mouse_state = 0;
                                    variables->window1_animation = 0;
                                }

                            }
                            else if((event.motion.y>=302&&event.motion.y<=315&&event.motion.x>=461&&event.motion.x<=474))
                            {
                                variables->window1_mouse_state = 4;
                                variables->window1_animation = 4;
                            }
                            else if((event.motion.y>=271&&event.motion.y<=284&&event.motion.x>=572&&event.motion.x<=585))
                            {
                                variables->window1_mouse_state = 5;
                                variables->window1_animation = 5;
                            }
                            else if((variables->window1_state==2)&&(event.motion.y>=295&&event.motion.y<=318)&&(event.motion.x>=249&&event.motion.x<=324))
                            {
                                variables->window1_mouse_state = 6;
                                variables->window1_animation = 6;
                            }
                            else
                            {
                                variables->window1_mouse_state = 0;
                                variables->window1_animation = 0;
                            }
                        }
                        else
                        {
                            variables->window1_mouse_state = 0;
                            variables->window1_animation = 0;
                        }
                    }
                break;

                case SDL_MOUSEMOTION:
                    {
                        if(event.motion.windowID==variables->window1_ID) variables->beam_is_unlock = 1;
                        else variables->beam_is_unlock = 0;
                        if(variables->window1_mouse_state!=0)
                        {
                            switch(variables->window1_mouse_state)
                            {
                                case 1:
                                    {
                                        if(!(event.motion.y>=94&&event.motion.y<=117&&event.motion.x>=170&&event.motion.x<=245))
                                        {
                                            variables->window1_animation = 0;
                                        }
                                        else variables->window1_animation = 1;
                                    }
                                break;

                                case 2:
                                    {
                                        if(!(event.motion.y>=7&&event.motion.y<=20&&event.motion.x>=568&&event.motion.x<=584))
                                        {
                                            variables->window1_animation = 0;
                                        }
                                        else variables->window1_animation = 2;
                                    }
                                break;

                                case 3:
                                    {
                                        if(!((event.motion.y>=5&&event.motion.y<=19)&&(event.motion.x>=586&&event.motion.x<=602)))
                                        {
                                            variables->window1_animation = 0;
                                        }
                                        else variables->window1_animation = 3;
                                    }
                                break;

                                case 4:
                                    {
                                        if(!(event.motion.y>=302&&event.motion.y<=315&&event.motion.x>=461&&event.motion.x<=474))
                                        {
                                            variables->window1_animation = 0;
                                        }
                                        else variables->window1_animation = 4;
                                    }
                                break;

                                case 5:
                                    {
                                        if(!(event.motion.y>=271&&event.motion.y<=284&&event.motion.x>=572&&event.motion.x<=585))
                                        {
                                            variables->window1_animation = 0;
                                        }
                                        else variables->window1_animation = 5;
                                    }
                                break;


                                case 6:
                                    {
                                        if(!((event.motion.y>=295&&event.motion.y<=318)&&(event.motion.x>=249&&event.motion.x<=324)))
                                        {
                                            variables->window1_animation = 0;
                                        }
                                        else variables->window1_animation = 6;
                                    }
                                break;



                                default: break;

                            }
                        }
                    }
                break;

                case SDL_MOUSEBUTTONUP:
                    {
                        if(variables->window1_mouse_state!=0&&event.button.button==SDL_BUTTON_LEFT)
                        {
                            switch(variables->window1_mouse_state)
                            {
                                //REFRESH
                                case 1:
                                    {
                                        if((event.motion.y>=94&&event.motion.y<=117&&event.motion.x>=170&&event.motion.x<=245))
                                        {
                                            #ifdef MAIN_PROGRAM0_DEBUG
                                            variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    refresh window1 event: refreshing public ip\n",0,0});
                                            variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                                            #endif
                                            if(get_public_IPv4(variables->public_ip_string,&variables->public_ip_int)!=0)
                                            {
                                                variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": error while refreshing your public ip;\n",(char*)"error while refreshing your public ip;",(SDL_Color){255,255,255,0},(SDL_Color){255,0,0,0}});
                                                #ifdef MAIN_PROGRAM0_DEBUG
                                                variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"cannot get your public ip from \"whatismyip.akamai.com\"\ncheck internet connection and try again\n\n",0,0});
                                                #endif
                                                this->global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_WARNING,"WARNING","cannot get your public ip from \"whatismyip.akamai.com\"\ncheck internet connection and try again","OK");
                                            }
                                            else
                                            {
                                                SDL_Surface* surface_temporary_ttf = TTF_RenderUTF8_Solid(global_variables->main_ttf,(const char*)variables->public_ip_string,(SDL_Color){135,136,143,0});
                                                SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window1_public_ip);
                                                SDL_DestroyTexture(variables->window1_public_ip);
                                                variables->rect_window1_public_ip.x = 137; variables->rect_window1_public_ip.y = 76;
                                                variables->window1_public_ip = SDL_CreateTextureFromSurface(variables->render1,surface_temporary_ttf);
                                                SDL_FreeSurface(surface_temporary_ttf);

                                                if(variables->window0_state==1)
                                                {
                                                    surface_temporary_ttf = TTF_RenderUTF8_Solid(global_variables->main_ttf,(const char*)variables->public_ip_string,(SDL_Color){135,136,143,0});
                                                    SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state0_text_texture[2]);
                                                    SDL_DestroyTexture(variables->window0_state0_text_texture[2]);
                                                    variables->window0_state0_text_texture[2] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
                                                    variables->rect_window0_state0_text_texture[2].x = 403; variables->rect_window0_state0_text_texture[2].y = 114;
                                                    SDL_FreeSurface(surface_temporary_ttf);
                                                }
                                                else if(variables->window0_state==0)
                                                {
                                                    surface_temporary_ttf = TTF_RenderUTF8_Solid(global_variables->main_ttf,(const char*)variables->public_ip_string,(SDL_Color){0,0,0,0});
                                                    SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window0_state0_text_texture[2]);
                                                    SDL_DestroyTexture(variables->window0_state0_text_texture[2]);
                                                    variables->window0_state0_text_texture[2] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
                                                    variables->rect_window0_state0_text_texture[2].x = 403; variables->rect_window0_state0_text_texture[2].y = 114;
                                                    SDL_FreeSurface(surface_temporary_ttf);
                                                }


                                                variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": your public ip has been refreshed;\n",(char*)"your public ip has been refreshed;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                                            }
                                        }
                                    }
                                break;

                                //MINIMALIZE_WINDOW1
                                case 2:
                                    {
                                        if((event.motion.y>=7&&event.motion.y<=20&&event.motion.x>=568&&event.motion.x<=584))
                                        {
                                            #ifdef MAIN_PROGRAM0_DEBUG
                                            variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    minimize window1 event: window1 minimized\n",0,0});
                                            #endif
                                            SDL_MinimizeWindow(variables->window1);
                                            variables->window1_minimalize = 1;
                                        }
                                    }
                                break;

                                //CLOSE_WINDOW1
                                case 3:
                                    {
                                        if(((event.motion.y>=5&&event.motion.y<=19)&&(event.motion.x>=586&&event.motion.x<=602)))
                                        {
                                            #ifdef MAIN_PROGRAM0_DEBUG
                                            variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    close window1 event: window1 is closing\n",0,0});
                                            #endif
                                            SDL_HideWindow(variables->window1);
                                            variables->window1_hide = 1;
                                        }
                                    }
                                break;

                                //WINDOW2_DISPLAY_BUTTON
                                case 4:
                                    {
                                        if((event.motion.y>=302&&event.motion.y<=315&&event.motion.x>=461&&event.motion.x<=474))
                                        {
                                            #ifdef MAIN_PROGRAM0_DEBUG
                                            variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    button window1 event: display window2 button pressed\n",0,0});
                                            variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                                            #endif
                                            if(variables->window2_hide==1)
                                            {
                                                variables->window2_is_fullscreen = 0;
                                                variables->window2_hide = 0;
                                                variables->window2_minimalize = 0;
                                                variables->window2_hittest.h = variables->screen_height_preview;
                                                variables->window2_hittest.w = variables->screen_width_preview-55;
                                                variables->rect_window2_bar = (SDL_Rect){(int)variables->screen_width_preview-54,0,54,19};
                                                SDL_SetWindowFullscreen(variables->window2,0);
                                                variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": preview window has been displayed;\n",(char*)"preview window has been displayed;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                                                SDL_RestoreWindow(variables->window2);
                                                SDL_ShowWindow(variables->window2);

                                            }
                                            else
                                            {
                                                variables->window2_hide = 1;
                                                variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": preview window has been hidden;\n",(char*)"preview window has been hidden;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                                                SDL_HideWindow(variables->window2);
                                            }
                                        }
                                    }
                                break;

                                //WINDOW2_ALWAYS_TOP
                                case 5:
                                    {
                                        if((event.motion.y>=271&&event.motion.y<=284&&event.motion.x>=572&&event.motion.x<=585))
                                        {
                                            #ifdef MAIN_PROGRAM0_DEBUG
                                            variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    button window1 event: always top window2 button pressed\n",0,0});
                                            variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                                            #endif
                                            if(variables->always_top_window2==1)
                                            {
                                                variables->always_top_window2 = 0;
                                                variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": preview window isn't always top now;\n",(char*)"preview window isn't always top now;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                                                SDL_SetWindowAlwaysOnTop(variables->window2,SDL_FALSE);
                                                SDL_RaiseWindow(variables->window1);
                                            }
                                            else
                                            {
                                                variables->always_top_window2 = 1;
                                                variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": preview window is always top now;\n",(char*)"preview window is always top now;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                                                SDL_SetWindowAlwaysOnTop(variables->window2,SDL_TRUE);
                                                SDL_RaiseWindow(variables->window1);
                                            }
                                        }
                                    }
                                break;

                                //SEND_MESSAGE
                                case 6:
                                    {
                                        if((event.motion.y>=295&&event.motion.y<=318)&&(event.motion.x>=249&&event.motion.x<=324))
                                        {
                                            bool send_message_or_not = 1;
                                            for(size_t i = 0; i!=variables->thread_vector_send_receive[0].size(); i++)
                                            {
                                                if(variables->thread_vector_send_receive[0][i].operation_code==1)
                                                {
                                                    send_message_or_not = 0;
                                                    break;
                                                }
                                            }
                                            if(send_message_or_not==1)
                                            {
                                                #ifdef MAIN_PROGRAM0_DEBUG
                                                variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    send window1 event: message sended to the server\n",0,0});
                                                variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                                                #endif
                                                variables->thread_vector_send_receive[0].push_back((Client_Menu::vector_thread_send_receive){1});
                                            }
                                            else
                                            {
                                                #ifdef MAIN_PROGRAM0_DEBUG
                                                variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    send window1 event error: message is already waiting to be sended\n",0,0});
                                                #endif
                                            }
                                        }
                                    }
                                break;
                            }
                        }
                        variables->window1_mouse_state = 0;
                        variables->window1_animation = 0;
                    }
                break;
                default: break;
            }
        }while(SDL_PollEvent(&event));

    }
    if((SDL_GetWindowFlags(variables->window2)&SDL_WINDOW_INPUT_FOCUS)!=0)
    {
        variables->bar_animation_opacity = 1;
        do
        {
            if(variables->window2_is_fullscreen==1)
            {
                if(event.key.keysym.sym==SDLK_ESCAPE)
                {
                    #ifdef MAIN_PROGRAM0_DEBUG
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    window2 quit fullscreen\n",0,0});
                    #endif
                    variables->window2_is_fullscreen = 0;
                    //if(variables->window0_state!=3)
                    //{
                        variables->window2_hittest.h = variables->screen_height_preview;
                        variables->window2_hittest.w = variables->screen_width_preview-55;
                        variables->rect_window2_bar = (SDL_Rect){(int)variables->screen_width_preview-54,0,54,19};
                    //}
                    SDL_SetWindowFullscreen(variables->window2,0);
                }
            }
            else
            {
                switch(event.type)
                {
                        case SDL_MOUSEBUTTONDOWN:
                        {
                            if(event.button.button==SDL_BUTTON_LEFT)
                            {
                                if(event.motion.y>=2&&event.motion.y<=16)
                                {
                                    if(event.motion.x>=(variables->screen_width_preview-54+2)&&event.motion.x<(variables->screen_width_preview-54+18))
                                    {
                                        variables->window2_mouse_state = 1;
                                        variables->window2_animation = 1;
                                    }
                                    else if(event.motion.x>=(variables->screen_width_preview-54+18)&&event.motion.x<=(variables->screen_width_preview-54+34))
                                    {
                                        variables->window2_mouse_state = 2;
                                        variables->window2_animation = 2;

                                    }
                                    else if(event.motion.x>=(variables->screen_width_preview-54+36)&&event.motion.x<=(variables->screen_width_preview-54+54))
                                    {
                                        variables->window2_mouse_state = 3;
                                        variables->window2_animation = 3;
                                    }
                                    else
                                    {
                                        variables->window2_mouse_state = 0;
                                        variables->window2_animation = 0;
                                    }

                                }
                                else
                                {
                                    variables->window2_mouse_state = 0;
                                    variables->window2_animation = 0;
                                }
                            }
                            else
                            {
                                variables->window2_mouse_state = 0;
                                variables->window2_animation = 0;
                            }
                        }
                    break;

                    case SDL_MOUSEMOTION:
                        {
                            if(event.motion.windowID==variables->window1_ID)
                            {
                                variables->beam_is_unlock = 1;
                                this->do_prepared_textboxes(&event,variables);
                            }
                            else variables->beam_is_unlock = 0;
                            switch(variables->window2_mouse_state)
                            {
                                case 1:
                                    {
                                        if(!(event.motion.y>=2&&event.motion.y<=16&&event.motion.x>=(variables->screen_width_preview-54+2)&&event.motion.x<(variables->screen_width_preview-54+18)))
                                        {
                                            variables->window2_animation = 0;
                                        }
                                        else variables->window2_animation = 1;
                                    }
                                break;

                                case 2:
                                    {
                                        if(!(event.motion.y>=2&&event.motion.y<=16&&event.motion.x>=(variables->screen_width_preview-54+18)&&event.motion.x<=(variables->screen_width_preview-54+34)))
                                        {
                                            variables->window2_animation = 0;
                                        }
                                        else variables->window2_animation = 2;
                                    }
                                break;

                                case 3:
                                    {
                                        if(!(event.motion.y>=2&&event.motion.y<=16&&event.motion.x>=(variables->screen_width_preview-54+36)&&event.motion.x<=(variables->screen_width_preview-54+54)))
                                        {
                                            variables->window2_animation = 0;
                                        }
                                        else variables->window2_animation = 3;
                                    }
                                break;
                            }
                        }
                        break;


                        case SDL_MOUSEBUTTONUP:
                        {
                            if(event.button.button==SDL_BUTTON_LEFT)
                            {
                                switch(variables->window2_mouse_state)
                                {

                                    //MINIMALIZE_WINDOW2
                                    case 1:
                                        {
                                            if((event.motion.y>=2&&event.motion.y<=16&&event.motion.x>=(variables->screen_width_preview-54+2)&&event.motion.x<(variables->screen_width_preview-54+18)))
                                            {
                                                #ifdef MAIN_PROGRAM0_DEBUG
                                                variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    minimize window2 event: window2 minimized\n",0,0});
                                                #endif
                                                SDL_MinimizeWindow(variables->window2);
                                                variables->window2_minimalize = 1;
                                            }
                                        }
                                    break;

                                    //FULLSCREEN_WINDOW2
                                    case 2:
                                        {
                                            if((event.motion.y>=2&&event.motion.y<=16&&event.motion.x>=(variables->screen_width_preview-54+18)&&event.motion.x<=(variables->screen_width_preview-54+34)))
                                            {
                                                #ifdef MAIN_PROGRAM0_DEBUG
                                                variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    maximize window2 event: window2 is now fullscreen\n",0,0});
                                                #endif
                                                variables->window2_hittest.h = 0;
                                                variables->window2_hittest.w = 0;
                                                variables->fullscreen_actual_opacity = 0;
                                                variables->fullscreen_info_timer0 = SDL_GetTicks();
                                                variables->fullscreen_info_timer1 = 0;
                                                variables->window2_is_fullscreen = 1;


                                                SDL_DisplayMode dm;
                                                SDL_GetCurrentDisplayMode(0, &dm);
                                                //variables->screen_width_preview = dm.w/2;
                                                //variables->screen_height_preview = dm.h/2;
                                                //variables->rect_window2_main = {0,0,dm.w,dm.h};
                                                SDL_SetTextureAlphaMod(variables->window2_fullscreen_information,0);
                                                //SDL_RenderCopy(variables->render2,variables->window2_main,NULL,NULL);
                                                SDL_SetWindowFullscreen(variables->window2,SDL_WINDOW_FULLSCREEN_DESKTOP);
                                                //SDL_RenderCopy(variables->render2,variables->window2_main,NULL,NULL);


                                            }
                                        }
                                    break;

                                    //CLOSE_WINDOW2
                                    case 3:
                                        {
                                            if((event.motion.y>=2&&event.motion.y<=16&&event.motion.x>=(variables->screen_width_preview-54+36)&&event.motion.x<=(variables->screen_width_preview-54+52)))
                                            {
                                                #ifdef MAIN_PROGRAM0_DEBUG
                                                variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    close window2 event: window2 is closing\n",0,0});
                                                variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    logs saved in \"files/client_logs.txt\"\n",0,0});
                                                #endif
                                                SDL_HideWindow(variables->window2);
                                                variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": preview window has been hidden;\n",(char*)"preview window has been hidden;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
                                                variables->window2_hide = 1;
                                            }
                                        }
                                    break;
                                }
                            }
                            variables->window2_mouse_state = 0;
                            variables->window2_animation = 0;
                        }
                    break;

                    default: break;
                }
            }
        }while(SDL_PollEvent(&event));
    }
    else
    {
        variables->bar_animation_opacity = 0;
        /*if(variables->window2_is_fullscreen==1)
        {
            #ifdef MAIN_PROGRAM0_DEBUG
            printf("    window2 quit fullscreen\n");
            #endif
            variables->window2_is_fullscreen = 0;
            //if(variables->window0_state!=3)
            //{
                variables->window2_hittest.h = variables->screen_height_preview;
                variables->window2_hittest.w = variables->screen_width_preview-55;
            //}
            SDL_SetWindowFullscreen(variables->window2,0);
            #ifdef MAIN_PROGRAM0_DEBUG
            printf("    close window2 event: window2 is closing\n");
            printf("    logs saved in \"files/server_logs.txt\"\n");
            #endif
            SDL_HideWindow(variables->window2);
            this->save_logs_to_file_and_create_texture(variables,": preview window has been hidden;\n","preview window has been hidden;",(SDL_Color){0,0,0,0});
            variables->window2_hide = 1;
        }*/
    }

    return;
}

void Client_Menu::client_paste_textures_to_render_and_display(Client_Menu_Variables* variables)
{
    static bool animation_mode = 0;
    static bool window1_input_focus;
    window1_input_focus = (SDL_GetWindowFlags(variables->window1)&SDL_WINDOW_INPUT_FOCUS);

    this->client_unpack_vectors(variables);
    if(variables->window0_display==1)
    {
//window0
        SDL_RenderClear(this->global_variables->render);
        SDL_RenderCopy(this->global_variables->render,variables->window0_main_background,NULL,&variables->rect_window0_main_background);
        if((SDL_GetWindowFlags(this->global_variables->window)&SDL_WINDOW_INPUT_FOCUS)==0) SDL_RenderCopy(this->global_variables->render,variables->window0_bar_lost_focus,NULL,&variables->rect_window0_bar_lost_focus);

        switch(variables->window0_state)
        {
            case 0: SDL_RenderCopy(this->global_variables->render,variables->window0_status_client_not_connected,NULL,&variables->rect_window0_status_client_not_connected);
                    for(int i = 0; i!=variables->COUNT_OF_WINDOW0_STATE0_TEXT_TEXTURE; i++) SDL_RenderCopy(this->global_variables->render,variables->window0_state0_text_texture[i],NULL,&variables->rect_window0_state0_text_texture[i]);
                    animation_mode = 0;
                break;

            case 1:
                    SDL_RenderCopy(this->global_variables->render,variables->window0_status_client_trying_to_connect,NULL,&variables->rect_window0_status_client_trying_to_connect);
                    for(int i = 0; i!=variables->COUNT_OF_WINDOW0_STATE0_TEXT_TEXTURE; i++) SDL_RenderCopy(this->global_variables->render,variables->window0_state0_text_texture[i],NULL,&variables->rect_window0_state0_text_texture[i]);
                    animation_mode = 0;
                break;

            case 2:
                    SDL_RenderCopy(this->global_variables->render,variables->window0_status_client_waiting_for_accept,NULL,&variables->rect_window0_status_client_waiting_for_accept);
                    for(int i = 0; i!=variables->COUNT_OF_WINDOW0_STATE2_3_TEXT_TEXTURE; i++) SDL_RenderCopy(this->global_variables->render,variables->window0_state2_3_text_texture[i],NULL,&variables->rect_window0_state2_3_text_texture[i]);
                    animation_mode = 1;
                break;

            case 3:
                    SDL_RenderCopy(this->global_variables->render,variables->window0_status_client_accepted,NULL,&variables->rect_window0_status_client_accepted);
                    for(int i = 0; i!=variables->COUNT_OF_WINDOW0_STATE2_3_TEXT_TEXTURE; i++) SDL_RenderCopy(this->global_variables->render,variables->window0_state2_3_text_texture[i],NULL,&variables->rect_window0_state2_3_text_texture[i]);
                    animation_mode = 1;

                break;

            default: break;
        }

        if(variables->window1_hide==0)
        {
                variables->rect_bar_pressed_button = {447,5,16,14};
                SDL_RenderCopy(this->global_variables->render,variables->window0_bar_pressed_button,NULL,&variables->rect_bar_pressed_button);
        }

        switch(variables->window0_animation)
        {
            //display window1;
            case 1:
                variables->rect_bar_pressed_button = {447,5,16,14};
                SDL_RenderCopy(this->global_variables->render,variables->window0_bar_pressed_button,NULL,&variables->rect_bar_pressed_button);
            break;

            //minimalize window0;
            case 2:
                variables->rect_bar_pressed_button = {473,5,16,14};
                SDL_RenderCopy(this->global_variables->render,variables->window0_bar_pressed_button,NULL,&variables->rect_bar_pressed_button);
            break;

            //close window0;
            case 3:
                variables->rect_bar_pressed_button = {491,5,16,14};
                SDL_RenderCopy(this->global_variables->render,variables->window0_bar_pressed_button,NULL,&variables->rect_bar_pressed_button);
            break;

            //start client window0;
            case 4:
                variables->rect_pressed_large_button = {392,377,104,23};
                SDL_RenderCopy(this->global_variables->render,variables->window0_pressed_large_button,NULL,&variables->rect_pressed_large_button);
            break;

            //stop client window0;
            case 5:
                variables->rect_pressed_large_button = {284,377,104,23};
                SDL_RenderCopy(this->global_variables->render,variables->window0_pressed_large_button,NULL,&variables->rect_pressed_large_button);
            break;
        }


        this->client_animation0(variables,animation_mode);

        if(variables->diode_red_counter!=0)
        {
            variables->diode_red_counter--;
            variables->how_much_fps_pass_without_red_diode = 0;
            SDL_RenderCopy(this->global_variables->render,variables->window0_red_diode,NULL,&variables->rect_red_diode);
        }
        else if(variables->how_much_fps_pass_without_red_diode!=4294967295) variables->how_much_fps_pass_without_red_diode++;

        if(variables->diode_blue_counter!=0)
        {
            variables->how_much_fps_pass_without_blue_diode = 0;
            variables->diode_blue_counter--;
            SDL_RenderCopy(this->global_variables->render,variables->window0_blue_diode,NULL,&variables->rect_blue_diode);
        }
        else if(variables->how_much_fps_pass_without_blue_diode!=4294967295) variables->how_much_fps_pass_without_blue_diode++;

        SDL_RenderCopy(this->global_variables->render,variables->main_logs_texture,&variables->rect_logs_src,&variables->rect_logs_dst);

        SDL_RenderPresent(this->global_variables->render);
    }

//window1
    if((variables->window1_hide==0&&variables->window1_minimalize==0))
    {
        SDL_RenderClear(variables->render1);
        SDL_RenderCopy(variables->render1,variables->window1_main_background,NULL,&variables->rect_window1_main_background);

        if(window1_input_focus==0) SDL_RenderCopy(variables->render1,variables->window1_bar_lost_focus,NULL,&variables->rect_window1_bar_lost_focus);


        if(variables->window2_hide==0)
        {
            variables->rect_selected_option = {461,302,13,13};
            SDL_RenderCopy(variables->render1,variables->window1_selected_option,NULL,&variables->rect_selected_option);
        }
        if(variables->always_top_window2==1)
        {
            variables->rect_selected_option = {572,271,13,13};
            SDL_RenderCopy(variables->render1,variables->window1_selected_option,NULL,&variables->rect_selected_option);
        }

        if(variables->window1_state==1) SDL_RenderCopy(variables->render1,variables->window1_state0,NULL,&variables->rect_window1_status0);
        else if(variables->window1_state==2) SDL_RenderCopy(variables->render1,variables->window1_state1,NULL,&variables->rect_window1_status1);


        switch(variables->window1_animation)
        {
            case 1:
                variables->rect_pressed_medium_button = {170,94,75,23};
                SDL_RenderCopy(variables->render1,variables->window1_pressed_medium_button,NULL,&variables->rect_pressed_medium_button);
            break;

            case 2:
                variables->rect_bar_pressed_button = {568,6,16,14};
                SDL_RenderCopy(variables->render1,variables->window1_bar_pressed_button,NULL,&variables->rect_bar_pressed_button);
            break;

            case 3:
                variables->rect_bar_pressed_button = {586,6,16,14};
                SDL_RenderCopy(variables->render1,variables->window1_bar_pressed_button,NULL,&variables->rect_bar_pressed_button);
            break;

            case 4:
                if(variables->window2_hide==0)
                {
                    variables->rect_pressed_selected_option = {463,304,9,9};
                    SDL_RenderCopy(variables->render1,variables->window1_pressed_selected_option,NULL,&variables->rect_pressed_selected_option);
                }
                else
                {
                    variables->rect_pressed_no_selected_option = {463,304,9,9};
                    SDL_RenderCopy(variables->render1,variables->window1_pressed_no_selected_option,NULL,&variables->rect_pressed_no_selected_option);
                }
            break;

            case 5:
                if(variables->always_top_window2==1)
                {
                    variables->rect_pressed_selected_option = {574,273,9,9};
                    SDL_RenderCopy(variables->render1,variables->window1_pressed_selected_option,NULL,&variables->rect_pressed_selected_option);
                }
                else
                {
                    variables->rect_pressed_no_selected_option = {574,273,9,9};
                    SDL_RenderCopy(variables->render1,variables->window1_pressed_no_selected_option,NULL,&variables->rect_pressed_no_selected_option);
                }
            break;

            case 6:
                variables->rect_pressed_medium_button = {249,295,75,23};
                SDL_RenderCopy(variables->render1,variables->window1_pressed_medium_button,NULL,&variables->rect_pressed_medium_button);
            break;

            default: break;

        }

        //text/textboxes
        SDL_RenderCopy(variables->render1,variables->window1_public_ip,NULL,&variables->rect_window1_public_ip);
        int do_display_beam = 0;
        for(int i = 0; i!=variables->COUNT_OF_TEXBOXES; i++)
        {
            SDL_RenderCopy(variables->render1,variables->textbox_variables[i]->get_text_texture(),NULL,variables->textbox_variables[i]->get_rect_of_text_texture());
            if(variables->textbox_variables[i]->should_beam_be_showed_or_not()==1&&window1_input_focus!=0) SDL_RenderCopy(variables->render1,variables->textbox_variables[i]->get_beam_texture(),NULL,variables->textbox_variables[i]->get_rect_of_beam_texture());
            if(variables->textbox_variables[i]->should_cursor_be_arrow_or_beam()==1) do_display_beam++;
        }
        if(do_display_beam!=0&&variables->beam_is_unlock==1) SDL_SetCursor(this->global_variables->beam_cursor);
        else SDL_SetCursor(this->global_variables->arrow_cursor);

        SDL_RenderPresent(variables->render1);
    }
    if(window1_input_focus==0&&variables->beam_is_unlock==0) SDL_SetCursor(this->global_variables->arrow_cursor);
    return;
}
void Client_Menu::client_paste_texture_to_render_and_display_window2(Client_Menu_Variables* variables)
{

//window2
    if((variables->window2_hide==0&&variables->window2_minimalize==0))
    {
        SDL_RenderClear(variables->render2);

        if(variables->bar_animation_opacity==1&&variables->bar_animation_actual_opacity!=255)
        {
            if(variables->bar_animation_timer0<SDL_GetTicks()-50)
            {
                variables->bar_animation_actual_opacity+=35;
                if(variables->bar_animation_actual_opacity>=255)
                {
                    variables->bar_animation_actual_opacity = 255;

                }
                SDL_SetTextureAlphaMod(variables->window2_bar,variables->bar_animation_actual_opacity);
                variables->bar_animation_timer0 = SDL_GetTicks();
            }
        }
        else if(variables->bar_animation_opacity==0&&variables->bar_animation_actual_opacity!=0)
        {
            if(variables->bar_animation_timer0<SDL_GetTicks()-50)
            {
                variables->bar_animation_actual_opacity-=35;
                if(variables->bar_animation_actual_opacity<=0)
                {
                    variables->bar_animation_actual_opacity = 0;
                }
                SDL_SetTextureAlphaMod(variables->window2_bar,variables->bar_animation_actual_opacity);
                variables->bar_animation_timer0 = SDL_GetTicks();
            }
        }

        if(variables->window2_is_fullscreen==0)
        {
            SDL_RenderCopy(variables->render2,variables->window2_background_no_signal,NULL,NULL);
            if(variables->window0_state==3) SDL_RenderCopy(variables->render2,variables->window2_main,NULL,NULL);
            SDL_RenderCopy(variables->render2,variables->window2_bar,NULL,&variables->rect_window2_bar);
        }
        else
        {
            SDL_RenderCopy(variables->render2,variables->window2_background_no_signal,NULL,NULL);
            if(variables->window0_state==3) SDL_RenderCopy(variables->render2,variables->window2_main,NULL,NULL);
        }

        switch(variables->window2_animation)
        {
            case 1:
                variables->rect_bar_pressed_button = {(int)(variables->screen_width_preview-54+2),2,16,16};
                SDL_RenderCopy(variables->render2,variables->window2_bar_pressed_button,NULL,&variables->rect_bar_pressed_button);
            break;

            case 2:
                variables->rect_bar_pressed_button = {(int)(variables->screen_width_preview-54+18),2,16,16};
                SDL_RenderCopy(variables->render2,variables->window2_bar_pressed_button,NULL,&variables->rect_bar_pressed_button);
            break;

            case 3:
                variables->rect_bar_pressed_button = {(int)(variables->screen_width_preview-54+36),2,16,16};
                SDL_RenderCopy(variables->render2,variables->window2_bar_pressed_button,NULL,&variables->rect_bar_pressed_button);
            break;

        }

        if(variables->window2_is_fullscreen==1)
        {
            if(variables->fullscreen_info_timer0<SDL_GetTicks()-2000)
            {
                if(variables->fullscreen_actual_opacity!=0&&variables->fullscreen_info_timer1<SDL_GetTicks()-40)
                {
                    variables->fullscreen_actual_opacity-=20;
                    if(variables->fullscreen_actual_opacity<=0)
                    {
                        variables->fullscreen_actual_opacity = 0;

                    }
                    variables->fullscreen_info_timer1 = SDL_GetTicks();
                    SDL_SetTextureAlphaMod(variables->window2_fullscreen_information,variables->fullscreen_actual_opacity);
                }
            }
            else
            {
                if(variables->fullscreen_info_timer1<SDL_GetTicks()-40)
                {
                    variables->fullscreen_actual_opacity+=25;
                    if(variables->fullscreen_actual_opacity>=255)
                    {
                        variables->fullscreen_actual_opacity = 255;

                    }
                    variables->fullscreen_info_timer1 = SDL_GetTicks();
                    SDL_SetTextureAlphaMod(variables->window2_fullscreen_information,variables->fullscreen_actual_opacity);
                }

            }
            SDL_RenderCopy(variables->render2,variables->window2_fullscreen_information,NULL,NULL);

        }

        SDL_RenderPresent(variables->render2);
    }

    return;
}

uint8_t Client_Menu::client_menu_run()
{

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("Client_Menu::client_menu:\n");
    #endif

    Client_Menu_Variables client_menu_variables;
    if(client_menu_sets_variables(&client_menu_variables)!=0) return 1;

    if(client_menu_variables.requested_fps_int>=this->global_variables->main_menu_fps) this->global_variables->sdl_universal_tool0->change_fps(client_menu_variables.requested_fps_int);
    else this->global_variables->sdl_universal_tool0->change_fps(this->global_variables->main_menu_fps);
    #ifdef MAIN_PROGRAM0_DEBUG
    printf("fps changed to: %d\n",client_menu_variables.requested_fps_int);
    printf("application interface fps is: %d\n",global_variables->main_menu_fps);
    #endif

    client_menu_variables.return_value = 0;
    SDL_ShowWindow(this->global_variables->window);
    SDL_ShowWindow(client_menu_variables.window1);
    SDL_RestoreWindow(this->global_variables->window);
    SDL_RaiseWindow(this->global_variables->window);

    uint32_t timer1_0 = SDL_GetTicks();
    uint32_t timer1_1 = timer1_0;

//thread_variables:
    Client_Menu::THREAD_client_menu_struct_variables THREAD_variables;
    THREAD_variables.THREAD_global_variables = this->global_variables;
    THREAD_variables.THREAD_variables = &client_menu_variables;
    pthread_t thread0;
    pthread_create(&thread0,NULL,(void*(*)(void*))&THREAD_send_data_to_server_and_receive_captured_screen_to_window2_buffor,(void*)&THREAD_variables); //creating new thread is slow so i'll create it only if necessary;
    #ifdef MAIN_PROGRAM0_DEBUG
    printf("second thread has been created;\nprogram working with in \"two threads\" mode\n");
    #endif

    while(this->close_program==0)
    {
        this->global_variables->sdl_universal_tool0->FpsControl_StartFrame();

        if(client_menu_variables.requested_fps_int>=this->global_variables->main_menu_fps) this->global_variables->sdl_universal_tool0->change_fps(client_menu_variables.requested_fps_int);
        else this->global_variables->sdl_universal_tool0->change_fps(this->global_variables->main_menu_fps);

        client_pause_frame_operations(&client_menu_variables);

        timer1_0 = SDL_GetTicks();
        if(timer1_0>=timer1_1+(uint32_t)(1000.0/this->global_variables->main_menu_fps)) //24fps (application_fps (may change))
        {
            timer1_1 = timer1_0;
            while(client_menu_variables.wait_to_end_operation_save_to_file_and_change_quality_fps_loss_variables==1) SDL_Delay(1);
            client_menu_variables.wait_to_end_operation_save_to_file_and_change_quality_fps_loss_variables = 1;
            this->event_client_menu(&client_menu_variables);
            this->client_paste_textures_to_render_and_display(&client_menu_variables);
            client_menu_variables.wait_to_end_operation_save_to_file_and_change_quality_fps_loss_variables = 0;

        }
        this->client_paste_texture_to_render_and_display_window2(&client_menu_variables);

        //while(client_menu_variables.active_thread==1) SDL_Delay(1);
        //client_menu_variables.active_thread = 1;

        this->global_variables->sdl_universal_tool0->FpsControl_EndFrame();
    }

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("\nfreeing memory: ");
    #endif

    if(client_menu_variables.client_structure.connected_with_the_server==1) //if connected with the server
    {
        client_menu_variables.client_is_trying_to_disconnect = 1;
        while(client_menu_variables.client_is_trying_to_disconnect==1) SDL_Delay(1);
    }
    else client_menu_variables.client.close_client(&client_menu_variables.client_structure); //function will not cause crash even if you haven't created a client;
    client_menu_variables.destroy_thread = 1;
    while(client_menu_variables.destroy_thread==1) SDL_Delay(1);

    free_client_menu_variables(&client_menu_variables);

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("DONE\n");
    #endif

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("Client_Menu::client_menu returns with value: %d\n\n",client_menu_variables.return_value);
    #endif

    SDL_SetWindowHitTest(this->global_variables->window,NULL,NULL);
    this->close_program = 0;
    return client_menu_variables.return_value;
}

uint8_t Client_Menu::client_menu_sets_variables(Client_Menu_Variables* variables)
{
    #ifdef MAIN_PROGRAM0_DEBUG
    printf("Client_Menu::client_menu_sets_variables:\n");
    #endif

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("allocate memory: ");
    #endif

    variables->thread_vector_reset_windows_request = new custom_vector0_ThreadSafePushBack<vector_reset_textures_request_from_thread>(4);
    variables->thread_vector_logs_request = new custom_vector0_ThreadSafePushBack<vector_log_request_from_thread>(32);
    variables->thread_vector_stdout_stderr = new custom_vector0_ThreadSafePushBack<vector_stdout_stderr>(16);
    variables->thread_vector_send_receive = new custom_vector0_ThreadSafePushBack<vector_thread_send_receive>(32);

//client_variables:
    variables->public_ip_string = (uint8_t*)malloc(16);
    variables->server_ip = (uint8_t*)calloc(18,1);
    variables->server_port = (uint8_t*)calloc(7,1);
    variables->password = (uint8_t*)calloc(66,1);
    variables->hash0 = (uint8_t*)calloc(66,1);
    variables->hash1 = (uint8_t*)calloc(66,1);
    variables->hash2 = (uint8_t*)calloc(66,1);
    variables->hash3 = (uint8_t*)calloc(66,1);
    variables->message0 = (uint8_t*)calloc(34,1);
    variables->message1 = (uint8_t*)calloc(34,1);
    variables->requested_quality = (uint8_t*)calloc(4,1);
    variables->requested_fps = (uint8_t*)calloc(5,1);
    variables->requested_loss = (uint8_t*)calloc(5,1);
    //variables->public_ip_int = 0;
    //variables->requested_quality_int = 0;
    //variables->requested_fps_int = 0;
    //variables->requested_loss_int = 0;
    //variables->screen_width_preview = 0;
    //variables->screen_height_preview = 0;

//server_variables:
    variables->message0_server = (uint8_t*)malloc(33);
    variables->message1_server = (uint8_t*)malloc(33);
    /*variables->max_shared_fps_int = 0;
    variables->screen_width_share_int = 0;
    variables->screen_height_share_int = 0;
    variables->max_shared_quality_int = 0;
    variables->max_shared_loss_int = 0;
    variables->server_hash_activate = 0;
    variables->server_password_required = 0;*/

    variables->textbox_variables = new TextBoxClass*[variables->COUNT_OF_TEXBOXES];
    variables->textbox_variables[0] = new TextBoxClass(15); //server_ip
    variables->textbox_variables[1] = new TextBoxClass(5);  //server_port
    variables->textbox_variables[2] = new TextBoxClass(3); //requested_fps
    variables->textbox_variables[3] = new TextBoxClass(2); //requested_quality
    variables->textbox_variables[4] = new TextBoxClass(3); //requested_loss
    variables->textbox_variables[5] = new TextBoxClass(64); //password
    variables->textbox_variables[6] = new TextBoxClass(64); //hash0
    variables->textbox_variables[7] = new TextBoxClass(64); //hash1
    variables->textbox_variables[8] = new TextBoxClass(64); //hash2
    variables->textbox_variables[9] = new TextBoxClass(64);//hash3
    variables->textbox_variables[10] = new TextBoxClass(32);//message0
    variables->textbox_variables[11] = new TextBoxClass(32);//message1
    variables->textbox_variables[12] = new TextBoxClass(4); //preview_width
    variables->textbox_variables[13] = new TextBoxClass(4); //preview_height

    variables->textbox_settings0 = new TextBoxClass::TextBoxStructure_settings*[variables->COUNT_OF_TEXBOXES];
    for(int i = 0; i!=variables->COUNT_OF_TEXBOXES; i++) variables->textbox_settings0[i] = new TextBoxClass::TextBoxStructure_settings;

    variables->textbox_data = (uint8_t**)malloc(sizeof(uint8_t*)*variables->COUNT_OF_TEXBOXES);
    variables->textbox_data[0] = (uint8_t*)malloc(16);
    variables->textbox_data[1] = (uint8_t*)malloc(6);
    variables->textbox_data[2] = (uint8_t*)malloc(4);
    variables->textbox_data[3] = (uint8_t*)malloc(3);
    variables->textbox_data[4] = (uint8_t*)malloc(4);
    variables->textbox_data[5] = (uint8_t*)malloc(65);
    variables->textbox_data[6] = (uint8_t*)malloc(65);
    variables->textbox_data[7] = (uint8_t*)malloc(65);
    variables->textbox_data[8] = (uint8_t*)malloc(65);
    variables->textbox_data[9] = (uint8_t*)malloc(65);
    variables->textbox_data[10] = (uint8_t*)malloc(33);
    variables->textbox_data[11] = (uint8_t*)malloc(33);
    variables->textbox_data[12] = (uint8_t*)malloc(5);
    variables->textbox_data[13] = (uint8_t*)malloc(5);

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("DONE\n");
    #endif

    RECT desktop;
    desktop.right = GetSystemMetrics(SM_CXSCREEN);
    desktop.bottom =  GetSystemMetrics(SM_CYSCREEN);

    if(get_public_IPv4(variables->public_ip_string,&variables->public_ip_int)!=0)
    {
        printf_error("cannot get your public ip from \"api.bigdatacloud.net/data/client-ip\"\ncheck internet connection and try again\n\n");
        this->global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_WARNING,"WARNING","cannot get your public ip from \"api.bigdatacloud.net\"\ncheck internet connection and try again","OK");
        variables->public_ip_int = 0;
        variables->public_ip_string[0] = '\0';
        //return 1;
    }

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("reading file \"config\" and setting variables:\n");
    #endif

    int32_t client_base_position_in_config = this->global_variables->universal_tool0->advanced_read_from_file0("config",(char*)variables->server_ip,"[Client]",1,NULL,750,128); //server_ip is just temporary buffor;
    variables->client_base_position_in_config = client_base_position_in_config;

    int32_t position = this->global_variables->universal_tool0->advanced_read_from_file0("config",(char*)variables->server_ip,": ",0,"\r\n",client_base_position_in_config,128);
    if(position<0) printf_error("ERROR: there was a error while reading config; program can working not properly\n");
    uint32_t check_local_ip_uint32 = 0;
    int return_value = convert_IPv4_from_string_to_uint32((const char*)variables->server_ip,&check_local_ip_uint32);
    if(return_value!=0)
    {
        #ifdef MAIN_PROGRAM0_DEBUG
        printf_error("server_ip was in wrong format; variable changed to: 127.0.0.1\n");
        #endif
        this->global_variables->universal_tool0->advanced_write_to_file0("config","127.0.0.1\0\0\0\0\0\0\r\n",17,": ",client_base_position_in_config,64);
        this->global_variables->universal_tool0->const_char_to_char("127.0.0.1",(char*)variables->server_ip);
    }

    position = this->global_variables->universal_tool0->advanced_read_from_file0("config",(char*)variables->server_port,": ",0,"\r\n",position,128);
    if(position<0) printf_error("ERROR: there was a error while reading config; program can working not properly\n");
    return_value = this->global_variables->universal_tool0->string_to_int32((const char*)variables->server_port);
    if(return_value==0 || return_value>65535||variables->server_port[0]=='0')
    {
        #ifdef MAIN_PROGRAM0_DEBUG
        printf_error("server_port was in wrong format; variable changed to: 1228\n");
        #endif
        this->global_variables->universal_tool0->advanced_write_to_file0("config","1228\0\r\n",7,"connect to the port: ",client_base_position_in_config,128);
        this->global_variables->universal_tool0->const_char_to_char("1228",(char*)variables->server_port);
    }

    position = this->global_variables->universal_tool0->advanced_read_from_file0("config",(char*)variables->requested_fps,": ",0,"\r\n",position,128);
    if(position<0) printf_error("ERROR: there was a error while reading config; program can working not properly\n");
    return_value = this->global_variables->universal_tool0->string_to_int32((const char*)variables->requested_fps);
    if(return_value<1 || return_value>480||variables->requested_fps[0]=='0')
    {
        #ifdef MAIN_PROGRAM0_DEBUG
        printf_error("requested_fps was in wrong format; variable changed to: 30\n");
        #endif
        this->global_variables->universal_tool0->advanced_write_to_file0("config","30\0\r\n",5,"requested fps: ",0,192);
        this->global_variables->universal_tool0->const_char_to_char("30",(char*)variables->requested_fps);
        return_value = 30;
    }
    variables->requested_fps_int = return_value;

    position = this->global_variables->universal_tool0->advanced_read_from_file0("config",(char*)variables->requested_quality,": ",0,"\r\n",position,128);
    return_value = this->global_variables->universal_tool0->string_to_int32((const char*)variables->requested_quality);
    if(return_value==0 || return_value>10||variables->requested_quality[0]=='0')
    {
        #ifdef MAIN_PROGRAM0_DEBUG
        printf_error("requested_quality was in wrong format; variable changed to: 10\n");
        #endif
        this->global_variables->universal_tool0->advanced_write_to_file0("config","10\r\n",4,"requested quality: ",client_base_position_in_config,256);
        this->global_variables->universal_tool0->const_char_to_char("10",(char*)variables->requested_quality);
        return_value = 10;
    }
    variables->requested_quality_int = return_value;

    position = this->global_variables->universal_tool0->advanced_read_from_file0("config",(char*)variables->requested_loss,": ",0,"\r\n",position,128);
    if(position<0) printf_error("ERROR: there was a error while reading config; program can working not properly\n");
    return_value = this->global_variables->universal_tool0->string_to_int32((const char*)variables->requested_loss);
    if(return_value>100||(variables->requested_loss[0]=='0'&&variables->requested_loss[1]!='\0'))
    {
        #ifdef MAIN_PROGRAM0_DEBUG
        printf_error("requested_loss was in wrong format; variable changed to: 50\n");
        #endif
        this->global_variables->universal_tool0->advanced_write_to_file0("config","50\0\r\n",5,"requested loss: ",client_base_position_in_config,320);
        this->global_variables->universal_tool0->const_char_to_char("50",(char*)variables->requested_loss);
        return_value = 50;
    }
    variables->requested_loss_int = return_value;

    position = this->global_variables->universal_tool0->advanced_read_from_file0("config",(char*)variables->password,": ",0,"\r\n",position,128);
    if(position<0) printf_error("ERROR: there was a error while reading config; program can working not properly\n");
    position = this->global_variables->universal_tool0->advanced_read_from_file0("config",(char*)variables->hash0,": ",0,"\r\n",position,128);
    if(position<0) printf_error("ERROR: there was a error while reading config; program can working not properly\n");
    this->shrink_string_to_fit_the_size(this->global_variables->main_ttf,(char*)variables->hash0,562);
    position = this->global_variables->universal_tool0->advanced_read_from_file0("config",(char*)variables->hash1,": ",0,"\r\n",position,128);
    if(position<0) printf_error("ERROR: there was a error while reading config; program can working not properly\n");
    this->shrink_string_to_fit_the_size(this->global_variables->main_ttf,(char*)variables->hash1,562);
    position = this->global_variables->universal_tool0->advanced_read_from_file0("config",(char*)variables->hash2,": ",0,"\r\n",position,128);
    if(position<0) printf_error("ERROR: there was a error while reading config; program can working not properly\n");
    this->shrink_string_to_fit_the_size(this->global_variables->main_ttf,(char*)variables->hash2,562);
    position = this->global_variables->universal_tool0->advanced_read_from_file0("config",(char*)variables->hash3,": ",0,"\r\n",position,128);
    if(position<0) printf_error("ERROR: there was a error while reading config; program can working not properly\n");
    this->shrink_string_to_fit_the_size(this->global_variables->main_ttf,(char*)variables->hash3,562);
    position = this->global_variables->universal_tool0->advanced_read_from_file0("config",(char*)variables->message0,": ",0,"\r\n",position,128);
    if(position<0) printf_error("ERROR: there was a error while reading config; program can working not properly\n");
    this->shrink_string_to_fit_the_size(this->global_variables->main_ttf,(char*)variables->message0,210);
    position = this->global_variables->universal_tool0->advanced_read_from_file0("config",(char*)variables->message1,": ",0,"\r\n",position,128);
    if(position<0) printf_error("ERROR: there was a error while reading config; program can working not properly\n");
    this->shrink_string_to_fit_the_size(this->global_variables->main_ttf,(char*)variables->message1,210);

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("    server_ip: %s\n",variables->server_ip);
    printf("    server_port: %s\n",variables->server_port);
    printf("    requested_fps: %s\n",variables->requested_fps);
    printf("    requested_quality: %s\n",variables->requested_quality);
    printf("    requested_loss: %s\n",variables->requested_loss);
    printf("    password: %s\n",variables->password);
    printf("    hash0: %s\n",variables->hash0);
    printf("    hash1: %s\n",variables->hash1);
    printf("    hash2: %s\n",variables->hash2);
    printf("    hash3: %s\n",variables->hash3);
    printf("    message0: %s\n",variables->message0);
    printf("    message1: %s\n\n",variables->message1);
    #endif

    variables->screen_width_preview = desktop.right/2;   //(desktop.right*0.1)*variables->requested_quality_int;
    variables->screen_height_preview = desktop.bottom/2; //(desktop.bottom*0.1)*variables->requested_quality_int;

    variables->rect_window2_bar = (SDL_Rect){(int)variables->screen_width_preview-54,0,54,19};

    variables->always_top_window2 = 0;

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("Creating windows and renders: ");
    #endif
    int x,y;
    SDL_SetWindowSize(this->global_variables->window,512,414);
    SDL_SetWindowPosition(this->global_variables->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
    SDL_GetWindowPosition(this->global_variables->window,&x,&y);
    SDL_SetWindowPosition(this->global_variables->window,x-256,y);
    variables->window1 = SDL_CreateWindow("Project006_ScreenSharing - ClientConfig",x+256,SDL_WINDOWPOS_CENTERED,608,338,SDL_WINDOW_HIDDEN|SDL_WINDOW_BORDERLESS);
    if(variables->window1==NULL)
    {
        printf_error("cannot create window: \"Project006_ScreenSharing - ClientConfig\"\n\n");
        this->global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"ERROR","cannot create window: \"Project006_ScreenSharing - ClientConfig\"","OK");
        return 1;
    }
    variables->render1 = SDL_CreateRenderer(variables->window1,-1,SDL_RENDERER_ACCELERATED);
    if(variables->render1==NULL)
    {
        printf_error("cannot create render for window: \"Project006_ScreenSharing - ClientConfig\"\n\n");
        this->global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"ERROR","create render for window: \"Project006_ScreenSharing - ClientConfig\"","OK");
        return 1;
    }
    SDL_SetRenderDrawColor(variables->render1,192,199,200,255);

    variables->window2 = SDL_CreateWindow("Project006_ScreenSharing - ClientSharedScreen",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,variables->screen_width_preview,variables->screen_height_preview,SDL_WINDOW_HIDDEN|SDL_WINDOW_BORDERLESS);
    if(variables->window2==NULL)
    {
        printf_error("cannot create window: \"Project006_ScreenSharing - ClientSharedScreen\"\n\n");
        this->global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"ERROR","cannot create window: \"Project006_ScreenSharing - ClientSharedScreen\"","OK");
        return 1;
    }
    variables->render2 = SDL_CreateRenderer(variables->window2,-1,SDL_RENDERER_ACCELERATED);
    if(variables->render2==NULL)
    {
        printf_error("cannot create render for window: \"Project006_ScreenSharing - ClientSharedScreen\"\n\n");
        this->global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"ERROR","create render for window: \"Project006_ScreenSharing - ClientSharedScreen\"","OK");
        return 1;
    }
    SDL_SetRenderDrawColor(variables->render2,192,199,200,255);

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("DONE\n");
    #endif

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("loading texture: ");
    #endif

//window0
    variables->window0_main_background = IMG_LoadTexture(this->global_variables->render,"files/sprites/client/000.png");
    variables->window0_status_client_not_connected = IMG_LoadTexture(this->global_variables->render,"files/sprites/client/001.png");
    variables->window0_status_client_trying_to_connect = IMG_LoadTexture(this->global_variables->render,"files/sprites/client/002.png");
    variables->window0_status_client_waiting_for_accept = IMG_LoadTexture(this->global_variables->render,"files/sprites/client/003.png");
    variables->window0_status_client_accepted = IMG_LoadTexture(this->global_variables->render,"files/sprites/client/004.png");
    variables->window0_bar_lost_focus = IMG_LoadTexture(this->global_variables->render,"files/sprites/client/005.png");
    variables->animation0 = new SDL_Texture*[10];
    variables->animation0[0] = IMG_LoadTexture(this->global_variables->render,"files/sprites/client/animation0/000.png");
    variables->animation0[1] = IMG_LoadTexture(this->global_variables->render,"files/sprites/client/animation0/001.png");
    variables->animation0[2] = IMG_LoadTexture(this->global_variables->render,"files/sprites/client/animation0/002.png");
    variables->animation0[3] = IMG_LoadTexture(this->global_variables->render,"files/sprites/client/animation0/003.png");
    variables->animation0[4] = IMG_LoadTexture(this->global_variables->render,"files/sprites/client/animation0/004.png");
    variables->animation0[5] = IMG_LoadTexture(this->global_variables->render,"files/sprites/client/animation0/005.png");
    variables->animation0[6] = IMG_LoadTexture(this->global_variables->render,"files/sprites/client/animation0/006.png");
    variables->animation0[7] = IMG_LoadTexture(this->global_variables->render,"files/sprites/client/animation0/007.png");
    variables->animation0[8] = IMG_LoadTexture(this->global_variables->render,"files/sprites/client/animation0/008.png");
    variables->animation0[9] = IMG_LoadTexture(this->global_variables->render,"files/sprites/client/animation0/009.png");
    variables->window0_state0_text_texture = new SDL_Texture*[variables->COUNT_OF_WINDOW0_STATE0_TEXT_TEXTURE];
    SDL_Color main_color = {0,0,0,0};
    SDL_Surface* surface_temporary_ttf;
    surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)variables->server_ip,main_color);
    variables->window0_state0_text_texture[0] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
    SDL_FreeSurface(surface_temporary_ttf);
    surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)variables->server_port,main_color);
    variables->window0_state0_text_texture[1] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
    SDL_FreeSurface(surface_temporary_ttf);
    surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)variables->public_ip_string,main_color);
    variables->window0_state0_text_texture[2] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
    SDL_FreeSurface(surface_temporary_ttf);
    surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)variables->requested_fps,main_color);
    variables->window0_state0_text_texture[3] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
    SDL_FreeSurface(surface_temporary_ttf);
    surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)variables->requested_quality,main_color);
    variables->window0_state0_text_texture[4] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
    SDL_FreeSurface(surface_temporary_ttf);
    surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)variables->requested_loss,main_color);
    variables->window0_state0_text_texture[5] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
    SDL_FreeSurface(surface_temporary_ttf);
    surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)variables->message0,main_color);
    variables->window0_state0_text_texture[6] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
    SDL_FreeSurface(surface_temporary_ttf);
    surface_temporary_ttf = TTF_RenderUTF8_Solid(this->global_variables->main_ttf,(const char*)variables->message1,main_color);
    variables->window0_state0_text_texture[7] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary_ttf);
    SDL_FreeSurface(surface_temporary_ttf);
    variables->rect_window0_state0_text_texture = new SDL_Rect[variables->COUNT_OF_WINDOW0_STATE0_TEXT_TEXTURE];
    int w,h;
    TTF_SizeUTF8(this->global_variables->main_ttf,(const char*)variables->server_ip,&w,&h);
    variables->rect_window0_state0_text_texture[0] = (SDL_Rect){403,82,w,h};
    TTF_SizeUTF8(this->global_variables->main_ttf,(const char*)variables->server_port,&w,&h);
    variables->rect_window0_state0_text_texture[1] = (SDL_Rect){403,98,w,h};
    TTF_SizeUTF8(this->global_variables->main_ttf,(const char*)variables->public_ip_string,&w,&h);
    variables->rect_window0_state0_text_texture[2] = (SDL_Rect){403,114,w,h};
    TTF_SizeUTF8(this->global_variables->main_ttf,(const char*)variables->requested_fps,&w,&h);
    variables->rect_window0_state0_text_texture[3] = (SDL_Rect){403,130,w,h};
    TTF_SizeUTF8(this->global_variables->main_ttf,(const char*)variables->requested_quality,&w,&h);
    variables->rect_window0_state0_text_texture[4] = (SDL_Rect){403,146,w,h};
    TTF_SizeUTF8(this->global_variables->main_ttf,(const char*)variables->requested_loss,&w,&h);
    variables->rect_window0_state0_text_texture[5] = (SDL_Rect){403,162,w,h};
    TTF_SizeUTF8(this->global_variables->main_ttf,(const char*)variables->message0,&w,&h);
    variables->rect_window0_state0_text_texture[6] = (SDL_Rect){284,196,w,h};
    TTF_SizeUTF8(this->global_variables->main_ttf,(const char*)variables->message1,&w,&h);
    variables->rect_window0_state0_text_texture[7] = (SDL_Rect){284,212,w,h};

    variables->window0_state2_3_text_texture = new SDL_Texture*[variables->COUNT_OF_WINDOW0_STATE2_3_TEXT_TEXTURE];
    SDL_Surface* surface_temporary0;
    for(int i = 0; i!=variables->COUNT_OF_WINDOW0_STATE2_3_TEXT_TEXTURE; i++)
    {
        surface_temporary0 = SDL_CreateRGBSurface(0,0,0,32,0x00FF0000,0x0000FF00,0x000000FF,0xFF000000);
        variables->window0_state2_3_text_texture[i] = SDL_CreateTextureFromSurface(this->global_variables->render,surface_temporary0);
        SDL_FreeSurface(surface_temporary0);
    }
    variables->rect_window0_state2_3_text_texture = new SDL_Rect[variables->COUNT_OF_WINDOW0_STATE2_3_TEXT_TEXTURE];

//window1
    variables->window1_main_background = IMG_LoadTexture(variables->render1,"files/sprites/client/008.png");
    variables->window1_state0 = IMG_LoadTexture(variables->render1,"files/sprites/client/009.png");
    variables->window1_state1 = IMG_LoadTexture(variables->render1,"files/sprites/client/010.png");
    variables->window1_bar_lost_focus = IMG_LoadTexture(variables->render1,"files/sprites/client/011.png");

//window2
    variables->window2_background_no_signal = IMG_LoadTexture(variables->render2,"files/sprites/universal/009.png");
    variables->size_of_image012 = this->global_variables->universal_tool0->file_size("files/sprites/client/012.png");
    variables->buffor_to_image012 = (uint8_t*)malloc(variables->size_of_image012);
    FILE* file = fopen("files/sprites/client/012.png","rb");
    fread(variables->buffor_to_image012,1,variables->size_of_image012,file);
    fclose(file);

//universal_window0
    variables->window0_bar_pressed_button = IMG_LoadTexture(this->global_variables->render,"files/sprites/universal/000.png");
    variables->window0_pressed_medium_button = IMG_LoadTexture(this->global_variables->render,"files/sprites/universal/001.png");
    variables->window0_pressed_large_button = IMG_LoadTexture(this->global_variables->render,"files/sprites/universal/003.png");
    variables->window0_red_diode = IMG_LoadTexture(this->global_variables->render,"files/sprites/universal/004.png");
    variables->window0_blue_diode = IMG_LoadTexture(this->global_variables->render,"files/sprites/universal/005.png");
//universal_window1
    variables->window1_bar_pressed_button = IMG_LoadTexture(variables->render1,"files/sprites/universal/000.png");
    variables->window1_pressed_medium_button = IMG_LoadTexture(variables->render1,"files/sprites/universal/001.png");
    variables->window1_beam = IMG_LoadTexture(variables->render1,"files/sprites/universal/002.png");
    variables->window1_selected_option = IMG_LoadTexture(variables->render1,"files/sprites/universal/006.png");
    variables->window1_pressed_no_selected_option = IMG_LoadTexture(variables->render1,"files/sprites/universal/007.png");
    variables->window1_pressed_selected_option = IMG_LoadTexture(variables->render1,"files/sprites/universal/008.png");
    surface_temporary_ttf = TTF_RenderUTF8_Solid(global_variables->main_ttf,(const char*)variables->public_ip_string,(SDL_Color){135,136,143,0});
    SDL_GetClipRect(surface_temporary_ttf,&variables->rect_window1_public_ip);
    variables->rect_window1_public_ip.x = 137; variables->rect_window1_public_ip.y = 76;
    variables->window1_public_ip = SDL_CreateTextureFromSurface(variables->render1,surface_temporary_ttf);
    SDL_FreeSurface(surface_temporary_ttf);
//universal_window2
    variables->window2_bar_pressed_button = IMG_LoadTexture(variables->render2,"files/sprites/universal/000.png");
    variables->window2_main = IMG_LoadTexture(variables->render2,"files/sprites/universal/009.png");
    variables->window2_fullscreen_information = IMG_LoadTexture(variables->render2,"files/sprites/universal/010.png");
    variables->window2_bar = IMG_LoadTexture(variables->render2,"files/sprites/universal/011.png");
    SDL_SetTextureBlendMode(variables->window2_bar,SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(variables->window2_fullscreen_information,SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(variables->window2_bar,0);
    SDL_SetTextureAlphaMod(variables->window2_fullscreen_information,0);

//logs
    //3328 : 256 lines
    variables->main_logs_surface = SDL_CreateRGBSurface(0,240,(int)variables->H_SIZE_OF_LOGS,32,0x00FF0000,0x0000FF00,0x000000FF,0xFF000000);
    variables->main_logs_texture = SDL_CreateTextureFromSurface(this->global_variables->render,variables->main_logs_surface);
    variables->rect_logs_dst = {18,47,240,variables->H_MAX_OF_DISPLAY};
    variables->rect_logs_src = {0,0,240,variables->H_MAX_OF_DISPLAY};
    variables->y_logs_position = 0;

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("DONE\n");
    #endif

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("setting hittests: ");
    #endif

    if(SDL_SetWindowHitTest(this->global_variables->window,hit_test0,&variables->window0_hittest))
    {
        printf_error("SDL_SetWindowHitTest failed; window0 cannot be draggable now\n");
        this->global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_WARNING,"WARNING","SDL_SetWindowHitTest failed; window0 cannot be draggable now","OK");
    }
    if(SDL_SetWindowHitTest(variables->window1,hit_test0,&variables->window1_hittest))
    {
        printf_error("SDL_SetWindowHitTest failed; window1 cannot be draggable now\n");
        this->global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_WARNING,"WARNING","SDL_SetWindowHitTest failed; window1 cannot be draggable now","OK");
    }
    variables->window2_hittest = (SDL_Rect){0,0,(int)variables->screen_width_preview-55,(int)variables->screen_height_preview};
    if(SDL_SetWindowHitTest(variables->window2,hit_test0,&variables->window2_hittest))
    {
        printf_error("SDL_SetWindowHitTest failed; window2 cannot be draggable now\n");
        this->global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_WARNING,"WARNING","SDL_SetWindowHitTest failed; window2 cannot be draggable now","OK");
    }

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("DONE\n");
    #endif

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("setting textboxes and other configurations: ");
    #endif

//textboxes:

    this->global_variables->universal_tool0->const_char_to_char((const char*)variables->server_ip,(char*)variables->textbox_data[0]);
    variables->textbox_settings0[0]->x = 135;
    variables->textbox_settings0[0]->y = 43;
    variables->textbox_settings0[0]->w = 110;
    variables->textbox_settings0[0]->h = 14;
    variables->textbox_settings0[0]->padding_up = 1;
    variables->textbox_settings0[0]->padding_left = 2;
    variables->textbox_settings0[0]->beam = variables->window1_beam;
    variables->textbox_settings0[0]->rect_beam = (SDL_Rect){variables->textbox_settings0[0]->x+1,variables->textbox_settings0[0]->y+2,1,11};
    variables->textbox_settings0[0]->render = variables->render1;
    variables->textbox_settings0[0]->beam_delay_in_ms = 500;
    variables->textbox_settings0[0]->mode = TextBoxClass::MODE_NUMBERS;
    variables->textbox_settings0[0]->extra_char_allowed_to_mode = '.';
    variables->textbox_settings0[0]->main_font = this->global_variables->main_ttf;
    variables->textbox_settings0[0]->is_space_allowed = 0;
    variables->textbox_settings0[0]->double_click_max_delay_ms = 500;
    variables->textbox_settings0[0]->solid_text_color = {0,0,0,0};//{135,136,143,0};
    variables->textbox_settings0[0]->selected_text_color = {255,255,255,0};
    variables->textbox_settings0[0]->selected_text_background_color = {0,0,168,0};//{0,0,168,0};
    variables->textbox_settings0[0]->solid_font_quality = TextBoxClass::SOLID_FONT_QUALITY_STANDARD;
    variables->textbox_settings0[0]->selected_font_quality = TextBoxClass::SELECTED_FONT_QUALITY_LCD;

    memcpy(variables->textbox_settings0[1],variables->textbox_settings0[0],sizeof(TextBoxClass::TextBoxStructure_settings));
    this->global_variables->universal_tool0->const_char_to_char((const char*)variables->server_port,(char*)variables->textbox_data[1]);
    variables->textbox_settings0[1]->x = 135; variables->textbox_settings0[1]->y = 59; variables->textbox_settings0[1]->w = 40;
    variables->textbox_settings0[1]->mode = TextBoxClass::MODE_NUMBERS;
    variables->textbox_settings0[1]->extra_char_allowed_to_mode = '\0';

    memcpy(variables->textbox_settings0[2],variables->textbox_settings0[1],sizeof(TextBoxClass::TextBoxStructure_settings));
    this->global_variables->universal_tool0->const_char_to_char((const char*)variables->requested_fps,(char*)variables->textbox_data[2]);
    variables->textbox_settings0[2]->x = 370; variables->textbox_settings0[2]->y = 43; variables->textbox_settings0[2]->w = 26;

    memcpy(variables->textbox_settings0[3],variables->textbox_settings0[1],sizeof(TextBoxClass::TextBoxStructure_settings));
    this->global_variables->universal_tool0->const_char_to_char((const char*)variables->requested_quality,(char*)variables->textbox_data[3]);
    variables->textbox_settings0[3]->x = 370; variables->textbox_settings0[3]->y = 59; variables->textbox_settings0[3]->w = 19;

    memcpy(variables->textbox_settings0[4],variables->textbox_settings0[1],sizeof(TextBoxClass::TextBoxStructure_settings));
    this->global_variables->universal_tool0->const_char_to_char((const char*)variables->requested_loss,(char*)variables->textbox_data[4]);
    variables->textbox_settings0[4]->x = 370; variables->textbox_settings0[4]->y = 75; variables->textbox_settings0[4]->w = 33;

    memcpy(variables->textbox_settings0[5],variables->textbox_settings0[1],sizeof(TextBoxClass::TextBoxStructure_settings));
    this->global_variables->universal_tool0->const_char_to_char((const char*)variables->password,(char*)variables->textbox_data[5]);
    variables->textbox_settings0[5]->mode = TextBoxClass::MODE_ALL;
    variables->textbox_settings0[5]->is_space_allowed = 1;
    variables->textbox_settings0[5]->x = 16; variables->textbox_settings0[5]->y = 132; variables->textbox_settings0[5]->w = 569;

    memcpy(variables->textbox_settings0[6],variables->textbox_settings0[1],sizeof(TextBoxClass::TextBoxStructure_settings));
    this->global_variables->universal_tool0->const_char_to_char((const char*)variables->hash0,(char*)variables->textbox_data[6]);
    variables->textbox_settings0[6]->mode = TextBoxClass::MODE_ALL;
    variables->textbox_settings0[6]->is_space_allowed = 1;
    variables->textbox_settings0[6]->x = 16; variables->textbox_settings0[6]->y = 186; variables->textbox_settings0[6]->w = 569;

    memcpy(variables->textbox_settings0[7],variables->textbox_settings0[1],sizeof(TextBoxClass::TextBoxStructure_settings));
    this->global_variables->universal_tool0->const_char_to_char((const char*)variables->hash1,(char*)variables->textbox_data[7]);
    variables->textbox_settings0[7]->is_space_allowed = 1;
    variables->textbox_settings0[7]->mode = TextBoxClass::MODE_ALL;
    variables->textbox_settings0[7]->x = 16; variables->textbox_settings0[7]->y = 202; variables->textbox_settings0[7]->w = 569;

    memcpy(variables->textbox_settings0[8],variables->textbox_settings0[1],sizeof(TextBoxClass::TextBoxStructure_settings));
    this->global_variables->universal_tool0->const_char_to_char((const char*)variables->hash2,(char*)variables->textbox_data[8]);
    variables->textbox_settings0[8]->is_space_allowed = 1;
    variables->textbox_settings0[8]->mode = TextBoxClass::MODE_ALL;
    variables->textbox_settings0[8]->x = 16; variables->textbox_settings0[8]->y = 218; variables->textbox_settings0[8]->w = 569;

    memcpy(variables->textbox_settings0[9],variables->textbox_settings0[1],sizeof(TextBoxClass::TextBoxStructure_settings));
    this->global_variables->universal_tool0->const_char_to_char((const char*)variables->hash3,(char*)variables->textbox_data[9]);
    variables->textbox_settings0[9]->is_space_allowed = 1;
    variables->textbox_settings0[9]->mode = TextBoxClass::MODE_ALL;
    variables->textbox_settings0[9]->x = 16; variables->textbox_settings0[9]->y = 234; variables->textbox_settings0[9]->w = 569;

    memcpy(variables->textbox_settings0[10],variables->textbox_settings0[1],sizeof(TextBoxClass::TextBoxStructure_settings));
    this->global_variables->universal_tool0->const_char_to_char((const char*)variables->message0,(char*)variables->textbox_data[10]);
    variables->textbox_settings0[10]->is_space_allowed = 1;
    variables->textbox_settings0[10]->mode = TextBoxClass::MODE_ALL;
    variables->textbox_settings0[10]->x = 16; variables->textbox_settings0[10]->y = 288; variables->textbox_settings0[10]->w = 213;

    memcpy(variables->textbox_settings0[11],variables->textbox_settings0[1],sizeof(TextBoxClass::TextBoxStructure_settings));
    this->global_variables->universal_tool0->const_char_to_char((const char*)variables->message1,(char*)variables->textbox_data[11]);
    variables->textbox_settings0[11]->is_space_allowed = 1;
    variables->textbox_settings0[11]->mode = TextBoxClass::MODE_ALL;
    variables->textbox_settings0[11]->x = 16; variables->textbox_settings0[11]->y = 304; variables->textbox_settings0[11]->w = 213;

    char buffor_width[6] = {'\0','\0','\0','\0','\0','\0'};
    char buffor_height[6] = {'\0','\0','\0','\0','\0','\0'};

    this->global_variables->universal_tool0->uint32_to_string(variables->screen_width_preview,buffor_width);
    this->global_variables->universal_tool0->uint32_to_string(variables->screen_height_preview,buffor_height);

    memcpy(variables->textbox_settings0[12],variables->textbox_settings0[1],sizeof(TextBoxClass::TextBoxStructure_settings));
    this->global_variables->universal_tool0->const_char_to_char((const char*)buffor_width,(char*)variables->textbox_data[12]);
    variables->textbox_settings0[12]->is_space_allowed = 1;
    variables->textbox_settings0[12]->mode = TextBoxClass::MODE_ALL;
    variables->textbox_settings0[12]->x = 461; variables->textbox_settings0[12]->y = 270; variables->textbox_settings0[12]->w = 33;

    memcpy(variables->textbox_settings0[13],variables->textbox_settings0[1],sizeof(TextBoxClass::TextBoxStructure_settings));
    this->global_variables->universal_tool0->const_char_to_char((const char*)buffor_height,(char*)variables->textbox_data[13]);
    variables->textbox_settings0[13]->mode = TextBoxClass::MODE_NUMBERS;
    variables->textbox_settings0[13]->x = 461; variables->textbox_settings0[13]->y = 286; variables->textbox_settings0[13]->w = 33;

    for(int i = 1; i!=variables->COUNT_OF_TEXBOXES; i++)
    {
        variables->textbox_settings0[i]->rect_beam.x = variables->textbox_settings0[i]->x+1;
        variables->textbox_settings0[i]->rect_beam.y = variables->textbox_settings0[i]->y+2;
    }

    //initialization/first enter;
    SDL_Event event;
    for(int i = 0; i!=variables->COUNT_OF_TEXBOXES; i++) variables->textbox_variables[i]->TextBox(&event,variables->textbox_data[i],variables->textbox_settings0[i],0);

    variables->window0_ID = SDL_GetWindowID(this->global_variables->window);
    variables->window1_ID = SDL_GetWindowID(variables->window1);
    variables->window2_ID = SDL_GetWindowID(variables->window2);

    variables->window0_mouse_state = 0;
    variables->window1_mouse_state = 0;
    variables->window2_mouse_state = 0;

    variables->window0_state = 0;
    variables->window1_state = 0;
    variables->window2_state = 0;

    variables->window0_animation = 0;
    variables->window1_animation = 0;
    variables->window2_animation = 0;

    variables->window0_display = 1;
    variables->window1_minimalize = 0;
    variables->window1_hide = 0;
    variables->window2_minimalize = 0;
    variables->window2_hide = 1;
    variables->window2_is_fullscreen = 0;

    variables->return_value = 0;

    variables->bar_animation_opacity = 0;
    variables->bar_animation_actual_opacity = 0;
    variables->bar_animation_timer0 = 0;
    variables->fullscreen_actual_opacity = 255;
    variables->fullscreen_info_timer0 = 0;

    variables->timer0_0 = SDL_GetTicks();
    variables->timer0_1 = variables->timer0_0;

    variables->diode_red_counter = 0;
    variables->diode_blue_counter = 0;
    variables->how_much_fps_pass_without_red_diode = 0;
    variables->how_much_fps_pass_without_blue_diode = 0;

    variables->beam_is_unlock = 0;
    variables->is_screen_sharing_paused = 1;

    //variables->state_of_waiting_for_client = 0;
    //variables->client_first_send_request = 0;
    //variables->wait_for_client_request = 0;

//thread_variables
    variables->ThreadFriendly_global_variables = this->global_variables;
    //variables->active_thread = 1;
    variables->destroy_thread = 0;
    variables->VARIABLE_do_prepared_textboxes_FORCE_TO_RESET_TO_0 = 0;
    variables->wait_to_end_operation_save_to_file_and_change_quality_fps_loss_variables = 0;
    variables->main_frame_data = NULL;
    variables->size_of_main_frame_data = 0;
    variables->operation_code_on_main_frame_data = 0;
    variables->screen_sharing_in_process = 0;
    variables->run_now_frame15_operation = 0;

//winsock_variables
    variables->client_is_trying_to_disconnect = 0;
    this->reset_winsock_operation_variables(variables);
    /*variables->do_server_is_destroying = 0;
    variables->do_client_is_rejecting = 0;
    variables->frame_data_should_be_displaying = 0;
    variables->VARIABLE_reset_window0_and_window1_to_state0_or_1_or_2_or_3_PAUSE_WINDOW = 0;*/

    //this->reset_all_server_state_variables(variables);

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("DONE\n");
    #endif

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("opening file: \"files/client_logs.txt\": ");
    #endif

    variables->logs_file = fopen("files/client_logs.txt","a+b");
    time_t date;
    date = time(NULL);
    char result[64];
    strcpy(result,"\nnew session: ");
    strcat(result,ctime(&date));
    fwrite(result,1,this->global_variables->universal_tool0->count_string_chars(result),variables->logs_file);
    fclose(variables->logs_file);

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("DONE\n");
    #endif

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("writed string into \"files/client_logs.txt\": \"%s\"\n",result);
    #endif

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("Client_Menu::server_menu_sets_variables returns with value 0\n\n");
    #endif

    return 0;
}

void Client_Menu::free_client_menu_variables(Client_Menu_Variables* variables)
{
    delete(variables->thread_vector_logs_request);          //it will clear automatically throught destructor;
    delete(variables->thread_vector_reset_windows_request); //it will clear automatically throught destructor;
    delete(variables->thread_vector_stdout_stderr);         //it will clear automatically throught destructor;
    delete(variables->thread_vector_send_receive);          //it will clear automatically throught destructor;
    variables->thread_vector_update_window0_state2_state3.clear();

//client_variables;
    free(variables->public_ip_string);
    free(variables->server_ip);
    free(variables->server_port);
    free(variables->requested_quality);
    free(variables->requested_fps);
    free(variables->requested_loss);
    free(variables->password);
    free(variables->hash0);
    free(variables->hash1);
    free(variables->hash2);
    free(variables->hash3);
    free(variables->message0);
    free(variables->message1);
//server_variables
    free(variables->message0_server);
    free(variables->message1_server);

    SDL_DestroyWindow(variables->window1);
    SDL_DestroyWindow(variables->window2);
    SDL_DestroyRenderer(variables->render1);
    SDL_DestroyRenderer(variables->render2);

//textures:
    //window0
        SDL_DestroyTexture(variables->window0_main_background);
        SDL_DestroyTexture(variables->window0_status_client_not_connected);
        SDL_DestroyTexture(variables->window0_status_client_trying_to_connect);
        SDL_DestroyTexture(variables->window0_status_client_waiting_for_accept);
        SDL_DestroyTexture(variables->window0_status_client_accepted);
        SDL_DestroyTexture(variables->window0_bar_lost_focus);
        for(int i = 0; i!=10; i++) SDL_DestroyTexture(variables->animation0[i]);
        delete[] variables->animation0;
        for(int i = 0; i!=variables->COUNT_OF_WINDOW0_STATE0_TEXT_TEXTURE; i++) SDL_DestroyTexture(variables->window0_state0_text_texture[i]);
        delete[] variables->window0_state0_text_texture;
        delete[] variables->rect_window0_state0_text_texture;
        for(int i = 0; i!=variables->COUNT_OF_WINDOW0_STATE2_3_TEXT_TEXTURE; i++) SDL_DestroyTexture(variables->window0_state2_3_text_texture[i]);
        delete[] variables->window0_state2_3_text_texture;
        delete[] variables->rect_window0_state2_3_text_texture;
    //window1
        SDL_DestroyTexture(variables->window1_main_background);
        SDL_DestroyTexture(variables->window1_state0);
        SDL_DestroyTexture(variables->window1_state1);
        SDL_DestroyTexture(variables->window1_bar_lost_focus);
        SDL_DestroyTexture(variables->window1_public_ip);
    //window2
        SDL_DestroyTexture(variables->window2_background_no_signal);
        free(variables->buffor_to_image012);
    //universal_window0
        SDL_DestroyTexture(variables->window0_bar_pressed_button);
        SDL_DestroyTexture(variables->window0_pressed_medium_button);
        SDL_DestroyTexture(variables->window0_pressed_large_button);
        SDL_DestroyTexture(variables->window0_red_diode);
        SDL_DestroyTexture(variables->window0_blue_diode);
    //universal_window1
        SDL_DestroyTexture(variables->window1_bar_pressed_button);
        SDL_DestroyTexture(variables->window1_pressed_medium_button);
        SDL_DestroyTexture(variables->window1_beam);
        SDL_DestroyTexture(variables->window1_selected_option);
        SDL_DestroyTexture(variables->window1_pressed_no_selected_option);
        SDL_DestroyTexture(variables->window1_pressed_selected_option);
    //universal_window2
        SDL_DestroyTexture(variables->window2_bar_pressed_button);
        SDL_DestroyTexture(variables->window2_main);
        SDL_DestroyTexture(variables->window2_fullscreen_information);
        SDL_DestroyTexture(variables->window2_bar);
    //logs
        SDL_DestroyTexture(variables->main_logs_texture);
        SDL_FreeSurface(variables->main_logs_surface);

//textbox
    for(int i = 0; i!=variables->COUNT_OF_TEXBOXES; i++) delete variables->textbox_variables[i];
    delete[] variables->textbox_variables;

    for(int i = 0; i!=variables->COUNT_OF_TEXBOXES; i++) delete variables->textbox_settings0[i];
    delete[] variables->textbox_settings0;

    for(int i = 0; i!=variables->COUNT_OF_TEXBOXES; i++) free(variables->textbox_data[i]);
    free(variables->textbox_data);

    return;
}

void Client_Menu::client_pause_frame_operations(Client_Menu_Variables* variables)
{
    if(variables->operation_code_on_main_frame_data!=0)
    {
        if(variables->operation_code_on_main_frame_data==4)             //4 means frame screen //TODO
        {
            if(variables->window2_hide==1||variables->window2_minimalize==1)
            {
                free(variables->main_frame_data);
                variables->operation_code_on_main_frame_data = 0;
                return;
            }
            unsigned char* buffer = NULL;
            SDL_Surface* surface0;
            uint8_t error = 0;

            SDL_DestroyTexture(variables->window2_main);

            if(variables->loss_of_actual_frame!=0) //if jpg
            {
                buffer = (unsigned char*)malloc((variables->width_of_actual_frame+1)*(variables->height_of_actual_frame*3));
                if(tj3Decompress8(this->global_variables->decompress_handle,variables->main_frame_data,variables->size_of_main_frame_data,buffer,variables->pitch_of_actual_frame,TJPF_BGR)==-1)
                {
                    #ifdef MAIN_PROGRAM0_DEBUG
                    char* debug_buffor = (char*)malloc(256);
                    sprintf(debug_buffor,"ERROR: %s\n",tj3GetErrorStr(this->global_variables->decompress_handle));
                    variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)debug_buffor,1,1});
                    #endif
                    error++;
                }
                surface0 = SDL_CreateRGBSurfaceFrom(buffer,variables->width_of_actual_frame,variables->height_of_actual_frame,24,
                                                    variables->pitch_of_actual_frame,0xFF0000,0x00FF00,0x0000FF,0);
                if(surface0==NULL) error++;
                if(error!=0)
                {
                    SDL_RWops* file;
                    file = SDL_RWFromMem(variables->buffor_to_image012,variables->size_of_image012);
                    surface0 = IMG_Load_RW(file,1);
                }
            }
            else
            {
                buffer = (unsigned char*)malloc(variables->size_of_main_frame_data*253);
                this->global_variables->universal_tool0->decompress_per3bytes_rgb_data(variables->main_frame_data,buffer,variables->size_of_main_frame_data);
                surface0 = SDL_CreateRGBSurfaceFrom(buffer,variables->width_of_actual_frame,variables->height_of_actual_frame,24,
                                                    variables->pitch_of_actual_frame,0xFF0000,0x00FF00,0x0000FF,0);
                if(surface0==NULL)
                {
                    SDL_RWops* file;
                    file = SDL_RWFromMem(variables->buffor_to_image012,variables->size_of_image012);
                    surface0 = IMG_Load_RW(file,1);
                }
            }

            SDL_DestroyTexture(variables->window2_main);
            variables->window2_main = SDL_CreateTextureFromSurface(variables->render2,surface0);
            if(surface0!=NULL) SDL_FreeSurface(surface0);
            if(buffer!=NULL) free(buffer);
            free(variables->main_frame_data);
            #ifdef MAIN_PROGRAM0_DEBUG
            variables->thread_vector_stdout_stderr[0].push_back((Client_Menu::vector_stdout_stderr){(char*)"    texture of the frame has been maded;\n",0,0});
            #endif

        }
        else if(variables->operation_code_on_main_frame_data==1)        //1 means pause image (first_enter)
        {

            SDL_Surface* surface;
            SDL_RWops* file;
            file = SDL_RWFromMem(variables->main_frame_data,variables->size_of_main_frame_data);
            surface = IMG_Load_RW(file,1);
            if(surface==NULL)
            {
                file = SDL_RWFromMem(variables->buffor_to_image012,variables->size_of_image012);
                surface = IMG_Load_RW(file,1);
                SDL_DestroyTexture(variables->window2_main);
                variables->window2_main = SDL_CreateTextureFromSurface(variables->render2,surface);
            }
            else
            {
                SDL_DestroyTexture(variables->window2_main);
                variables->window2_main = SDL_CreateTextureFromSurface(variables->render2,surface);
            }

            free(variables->main_frame_data);
            variables->main_frame_data = NULL;
            //===========================================================================================

            SDL_GetClipRect(surface,&variables->rect_window2_pause_image);
            SDL_FreeSurface(surface);

            variables->window2_hittest.h = (variables->rect_window2_pause_image.h/2);
            variables->window2_hittest.w = (variables->rect_window2_pause_image.w/2)-55;
            variables->rect_window2_bar = (SDL_Rect){(int)(variables->rect_window2_pause_image.w/2)-54,0,54,19};

            variables->buffor_for_screen_height_preview = (variables->screen_height_share_int*0.1)*variables->requested_quality_int;
            if(variables->buffor_for_screen_height_preview<64) variables->buffor_for_screen_height_preview = 64;
            variables->buffor_for_screen_width_preview = (variables->screen_width_share_int*0.1)*variables->requested_quality_int;
            if(variables->buffor_for_screen_width_preview<64) variables->buffor_for_screen_width_preview = 64;
            variables->screen_width_preview = variables->rect_window2_pause_image.w/2;
            variables->screen_height_preview = variables->rect_window2_pause_image.h/2;

            char buffor[5];
            this->global_variables->universal_tool0->uint32_to_string(variables->screen_width_preview,buffor);
            memcpy(variables->textbox_data[12],buffor,4);
            this->global_variables->universal_tool0->uint32_to_string(variables->screen_height_preview,buffor);
            memcpy(variables->textbox_data[13],buffor,4);

            SDL_Event clear_event;
            variables->textbox_variables[12]->update_textbox();
            variables->textbox_variables[12]->TextBox(&clear_event,variables->textbox_data[12],variables->textbox_settings0[12],0);
            variables->textbox_variables[13]->update_textbox();
            variables->textbox_variables[13]->TextBox(&clear_event,variables->textbox_data[13],variables->textbox_settings0[13],0);

            if(variables->window2_hide==1) variables->thread_vector_logs_request[0].push_back((Client_Menu::vector_log_request_from_thread){(char*)": preview window has been displayed;\n",(char*)"preview window has been displayed;",(SDL_Color){0,0,0,0},(SDL_Color){0,0,0,255},0});
            variables->window2_is_fullscreen = 0;
            variables->window2_hide = 0;
            variables->window2_minimalize = 0;
            SDL_RestoreWindow(variables->window2);
            SDL_ShowWindow(variables->window2);
            SDL_SetWindowFullscreen(variables->window2,0);
            SDL_SetWindowSize(variables->window2,variables->rect_window2_pause_image.w/2,variables->rect_window2_pause_image.h/2);
        }
        else if(variables->operation_code_on_main_frame_data==2)    //2 means server sended pause image; (to check if is good)
        {

            SDL_Surface* surface;
            SDL_RWops* file;
            file = SDL_RWFromMem(variables->main_frame_data,variables->size_of_main_frame_data);
            surface = IMG_Load_RW(file,1);
            if(surface==NULL)
            {
                file = SDL_RWFromMem(variables->buffor_to_image012,variables->size_of_image012);
                surface = IMG_Load_RW(file,1);
                SDL_DestroyTexture(variables->window2_main);
                variables->window2_main = SDL_CreateTextureFromSurface(variables->render2,surface);
            }
            else
            {
                SDL_DestroyTexture(variables->window2_main);
                variables->window2_main = SDL_CreateTextureFromSurface(variables->render2,surface);
            }

            free(variables->main_frame_data);
            variables->main_frame_data = NULL;
            //===========================================================================================

            SDL_GetClipRect(surface,&variables->rect_window2_pause_image);
            SDL_FreeSurface(surface);

            if(variables->window2_is_fullscreen==0)
            {
                variables->window2_hittest.h = (variables->rect_window2_pause_image.h/2);
                variables->window2_hittest.w = (variables->rect_window2_pause_image.w/2)-55;
            }
             variables->rect_window2_bar = (SDL_Rect){(int)(variables->rect_window2_pause_image.w/2)-54,0,54,19};


            variables->buffor_for_screen_height_preview = variables->screen_height_preview;
            variables->buffor_for_screen_width_preview = variables->screen_width_preview;
            variables->screen_width_preview = variables->rect_window2_pause_image.w/2;
            variables->screen_height_preview = variables->rect_window2_pause_image.h/2;

            char buffor[5];
            this->global_variables->universal_tool0->uint32_to_string(variables->screen_width_preview,buffor);
            memcpy(variables->textbox_data[12],buffor,4);
            this->global_variables->universal_tool0->uint32_to_string(variables->screen_height_preview,buffor);
            memcpy(variables->textbox_data[13],buffor,4);

            SDL_Event clear_event;
            variables->textbox_variables[12]->update_textbox();
            variables->textbox_variables[12]->TextBox(&clear_event,variables->textbox_data[12],variables->textbox_settings0[12],0);
            variables->textbox_variables[13]->update_textbox();
            variables->textbox_variables[13]->TextBox(&clear_event,variables->textbox_data[13],variables->textbox_settings0[13],0);

            SDL_RestoreWindow(variables->window2);
            variables->window2_minimalize = 0;
            SDL_SetWindowSize(variables->window2,variables->rect_window2_pause_image.w/2,variables->rect_window2_pause_image.h/2);
        }
        else if(variables->operation_code_on_main_frame_data==3)    //3 means server starts sending frame of screen; (to check if is good)
        {
            if(variables->window2_is_fullscreen==0)
            {
                variables->window2_hittest.h = variables->buffor_for_screen_height_preview;
                variables->window2_hittest.w = variables->buffor_for_screen_width_preview-55;
            }
            variables->rect_window2_bar = (SDL_Rect){(int)variables->buffor_for_screen_width_preview-54,0,54,19};

            variables->screen_width_preview = variables->buffor_for_screen_width_preview;
            variables->screen_height_preview = variables->buffor_for_screen_height_preview;

            char buffor[5];
            this->global_variables->universal_tool0->uint32_to_string(variables->screen_width_preview,buffor);
            memcpy(variables->textbox_data[12],buffor,4);
            this->global_variables->universal_tool0->uint32_to_string(variables->screen_height_preview,buffor);
            memcpy(variables->textbox_data[13],buffor,4);

            SDL_Event clear_event;
            variables->textbox_variables[12]->update_textbox();
            variables->textbox_variables[12]->TextBox(&clear_event,variables->textbox_data[12],variables->textbox_settings0[12],0);
            variables->textbox_variables[13]->update_textbox();
            variables->textbox_variables[13]->TextBox(&clear_event,variables->textbox_data[13],variables->textbox_settings0[13],0);

            //SDL_SetWindowFullscreen(variables->window2,0);
            if(variables->window2_minimalize==1) //anty SDL2 bug;
            {
                variables->window2_minimalize = 0;
                SDL_RestoreWindow(variables->window2);
            }
            SDL_SetWindowSize(variables->window2,variables->screen_width_preview,variables->screen_height_preview);
        }

        variables->operation_code_on_main_frame_data = 0;
    }
    return;
}


