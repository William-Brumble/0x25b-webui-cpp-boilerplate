import { useMutation } from '@tanstack/react-query';
import { toast } from 'sonner';

import type { Response } from './models/response';
import type { Settings } from './models/settings';
import { useWebuiReadSettingsInvalidate } from './webui-read-settings';

async function webuiUpdatePos(request: {
    x: number;
    y: number;
}): Promise<Response<Settings>> {
    const payload = {
        x: request.x,
        y: request.y,
    };

    const serialized = JSON.stringify(payload);

    try {
        if (typeof window.webui.webui_route_pos === 'function') {
            const res = await window.webui.webui_route_pos(serialized);
            const settings: Response<Settings> = JSON.parse(res);
            return settings;
        } else {
            throw new Error('Unavailable function: webui_route_pos');
        }
    } catch (error) {
        throw new Error(`Error calling webui_route_pos: ${error}`);
    }
}

export const useWebuiUpdatePos = () => {
    const { invalidateWebuiReadSettings } = useWebuiReadSettingsInvalidate();

    const mutation = useMutation({
        mutationFn: webuiUpdatePos,
        onSuccess: async (res) => {
            if (res.error) {
                toast('Error:', { description: res.errorMessage });
            } else {
                toast('Success:', {
                    description: JSON.stringify(res.data, null, 2),
                });
                await invalidateWebuiReadSettings();
            }
        },
        onError: (error) => {
            toast('Error:', { description: error.message });
        },
    });

    return mutation;
};
