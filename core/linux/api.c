#include"api.h"

WebApp *webapp_create(char *app_name, uint32_t version, char *title, char *uri, uint8_t is_debug){
    WebApp *app = (WebApp *)malloc(sizeof(WebApp));
    printf("申请内存大小：%ld字节\n", sizeof(WebApp));
    app->name = app_name;
    app->version = version; 
    app->is_debug = is_debug; 
    printf("app_name: %s 版本: %d 是否开启开发者模式: %d\n", app->name, app->version, app->is_debug); 
    printf("app ptr = %p\n", app); 

    if(gtk_init_check() == FALSE){
        free(app);
        return NULL; 
    }
    app->window = window_create(title, 800, 600);  
    app->webview = webview_create(uri, is_debug);
    gtk_window_set_child(app->window, GTK_WIDGET(app->webview)); 
    
    g_signal_connect(app->window, "destroy", G_CALLBACK(on_window_destroy), app);

    GtkEventControllerKey *key_controller = GTK_EVENT_CONTROLLER_KEY(gtk_event_controller_key_new());
    gtk_widget_add_controller( GTK_WIDGET(app->webview), GTK_EVENT_CONTROLLER(key_controller));
    g_signal_connect(key_controller, "key-pressed", G_CALLBACK(on_window_key_press), app);

    app->is_window_closed = 0; 
    return app; 
}


void webapp_run(WebApp *webapp){
    gtk_window_present(webapp->window); 
    while (webapp->is_window_closed <= 0)
    {
        GMainContext *context = g_main_context_default(); 
        g_main_context_iteration(context, FALSE); 
    }
    // printf("程序关闭的逻辑处理\n"); 
    free(webapp);
}

void webapp_switch_fullscreen(WebApp *webapp)
{
    gboolean is_fullscreen =  gtk_window_is_fullscreen(webapp->window);  
    if(is_fullscreen == TRUE){
        // 处于全屏状态，退出全屏
        gtk_window_unfullscreen(webapp->window);
    }else{
        // 设置窗口全屏
        gtk_window_fullscreen(webapp->window); 
    }
}

void webapp_set_icon_by_svg_bytes(WebApp *webapp, uint8_t *svg_bytes, uint64_t svg_size)
{
    const size_t app_id_max_size = 1024; 
    const size_t file_name_max_size = app_id_max_size+4; 
    char *app_id = (char *)malloc(app_id_max_size); 
    snprintf(app_id, app_id_max_size, "%s.%d", webapp->name, webapp->version); 
    // printf("icon app_id=%s\n", app_id); 
    char *icon_file_name = (char *)malloc(file_name_max_size);  
    snprintf(icon_file_name, file_name_max_size, "%s.svg", app_id); 
    // printf("icon_file_name=%s\n", icon_file_name); 
    int is_icon_created = save_icon_file_for_user(icon_file_name, svg_bytes, svg_size); 
    if(is_icon_created){
        gtk_window_set_icon_name(webapp->window, app_id); 
    }
    free(app_id);
    free(icon_file_name);
    app_id = NULL;
    icon_file_name = NULL; 
}


void webapp_set_user_agent(WebApp *webapp, char *user_agent){
    WebKitSettings *setting = webkit_web_view_get_settings(webapp->webview); 
    webkit_settings_set_user_agent(setting, user_agent); 
}

static GtkWindow *window_create(char *title, uint16_t width, uint16_t height){
    // printf("开始创建GtkWindow组件\n");
    GtkWidget *window_widget = gtk_window_new(); 
    GtkWindow *window = GTK_WINDOW(window_widget);
    gtk_window_set_title(window, title); 
    gtk_window_set_default_size(window, (int)width, (int)height); 
    
    
    return window; 
} 


static WebKitWebView *webview_create(char *uri, uint8_t is_debug){
    printf("开始创建Webkit组件\n");
    WebKitWebView * _webview_instance = WEBKIT_WEB_VIEW(webkit_web_view_new());
    if(!_webview_instance){
        printf("创建Webkit组件失败\n");
        return NULL; 
    } 
    // 设置header
    WebKitSettings *setting = webkit_web_view_get_settings(_webview_instance);
    if(is_debug > 0){
        webkit_settings_set_enable_developer_extras(setting, true); 
    }
    webkit_settings_set_user_agent(setting, "Mozilla/5.0 (X11; Linux x86_64; rv:130.0) Gecko/20100101 Firefox/130.0");

    webkit_web_view_load_uri(_webview_instance, uri);
    
    
    
    return _webview_instance; 
}

static void on_window_destroy(GtkWidget* close_window_widget, gpointer app_ptr){
    WebApp *app =  (WebApp *)app_ptr;
    printf("app ptr = %p\n", app); 
    printf("窗口被关闭, app_name=%s\n", app->name); 
    app->is_window_closed = 1; 
}

static void on_window_key_press(GtkEventControllerKey *controller, guint keyval, guint keycode, GdkModifierType state, gpointer webapp_ptr){
    // printf("Key pressed: keyval=%d, keycode=%d, modifiers=%d\n", keyval, keycode, state); 
    // Key pressed: keyval=65480, keycode=95, modifiers=21 设置：ctrl + shift + f11 全屏切换
    if(keycode == 95 && state == 21){
        webapp_switch_fullscreen((WebApp *)webapp_ptr); 
    }
}