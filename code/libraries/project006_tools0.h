#ifndef SECURITY_PROJECT006_TOOLS0_H
#define SECURITY_PROJECT006_TOOLS0_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>                      //IMG_
#include <SDL2/SDL_ttf.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <windows.h>
#include <pthread.h>

//#pragma comment(lib, "gdi32.lib") //or -lgdi32

#define printf_error(string) fprintf(stderr,string)
#define printf_error_args(string,args...) fprintf(stderr,string,args)

template <typename T> class custom_vector0_ThreadSafePushBack;     //dynamic object
//struct TextureRectVector;                       //dynamic object

class UniversalTools0;
class SDL_UniversalTools0;

//#include <stdlib.h>
template <typename T> class custom_vector0_ThreadSafePushBack
{

    T* main_data;
    size_t element_count;
    size_t size_of_obiekt;
    size_t count_of_starting_elements;

    pthread_mutex_t lock; //for thread_safe

public:
    custom_vector0_ThreadSafePushBack()
    {
        this->count_of_starting_elements = 4;
        this->main_data = (T*)malloc(sizeof(T)*this->count_of_starting_elements);
        this->element_count = 0;
        this->size_of_obiekt = sizeof(T)*this->count_of_starting_elements;

        pthread_mutex_init(&lock, NULL);

    }

    custom_vector0_ThreadSafePushBack(const size_t count_of_elements)
    {
        this->count_of_starting_elements = count_of_elements;
        this->main_data = (T*)malloc(sizeof(T)*this->count_of_starting_elements);
        this->element_count = 0;
        this->size_of_obiekt = sizeof(T)*this->count_of_starting_elements;

        pthread_mutex_init(&lock, NULL);
    }

    void clear()
    {
        if(this->size_of_obiekt==0) return;
        this->element_count = 0;
        this->size_of_obiekt = sizeof(T)*this->count_of_starting_elements;
        free(this->main_data);
        this->main_data = (T*)malloc(sizeof(T)*this->count_of_starting_elements);
        return;
    }

    void push_back(const T variable) //thread_safe
    {
        pthread_mutex_lock(&lock);
        if((this->element_count+1)%this->count_of_starting_elements==0)
        {
            this->element_count++;
            T* copy_data = (T*)malloc((sizeof(T)*(this->element_count*2)));
            size_t i;
            for(i = 0; i!=this->element_count; i++) copy_data[i] = this->main_data[i];


            free(this->main_data);
            this->main_data = (T*)malloc((sizeof(T)*(this->element_count*2)));
            for(i = 0; i!=this->element_count; i++) this->main_data[i] = copy_data[i];
            free(copy_data);

            this->size_of_obiekt = (sizeof(T)*(this->element_count*2));
            this->main_data[this->element_count-1] = variable;
        }
        else
        {
            this->main_data[this->element_count] = variable;
            this->element_count++;
        }
        pthread_mutex_unlock(&lock);
    }

    void pop_back()
    {
        if(this->element_count!=0)
        {
            //this->main_data[this->element_count-1] = (T)NULL;
            memset(&this->main_data[this->element_count-1],0,sizeof(this->main_data[this->element_count-1]));
            this->element_count--;
        }
        return;
    }

    void pop_front()
    {
        if(this->element_count!=0)
        {
            if(this->element_count==1)
            {
                //this->main_data[0] = (T)NULL;
                memset(&this->main_data[0],0,sizeof(this->main_data[0]));
                this->element_count--;
                return;
            }
            size_t i = 0;
            for(; i!=this->element_count-1; i++)
            {
                this->main_data[i] = this->main_data[i+1];
            }
            //this->main_data[i] = (T)NULL;
            memset(&this->main_data[i],0,sizeof(this->main_data[i]));
            this->element_count--;
        }
        return;
    }

    size_t size()
    {
        return this->element_count;
    }

    size_t real_size_in_bytes()
    {
        return this->size_of_obiekt;
    }

    size_t size_of_elements_in_bytes()
    {
        return this->element_count*sizeof(T);
    }

    bool empty()
    {
        return 1 ? this->element_count == 0 : 0;
    }

    T& operator[](const size_t iterator)
    {
        return this->main_data[iterator];
    }

    ~custom_vector0_ThreadSafePushBack()
    {
        if(this->size_of_obiekt!=0) free(this->main_data);
        pthread_mutex_destroy(&lock);
    }

};


