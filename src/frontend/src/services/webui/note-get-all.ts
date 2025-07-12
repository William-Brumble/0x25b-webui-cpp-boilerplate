import type { Response } from './models/response';
import type { Note } from './models/note';
import { useQuery } from '@tanstack/react-query';

import {
    DEFAULT_STALE_TIME,
    queryClient,
} from '@/services/query-client/query-client';

async function noteGetAll(): Promise<Response<Note[]>> {
    try {
        if (typeof window.webui.note_route_get_all === 'function') {
            const res = await window.webui.note_route_get_all();
            const notes: Response<Note[]> = JSON.parse(res);
            return notes;
        } else {
            throw new Error('Unavailable function: noteGetAll');
        }
    } catch (error) {
        throw new Error(`Error calling noteGetAll: ${error}`);
    }
}

const QID_FETCH_NOTE_GET_ALL = 'fetch-note-get-all';

export const prefetchNoteGetAll = async (
    postId: string,
    userZipcode: string
) => {
    return queryClient.prefetchQuery({
        queryKey: [QID_FETCH_NOTE_GET_ALL, postId, userZipcode],
        queryFn: () => noteGetAll(),
        staleTime: DEFAULT_STALE_TIME,
    });
};

export const useNoteGetAll = () => {
    return useQuery({
        queryKey: [QID_FETCH_NOTE_GET_ALL],
        queryFn: () => noteGetAll(),
        staleTime: DEFAULT_STALE_TIME,
    });
};

export const useFetchNoteGetAll = () => {
    return queryClient.fetchQuery({
        queryKey: [QID_FETCH_NOTE_GET_ALL],
        queryFn: () => noteGetAll(),
        staleTime: DEFAULT_STALE_TIME,
    });
};

export const useNoteGetAllInvalidate = () => {
    const invalidateNoteGetAll = async () => {
        await queryClient.invalidateQueries({
            queryKey: [QID_FETCH_NOTE_GET_ALL],
        });
    };

    return {
        invalidateNoteGetAll,
    };
};
