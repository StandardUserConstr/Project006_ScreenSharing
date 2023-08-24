#include "../libraries/project006_tools0.h"


//UniversalTools0
//===================================================================================================

uint8_t UniversalTools0::capture_screen_to_buffor_RGB(uint8_t* const data_out,uint16_t screen_w,uint16_t screen_h,uint8_t quality_from_1_to_10,bool should_image_be_upside_down,bool speed_quality)
{
    if(quality_from_1_to_10==0) quality_from_1_to_10 = 1;
    else if (quality_from_1_to_10>10) quality_from_1_to_10 = 10;
    uint16_t scaling_x = (screen_w*0.1)*quality_from_1_to_10;
    uint16_t scaling_y = (screen_h*0.1)*quality_from_1_to_10;

    #ifdef CAPTURE_SCREEN_TO_BUFFOR_RGB_DEBUG
    printf("capture_screen_to_buffor_RGB\n");
    HDC hDesktopDC = GetDC(NULL);
    if(hDesktopDC==NULL)
    {
        fprintf(stderr,"GetDC() failed\n\n");
        return 1;
    }

    HDC hCaptureDC = CreateCompatibleDC(hDesktopDC);
    if(hCaptureDC==NULL)
    {
        fprintf(stderr,"CreateCompatibleDC() failed\n\n");
        return 1;
    }

    HBITMAP hCaptureBitmap = CreateCompatibleBitmap(hDesktopDC, scaling_x, scaling_y);
    if(hCaptureBitmap==NULL)
    {
        fprintf(stderr,"CreateCompatibleBitmap() failed\n\n");
        return 1;
    }

    if(SelectObject(hCaptureDC, hCaptureBitmap)==NULL)
    {
        fprintf(stderr,"SelectObject() failed\n\n");
        return 1;
    }

    if(quality_from_1_to_10!=10)
    {
        if(speed_quality==1)
        {
            if(SetStretchBltMode(hCaptureDC,COLORONCOLOR)==0)
            {
                fprintf(stderr,"SetStretchBltMode() failed\n\n");
                return 1;
            }
        }
        else
        {
            if(SetStretchBltMode(hCaptureDC,HALFTONE)==0)
            {
                fprintf(stderr,"SetStretchBltMode() failed\n\n");
                return 1;
            }
            SetBrushOrgEx(hCaptureDC, 0, 0, 0);
        }

        if(StretchBlt(hCaptureDC,0,0,scaling_x,scaling_y,hDesktopDC,0,0,screen_w,screen_h,SRCCOPY)==0)
        {
            fprintf(stderr,"StretchBlt() failed\n\n");
            return 1;
        }

        CURSORINFO cursor = { sizeof(cursor) };
        GetCursorInfo(&cursor);
        if (cursor.flags == CURSOR_SHOWING)
        {
            ICONINFO info = { sizeof(info) };
            GetIconInfo(cursor.hCursor, &info);
            int x = cursor.ptScreenPos.x - info.xHotspot;
            int y = cursor.ptScreenPos.y - info.yHotspot;
            x = ((x*0.1)*quality_from_1_to_10);
            y = (y*0.1)*quality_from_1_to_10;
            BITMAP bmpCursor = { 0 };
            GetObject(info.hbmMask, sizeof(bmpCursor), &bmpCursor);
            if(info.hbmColor == NULL)
            {
                bmpCursor.bmHeight = bmpCursor.bmHeight/2;
            }
            DrawIconEx(hCaptureDC, x, y, cursor.hCursor, ((bmpCursor.bmWidth*0.1)*quality_from_1_to_10), ((bmpCursor.bmHeight*0.1)*quality_from_1_to_10),
                0, NULL, DI_NORMAL);
            DeleteObject(info.hbmColor);
            DeleteObject(info.hbmMask);
        }
        printf("    Screen has been taken\n");
        //BLACKONWHITE
        //COLORONCOLOR
        //HALFTONE
        //WHITEONBLACK
    }
    else
    {
        if(BitBlt(hCaptureDC, 0, 0, screen_w, screen_h, hDesktopDC, 0,0, SRCCOPY)==0)
        {
            fprintf(stderr,"BitBlt() failed\n\n");
            return 1;
        }

        CURSORINFO cursor = { sizeof(cursor) };
        GetCursorInfo(&cursor);
        if (cursor.flags == CURSOR_SHOWING)
        {
            ICONINFO info = { sizeof(info) };
            GetIconInfo(cursor.hCursor, &info);
            int x = cursor.ptScreenPos.x - info.xHotspot;
            int y = cursor.ptScreenPos.y - info.yHotspot;
            BITMAP bmpCursor = { 0 };
            GetObject(info.hbmMask, sizeof(bmpCursor), &bmpCursor);
            if(info.hbmColor == NULL)
            {
                bmpCursor.bmHeight = bmpCursor.bmHeight/2;
            }
            DrawIconEx(hCaptureDC, x, y, cursor.hCursor, bmpCursor.bmWidth, bmpCursor.bmHeight,
                0, NULL, DI_NORMAL);
            DeleteObject(info.hbmColor);
            DeleteObject(info.hbmMask);
        }
        printf("    Screen has been taken\n");
    }

    #else

    HDC hDesktopDC = GetDC(NULL);
    HDC hCaptureDC = CreateCompatibleDC(hDesktopDC);
    HBITMAP hCaptureBitmap = CreateCompatibleBitmap(hDesktopDC, scaling_x, scaling_y);

    SelectObject(hCaptureDC, hCaptureBitmap);

    if(quality_from_1_to_10!=10)
    {
        if(speed_quality==1) SetStretchBltMode(hCaptureDC,COLORONCOLOR);
        else
        {
            SetStretchBltMode(hCaptureDC,HALFTONE);
            SetBrushOrgEx(hCaptureDC, 0, 0, 0);
        }
        StretchBlt(hCaptureDC,0,0,scaling_x,scaling_y,hDesktopDC,0,0,screen_w,screen_h,SRCCOPY);

        CURSORINFO cursor = { sizeof(cursor) };
        GetCursorInfo(&cursor);
        if (cursor.flags == CURSOR_SHOWING)
        {
            ICONINFO info = { sizeof(info) };
            GetIconInfo(cursor.hCursor, &info);
            int x = cursor.ptScreenPos.x - info.xHotspot;
            int y = cursor.ptScreenPos.y - info.yHotspot;
            x = ((x*0.1)*quality_from_1_to_10);
            y = (y*0.1)*quality_from_1_to_10;
            BITMAP bmpCursor = { 0 };
            GetObject(info.hbmMask, sizeof(bmpCursor), &bmpCursor);
            if(info.hbmColor == NULL)
            {
                bmpCursor.bmHeight = bmpCursor.bmHeight/2;
            }
            DrawIconEx(hCaptureDC, x, y, cursor.hCursor, ((bmpCursor.bmWidth*0.1)*quality_from_1_to_10), ((bmpCursor.bmHeight*0.1)*quality_from_1_to_10),
                0, NULL, DI_NORMAL);
            DeleteObject(info.hbmColor);
            DeleteObject(info.hbmMask);
        }
    }
    else
    {
        BitBlt(hCaptureDC, 0, 0, screen_w, screen_h, hDesktopDC, 0,0, SRCCOPY);

        CURSORINFO cursor = { sizeof(cursor) };
        GetCursorInfo(&cursor);
        if (cursor.flags == CURSOR_SHOWING)
        {
            ICONINFO info = { sizeof(info) };
            GetIconInfo(cursor.hCursor, &info);
            int x = cursor.ptScreenPos.x - info.xHotspot;
            int y = cursor.ptScreenPos.y - info.yHotspot;
            BITMAP bmpCursor = { 0 };
            GetObject(info.hbmMask, sizeof(bmpCursor), &bmpCursor);
            if(info.hbmColor == NULL)
            {
                bmpCursor.bmHeight = bmpCursor.bmHeight/2;
            }
            DrawIconEx(hCaptureDC, x, y, cursor.hCursor, bmpCursor.bmWidth, bmpCursor.bmHeight,
                0, NULL, DI_NORMAL);
            DeleteObject(info.hbmColor);
            DeleteObject(info.hbmMask);
        }
    }


    #endif

    BITMAPINFO bmi = {0};
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = scaling_x;
    if(should_image_be_upside_down==1) bmi.bmiHeader.biHeight = scaling_y*-1;
    else bmi.bmiHeader.biHeight = scaling_y;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;

    #ifdef CAPTURE_SCREEN_TO_BUFFOR_RGB_DEBUG
    if(GetDIBits(hCaptureDC,hCaptureBitmap,0,scaling_y,data_out,&bmi,DIB_RGB_COLORS)!=scaling_y)
    {
        fprintf(stderr,"GetDIBits() failed\n\n");
        return 1;
    }
    printf("    Buffor filled with data\n");
    #else

//slower version
/*int i = 0;
    for(int y = 0; y<scaling_y; y++)
    {
        for(int x = 0; x<scaling_x; x++)
        {
            COLORREF color = GetPixel(hCaptureDC,x,y);

            data_out[i+2] = GetRValue(color);
            data_out[i+1] = GetGValue(color);
            data_out[i] = GetBValue(color);
            i+=3;
        }
    }*/

    GetDIBits(hCaptureDC,hCaptureBitmap,0,scaling_y,data_out,&bmi,DIB_RGB_COLORS);

    #endif

    #ifdef CAPTURE_SCREEN_TO_BUFFOR_RGB_DEBUG
    if(ReleaseDC(NULL,hDesktopDC)==0)
    {
        fprintf(stderr,"ReleaseDC() failed\n\n");
        return 1;
    }
    if(DeleteDC(hCaptureDC)==0)
    {
        fprintf(stderr,"DeleteDC() failed\n\n");
        return 1;
    }
    if(DeleteObject(hCaptureBitmap)==0)
    {
        fprintf(stderr,"DeleteObject() failed\n\n");
        return 1;
    }

    printf("    Cleared\n\n");

    #else

    ReleaseDC(NULL,hDesktopDC);
    DeleteDC(hCaptureDC);
    DeleteObject(hCaptureBitmap);

    #endif

    return 0;
}

