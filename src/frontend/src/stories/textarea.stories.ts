import type { Meta, StoryObj } from '@storybook/react-vite';

import { TextareaDemo } from './textarea';

const meta = {
    title: 'shadcn/Textarea',
    component: TextareaDemo,
    parameters: {
        layout: 'centered',
    },
    tags: ['autodocs'],
    argTypes: {},
    args: {},
} satisfies Meta<typeof TextareaDemo>;

export default meta;
type Story = StoryObj<typeof meta>;

export const Default: Story = {
    args: {},
};
