import type { Response } from "./models/response";

export async function noteDelete(id: number): Promise<Response<null>> {
  const payload = {
    id: id,
  };

  const serialized = JSON.stringify(payload);

  try {
    if (typeof window.webui.note_route_delete === "function") {
      const res = await window.webui.note_route_delete(serialized);
      const response: Response<null> = JSON.parse(res);
      return response;
    } else {
      throw new Error("Unavailable function: noteDelete");
    }
  } catch (error) {
    throw new Error(`Error calling noteDelete: ${error}`);
  }
}