uint32_t UniversalTools0::compress_per3bytes_rgb_data(const uint8_t* const data_in,uint8_t* const data_out,const uint32_t size_of_data_in)
{
    int32_t buffor0[3];
    buffor0[0] = data_in[0]; buffor0[1] = data_in[1];
    buffor0[2] = data_in[2];

    uint32_t i = 0;
    uint32_t new_data_counter = 0;
    int32_t counter;
    if(size_of_data_in%3==0) //if data format can be threated as real rgb format;
    {
        for(; i!=size_of_data_in; i+=3,new_data_counter+=4)
        {
            counter = 0;
            for(; i!=size_of_data_in&&counter!=255; i+=3,counter++)
            {
                if(!(data_in[i]==buffor0[0]&&data_in[i+1]==buffor0[1]&&data_in[i+2]==buffor0[2])) break;
            }
            if(counter==0)
            {
                data_out[new_data_counter] = 1; data_out[new_data_counter+1] = data_in[i];
                data_out[new_data_counter+2] = data_in[i+1]; data_out[new_data_counter+3] = data_in[i+2];
                if(i==size_of_data_in) {new_data_counter+=4; return new_data_counter;}
                buffor0[0] = data_in[i+3]; buffor0[1] = data_in[i+4];
                buffor0[2] = data_in[i+5];


            }
            else
            {

                data_out[new_data_counter] = counter; data_out[new_data_counter+1] = data_in[i-3];
                data_out[new_data_counter+2] = data_in[i-2]; data_out[new_data_counter+3] = data_in[i-1];
                if(i==size_of_data_in) {new_data_counter+=4; return new_data_counter;}
                buffor0[0] = data_in[i]; buffor0[1] = data_in[i+1];
                buffor0[2] = data_in[i+2];
                i-=3;
            }
        }
    }
    else
    {
        return 0;
    }

    return new_data_counter;
}

