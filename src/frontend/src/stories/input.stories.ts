import type { Meta, StoryObj } from '@storybook/react-vite';

import { InputDemo } from './input';

const meta = {
    title: 'shadcn/Input',
    component: InputDemo,
    parameters: {
        layout: 'centered',
    },
    tags: ['autodocs'],
    argTypes: {},
    args: {},
} satisfies Meta<typeof InputDemo>;

export default meta;
type Story = StoryObj<typeof meta>;

export const Default: Story = {
    args: {},
};
