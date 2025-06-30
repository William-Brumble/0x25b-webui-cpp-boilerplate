import { useState } from "react";
import "./App.css";

import type { Note } from "./services/webui/models/note";
import { noteCreate } from "./services/webui/note-create";
//import { noteDelete } from "./services/webui/note-delete";
import { noteGetAll } from "./services/webui/note-get-all";
//import { noteReadById } from "./services/webui/note-read-by-id";
//import { noteUpdate } from "./services/webui/note-update";

function App() {
  const [title, setTitle] = useState<string | null>(null);
  const [content, setContent] = useState<string | null>(null);
  const [notes, setNotes] = useState<Note[]>([]);

  async function getAllNotes() {
    const res = await noteGetAll();
    setNotes(res.data);
  }

  async function createNote() {
    if (!title) {
      return;
    }

    if (!content) {
      return;
    }

    await noteCreate(title, content);

    setTitle(null);
    setContent(null);
  }

  return (
    <>
      <div>
        <input
          placeholder="Input a title"
          onChange={(e: React.ChangeEvent<HTMLInputElement>) => {
            setTitle(e.target.value);
          }}
        />
        <input
          placeholder="Input a content"
          onChange={(e: React.ChangeEvent<HTMLInputElement>) => {
            setContent(e.target.value);
          }}
        />
        <button onClick={createNote}>CREATE NOTE</button>
      </div>
      <button onClick={getAllNotes}>GET ALL NOTES</button>
      <div>
        {notes &&
          notes.map((note, index) => {
            return (
              <div key={index}>
                <div>NOTE</div>
                <div>====================</div>
                <div>id: {note.id}</div>
                <div>title: {note.title}</div>
                <div>content: {note.content}</div>
                <div>created at: {note.createdAt}</div>
              </div>
            );
          })}
      </div>
    </>
  );
}

export default App;
