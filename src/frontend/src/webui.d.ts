import { Note } from "./services/webui/models/note";
import { Response } from "./services/webui/models/response";

declare global {
  interface WebUI {
    note_route_create: (payload: string) => Promise<string>;
    note_route_delete: (payload: string) => Promise<string>;
    note_route_get_all: () => Promise<string>;
    note_route_read_by_id: (payload: string) => Promise<string>;
    note_route_update: (payload: string) => Promise<string>;
    webui_route_read: (payload: string) => Promise<string>;
    webui_route_update_kiosk: (payload: string) => Promise<string>;
    webui_route_update_size: (payload: string) => Promise<string>;
    webui_route_pos: (payload: string) => Promise<string>;
    exit: () => void;
  }

  interface Window {
    webui: WebUI;
  }
}

export {}; // ← super important