uint32_t UniversalTools0::decompress_per3bytes_rgb_data(const uint8_t* const data_in,uint8_t* const data_out,const uint32_t size_of_data_in)
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t new_position = 0;
    int32_t counter;
    if(size_of_data_in%4==0) //if data format can be threated as real rgb compressed per3bytes format;
    {
        for(; i!=size_of_data_in; i+=4)
        {
            counter = data_in[i];
            for(; ; j+=3)
            {
                if(j==new_position+(counter*3)){break;}
                data_out[j] = data_in[i+1];
                data_out[j+1] = data_in[i+2];
                data_out[j+2] = data_in[i+3];

            }
            new_position = j;
        }
    }
    else
    {
        return 0;
    }
    return new_position;

}

uint8_t UniversalTools0::hash0_32bit(uint8_t* const data_in_out,uint8_t* const hash_seed,const uint32_t size_of_data,const uint32_t size_of_hash_seed) //CHANGED VERSION
{                                                                                                                                                           //THIS ISN'T ACTUAL VERSION OF THE FUNCTION USED IN OFFICIAL PROGRAM
    if(size_of_hash_seed<=0) return 1;
    if(size_of_data<=0) return 1;

    for(uint32_t i = 0; i!=size_of_data; i++)
    {
        data_in_out[i]+=hash_seed[i%size_of_hash_seed];
    }
    return 0;
}

