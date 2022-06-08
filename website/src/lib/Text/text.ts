import { writable } from 'svelte/store';
import { state } from '../state';
import { patch } from '../websockets';

export const selectedText = writable(-1);

export type TextType = {
	type: number;
	font: number;
	x: number;
	y: number;
	enabled: boolean;
	color: number;
	body: string;
};

type TextPartial = {
	[P in keyof TextType]?: TextType[P];
};

export function editText(index: number, data: TextPartial) {
	let texts: TextType[];
	state.subscribe((v) => (texts = v.text))();
	if (!texts) return;
	texts[index] = Object.assign(texts[index], data);
	patch({ text: texts });
}

export function updateText() {
	state.subscribe(({ text }) => patch({ text }))();
}
