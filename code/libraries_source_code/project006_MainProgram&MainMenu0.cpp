#include "../libraries/project006_main_program_headers0.h"

SDL_HitTestResult SDLCALL hit_test0(SDL_Window *window, const SDL_Point *pt, void *data)
{
    if (SDL_PointInRect(pt, (SDL_Rect*)data))
    {
        return SDL_HITTEST_DRAGGABLE;
    }
    else
    {
        return SDL_HITTEST_NORMAL;
    }
}

void MAIN_PROGRAM::init_everything(Global_Variables* global_variables)
{
        if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_EVENTS|SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
        {
            printf_error("Initialization SDL2 failed");
            exit(1);
        }

        SDL_SetHint("SDL_HINT_RENDER_SCALE_QUALITY","1");

        if(winsock_initialization()!=0)
        {
            printf_error("winsock initialization failed");
            global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"ERROR","Winsock initialization failed","OK");
            exit(1);
        }

        global_variables->sdl_universal_tool0 = new SDL_UniversalTools0(30);
        global_variables->universal_tool0 = new UniversalTools0();
        global_variables->compressor_handle = tj3Init(TJINIT_COMPRESS);
        global_variables->decompress_handle = tj3Init(TJINIT_DECOMPRESS);

        global_variables->arrow_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
        if(global_variables->arrow_cursor==NULL)
        {
            printf_error("init_everything: failed to load system cursor \"arrow\"\n");
            global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_WARNING,"WARNING","failed to load system cursor \"arrow\"","OK");
        }

        global_variables->beam_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
        if(global_variables->beam_cursor==NULL)
        {
            printf_error("init_everything: failed to load system cursor \"ibeam\"\n");
            global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_WARNING,"WARNING","failed to load system cursor \"ibeam\"","OK");
        }



        if(IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG)!=(IMG_INIT_JPG|IMG_INIT_PNG))
        {
            printf_error("Initialization SDL2_image failed");
            global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"ERROR","Initialization SDL2_image failed","OK");
            exit(1);

        }
        if(TTF_Init()!=0)
        {
            printf_error("Initialization SDL2_ttf failed");
            global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"ERROR","Initialization SDL2_image failed","OK");
            exit(1);
        }
        global_variables->main_ttf = TTF_OpenFont("files/fonts/W95FA.otf",13);
        if(global_variables->main_ttf==NULL)
        {
            printf_error("Cannot load: \"files/fonts/W95FA.otf\"failed");
            global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_WARNING,"WARNING","Cannot load: \"files/fonts/W95FA.otf\"failed","OK");
        }

        global_variables->window = SDL_CreateWindow("Project006_ScreenCapture", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,384,
                                                    240,SDL_WINDOW_HIDDEN|SDL_WINDOW_BORDERLESS);

        if(global_variables->window==NULL)
        {
            printf_error("Creating window failed");
            global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"ERROR","SDL_CreateWindow failed","OK");
            exit(1);
        }

        global_variables->render = SDL_CreateRenderer(global_variables->window, -1, SDL_RENDERER_ACCELERATED);
        if(global_variables->render==NULL)
        {
            printf_error("Creating render failed");
            global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"ERROR","SDL_CreateRenderer failed","OK");
            exit(1);
        }

        char buffor[10];
        int error = global_variables->universal_tool0->advanced_read_from_file0("config",(char*)buffor,"application_fps: ",0,"\r\n",0,2048);
        uint64_t return_value = global_variables->universal_tool0->string_to_int32((const char*)buffor);
        if(return_value==0 || return_value>999)
        {
            printf_error("applicatioN_fps was in wrong format; variable changed to: 24\n");
            global_variables->universal_tool0->advanced_write_to_file0("config","24\0\r\n",5,"application_fps: ",0,2048);
            return_value = 24;
        }
        global_variables->main_menu_fps = return_value;
        if(error<0) printf_error("ERROR: there was a error while reading config; program can working not properly\n");

        error = global_variables->universal_tool0->advanced_read_from_file0("config",(char*)buffor,": ",0,"\r\n",error,2112);
        return_value = global_variables->universal_tool0->string_to_int32((const char*)buffor);
        if(return_value<0 || return_value>1)
        {
            printf_error("fastest/bad_quality_share was in wrong format; variable changed to: 0\n");
            global_variables->universal_tool0->advanced_write_to_file0("config","0\r\n",3,"fastest/bad_quality_share: ",0,2112);
            return_value = 0;
        }
        global_variables->server_bad_quality_share = return_value;
        if(error<0) printf_error("ERROR: there was a error while reading config; program can working not properly\n");

        error = global_variables->universal_tool0->advanced_read_from_file0("config",(char*)buffor,": ",0,"\r\n",error,2176);
        return_value = global_variables->universal_tool0->string_to_int32((const char*)buffor);
        if(return_value<1 || return_value>999999999)
        {
            printf_error("inactive_timeout_in_ms was in wrong format; variable changed to: 10000\n");
            global_variables->universal_tool0->advanced_write_to_file0("config","10000\r\n",7,"inactive_timeout_in_ms: ",0,2176);
            return_value = 10000;
        }
        global_variables->inactive_timeout_in_ms = return_value;
        if(error<0) printf_error("ERROR: there was a error while reading config; program can working not properly\n");

        error = global_variables->universal_tool0->advanced_read_from_file0("config",(char*)buffor,": ",0,"\r\n",error,2240);
        return_value = global_variables->universal_tool0->string_to_int32((const char*)buffor);
        if(return_value>6)
        {
            printf_error("compression_method_from_0_to_6 was in wrong format; variable changed to: 2\n");
            global_variables->universal_tool0->advanced_write_to_file0("config","2\r\n",3,"compression_method_from_0_to_6: ",0,2240);
            return_value = 2;
        }
        global_variables->compression_method = return_value;
        if(error<0) printf_error("ERROR: there was a error while reading config; program can working not properly\n");

        error = global_variables->universal_tool0->advanced_read_from_file0("config",(char*)buffor,": ",0,"\r\n",error,2304);
        return_value = global_variables->universal_tool0->string_to_int32((const char*)buffor);
        uint64_t how_much_bytes_to_delete_logs = return_value;
        if(how_much_bytes_to_delete_logs<=global_variables->universal_tool0->file_size("files/server_logs.txt"))
        {
            FILE* file = fopen("files/server_logs.txt","wb+");
            fclose(file);
        }
        if(error<0) printf_error("ERROR: there was a error while reading config; program can working not properly\n");

        error = global_variables->universal_tool0->advanced_read_from_file0("config",(char*)buffor,": ",0,"\r\n",error,2368);
        return_value = global_variables->universal_tool0->string_to_int32((const char*)buffor);
        how_much_bytes_to_delete_logs = return_value;
        if(how_much_bytes_to_delete_logs<=global_variables->universal_tool0->file_size("files/client_logs.txt"))
        {
            FILE* file = fopen("files/server_logs.txt","wb+");
            fclose(file);
        }
        if(error<0) printf_error("ERROR: there was a error while reading config; program can working not properly\n");

        global_variables->processor_cores = SDL_GetCPUCount();

        //Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024);
        SDL_SetRenderDrawColor(global_variables->render,192,199,200,255);
        return;
}