uint8_t UniversalTools0::unhash0_32bit(uint8_t* const data_in_out,uint8_t* const hash_seed,const uint32_t size_of_data,const uint32_t size_of_hash_seed) //CHANGED VERSION
{                                                                                                                                                           //THIS ISN'T ACTUAL VERSION OF THE FUNCTION USED IN OFFICIAL PROGRAM
    if(size_of_hash_seed<=0) return 1;
    if(size_of_data<=0) return 1;

    for(uint32_t i = 0; i!=size_of_data; i++)
    {
        data_in_out[i]-=hash_seed[i%size_of_hash_seed];
    }
    return 0;
}

size_t UniversalTools0::count_string_chars(const char* string_data)
{
    size_t count_chars = 0;
    for(;; count_chars++) if(string_data[count_chars]=='\0') break;
    return count_chars;
}

//--DANGEROUS
void UniversalTools0::const_char_to_char(const char* data_in,char* data_out)
{
    int i = 0;
    for(; data_in[i]!='\0'; i++) data_out[i] = data_in[i];
    data_out[i] = '\0';
    return;
}

unsigned int UniversalTools0::write_to_file0(const char* file,char* data,const size_t how_many_chars_write,const size_t write_at_position)
{
    FILE* file0 = fopen(file,"r+b");;
    if(file0==NULL) return 1;
    fseek(file0,write_at_position,SEEK_SET);
    size_t result0 = fwrite(data,1,how_many_chars_write,file0);
    fclose(file0);
    if(how_many_chars_write!=result0) return 2;
    return 0;

}

unsigned int UniversalTools0::read_from_file0(const char* file,char* data,const size_t read_from_position,const size_t how_many_chars_read)
{

    FILE* file0 = fopen(file,"rb");
    if(file0==NULL) return 1;
    fseek(file0,read_from_position,SEEK_SET);
    size_t result0 = fread(data,sizeof(data[0]),how_many_chars_read,file0);
    fclose(file0);
    if(how_many_chars_read!=result0) return 2;
    data[result0] = '\0';
    return 0;
}

