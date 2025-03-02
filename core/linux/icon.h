#ifndef ___ICON_H___
#define ___ICON_H___
#include <gtk/gtk.h>
#include<stdlib.h>

/** 为当前用户保存图标文件 */
int save_icon_file_for_user(const char const* icon_file_name, uint8_t *icon_svg_byte, size_t icon_svg_byte_size);

// 将unsigned char数组写入图片文件 
static int write_uchar_array_to_icon_file(const char *filename, const unsigned char *data, size_t size) ; 
#endif