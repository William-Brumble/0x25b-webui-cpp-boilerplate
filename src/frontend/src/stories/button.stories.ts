import type { Meta, StoryObj } from '@storybook/react-vite';

import { ButtonDemo } from './button';

const meta = {
    title: 'shadcn/Button',
    component: ButtonDemo,
    parameters: {
        layout: 'centered',
    },
    tags: ['autodocs'],
    argTypes: {},
} satisfies Meta<typeof ButtonDemo>;

export default meta;
type Story = StoryObj<typeof meta>;

export const Default: Story = {
    args: {},
};
