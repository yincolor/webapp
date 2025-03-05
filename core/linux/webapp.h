#ifndef ___LINUX_WEBAPP_H___
#define ___LINUX_WEBAPP_H___

#include"api.h"

extern WebApp *webapp_create(char *app_name, uint32_t version, char *title, char *uri, uint8_t is_debug);
extern void webapp_run(WebApp *webapp); 
extern void webapp_switch_fullscreen(WebApp *webapp); 
extern void webapp_set_icon_by_svg_bytes(WebApp *webapp, uint8_t *icon_file_bytes, uint64_t icon_file_size);
extern void webapp_set_user_agent(WebApp *webapp, char *user_agent);

#endif


