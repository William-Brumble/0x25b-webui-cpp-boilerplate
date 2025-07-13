import { useQuery } from '@tanstack/react-query';

import type { Response } from './models/response';
import type { Note } from './models/note';
import {
    DEFAULT_STALE_TIME,
    queryClient,
} from '@/services/query-client/query-client';

async function noteReadById(request: { id: number }): Promise<Response<Note>> {
    const payload = {
        id: request.id,
    };

    const serialized = JSON.stringify(payload);

    try {
        if (typeof window.webui.note_route_read_by_id === 'function') {
            const res = await window.webui.note_route_read_by_id(serialized);
            const note: Response<Note> = JSON.parse(res);
            return note;
        } else {
            throw new Error('Unavailable function: noteReadById');
        }
    } catch (error) {
        throw new Error(`Error calling noteReadById: ${error}`);
    }
}

const QID_NOTE_GET_BY_ID = 'fetch-note-get-by-id';

export const prefetchNoteReadById = async (id: number) => {
    return queryClient.prefetchQuery({
        queryKey: [QID_NOTE_GET_BY_ID, id],
        queryFn: () => noteReadById({ id }),
        staleTime: DEFAULT_STALE_TIME,
    });
};

export const useNoteReadById = (id: number) => {
    return useQuery({
        queryKey: [QID_NOTE_GET_BY_ID, id],
        queryFn: () => noteReadById({ id }),
        staleTime: DEFAULT_STALE_TIME,
    });
};

export const useFetchNoteReadById = (id: number) => {
    return queryClient.fetchQuery({
        queryKey: [QID_NOTE_GET_BY_ID, id],
        queryFn: () => noteReadById({ id }),
        staleTime: DEFAULT_STALE_TIME,
    });
};

export const useNoteReadByIdInvalidate = (id: number) => {
    const invalidateNoteGetAll = async () => {
        await queryClient.invalidateQueries({
            queryKey: [QID_NOTE_GET_BY_ID, id],
        });
    };

    return {
        invalidateNoteGetAll,
    };
};
