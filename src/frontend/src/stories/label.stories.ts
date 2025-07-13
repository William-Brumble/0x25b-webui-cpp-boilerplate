import type { Meta, StoryObj } from '@storybook/react-vite';

import { LabelDemo } from './label';

const meta = {
    title: 'shadcn/Label',
    component: LabelDemo,
    parameters: {
        layout: 'centered',
    },
    tags: ['autodocs'],
    argTypes: {},
    args: {},
} satisfies Meta<typeof LabelDemo>;

export default meta;
type Story = StoryObj<typeof meta>;

export const Default: Story = {
    args: {},
};