int UniversalTools0::advanced_write_to_file0(const char* const filename,const char* const data_in,unsigned int sizeof_data_in,const char* const search_for,
                            unsigned int start_reading_from_pos,unsigned int how_many_bytes_allocate_for_searching_operation = 1024)
{
    FILE* file = fopen(filename,"r+b");
    if(file==NULL) return -3;

    if(how_many_bytes_allocate_for_searching_operation==0) return -1;
    char* buffor = (char*)malloc(how_many_bytes_allocate_for_searching_operation);
    unsigned int search_for_counter = 0;
    unsigned int read_counter;
    unsigned int actual_position = 0;
    for(; search_for[search_for_counter]!='\0'; search_for_counter++) {}

    fseek(file,start_reading_from_pos,SEEK_SET);

    for(;;)
    {
        read_counter = fread(buffor,1,how_many_bytes_allocate_for_searching_operation,file);
        for(unsigned int i = 0; i!=read_counter; i++,actual_position++)
        {
            if(buffor[i]==search_for[0])
            {
                if(search_for_counter!=1)
                {
                    bool exit_loop0 = 0;
                    for(unsigned int k = 1; k<search_for_counter; k++)
                    {
                        if(buffor[i+k]!=search_for[k])
                        {
                            exit_loop0 = 1;
                            break;
                        }
                    }
                    if(exit_loop0==1) continue;
                }
                actual_position+=search_for_counter+start_reading_from_pos;
                fseek(file,actual_position,SEEK_SET);

                fwrite(data_in,1,sizeof_data_in,file);
                fclose(file);
                free(buffor);
                return actual_position;
            }
        }
        if(read_counter!=how_many_bytes_allocate_for_searching_operation) break;
    }
    fclose(file);
    free(buffor);

    return -2;
}

int UniversalTools0::advanced_read_from_file0(const char* const filename,char* const data_out,const char* const search_for,
                                 unsigned int how_many_chars_read,const char* const at_what_chars_stop_reading,
                                 unsigned int start_reading_from_pos,unsigned int how_many_bytes_allocate_for_searching_operation = 1024)
{
    FILE* file = fopen(filename,"rb");
    if(file==NULL) return -3;

    if(how_many_bytes_allocate_for_searching_operation==0) return -1;
    char* buffor = (char*)malloc(how_many_bytes_allocate_for_searching_operation);
    unsigned int search_for_counter = 0;
    unsigned int read_counter;
    unsigned int actual_position = 0;
    unsigned int at_what_chars_stop_reading_counter = 0;
    for(; search_for[search_for_counter]!='\0'; search_for_counter++) {}
    if(at_what_chars_stop_reading!=NULL) for(; at_what_chars_stop_reading[at_what_chars_stop_reading_counter]!='\0'; at_what_chars_stop_reading_counter++) {}

    if(how_many_chars_read==0&&at_what_chars_stop_reading_counter==0){free(buffor); return -1;}
    if(search_for_counter==0||search_for_counter>how_many_bytes_allocate_for_searching_operation){free(buffor); return -1;}
    if(at_what_chars_stop_reading_counter>how_many_bytes_allocate_for_searching_operation) {free(buffor); return -1;}

    fseek(file,start_reading_from_pos,SEEK_SET);

    for(;;)
    {
        read_counter = fread(buffor,1,how_many_bytes_allocate_for_searching_operation,file);
        for(unsigned int i = 0; i!=read_counter; i++,actual_position++)
        {
            if(buffor[i]==search_for[0])
            {
                if(search_for_counter!=1)
                {
                    bool exit_loop0 = 0;
                    for(unsigned int k = 1; k<search_for_counter; k++)
                    {
                        if(buffor[i+k]!=search_for[k])
                        {
                            exit_loop0 = 1;
                            break;
                        }
                    }
                    if(exit_loop0==1) continue;
                }
                actual_position+=search_for_counter+start_reading_from_pos;

                fseek(file,actual_position,SEEK_SET);
                if(how_many_chars_read!=0)
                {
                    unsigned int how_many_gets = fread(data_out,1,how_many_chars_read,file);
                    if(how_many_gets!=how_many_chars_read)
                    {
                        data_out[how_many_gets] = '\0';
                        fclose(file);
                        free(buffor);
                        return -2;
                    }
                    data_out[how_many_chars_read] = '\0';
                    actual_position = ftell(file);
                    fclose(file);
                    free(buffor);
                    return actual_position+1;
                }
                else
                {
                    bool continue_loop0 = 0;
                    for(unsigned int k = 0;;k++)
                    {
                        if(feof(file)!=0)
                        {
                            fclose(file);
                            data_out[k] = '\0';
                            free(buffor);
                            return -2;
                        }
                        buffor[0] = fgetc(file);
                        if(buffor[0]==at_what_chars_stop_reading[0])
                        {
                            data_out[k] = '\0';
                            if(at_what_chars_stop_reading_counter!=1)
                            {
                                for(unsigned int j = 1; j<at_what_chars_stop_reading_counter; j++)
                                {
                                    if(feof(file)!=0)
                                    {
                                        fclose(file);
                                        free(buffor);
                                        return -2;
                                    }
                                    buffor[j] = fgetc(file);
                                    if(buffor[j]!=at_what_chars_stop_reading[j])
                                    {

                                        continue_loop0 = 1;
                                        fseek(file,-1,SEEK_CUR);
                                        for(unsigned int l = 0; l<j; l++,k++) data_out[k] = buffor[l];
                                        k--;
                                        break;
                                    }
                                }
                                if(continue_loop0==1)
                                {
                                    continue_loop0 = 0;
                                    continue;
                                }
                            }
                            actual_position = ftell(file);
                            fclose(file);
                            free(buffor);
                            return actual_position;
                        }
                        else data_out[k] = buffor[0];
                    }
                }
            }
        }
        if(read_counter!=how_many_bytes_allocate_for_searching_operation) break;
    }
    fclose(file);
    data_out[0] = '\0';
    free(buffor);

    return -2;
}


