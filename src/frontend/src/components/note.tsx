import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { Badge } from "@/components/ui/badge";

import type { Note } from "@/services/webui/models/note";
import { useNoteReadById } from "@/services/webui/note-read-by-id";

type IProps = {
  id: number;
};

export function Note({ id }: IProps) {
  const { data: res, isPending, isError, error } = useNoteReadById(id);

  if (isPending) {
    return <div>Loading...</div>;
  }

  if (isError) {
    return <span>Error: {error.message}</span>;
  }

  return (
    <div className="grid gap-4">
      <Card key={res.data.id} className="bg-background border">
        <CardHeader className="pb-1">
          <div className="flex items-start justify-between">
            <CardTitle className="text-lg">{res.data.title}</CardTitle>
            <Badge variant="outline" className="text-xs">
              {res.data.id}
            </Badge>
          </div>
        </CardHeader>
        <CardContent className="pt-0">
          <p className="text-muted-foreground mb-3">{res.data.content}</p>
          <div className="flex justify-between text-xs text-muted-foreground">
            <span>
              Created: {new Date(res.data.createdAt).toLocaleString()}
            </span>
          </div>
        </CardContent>
      </Card>
    </div>
  );
}
