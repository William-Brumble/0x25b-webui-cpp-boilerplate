import { createFileRoute } from "@tanstack/react-router";

export const Route = createFileRoute("/settings/settings")({
  component: RouteComponent,
});

function RouteComponent() {
  return <div className="flex-1 p-4">Hello "/settings"!</div>;
}