void MAIN_PROGRAM::file_checks()
{
    int count_of_elements = 59;
    char** buffor = (char**)malloc(count_of_elements*(sizeof(uint8_t*)));
    for(int i = 0; i!=count_of_elements; i++) buffor[i] = (char*)malloc(64);

    this->global_variables->universal_tool0->const_char_to_char("files/fonts/W95FA.otf",buffor[0]);
    this->global_variables->universal_tool0->const_char_to_char("files/sprites/client/animation0/000.png",buffor[1]);
    for(int i = 1; i!=10; i++)
    {
        memcpy(buffor[i+1],buffor[1],40);
        buffor[i+1][34] = 47+i+1;
    }
    this->global_variables->universal_tool0->const_char_to_char("files/sprites/client/000.png",buffor[11]);
    for(int i = 1,j = 11; i!=10; i++,j++)
    {
        memcpy(buffor[j+1],buffor[11],29);
        buffor[j+1][23] = 47+i+1;
    }
    this->global_variables->universal_tool0->const_char_to_char("files/sprites/client/010.png",buffor[21]);
    this->global_variables->universal_tool0->const_char_to_char("files/sprites/client/011.png",buffor[22]);
    this->global_variables->universal_tool0->const_char_to_char("files/sprites/client/012.png",buffor[23]);
    this->global_variables->universal_tool0->const_char_to_char("files/sprites/menu/000.png",buffor[24]);
    this->global_variables->universal_tool0->const_char_to_char("files/sprites/menu/001.png",buffor[25]);
    this->global_variables->universal_tool0->const_char_to_char("files/sprites/server/animation0/000.png",buffor[26]);
    for(int i = 1,j = 26; i!=10; i++,j++)
    {
        memcpy(buffor[j+1],buffor[26],40);
        buffor[j+1][34] = 47+i+1;
    }
    this->global_variables->universal_tool0->const_char_to_char("files/sprites/server/000.png",buffor[36]);
    for(int i = 1,j = 36; i!=10; i++,j++)
    {
        memcpy(buffor[j+1],buffor[36],29);
        buffor[j+1][23] = 47+i+1;
    }
    this->global_variables->universal_tool0->const_char_to_char("files/sprites/server/010.png",buffor[46]);
    this->global_variables->universal_tool0->const_char_to_char("files/sprites/universal/000.png",buffor[47]);
    for(int i = 1,j = 47; i!=10; i++,j++)
    {
        memcpy(buffor[j+1],buffor[47],32);
        buffor[j+1][26] = 47+i+1;
    }
    this->global_variables->universal_tool0->const_char_to_char("files/sprites/universal/010.png",buffor[57]);
    this->global_variables->universal_tool0->const_char_to_char("files/sprites/universal/011.png",buffor[58]);

    int error;
    for(int i = 0; i!=count_of_elements; i++)
    {
        error = this->global_variables->universal_tool0->do_file_exist((const char*)buffor[i]);
        if(error==0)
        {
            char buffor0[128];
            sprintf(buffor0,"file: %s\ndoesn't exist;\nprogram 'll not work properly;",buffor[i]);
            this->global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_WARNING,"WARNING",(const char*)buffor0,"OK");
        }
        #ifdef MAIN_PROGRAM0_DEBUG
        if(error==1) printf("%s: exist\n",buffor[i]);
        else printf("%s: not exist\n",buffor[i]);
        #endif
    }

    for(int i = 0; i!=count_of_elements; i++) free(buffor[i]);
    free(buffor);
    return;
}

