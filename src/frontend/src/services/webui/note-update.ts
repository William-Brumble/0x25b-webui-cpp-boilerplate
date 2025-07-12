import type { Response } from './models/response';
import { useMutation } from '@tanstack/react-query';
import { toast } from 'sonner';

import type { Note } from './models/note';
import { useNoteGetAllInvalidate } from '@/services/webui/note-get-all';

async function noteUpdate(request: {
    id: number;
    title: string;
    content: string;
}): Promise<Response<Note>> {
    const payload = {
        id: request.id,
        title: request.title,
        content: request.content,
    };

    const serialized = JSON.stringify(payload);

    try {
        if (typeof window.webui.note_route_update === 'function') {
            const res = await window.webui.note_route_update(serialized);
            const note: Response<Note> = JSON.parse(res);
            return note;
        } else {
            throw new Error('Unavailable function: noteUpdate');
        }
    } catch (error) {
        throw new Error(`Error calling noteUpdate: ${error}`);
    }
}

export const useNoteUpdate = () => {
    const { invalidateNoteGetAll } = useNoteGetAllInvalidate();

    const mutation = useMutation({
        mutationFn: noteUpdate,
        onSuccess: async (res) => {
            if (res.error) {
                toast('Error:', { description: res.errorMessage });
            } else {
                toast('Success:', {
                    description: JSON.stringify(res.data, null, 2),
                });
                await invalidateNoteGetAll();
            }
        },
        onError: (error) => {
            toast('Error:', { description: error.message });
        },
    });

    return mutation;
};
