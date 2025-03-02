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
    printf("程序关闭的逻辑处理\n"); 
    free(webapp);
}


void webapp_set_icon_by_svg_bytes(WebApp *webapp, uint8_t *svg_bytes, uint64_t svg_size){
    const size_t app_id_max_size = 1024; 
    const size_t file_name_max_size = app_id_max_size+4; 
    char *app_id = (char *)malloc(app_id_max_size); 
    snprintf(app_id, app_id_max_size, "%s.%d", webapp->name, webapp->version); 
    char *icon_file_name = (char *)malloc(file_name_max_size);  
    snprintf(icon_file_name, file_name_max_size, "%s.svg", app_id); 
    int is_icon_created = save_icon_file_for_user(icon_file_name, svg_bytes, svg_size); 
    if(is_icon_created){
        gtk_window_set_icon_name(webapp->window, app_id); 
    }
}


static GtkWindow *window_create(char *title, uint16_t width, uint16_t height){
    printf("开始创建GtkWindow组件\n");
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
    webkit_settings_set_user_agent(setting, "Mozilla/5.0 (X11; Linux x86_64; rv:135.0) Gecko/20100101 Firefox/135.0 WebApp/0");

    webkit_web_view_load_uri(_webview_instance, uri);
    return _webview_instance; 
}

static void on_window_destroy(GtkWidget* close_window_widget, gpointer app_ptr){
    // GtkWindow *close_window = GTK_WINDOW(close_window_widget); 
    // WebApp *app = webapp_container_of(&close_window, WebApp, window);
    WebApp *app =  (WebApp *)app_ptr;
    printf("app ptr = %p\n", app); 
    printf("窗口被关闭, app_name=%s\n", app->name); 
    app->is_window_closed = 1; 
}

// static void on_gtk_app_activate(GApplication *app, gpointer user_data){
//     printf("gtk app 初始化完毕\n"); 
// }