import type { Meta, StoryObj } from '@storybook/react-vite';

import { BadgeDemo } from './badge';

const meta = {
    title: 'shadcn/Badge',
    component: BadgeDemo,
    parameters: {
        layout: 'centered',
    },
    tags: ['autodocs'],
    argTypes: {},
    args: {},
} satisfies Meta<typeof BadgeDemo>;

export default meta;
type Story = StoryObj<typeof meta>;

export const Default: Story = {
    args: {},
};
