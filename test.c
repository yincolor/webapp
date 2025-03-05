#include"webapp.h"

int main(int argc, char const *argv[])
{
    WebApp *app = webapp_create("app.ty.test_app", 0, "你好世界", "https://www.baidu.com", 1);
    printf("开始运行: %s\n", app->name);
    char * icon_svg_byte =  "<svg viewBox=\"0 0 1024 1024\" version=\"1.1\" width=\"64\" height=\"64\"><path d=\"M512 512m-512 0a512 512 0 1 0 1024 0 512 512 0 1 0-1024 0Z\" p-id=\"4477\" fill=\"#d81e06\"></path></svg>";
    size_t icon_byte_size = strlen(icon_svg_byte);
    webapp_set_icon_by_svg_bytes(app, icon_svg_byte, icon_byte_size+1);
    // webapp_switch_fullscreen(app); 
    webapp_set_user_agent(app, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/134.0.0.0 Safari/537.36");
    webapp_run(app); 
    return 0;
}