void MAIN_PROGRAM::free_everything(Global_Variables* global_variables)
{
    delete global_variables->sdl_universal_tool0;
    delete global_variables->universal_tool0;
    winsock_free();
    SDL_FreeCursor(global_variables->arrow_cursor);
    SDL_FreeCursor(global_variables->beam_cursor);
    SDL_DestroyRenderer(global_variables->render);
    SDL_DestroyWindow(global_variables->window);
    tj3Destroy(global_variables->compressor_handle);
    tj3Destroy(global_variables->decompress_handle);
    TTF_CloseFont(global_variables->main_ttf);
    TTF_Quit();
    IMG_Quit();
    return;
}

void MAIN_PROGRAM::event_standard()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_WINDOWEVENT:
                if(event.window.event==SDL_WINDOWEVENT_CLOSE) this->close_program = 1;
            break;

            default:
                break;
        }
    }
    return;
}

bool MAIN_PROGRAM::shrink_string_to_fit_the_size(TTF_Font* font,char* string_in_out,uint32_t max_width_of_text)
{
    uint32_t end_of_string_position = 0;
    for(; string_in_out[end_of_string_position]!='\0'; end_of_string_position++){}
    int w,h;
    TTF_SizeUTF8(font,(const char*)string_in_out,&w,&h);
    if((uint32_t)w<=max_width_of_text) return 0;

    while((uint32_t)w>max_width_of_text)
    {
        end_of_string_position--;
        string_in_out[end_of_string_position] = '\0';
        if(end_of_string_position==0) break;
        TTF_SizeUTF8(font,(const char*)string_in_out,&w,&h);
    }

    return 1;
}

