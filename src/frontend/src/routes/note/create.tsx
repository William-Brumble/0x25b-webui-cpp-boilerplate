import { createFileRoute } from '@tanstack/react-router';
import { Plus } from 'lucide-react';
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
import { Textarea } from '@/components/ui/textarea';
import { useNoteCreate } from '@/services/webui/note-create';

export const Route = createFileRoute('/note/create')({
    component: RouteComponent,
});

function RouteComponent() {
    const [title, setTitle] = useState('');
    const [content, setContent] = useState('');

    const mutate = useNoteCreate();

    const handleSubmit = () => {
        mutate.mutate({
            title,
            content,
        });
    };

    return (
        <div className="flex-1 p-4">
            <Card className="shadow-lg border bg-card/70 dark:bg-card/60 backdrop-blur-sm">
                <CardHeader>
                    <CardTitle className="flex items-center gap-2 text-green-600 dark:text-green-400">
                        <Plus className="h-5 w-5" />
                        Create Note
                    </CardTitle>
                    <CardDescription className="text-muted-foreground">
                        Add a new note to your collection
                    </CardDescription>
                </CardHeader>
                <CardContent className="space-y-4">
                    <div className="space-y-2">
                        <Label htmlFor="create-title">Title</Label>
                        <Input
                            id="create-title"
                            placeholder="Enter note title"
                            value={title}
                            onChange={(e) => setTitle(e.target.value)}
                        />
                    </div>
                    <div className="space-y-2">
                        <Label htmlFor="create-content">Content</Label>
                        <Textarea
                            id="create-content"
                            placeholder="Enter note content"
                            value={content}
                            onChange={(e) => setContent(e.target.value)}
                            rows={3}
                        />
                    </div>
                    <Button
                        onClick={handleSubmit}
                        className="w-full bg-green-400 hover:bg-green-500"
                    >
                        Create Note
                    </Button>
                </CardContent>
            </Card>
        </div>
    );
}
