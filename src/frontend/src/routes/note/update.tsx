import { createFileRoute } from "@tanstack/react-router";
import { useState } from "react";
import { Edit } from "lucide-react";

import {
  Card,
  CardContent,
  CardDescription,
  CardHeader,
  CardTitle,
} from "@/components/ui/card";
import { Input } from "@/components/ui/input";
import { Label } from "@/components/ui/label";
import { Textarea } from "@/components/ui/textarea";
import { Button } from "@/components//ui/button";
import { useNoteUpdate } from "@/services/webui/note-update";

export const Route = createFileRoute("/note/update")({
  component: RouteComponent,
});

function RouteComponent() {
  const [id, setId] = useState<number | null>(null);
  const [title, setTitle] = useState("");
  const [content, setContent] = useState("");

  const mutation = useNoteUpdate();

  const handleSubmit = () => {
    if (!id) {
      return;
    }

    mutation.mutate({
      id,
      title,
      content,
    });
  };

  return (
    <div className="flex-1 p-4">
      <Card className="shadow-lg border bg-card/70 dark:bg-card/60 backdrop-blur-sm">
        <CardHeader>
          <CardTitle className="flex items-center gap-2 text-orange-600 dark:text-orange-400">
            <Edit className="h-5 w-5" />
            Update Note
          </CardTitle>
          <CardDescription className="text-muted-foreground">
            Modify an existing note
          </CardDescription>
        </CardHeader>
        <CardContent className="space-y-4">
          <div className="space-y-2">
            <Label htmlFor="update-id">Note ID</Label>
            <Input
              id="update-id"
              placeholder="Enter note ID"
              value={id || 0}
              type="number"
              onChange={(e) => setId(parseInt(e.target.value))}
            />
          </div>
          <div className="space-y-2">
            <Label htmlFor="update-title">New Title</Label>
            <Input
              id="update-title"
              placeholder="Enter new title"
              value={title}
              onChange={(e) => setTitle(e.target.value)}
            />
          </div>
          <div className="space-y-2">
            <Label htmlFor="update-content">New Content</Label>
            <Textarea
              id="update-content"
              placeholder="Enter new content"
              value={content}
              onChange={(e) => setContent(e.target.value)}
              rows={3}
            />
          </div>
          <Button
            onClick={handleSubmit}
            disabled={mutation.isPending}
            className="w-full bg-orange-400 hover:bg-orange-500"
          >
            Update Note
          </Button>
        </CardContent>
      </Card>
    </div>
  );
}
