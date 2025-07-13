import { useQuery } from '@tanstack/react-query';

import type { Response } from './models/response';
import type { Settings } from './models/settings';
import {
    DEFAULT_STALE_TIME,
    queryClient,
} from '@/services/query-client/query-client';

async function webuiReadSettings(): Promise<Response<Settings>> {
    try {
        if (typeof window.webui.webui_route_read === 'function') {
            const res = await window.webui.webui_route_read();
            const settings: Response<Settings> = JSON.parse(res);
            return settings;
        } else {
            throw new Error('Unavailable function: webui_route_read');
        }
    } catch (error) {
        throw new Error(`Error calling webui_route_read: ${error}`);
    }
}

const QID_WEBUI_READ_SETTINGS = 'fetch-webui-read-settings';

export const prefetchWebuiReadSettings = async () => {
    return queryClient.prefetchQuery({
        queryKey: [QID_WEBUI_READ_SETTINGS],
        queryFn: () => webuiReadSettings(),
        staleTime: DEFAULT_STALE_TIME,
    });
};

export const useWebuiReadSettings = () => {
    return useQuery({
        queryKey: [QID_WEBUI_READ_SETTINGS],
        queryFn: () => webuiReadSettings(),
        staleTime: DEFAULT_STALE_TIME,
    });
};

export const useFetchWebuiReadSettings = () => {
    return queryClient.fetchQuery({
        queryKey: [QID_WEBUI_READ_SETTINGS],
        queryFn: () => webuiReadSettings(),
        staleTime: DEFAULT_STALE_TIME,
    });
};

export const useWebuiReadSettingsInvalidate = () => {
    const invalidateWebuiReadSettings = async () => {
        await queryClient.invalidateQueries({
            queryKey: [QID_WEBUI_READ_SETTINGS],
        });
    };

    return {
        invalidateWebuiReadSettings,
    };
};
