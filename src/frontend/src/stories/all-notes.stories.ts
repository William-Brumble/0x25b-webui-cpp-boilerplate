import type { Meta, StoryObj } from '@storybook/react-vite';

import { AllNotesPresentation } from '@/components/all-notes';

const meta = {
    title: 'components/AllNotes',
    component: AllNotesPresentation,
    parameters: {
        layout: 'centered',
    },
    tags: ['autodocs'],
    argTypes: {
        isPending: { control: 'boolean' },
        isError: { control: 'boolean' },
    },
} satisfies Meta<typeof AllNotesPresentation>;

export default meta;
type Story = StoryObj<typeof meta>;

export const Default: Story = {
    args: {
        isPending: false,
        isError: false,
        error: null,
        data: [
            {
                id: 0,
                title: 'first',
                content: 'content',
                createdAt: '2024-07-10T08:00:00.000Z',
            },
            {
                id: 1,
                title: 'second',
                content: 'content',
                createdAt: '2024-07-11T14:30:00.000Z',
            },
            {
                id: 2,
                title: 'third',
                content: 'content',
                createdAt: '2024-07-12T21:45:00.000Z',
            },
        ],
    },
};
