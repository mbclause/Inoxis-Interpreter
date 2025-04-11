#include <glib.h>
#include <stdio.h>

int func();

int func()
{
    gchar* msg = g_strdup("GLib is working in MSVC!");
    g_print("%s\n", msg);
    g_free(msg);
    return 0;
}