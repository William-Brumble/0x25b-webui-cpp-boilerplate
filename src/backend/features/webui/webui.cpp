#include <optional>
#include <spdlog/spdlog.h>
#include <webui.hpp>

#include "features/webui/models/webui_model.h"
#include "features/webui/services/webui_database.h"
#include "features/webui/state/webui_state.h"
#include "features/webui/webui.h"
#include "vfs.h" // Generated using: python vfs.py "/path/to/folder" "vfs.h"

bool webui_srv_init() {
  spdlog::info("Reading webui settings...");
  std::optional<Settings> settings = webui_srv_read();
  if (!settings) {
    spdlog::info("Settings not found, creating defaults...");
    settings = webui_srv_create(false, 640, 360, 0, 0);
  }
  spdlog::debug("WebUI window configured: size={}x{}, pos={}x{}",
                settings->width, settings->height, settings->x, settings->y);

  webui::set_config(multi_client, true);
  webui::set_config(use_cookies, false);
  window.win.set_file_handler(vfs);

  return true;
}

bool webui_srv_init_schema() { return webui_db_init_schema(); }

bool webui_srv_show_window() {
  constexpr auto entryFile = "index.html";
  if (!window.win.show(entryFile)) {
    return false;
  }

  return true;
}

void webui_srv_wait() { webui::wait(); }

void webui_srv_clean() { webui::clean(); }

std::optional<Settings> webui_srv_read() {
  std::optional<Settings> settings = webui_db_read_first();

  if (settings) {
    window.win.set_position(settings->x, settings->y);
    window.win.set_size(settings->width, settings->height);
    window.win.set_kiosk(settings->kiosk);
  }

  return settings;
}

std::optional<Settings> webui_srv_create(const bool pKiosk,
                                         const int64_t pWidth,
                                         const int64_t pHeight,
                                         const int64_t pX, const int64_t pY) {
  window.win.set_position(pX, pY);
  window.win.set_size(pWidth, pHeight);
  window.win.set_kiosk(pKiosk);

  return webui_db_create(false, pWidth, pHeight, pX, pY);
}

std::optional<Settings> webui_srv_update_kiosk(const bool pKiosk) {
  window.win.set_kiosk(pKiosk);

  std::optional<Settings> settings = webui_db_read_first();
  if (settings) {
    return webui_db_update_kiosk(settings->id, pKiosk);
  }

  return webui_db_create(pKiosk, 640, 360, 0, 0);
}
std::optional<Settings> webui_srv_update_size(const int64_t pWidth,
                                              const int64_t pHeight) {
  window.win.set_size(pWidth, pHeight);

  std::optional<Settings> settings = webui_db_read_first();
  if (settings) {
    return webui_db_update_size(settings->id, pWidth, pHeight);
  }

  return webui_db_create(false, pWidth, pHeight, 0, 0);
}

std::optional<Settings> webui_srv_update_pos(const int64_t pX,
                                             const int64_t pY) {
  window.win.set_position(pX, pY);

  std::optional<Settings> settings = webui_db_read_first();
  if (settings) {
    return webui_db_update_pos(settings->id, pX, pY);
  }

  return webui_db_create(false, 640, 360, pX, pY);
}
