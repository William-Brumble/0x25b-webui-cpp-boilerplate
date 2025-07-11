#pragma once
#include <webui.hpp>

#include "features/webui/models/webui_model.h"

bool webui_srv_init();
bool webui_srv_init_schema();
bool webui_srv_show_window();
void webui_srv_wait();
void webui_srv_clean();
std::optional<Settings> webui_srv_read();
std::optional<Settings> webui_srv_create(const bool pKiosk, const int64_t pWidth, const int64_t pHeight, const int64_t pX, const int64_t pY);
std::optional<Settings> webui_srv_update_kiosk(const bool pKiosk);
std::optional<Settings> webui_srv_update_size(const int64_t pWidth, const int64_t pHeight);
std::optional<Settings> webui_srv_update_pos(const int64_t pX, const int64_t pY);
