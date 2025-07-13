#pragma once
#include <optional>

#include "features/webui/models/webui_model.h"

bool webui_db_init_schema();
std::optional<Settings> webui_db_read_first();
std::optional<Settings> webui_db_read_by_id(const int64_t pId);
std::optional<Settings> webui_db_create(const bool pKiosk, const int64_t pWidth,
                                        const int64_t pHeight, const int64_t pX,
                                        const int64_t pY);
std::optional<Settings> webui_db_update_kiosk(const int64_t pId,
                                              const bool pKiosk);
std::optional<Settings> webui_db_update_size(const int64_t pId,
                                             const int64_t pWidth,
                                             const int64_t pHeight);
std::optional<Settings> webui_db_update_pos(const int64_t pId, const int64_t pX,
                                            const int64_t xY);
