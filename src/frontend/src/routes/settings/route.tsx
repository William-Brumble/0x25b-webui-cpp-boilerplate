import { createFileRoute, Outlet } from '@tanstack/react-router';

export const Route = createFileRoute('/settings')({
    component: RouteComponent,
});

function RouteComponent() {
    return (
        <div className="flex justify-between flex-col lg:flex-row gap-4">
            <Outlet />
        </div>
    );
}
