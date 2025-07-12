import { StrictMode } from 'react';
import ReactDOM from 'react-dom/client';
import { QueryClientProvider } from '@tanstack/react-query';
import { RouterProvider, createRouter } from '@tanstack/react-router';

import './index.css';
import { Toaster } from '@/components/ui/sonner';
import { ThemeProvider } from '@/store/theme-provider';
import { queryClient } from './services/query-client/query-client.tsx';

// Import the generated route tree
import { routeTree } from './routeTree.gen';

// Create a new router instance
const router = createRouter({
    routeTree,
    defaultPreload: 'intent',
    // Configure for WebUI compatibility
    context: {
        // Add any context you need
    },
});

// Register the router instance for type safety
declare module '@tanstack/react-router' {
    interface Register {
        router: typeof router;
    }
}

// Render the app
const rootElement = document.getElementById('root')!;
if (!rootElement.innerHTML) {
    const root = ReactDOM.createRoot(rootElement);
    root.render(
        <StrictMode>
            <QueryClientProvider client={queryClient}>
                <ThemeProvider defaultTheme="dark" storageKey="vite-ui-theme">
                    <RouterProvider router={router} />
                    <Toaster />
                </ThemeProvider>
            </QueryClientProvider>
        </StrictMode>
    );
}
