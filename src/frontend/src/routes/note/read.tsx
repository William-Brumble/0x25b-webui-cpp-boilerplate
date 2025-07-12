import { createFileRoute } from "@tanstack/react-router";
import { Search } from "lucide-react";

import {
  Card,
  CardContent,
  CardDescription,
  CardHeader,
  CardTitle,
} from "@/components/ui/card";
import { Input } from "@/components/ui/input";
import { Label } from "@/components/ui/label";
import { Button } from "@/components/ui/button";
import { useState } from "react";
import { useFetchNoteReadById } from "@/services/webui/note-read-by-id";
import { toast } from "sonner";

export const Route = createFileRoute("/note/read")({
  component: RouteComponent,
});

function RouteComponent() {
  const [id, setId] = useState<number | null>(null);

  const handleSubmit = async () => {
    if (!id) {
      return;
    }

    const res = await useFetchNoteReadById(id);

    if (res.error) {
      toast("Error:", { description: res.errorMessage });
    } else {
      toast("Success:", { description: JSON.stringify(res.data, null, 2) });
    }
  };

  return (
    <div className="flex-1 p-4">
      <Card className="shadow-lg border bg-card/70 dark:bg-card/60 backdrop-blur-sm">
        <CardHeader>
          <CardTitle className="flex items-center gap-2 text-blue-600 dark:text-blue-400">
            <Search className="h-5 w-5" />
            Read by ID
          </CardTitle>
          <CardDescription className="text-muted-foreground">
            Find a specific note by its ID
          </CardDescription>
        </CardHeader>
        <CardContent className="space-y-4">
          <div className="space-y-2">
            <Label htmlFor="read-id">Note ID</Label>
            <Input
              id="read-id"
              placeholder="Enter note ID"
              value={id || 0}
              type="number"
              onChange={(e) => setId(parseInt(e.target.value))}
            />
          </div>
          <Button
            onClick={handleSubmit}
            className="w-full bg-blue-400 hover:bg-blue-500"
          >
            Read Note
          </Button>
        </CardContent>
      </Card>
    </div>
  );
}
