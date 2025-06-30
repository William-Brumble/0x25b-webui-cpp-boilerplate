import type { Response } from "./models/response";
import type { Note } from "./models/note";

export async function noteReadById(id: number): Promise<Response<Note>> {
  const payload = {
    id: id,
  };

  const serialized = JSON.stringify(payload);

  try {
    if (typeof window.webui.note_route_read_by_id === "function") {
      const res = await window.webui.note_route_read_by_id(serialized);
      const note: Response<Note> = JSON.parse(res);
      return note;
    } else {
      throw new Error("Unavailable function: noteReadById");
    }
  } catch (error) {
    throw new Error(`Error calling noteReadById: ${error}`);
  }
}
