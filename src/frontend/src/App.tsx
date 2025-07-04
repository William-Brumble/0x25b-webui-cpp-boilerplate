import { AllNotes } from "@/components/all-notes";
import { UpdateNote } from "@/components/update-note";
import { CreateNote } from "@/components/create-note";
import { DeleteById } from "@/components/delete-by-id";
import { ReadById } from "@/components/read-by-id";

function App() {
  return (
    <div className="min-h-screen bg-black p-4 text-foreground">
      <div className="max-w-6xl mx-auto">
        <div className="grid grid-cols-1 lg:grid-cols-2 gap-6">
          {/* Read by ID */}
          <ReadById />

          {/* Delete by ID */}
          <DeleteById />

          {/* Create Note */}
          <CreateNote />

          {/* Update Note */}
          <UpdateNote />

          {/* Get All Notes */}
          <AllNotes />
        </div>
      </div>
    </div>
  );
}

export default App;