int UniversalTools0::string_to_int32(const char* const data_in)
{
    int result = 0;
    int sign = 1;
    int counter = 0;

    while(!((data_in[counter]>='0'&&data_in[counter]<='9')||(data_in[counter]=='-')))
    {
        if(data_in[counter]=='\0') return 0;
        counter++;
    }

    if(data_in[counter]=='-')
    {
        sign = -1;
        counter++;
    }

    for(; data_in[counter]!='\0'; counter++)
    {
        if(data_in[counter]>='0'&&data_in[counter]<='9') result = result*10+data_in[counter]-'0';
        else break;

    }

    return result*sign;
}


bool UniversalTools0::do_file_exist(const char* file)
{
    FILE* file0 = fopen(file,"rb");
    if(file0==NULL) return 0;
    fclose(file0);
    return 1;
}

void UniversalTools0::uint32_to_string(unsigned int data_in,char* const data_out)
{
	char data_rev[10];
	for(int i = 0;; i++)
	{
		if(data_in < 10)
		{
			data_rev[i] = data_in+48;
			data_out[i+1] = '\0';
			for(int j = 0; j!=i+1; j++) data_out[j] = data_rev[i-j];
			return;
		}
		data_rev[i] = (data_in%10)+48;
		data_in = (data_in-(data_in%10))/10;
	}
}

bool UniversalTools0::compare_data(uint8_t* data0, uint8_t* data1,size_t sizeof_data0_and_data1)
{
	for(size_t i = 0; i!=sizeof_data0_and_data1; i++) if(data0[i]!=data1[i]) return 1;
	return 0;
}

size_t UniversalTools0::file_size(const char* file_name)
{
    FILE* file0 = fopen(file_name,"rb");
    size_t pos0;
    fseek(file0,0,SEEK_END);
    pos0 = ftell(file0);
    fclose(file0);
    return pos0;
}


//===================================================================================================


//SDL_UniversalTools
//===================================================================================================



