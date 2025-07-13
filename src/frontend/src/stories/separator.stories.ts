import type { Meta, StoryObj } from '@storybook/react-vite';

import { SeparatorDemo } from './separator';

const meta = {
    title: 'shadcn/Separator',
    component: SeparatorDemo,
    parameters: {
        layout: 'centered',
    },
    tags: ['autodocs'],
    argTypes: {},
    args: {},
} satisfies Meta<typeof SeparatorDemo>;

export default meta;
type Story = StoryObj<typeof meta>;

export const Default: Story = {
    args: {},
};
