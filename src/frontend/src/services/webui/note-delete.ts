import type { Response } from './models/response';
import { useMutation } from '@tanstack/react-query';

import { useNoteGetAllInvalidate } from '@/services/webui/note-get-all';
import { toast } from 'sonner';

async function noteDelete(request: { id: number }): Promise<Response<null>> {
    const payload = {
        id: request.id,
    };

    const serialized = JSON.stringify(payload);

    try {
        if (typeof window.webui.note_route_delete === 'function') {
            const res = await window.webui.note_route_delete(serialized);
            const response: Response<null> = JSON.parse(res);
            return response;
        } else {
            throw new Error('Unavailable function: noteDelete');
        }
    } catch (error) {
        throw new Error(`Error calling noteDelete: ${error}`);
    }
}

export const useNoteDelete = () => {
    const { invalidateNoteGetAll } = useNoteGetAllInvalidate();

    const mutation = useMutation({
        mutationFn: noteDelete,
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
