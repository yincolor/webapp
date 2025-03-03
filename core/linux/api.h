#ifndef ___WEBAPP_LINUX_API_H___
#define ___WEBAPP_LINUX_API_H___

#include<gtk/gtk.h>
#include<webkit/webkit.h>
#include"icon.h"

// Define the container_of macro for user-space programs
#define webapp_offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define webapp_container_of(ptr, type, member) ({                      \
	const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
	(type *)( (char *)__mptr - webapp_offsetof(type,member) );})

struct WebApp{ 
    char *name;
    uint32_t version; 
    GtkWindow *window; 
    WebKitWebView *webview; 
    uint8_t is_debug; 
    uint8_t is_window_closed; 

};
typedef struct WebApp WebApp; 

/** 
 * 应用初始化
 * app_name 应遵循 app.<开发者代号>.<应用名称> 如: app.buildername.sxcample_app
 */
WebApp *webapp_create(char *app_name, uint32_t version, char *title, char *uri, uint8_t is_debug);
/**
 * 应用启动
 * 当启动后，会阻塞
 */
void webapp_run(WebApp *webapp); 
/**
 * 切换窗口全屏状态
 */
void webapp_switch_fullscreen(WebApp *webapp); 
void webapp_set_icon_by_svg_bytes(WebApp *webapp, uint8_t *icon_file_bytes, uint64_t icon_file_size);

static GtkWindow *window_create(char *title, uint16_t width, uint16_t height); 
static WebKitWebView *webview_create(char *uri, uint8_t is_debug);


static void on_window_destroy(GtkWidget* close_window, gpointer arg);
static void on_window_key_press(GtkEventControllerKey *controller, guint keyval, guint keycode, GdkModifierType state, gpointer user_data); 

#endif
