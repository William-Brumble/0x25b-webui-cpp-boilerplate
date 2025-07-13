import {
    Outlet,
    createRootRoute,
    Link,
    redirect,
} from '@tanstack/react-router';

export const Route = createRootRoute({
    beforeLoad: ({ location }) => {
        // Redirect to "/" on initial app startup
        // This is needed due to webui cpp file handler serving up /index.html, and not /
        if (location.pathname === '/index.html') {
            throw redirect({
                to: '/',
                replace: true,
            });
        }
    },
    component: RootComponent,
});

function RootComponent() {
    return (
        <div className="min-h-screen bg-background">
            {/* Header */}
            <header className="border-b border-border bg-card/50 backdrop-blur-sm sticky top-0 z-50">
                <div className="container mx-auto px-4 sm:px-6 lg:px-8">
                    <div className="flex items-center justify-between h-16">
                        {/* Logo/Brand */}
                        <div className="flex items-center">
                            <Link
                                to="/"
                                className="text-xl font-semibold text-foreground hover:text-primary transition-colors"
                            >
                                App
                            </Link>
                        </div>

                        {/* Navigation */}
                        <nav className="hidden md:flex items-center space-x-1">
                            <Link
                                to="/"
                                className="px-3 py-2 rounded-md text-sm font-medium text-muted-foreground hover:text-foreground hover:bg-accent transition-all duration-200 [&.active]:text-foreground [&.active]:bg-accent [&.active]:font-medium"
                            >
                                Home
                            </Link>
                            <Link
                                to="/note/create"
                                className="px-3 py-2 rounded-md text-sm font-medium text-muted-foreground hover:text-foreground hover:bg-accent transition-all duration-200 [&.active]:text-foreground [&.active]:bg-accent [&.active]:font-medium"
                            >
                                Create
                            </Link>
                            <Link
                                to="/note/read"
                                className="px-3 py-2 rounded-md text-sm font-medium text-muted-foreground hover:text-foreground hover:bg-accent transition-all duration-200 [&.active]:text-foreground [&.active]:bg-accent [&.active]:font-medium"
                            >
                                Read
                            </Link>
                            <Link
                                to="/note/update"
                                className="px-3 py-2 rounded-md text-sm font-medium text-muted-foreground hover:text-foreground hover:bg-accent transition-all duration-200 [&.active]:text-foreground [&.active]:bg-accent [&.active]:font-medium"
                            >
                                Update
                            </Link>
                            <Link
                                to="/note/delete"
                                className="px-3 py-2 rounded-md text-sm font-medium text-muted-foreground hover:text-foreground hover:bg-accent transition-all duration-200 [&.active]:text-foreground [&.active]:bg-accent [&.active]:font-medium"
                            >
                                Delete
                            </Link>
                            <Link
                                to="/settings/settings"
                                className="px-3 py-2 rounded-md text-sm font-medium text-muted-foreground hover:text-foreground hover:bg-accent transition-all duration-200 [&.active]:text-foreground [&.active]:bg-accent [&.active]:font-medium"
                            >
                                Settings
                            </Link>
                        </nav>

                        {/* Mobile menu button */}
                        <div className="md:hidden">
                            <button className="p-2 rounded-md text-muted-foreground hover:text-foreground hover:bg-accent transition-colors">
                                <svg
                                    className="h-5 w-5"
                                    fill="none"
                                    viewBox="0 0 24 24"
                                    stroke="currentColor"
                                >
                                    <path
                                        strokeLinecap="round"
                                        strokeLinejoin="round"
                                        strokeWidth={2}
                                        d="M4 6h16M4 12h16M4 18h16"
                                    />
                                </svg>
                            </button>
                        </div>
                    </div>
                </div>
            </header>

            {/* Main content */}
            <main className="container mx-auto min-h-screen ">
                <div className="p-4 text-foreground">
                    <div className="max-w-6xl mx-auto">
                        <Outlet />
                    </div>
                </div>
            </main>
        </div>
    );
}
