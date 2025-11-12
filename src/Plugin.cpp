#include "Dock.hpp"

#include <obs-module.h>
#include <obs-frontend-api.h>

#include <QAction>
#include <QPointer>
#include <QMainWindow>
#include "ShaderDispatcher.hpp"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("audiolink-obs", "en-US")

static QPointer<AudioLinkDock> g_dock;
static QAction* g_toolsAction = nullptr;

const char* obs_module_name(void)
{
    return "AudioLink (OBS Tool/Dock)";
}

const char* obs_module_description(void)
{
    return "Provides a dockable tool that enumerates audio sources.";
}

bool obs_module_load(void)
{
    g_dock = new AudioLinkDock();
    g_dock->setObjectName("audiolink_dock");

    // ✅ OBS 27–29 dock registration
    obs_frontend_add_custom_qdock("audiolink", g_dock);


    // ✅ OBS 27–29 Tools menu (returns QAction*)
    g_toolsAction = static_cast<QAction*>(obs_frontend_add_tools_menu_qaction("AudioLink"));
    QObject::connect(g_toolsAction, &QAction::triggered, [] {
        if (g_dock) {
            g_dock->show();
            g_dock->raise();
            g_dock->activateWindow();
        }
    });

    ShaderDispatcher::Initialize();

    blog(LOG_INFO, "[audiolink-obs] module loaded");
    return true;
}

void obs_module_unload(void)
{
    // Deleted automatically on OBS shutdown, but safe to clean up
    if (g_toolsAction) {
        delete g_toolsAction;
        g_toolsAction = nullptr;
    }

    if (g_dock) {
        delete g_dock;
        g_dock = nullptr;
    }

    ShaderDispatcher::Shutdown();

    blog(LOG_INFO, "[audiolink-obs] module unloaded");
}
