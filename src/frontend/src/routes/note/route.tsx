import { createFileRoute, Outlet } from '@tanstack/react-router';

import { AllNotes } from '@/components/all-notes';

export const Route = createFileRoute('/note')({
    component: RouteComponent,
});

function RouteComponent() {
    return (
        <div className="flex justify-between flex-col lg:flex-row gap-4">
            <Outlet />
            <AllNotes />
        </div>
    );
}
