/*******************************************************
 * Casio QR Code Generator
 * Developer: Wildchiken
 *******************************************************/

#include <fxlib.h>
#include <string.h>
#include "qrcodegen.h"

char qr_text_buffer[64]; 

static uint8_t qr0[qrcodegen_BUFFER_LEN_MAX];
static uint8_t qrTempBuffer[qrcodegen_BUFFER_LEN_MAX];

void input_string(char *buf, int max_len)
{
    unsigned int key;
    int len = 0;
    int mode = 1; 
    int last_key = 0;
    int sym_idx = 0;
    const char *symbols = ":/.?=&-_@#! %"; 
    
    int chars_per_line = 20; 
    int num_lines, start_line, i, start_idx, copy_len, current_line;
    char line_buf[22];

    buf[0] = '\0';

    while(1) {
        Bdisp_AllClr_DDVRAM();
        PrintXY(2, 2, (unsigned char*)"ENTER URL (Max 60):", 0);
        
        Bdisp_DrawLineVRAM(3, 12, 124, 12);
        Bdisp_DrawLineVRAM(3, 39, 124, 39);
        Bdisp_DrawLineVRAM(3, 12, 3, 39);
        Bdisp_DrawLineVRAM(124, 12, 124, 39);
        
        num_lines = (len + chars_per_line - 1) / chars_per_line;
        if (num_lines == 0) num_lines = 1;

        start_line = 0;
        if (num_lines > 3) {
            start_line = num_lines - 3; 
        }

        for (i = 0; i < 3; i++) {
            current_line = start_line + i;
            start_idx = current_line * chars_per_line;
            
            if (start_idx < len) {
                copy_len = len - start_idx;
                if (copy_len > chars_per_line) copy_len = chars_per_line;
                
                strncpy(line_buf, &buf[start_idx], copy_len);
                line_buf[copy_len] = '\0';
                
                if (current_line == (len / chars_per_line) && copy_len < chars_per_line) {
                    strcat(line_buf, "_");
                }
                
                PrintXY(5, 14 + i * 8, (unsigned char*)line_buf, 0);
            } else if (current_line == (len / chars_per_line)) {
                PrintXY(5, 14 + i * 8, (unsigned char*)"_", 0);
            }
        }
        
        if (mode == 0) PrintXY(2, 42, (unsigned char*)"[F1] Mode: ABC", 0);
        else           PrintXY(2, 42, (unsigned char*)"[F1] Mode: abc", 0);
        
        PrintXY(2, 49, (unsigned char*)"[F2] Sym: : / . ?", 0);
        PrintXY(2, 56, (unsigned char*)"[EXE] OK [DEL] Back", 0);
        Bdisp_PutDisp_DD();

        GetKey(&key);

        if (key == KEY_CTRL_EXE) {
            break; 
        }
        else if (key == KEY_CTRL_DEL) {
            if (len > 0) {
                len--;
                buf[len] = '\0';
            }
        }
        else if (key == KEY_CTRL_F1) {
            mode = 1 - mode;
        }
        else if (key == KEY_CTRL_F2) {
            if (last_key == KEY_CTRL_F2 && len > 0) {
                sym_idx = (sym_idx + 1) % 13;
                buf[len-1] = symbols[sym_idx];
            } else {
                if (len < max_len - 1) {
                    sym_idx = 0;
                    buf[len] = symbols[sym_idx];
                    len++;
                    buf[len] = '\0';
                }
            }
        }
        else if (key >= 0x20 && key <= 0x7E) {
            char c = (char)key;
            
            if (mode == 1 && c >= 'A' && c <= 'Z') {
                c += 32; 
            }
            
            if (len < max_len - 1) {
                buf[len] = c;
                len++;
                buf[len] = '\0';
            }
        }
        last_key = key; 
    }
}

void show_qr_code(const char *text)
{
    unsigned int key;
    int size, scale, offset_x, offset_y;
    int x, y, dx, dy;
    int ok;

    ok = qrcodegen_encodeText(text, qrTempBuffer, qr0, qrcodegen_Ecc_LOW,
        qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, 1);

    Bdisp_AllClr_DDVRAM();

    if (ok) {
        size = qrcodegen_getSize(qr0);

        scale = 2;
        if (size * 3 <= 64) scale = 3; 

        offset_x = (128 - size * scale) / 2;
        offset_y = (64 - size * scale) / 2;

        for (y = 0; y < size; y++) {
            for (x = 0; x < size; x++) {
                if (qrcodegen_getModule(qr0, x, y)) {
                    for(dy = 0; dy < scale; dy++) {
                        for(dx = 0; dx < scale; dx++) {
                            Bdisp_SetPoint_VRAM(offset_x + x*scale + dx, offset_y + y*scale + dy, 1);
                        }
                    }
                }
            }
        }
    } else {
        PrintXY(10, 30, (unsigned char*)"ERROR: TEXT TOO LONG", 0);
    }

    PrintXY(2, 2, (unsigned char*)"EXIT", 0);
    Bdisp_PutDisp_DD();

    while(1) {
        GetKey(&key);
        if (key == KEY_CTRL_EXIT) break;
    }
}

int AddIn_main(int isAppli, unsigned short OptionNum)
{
    unsigned int key;

    qr_text_buffer[0] = '\0';

    while(1) {
        Bdisp_AllClr_DDVRAM();
        PrintXY(20, 20, (unsigned char*)"QR CODE MAKER", 0);
        PrintXY(15, 40, (unsigned char*)"Press EXE to Start", 0);
        PrintXY(15, 50, (unsigned char*)"Press EXIT to Quit", 0);
        Bdisp_PutDisp_DD();

        GetKey(&key);
        
        if (key == KEY_CTRL_EXIT) {
            break; 
        }
        else if (key == KEY_CTRL_EXE) {
            input_string(qr_text_buffer, 60);
            
            if (qr_text_buffer[0] != '\0') {
                show_qr_code(qr_text_buffer);
            }
        }
    }
    
    return 1;
}

#pragma section _BR_Size
unsigned long BR_Size;
#pragma section

#pragma section _TOP
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}
#pragma section