/*struct TextureRectVector
{
    custom_vector0_ThreadSafePushBack<SDL_Texture*> texture;
    custom_vector0_ThreadSafePushBack<SDL_Rect> rect;

};*/


//#include <stdio.h>
//#include <stdint.h>
//#include <windows.h>
class UniversalTools0
{

public:

    UniversalTools0()
    {

    }

    //--DANGEROUS
    //-lgdi32
    //<windows.h> <stdint.h>
    //data_out length has to be minimum screen_w*screen_h*3;
    //if returns 0 then success; else error;
    //add -D CAPTURE_SCREEN_TO_BUFFOR_RGB_DEBUG for debug purpose
    //after this function, image will have size: w = (screen_w*0.1)*quality_from_1_to_10; & h = (screen_h*0.1)*quality_from_1_to_10;
    uint8_t capture_screen_to_buffor_RGB(uint8_t* const data_out,uint16_t screen_w,uint16_t screen_h,uint8_t quality_from_1_to_10,bool should_image_be_upside_down,bool speed_quality);

    //-- DANGEROUS --
    //returns size of new data that has been compressed and returned in data_out;
    //if returns 0 then it's error: invalid format;
    //DATA_OUT SHOULD HAVE MINIMUM SIZE: (SIZEOF(data_in)+(SIZEOF(data_in)/3));
    uint32_t compress_per3bytes_rgb_data(const uint8_t* const data_in,uint8_t* const data_out,const uint32_t size_of_data_in);

    //-- DANGEROUS --
    //returns size of decompressed data pushed into "data_out" and decompressed data in "data_out";
    //if "data_out" is too small, then program will crash; size of data_out should be decompressed version of this data;
    //if size of decompressed version of data is unknown, then size of "data_out" should be SIZEOF(data_in)*253;
    //if returns 0 then it's error: invalid format;
    uint32_t decompress_per3bytes_rgb_data(const uint8_t* const data_in,uint8_t* const data_out,const uint32_t size_of_data_in);

    //--- DANGEROUS ---
    //hashes data in variable "data_in_out";
    ////benchmark == 110ms
    //
    //data_in_out - data to be hashed;
    //hash_seed - array of hash seed;
    //size_of_data - size of "data_in_out" (must be not higher than size of "data_in_out"; otherwise function 'll crash);
    //size_of_hash_seed - size of "hash_seed" (must be not higher than size of "hash_seed"; otherwise function 'll crash);
    //
    //returns 0 if function ends with success; returns 1 if "size_of_hash_seed" or/and "size_of_data" is/are too smalll;
    uint8_t hash0_32bit(uint8_t* const data_in_out,uint8_t* const hash_seed,const uint32_t size_of_data,const uint32_t size_of_hash_seed);

    //--- DANGEROUS ---
    //unhashes data in variable "data_in_out" which was hashed throught function "hash0_32bit";
    ////benchmark == 110ms
    //
    //data_in_out - data to be hashed;
    //hash_seed - array of hash seed;
    //size_of_data - size of "data_in_out" (must be not higher than size of "data_in_out"; otherwise function 'll crash);
    //size_of_hash_seed - size of "hash_seed" (must be not higher than size of "hash_seed"; otherwise function 'll crash);
    //
    //returns 0 if function ends with success; returns 1 if "size_of_hash_seed" or/and "size_of_data" is/are too smalll;
    uint8_t unhash0_32bit(uint8_t* const data_in_out,uint8_t* const hash_seed,const uint32_t size_of_data,const uint32_t size_of_hash_seed);

    //--DANGEROUS
    //returns count of chars in string without '\0' (string must have NULL at the end)
    size_t count_string_chars(const char* string_data);

    //--DANGEROUS
    template <typename T> void memset_custom(T* const data,const size_t value,const size_t count_of_elements)
    {
        for(size_t i = 0; i!=count_of_elements; i++) *((T*)data+i) = (T)value;
        return;
    }

    //--DANGEROUS
    //adds '\0' at the end to data_out;
    void const_char_to_char(const char* data_in,char* data_out);

