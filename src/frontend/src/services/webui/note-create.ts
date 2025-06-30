import type { Response } from "./models/response";
import type { Note } from "./models/note";

export async function noteCreate(
  title: string,
  content: string
): Promise<Response<Note>> {
  const payload = {
    title: title,
    content: content,
  };

  const serialized = JSON.stringify(payload);

  try {
    if (typeof window.webui.note_route_create === "function") {
      const res = await window.webui.note_route_create(serialized);
      const note: Response<Note> = JSON.parse(res);
      return note;
    } else {
      throw new Error("Unavailable function: noteCreate");
    }
  } catch (error) {
    throw new Error(`Error calling noteCreate: ${error}`);
  }
}
