import type { Response } from "./models/response";
import type { Note } from "./models/note";

export async function noteUpdate(
  id: number,
  title: string,
  content: string
): Promise<Response<Note>> {
  const payload = {
    id: id,
    title: title,
    content: content,
  };

  const serialized = JSON.stringify(payload);

  try {
    if (typeof window.webui.note_route_update === "function") {
      const res = await window.webui.note_route_update(serialized);
      const note: Response<Note> = JSON.parse(res);
      return note;
    } else {
      throw new Error("Unavailable function: noteUpdate");
    }
  } catch (error) {
    throw new Error(`Error calling noteUpdate: ${error}`);
  }
}
