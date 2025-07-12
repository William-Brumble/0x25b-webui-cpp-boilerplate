import { createFileRoute } from '@tanstack/react-router';
import { Trash2 } from 'lucide-react';
import { useState } from 'react';

import { Button } from '@/components/ui/button';
import {
    Card,
    CardContent,
    CardDescription,
    CardHeader,
    CardTitle,
} from '@/components/ui/card';
import { Input } from '@/components/ui/input';
import { Label } from '@/components/ui/label';
import { useNoteDelete } from '@/services/webui/note-delete';

export const Route = createFileRoute('/note/delete')({
    component: RouteComponent,
});

function RouteComponent() {
    const [id, setId] = useState(0);

    const mutate = useNoteDelete();

    const handleSubmit = () => {
        mutate.mutate({
            id,
        });
    };

    return (
        <div className="flex-1 p-4">
            <Card className="shadow-lg border bg-card/70 dark:bg-card/60 backdrop-blur-sm">
                <CardHeader>
                    <CardTitle className="flex items-center gap-2 text-red-600 dark:text-red-400">
                        <Trash2 className="h-5 w-5" />
                        Delete by ID
                    </CardTitle>
                    <CardDescription className="text-muted-foreground">
                        Remove a note by its ID
                    </CardDescription>
                </CardHeader>
                <CardContent className="space-y-4">
                    <div className="space-y-2">
                        <Label htmlFor="delete-id">Note ID</Label>
                        <Input
                            id="delete-id"
                            placeholder="Enter note ID"
                            value={id}
                            type="number"
                            onChange={(e) => setId(parseInt(e.target.value))}
                        />
                    </div>
                    <Button
                        onClick={handleSubmit}
                        disabled={mutate.isPending}
                        className="w-full bg-red-400 hover:bg-red-500"
                    >
                        Delete Note
                    </Button>
                </CardContent>
            </Card>
        </div>
    );
}
