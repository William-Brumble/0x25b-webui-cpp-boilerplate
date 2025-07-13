import type { Response } from './models/response';
import { useMutation } from '@tanstack/react-query';
import { toast } from 'sonner';

import type { Note } from './models/note';
import { useNoteGetAllInvalidate } from '@/services/webui/note-get-all';

async function noteCreate(request: {
    title: string;
    content: string;
}): Promise<Response<Note>> {
    const payload = {
        title: request.title,
        content: request.content,
    };

    const serialized = JSON.stringify(payload);

    try {
        if (typeof window.webui.note_route_create === 'function') {
            const res = await window.webui.note_route_create(serialized);
            const note: Response<Note> = JSON.parse(res);
            return note;
        } else {
            throw new Error('Unavailable function: noteCreate');
        }
    } catch (error) {
        throw new Error(`Error calling noteCreate: ${error}`);
    }
}

export const useNoteCreate = () => {
    const { invalidateNoteGetAll } = useNoteGetAllInvalidate();

    const mutation = useMutation({
        mutationFn: noteCreate,
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