void Main_Menu::event_main_menu(Main_Menu::Main_Menu_Variables* variables)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                this->close_program = 1;
            break;

            case SDL_MOUSEMOTION:
                {
                    if(event.motion.y>=5&&event.motion.y<=19)
                    {
                        if(event.motion.x>=345&&event.motion.x<=361)
                        {
                            if(variables->mouse_focus==1) variables->mouse_state = 2;
                            else variables->mouse_state = 1;
                        }
                        else if(event.motion.x>=363&&event.motion.x<=379)
                        {
                            if(variables->mouse_focus==2) variables->mouse_state = 5;
                            else variables->mouse_state = 4;
                        }
                        else variables->mouse_state = 0;
                    }
                    else if(event.motion.y>=200&&event.motion.y<=223)
                    {
                        if(event.motion.x>=24&&event.motion.x<=99)
                        {
                            if(variables->mouse_focus==3) variables->mouse_state = 8;
                            else variables->mouse_state = 7;
                        }
                        else if(event.motion.x>=285&&event.motion.x<=360)
                        {
                            if(variables->mouse_focus==4) variables->mouse_state = 11;
                            else variables->mouse_state = 10;
                        }
                        else variables->mouse_state = 0;
                    }
                    else variables->mouse_state = 0;

                }break;

            case SDL_MOUSEBUTTONDOWN:
                {
                    switch(variables->mouse_state)
                    {
                        case 1:
                            {
                                if(event.button.button==SDL_BUTTON_LEFT)
                                {
                                    variables->mouse_state = 2;
                                    variables->mouse_focus = 1;
                                }
                            }break;
                        case 4:
                            {
                                if(event.button.button==SDL_BUTTON_LEFT)
                                {
                                    variables->mouse_state = 5;
                                    variables->mouse_focus = 2;
                                }
                            }break;
                        case 7:
                            {
                                if(event.button.button==SDL_BUTTON_LEFT)
                                {
                                    variables->mouse_state = 8;
                                    variables->mouse_focus = 3;
                                }
                            }break;
                        case 10:
                            {
                                if(event.button.button==SDL_BUTTON_LEFT)
                                {
                                    variables->mouse_state = 11;
                                    variables->mouse_focus = 4;
                                }
                            }break;

                        default:
                            break;
                    }
                }break;


            case SDL_MOUSEBUTTONUP:
                {
                    switch(variables->mouse_state)
                    {
                        case 2:
                            {
                                if(event.button.button==SDL_BUTTON_LEFT)
                                {
                                    #ifdef MAIN_PROGRAM0_DEBUG
                                    printf("    minimalize button released \n");
                                    #endif
                                    variables->mouse_state = 3;
                                    return;
                                }
                            }break;

                        case 5:
                            {

                                if(event.button.button==SDL_BUTTON_LEFT)
                                {
                                    variables->mouse_state = 6;
                                    #ifdef MAIN_PROGRAM0_DEBUG
                                    printf("    close button released\n");
                                    #endif
                                    return;
                                }
                            }break;
                        case 8:
                            {
                                if(event.button.button==SDL_BUTTON_LEFT)
                                {
                                    #ifdef MAIN_PROGRAM0_DEBUG
                                    printf("    server button released\n");
                                    #endif
                                    variables->mouse_state = 9;
                                    return;
                                }
                            }break;
                        case 11:
                            {
                                if(event.button.button==SDL_BUTTON_LEFT)
                                {
                                    #ifdef MAIN_PROGRAM0_DEBUG
                                    printf("    client button released\n");
                                    #endif
                                    variables->mouse_state = 12;
                                    return;
                                }
                            }break;


                        default:
                            break;
                    }
                    variables->mouse_focus = 0;
                }break;

            default:
                break;
        }
    }
    return;

}

