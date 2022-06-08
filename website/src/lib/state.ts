import { writable } from 'svelte/store';

export const defaultTextObject = {
	type: 0,
	font: 0,
	x: 0,
	y: 0,
	enabled: true,
	color: 16777215,
	body: 'Edit me!',
};
// prettier-ignore
export const state = writable(
	{
		"brightness": 30,
		"text": [],
		"speed": 1,
		"pattern": 1
	}
)

export const patterns: [number, string][] = [
	[15, 'Off'],
	[0, 'Alien Zoom'],
	[1, 'Ameoba'],
	[2, 'Andromeda'],
	[3, 'Block Puzzle'],
	[4, 'Conways Life'],
	[5, 'Cross Hatch'],
	[6, 'Energy Balls'],
	[7, 'Fire Rings'],
	[8, 'Fireplace'],
	[9, 'Galaxy'],
	[10, 'Geometry'],
	[11, 'Icy Noise'],
	[12, 'Infinity Sign'],
	[13, 'Living'],
	[14, 'Lost Lands'],
	[16, 'Oscilloscope'],
	[17, 'Plasm'],
	[18, 'Plasma Waves'],
	[19, 'Pool'],
	[20, 'Rainbow'],
	[21, 'Smoke Curtains'],
	// [22, 'Solid Color'],
	[22, 'Spirits'],
	[23, 'Strobe'],
	[24, 'The Matrix'],
];
