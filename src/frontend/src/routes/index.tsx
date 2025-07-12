import { createFileRoute } from '@tanstack/react-router';

export const Route = createFileRoute('/')({
    component: RouteComponent,
});

function RouteComponent() {
    return <div className="flex-1 p-4">Home</div>;
}
