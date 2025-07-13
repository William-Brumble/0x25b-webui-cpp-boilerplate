import type { Meta, StoryObj } from '@storybook/react-vite';

import { CardDemo } from './card';

const meta = {
    title: 'shadcn/Card',
    component: CardDemo,
    parameters: {
        layout: 'centered',
    },
    tags: ['autodocs'],
    argTypes: {},
    args: {},
} satisfies Meta<typeof CardDemo>;

export default meta;
type Story = StoryObj<typeof meta>;

export const Default: Story = {
    args: {},
};
