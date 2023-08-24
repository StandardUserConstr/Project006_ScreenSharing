#include "libraries/project006_main_program_headers0.h"

int main(int argc, char *argv[])
{
    Global_Variables global_variables;

    MAIN_PROGRAM main_program;
    main_program.initialization_global_variables(&global_variables);

    Main_Menu main_menu_program(&global_variables);

    for(;;)
    {
        int return_value = main_menu_program.main_menu_run();
        if(return_value==0)
        {
            Client_Menu client_menu_program(&global_variables);
            if(client_menu_program.client_menu_run()!=0)
            {
                main_program.free_global_variables(&global_variables);
                return 1;
            }
            else continue;

        }
        else if(return_value==1)
        {
            Server_Menu server_menu_program(&global_variables);
            if(server_menu_program.server_menu_run()!=0)
            {
                main_program.free_global_variables(&global_variables);
                return 1;
            }
            else continue;
        }
        else if(return_value==2)
        {
            main_program.free_global_variables(&global_variables);
            return 0;
        }
    }


    return 0;

}
