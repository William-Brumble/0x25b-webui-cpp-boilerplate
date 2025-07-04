import {
  Card,
  CardContent,
  CardDescription,
  CardHeader,
  CardTitle,
} from "@/components/ui/card";
import { Separator } from "@/components/ui/separator";
import { Badge } from "@/components/ui/badge";
import { BookOpen } from "lucide-react";

import { useNoteGetAll } from "@/services/webui/note-get-all";

export function AllNotes() {
  const { data, isPending, isError, error } = useNoteGetAll();

  if (isPending) {
    return <div>Loading...</div>;
  }

  if (isError) {
    return <span>Error: {error.message}</span>;
  }

  return (
    <div className="lg:col-start-2 lg:row-span-4 row-start-5">
      <Card className="shadow-lg border bg-card/70 dark:bg-card/60 backdrop-blur-sm">
        <CardHeader>
          <CardTitle className="flex items-center gap-2 text-purple-600 dark:text-purple-400">
            <BookOpen className="h-5 w-5" />
            All Notes
          </CardTitle>
          <CardDescription className="text-muted-foreground">
            View all your notes
          </CardDescription>
        </CardHeader>
        <CardContent>
          <div className="space-y-4">
            <Separator />
            <div className="grid gap-4">
              {data?.data.map((note) => (
                <Card key={note.id} className="bg-background border">
                  <CardHeader className="pb-3">
                    <div className="flex items-start justify-between">
                      <CardTitle className="text-lg">{note.title}</CardTitle>
                      <Badge variant="outline" className="text-xs">
                        {note.id}
                      </Badge>
                    </div>
                  </CardHeader>
                  <CardContent className="pt-0">
                    <p className="text-muted-foreground mb-3">{note.content}</p>
                    <div className="flex justify-between text-xs text-muted-foreground">
                      <span>
                        Created: {new Date(note.createdAt).toLocaleString()}
                      </span>
                    </div>
                  </CardContent>
                </Card>
              ))}
            </div>
          </div>
        </CardContent>
      </Card>
    </div>
  );
}
