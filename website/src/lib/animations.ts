import { expoOut, linear, quintInOut, quintOut } from 'svelte/easing'
import { crossfade } from 'svelte/transition'

export const [send, receive] = crossfade({
	duration: (d) => Math.sqrt(d * 200),

	fallback(node, params) {
		const style = getComputedStyle(node)
		const transform = style.transform === 'none' ? '' : style.transform

		return {
			duration: 600,
			easing: quintOut,
			css: (t) => `
				transform: ${transform} scale(${t});
				opacity: ${t}
			`,
		}
	},
})

export function width(
	node,
	{ delay = 0, duration = 300, eased = quintOut, maxWidth = 100 }
) {
	const o = +getComputedStyle(node).marginBottom

	return {
		delay,
		duration,
		css: (t) => {
			const e = eased(t)
			return `
			width: calc(${Math.ceil(e * maxWidth)}% - 2px);
			margin-bottom: ${o * t}px;
			`
		},
	}
}

export function fadeIn(node, { delay = 0, duration = 300, eased = linear }) {
	const o = +getComputedStyle(node).opacity

	return {
		delay,
		duration,
		css: (t) => `opacity: ${eased(t) * o}`,
	}
}

export function fadeInUp(
	node,
	{ delay = 0, duration = 400, amount = 8, eased = quintOut }
) {
	const o = +getComputedStyle(node).opacity

	return {
		delay,
		duration,
		css: (t) => {
			const e = eased(t)
			return `
		opacity: ${e * (o / 2 + 0.5)};
		transform: translateY(${(1 - e) * amount}px);`
		},
	}
}
