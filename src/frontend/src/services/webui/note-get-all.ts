import type { Response } from "./models/response";
import type { Note } from "./models/note";

export async function noteGetAll(): Promise<Response<Note[]>> {
  try {
    if (typeof window.webui.note_route_get_all === "function") {
      const res = await window.webui.note_route_get_all();
      const notes: Response<Note[]> = JSON.parse(res);
      return notes;
    } else {
      throw new Error("Unavailable function: noteGetAll");
    }
  } catch (error) {
    throw new Error(`Error calling noteGetAll: ${error}`);
  }
}