uint8_t Main_Menu::main_menu_run()
{
    SDL_Rect rect_hittest0 = {0, 0, 345, 21};
    #ifdef MAIN_PROGRAM0_DEBUG
    printf("Main_Menu::main_menu_run:\n\n");
    #endif
    #ifdef MAIN_PROGRAM0_DEBUG
    printf("setting hitTest: ");
    #endif
    if(SDL_SetWindowHitTest(global_variables->window,hit_test0,&rect_hittest0))
    {
        printf_error("SDL_SetWindowHitTest failed; window cannot be draggable now\n");
        global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_WARNING,"WARNING","SDL_SetWindowHitTest failed; window cannot be draggable now","OK");
    }
    #ifdef MAIN_PROGRAM0_DEBUG
    printf("DONE\n");
    #endif

    Main_Menu_Variables main_menu_variables;
    uint8_t return_value = 2;
    main_menu_variables.mouse_focus = 0;
    main_menu_variables.mouse_state = 0;

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("loading sprites: ");
    #endif

    SDL_Texture* background0 = IMG_LoadTexture(this->global_variables->render,"files/sprites/menu/000.png");
    SDL_Rect rect_background = {0,0,384,240};
    SDL_Texture* buttons_animation0 = IMG_LoadTexture(this->global_variables->render,"files/sprites/universal/000.png");
    SDL_Rect rect_buttons_animation0 = {345,5,16,14};
    SDL_Texture* buttons_animation1 = IMG_LoadTexture(this->global_variables->render,"files/sprites/universal/001.png");
    SDL_Rect rect_buttons_animation1 = {24,200,75,23};
    SDL_Texture* background_animation0 = IMG_LoadTexture(this->global_variables->render,"files/sprites/menu/001.png");
    SDL_Rect rect_background_animation0 = {3,3,378,18};

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("DONE\n");
    #endif

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("sets and displaying window: ");
    #endif

    SDL_SetWindowSize(this->global_variables->window,384,240);
    SDL_SetWindowPosition(this->global_variables->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(this->global_variables->window);

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("DONE\n");
    #endif

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("fps changed to %d\n\n",global_variables->main_menu_fps);
    #endif
    this->global_variables->sdl_universal_tool0->change_fps(global_variables->main_menu_fps);

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("entered main loop:\n");
    #endif
    while(this->close_program==0)
    {
        this->global_variables->sdl_universal_tool0->FpsControl_StartFrame();

        SDL_RenderClear(this->global_variables->render);
        SDL_RenderCopy(this->global_variables->render,background0,NULL,&rect_background);

        if((SDL_GetWindowFlags(this->global_variables->window)&SDL_WINDOW_INPUT_FOCUS)==0)
        {
            this->global_variables->sdl_universal_tool0->change_fps(global_variables->main_menu_fps/2);
            SDL_RenderCopy(this->global_variables->render,background_animation0,NULL,&rect_background_animation0);
            this->event_standard();
        }
        else
        {
            this->global_variables->sdl_universal_tool0->change_fps(global_variables->main_menu_fps);
            this->event_main_menu(&main_menu_variables);
            switch(main_menu_variables.mouse_state)
            {
                case 2:
                    {
                        rect_buttons_animation0.x = 345;
                        SDL_RenderCopy(this->global_variables->render,buttons_animation0,NULL,&rect_buttons_animation0);
                    }break;
                case 3:
                    {

                        SDL_MinimizeWindow(this->global_variables->window);
                        main_menu_variables.mouse_state = 1;
                    }break;

                case 5:
                    {
                        rect_buttons_animation0.x = 363;
                        SDL_RenderCopy(this->global_variables->render,buttons_animation0,NULL,&rect_buttons_animation0);
                    }break;
                case 6:
                    {
                        this->close_program = 1;
                        main_menu_variables.mouse_state = 4;
                        return_value = 2;
                    }break;
                case 8:
                    {
                        rect_buttons_animation1.x = 24;
                        SDL_RenderCopy(this->global_variables->render,buttons_animation1,NULL,&rect_buttons_animation1);
                    }break;
                case 9:
                    {
                        this->close_program = 1;
                        main_menu_variables.mouse_state = 7;
                        return_value = 1;
                    }break;
                case 11:
                    {
                        rect_buttons_animation1.x = 285;
                        SDL_RenderCopy(this->global_variables->render,buttons_animation1,NULL,&rect_buttons_animation1);
                    }break;
                case 12:
                    {
                        this->close_program = 1;
                        main_menu_variables.mouse_state = 10;
                        return_value = 0;
                    }break;
            }
        }



        SDL_RenderPresent(this->global_variables->render);

        this->global_variables->sdl_universal_tool0->FpsControl_EndFrame();
    }

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("\nfreeing memory: ");
    #endif
    SDL_SetWindowHitTest(global_variables->window,NULL,NULL);
    SDL_HideWindow(this->global_variables->window);

    SDL_DestroyTexture(background0);
    SDL_DestroyTexture(buttons_animation0);
    SDL_DestroyTexture(buttons_animation1);
    SDL_DestroyTexture(background_animation0);

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("DONE\n");
    #endif

    #ifdef MAIN_PROGRAM0_DEBUG
    printf("Main_Menu::main_menu returns with value: %d\n\n",return_value);
    #endif
    this->close_program = 0;
    return return_value;
}
