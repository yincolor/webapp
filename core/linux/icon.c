#include "icon.h"

// static unsigned char icon_svg_byte[1585] = {0x3c, 0x73, 0x76, 0x67, 0x20, 0x74, 0x3d, 0x22, 0x31, 0x37, 0x34, 0x30,0x0a};

// static size_t icon_svg_byte_size = 1585;

int save_icon_file_for_user(const char *icon_file_name, uint8_t *icon_svg_byte, size_t icon_svg_byte_size)
{
    const char *home_dir = g_get_home_dir();
    if (!home_dir)
    {
        g_print("获取用户家目录失败\n");
        return -1;
    }

    const char *icon_dir = g_build_filename(home_dir, ".local", "share", "icons", "hicolor", "48x48", "apps", NULL);
    if (!icon_dir)
    {
        /* 获取用户icons图标目录失败 */
        g_print("获取用户icons图标目录失败\n");
        return -2;
    }
    g_print("icons dir is %s\n", icon_dir);

    if (!g_file_test(icon_dir, G_FILE_TEST_IS_DIR))
    {
        /* 没有这个图标目录 */
        g_print("没有这个图标目录\n");
        return -3;
    }
    const char *icon_file_path = g_build_filename(icon_dir, icon_file_name, NULL);

    g_print("保存文件：%s\n", icon_file_path);

    if (g_file_test(icon_file_path, G_FILE_TEST_EXISTS))
    {
        g_print("图标的文件路径下，存在该文件，不需要创建\n");
        return 1;
    }
    int is_ok = write_uchar_array_to_icon_file(icon_file_path, icon_svg_byte, icon_svg_byte_size);
    if (is_ok > 0)
    {
        g_print("保存图标文件成功\n");
        return 2;
    }
    else
    {
        /* 保存失败 */
        g_print("fail to save icon file\n");
        return -5;
    }
}

// 将unsigned char数组写入图片文件
static int write_uchar_array_to_icon_file(const char *filename, const unsigned char *data, size_t size)
{
    // 打开文件以二进制写入模式（如果文件不存在则创建）
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        g_print("[write_uchar_array_to_icon_file] 无法打开icon文件\n");
        return -1;
    }

    // 写入数据到文件
    size_t written = fwrite(data, sizeof(unsigned char), size, file);
    if (written != size)
    {
        g_print("写入文件时出错\n");
        fclose(file);
        return -2;
    }

    // 关闭文件
    fclose(file);
    printf("成功将 %zu 字节写入文件 '%s'。\n", size, filename);
    return 1;
}