void SDL_UniversalTools0::FpsControl_EndFrame()
{
    //working version but too much complicated for no reason;
    /*this->FpsControl_FpsTimerEnd = (this->FpsControl_FpsTimerStart-SDL_GetTicks());
    if(this->FpsControl_FpsTimerEnd<0)
    {
        if((1000.0/this->FpsControl_fps)+this->FpsControl_FpsTimerEnd<0) return;
        SDL_Delay((1000.0/this->FpsControl_fps)+this->FpsControl_FpsTimerEnd);
    }
    else SDL_Delay(1000.0/this->FpsControl_fps);*/

    this->FpsControl_FpsTimerEnd = (SDL_GetTicks()-this->FpsControl_FpsTimerStart);
    if((1000.0/this->FpsControl_fps)>this->FpsControl_FpsTimerEnd) SDL_Delay((1000.0/this->FpsControl_fps)-this->FpsControl_FpsTimerEnd);

    return;
}

void SDL_UniversalTools0::FpsControl_StartFrame()
{
    FpsControl_FpsTimerStart = SDL_GetTicks();
    return;
}

void SDL_UniversalTools0::change_fps(uint32_t fps)
{
    this->FpsControl_fps = fps;
    return;
}

uint8_t SDL_UniversalTools0::Change_Texture_Opacity_To_Max(SDL_Texture* texture,uint8_t increase_by)
{
    SDL_BlendMode blendMode;
    SDL_GetTextureBlendMode(texture,&blendMode);
    if(blendMode!=SDL_BLENDMODE_BLEND) SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
    uint8_t actual_alpha;
    SDL_GetTextureAlphaMod(texture,&actual_alpha);
    if(actual_alpha==255) return 1;
    if((actual_alpha+increase_by)>255)
    {
        increase_by = 0;
        actual_alpha = 255;
    }
    SDL_SetTextureAlphaMod(texture,actual_alpha+increase_by);
    return 0;
}

void SDL_UniversalTools0::Set_Texture_Opacity_To_Zero_In_Instant(SDL_Texture* texture)
{
    SDL_BlendMode blendMode;
    SDL_GetTextureBlendMode(texture,&blendMode);
    if(blendMode!=SDL_BLENDMODE_BLEND) SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture,0);
    return;
}

void SDL_UniversalTools0::ShowSimpleMessageBox0(Uint32 flag,const char* title,const char* message,const char* StringButton)
{
    SDL_MessageBoxButtonData button = {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,0,StringButton};
    SDL_MessageBoxData MsgData =
    {
        flag,
        NULL,
        title,
        message,
        1,
        &button,
        NULL
    };
    int buttonid;
    SDL_ShowMessageBox(&MsgData, &buttonid);
    return;
}

void SDL_UniversalTools0::ScreenShotJPG(SDL_Renderer* render,const char* filename,int quality,size_t width,size_t height)
{
    SDL_Surface* CurrentSurf0 = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    SDL_RenderReadPixels(render,NULL,SDL_PIXELFORMAT_UNKNOWN,CurrentSurf0->pixels,CurrentSurf0->pitch);
    IMG_SaveJPG(CurrentSurf0,filename,quality);
    return;
}

void SDL_UniversalTools0::ScreenShotPNG(SDL_Renderer* render,const char* filename,size_t width,size_t height)
{
    SDL_Surface* CurrentSurf0 = SDL_CreateRGBSurface(0,width,height,16,3840,240,15,61440); //0x0f00 0x00f0 0x000f 0xf000 (it isn't in hex for multiplatform purpouse);
    SDL_RenderReadPixels(render,NULL,SDL_PIXELFORMAT_ARGB4444,CurrentSurf0->pixels,CurrentSurf0->pitch);
    IMG_SavePNG(CurrentSurf0,filename);
    return;
}

void SDL_UniversalTools0::combine_surfaces(uint32_t x,uint32_t y,SDL_Surface* src,SDL_Surface* dst)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_BlitSurface(src,NULL,dst,&rect);
    return;
}
//===================================================================================================