    //--DANGEROUS
    //#include <stdio.h>
    //
    //if function ends success then 'll return 0,else if file not exist returns 1,else if writing failed returns 2;
    unsigned int write_to_file0(const char* file,char* data,const size_t how_many_chars_write,const size_t write_at_position);

    //--DANGEROUS
    //#include <stdio.h>
    //
    //if function ends success then 'll return 0,else 'll return 1 if "file not exist" or 2 if "reading data error";
    //"data" variable must be 1 byte longer 'cause of '\0' that 'll be added at the end;
    unsigned int read_from_file0(const char* file,char* data,const size_t read_from_position,const size_t how_many_chars_read);

    //-- DANGEROUS --
    //#include <stdio.h> && #include <stdlib.h>
    //
    //arg search_for must have at the end of string char '\0';
    //returns position of the beginning of writing in file if success;
    //arg how_many_bytes_allocate_for_searching_operation: lower number == better
    //returns -1 if args parameters are invalid;
    //returns -2 if end of file is reached;
    //returns -3 if file not exist;
    int advanced_write_to_file0(const char* const filename,const char* const data_in,unsigned int sizeof_data_in,const char* const search_for,
                                unsigned int start_reading_from_pos,unsigned int how_many_bytes_allocate_for_searching_operation);

    //-- DANGEROUS --
    //#include <stdio.h> && #include <stdlib.h>
    //
    //max size of at_what_chars_stop_reading must be not greater than 1024bytes;
    //if how_many_chars_read == 0 then this arg is ignored and needed is arg at_what_chars_stop_reading
    //but if how_many_chars_read is != 0 then arg at_what_chars_stop_reading is ignored;
    //leaves how_many_chars_read with non-zero variable makes function a lot faster;
    //args at_what_chars_stop_reading and search_for must have at the end of string char '\0';
    //arg how_many_bytes_allocate_for_searching_operation: lower number == better
    //returns position of the end of reading + 1 in file if success;
    //returns data to data_out with end char '\0';
    //returns -1 if args parameters are invalid;
    //returns -2 if end of file is reached;
    //returns -3 if file not exist;
    int advanced_read_from_file0(const char* const filename,char* const data_out,const char* const search_for,
                                     unsigned int how_many_chars_read,const char* const at_what_chars_stop_reading,
                                     unsigned int start_reading_from_pos,unsigned int how_many_bytes_allocate_for_searching_operation);

    //returns actual value if success; else returns 0;
    //max value that can be returned is int;
    int string_to_int32(const char* const data_in);

    //if file exist then 'll return 1; else 'll return 0;
    bool do_file_exist(const char* file);

    //adds '\0' at the end of data_out
    void uint32_to_string(unsigned int data_in,char* const data_out);

    //--DANGEROUS
    //if data is the same, then return 0; if not, return 1;
    bool compare_data(uint8_t* data0, uint8_t* data1,size_t sizeof_data0_and_data1);

    //returns file size in bytes
    size_t file_size(const char* file_name);

};

//#include <stdint.h>
//#include <SDL2/SDL.h>
class SDL_UniversalTools0
{

    int32_t FpsControl_FpsTimerEnd;
    uint32_t FpsControl_FpsTimerStart;
    uint8_t FpsControl_fps;

public:
    SDL_UniversalTools0(uint32_t fps)
    {
        this->FpsControl_fps = fps;
    }

    void FpsControl_EndFrame();     //add at the end of loop;
    void FpsControl_StartFrame();   //add at the the start of loop;
    void change_fps(uint32_t fps);

    //changes opacity of texture to maximum per loop literals which represents variable "increase_by";
    uint8_t Change_Texture_Opacity_To_Max(SDL_Texture* texture,uint8_t increase_by);
    //setting opacity to zero;
    void Set_Texture_Opacity_To_Zero_In_Instant(SDL_Texture* texture);

    void ShowSimpleMessageBox0(Uint32 flag,const char* title,const char* message,const char* StringButton);

    //[0; 33] is lowest quality,[34; 66] is middle quality,[67; 100] is highest quality;
    void ScreenShotJPG(SDL_Renderer* render,const char* filename,int quality,size_t width,size_t height);
    void ScreenShotPNG(SDL_Renderer* render,const char* filename,size_t width,size_t height);

    void combine_surfaces(uint32_t x,uint32_t y,SDL_Surface* src,SDL_Surface* dst);
};




#endif
