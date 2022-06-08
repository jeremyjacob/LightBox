<script lang="ts">
	import { onMount } from 'svelte'

	import { imageCanvas } from './websockets'
	const WIDTH = 30
	const HEIGHT = 15

	export let dragCallback = (x: number, y: number) => {}

	let canvas: HTMLCanvasElement
	let context: CanvasRenderingContext2D

	let dragging = false
	let dragCoords: [number, number] = [0, 0]
	let lastChangeCoords: [number, number] = [0, 0]

	onMount(() => {
		context = canvas.getContext('2d')
		canvas.width = WIDTH
		canvas.height = HEIGHT

		imageCanvas.subscribe((d) => {
			if (!d || !d.length) return
			let i = 0
			for (let x = 0; x < WIDTH; x++) {
				for (let y = 0; y < HEIGHT; y++) {
					context.fillStyle = `rgb(${d[i]}, ${d[i + 1]}, ${d[i + 2]})`
					context.fillRect(x, y, 1, 1)
					i += 3
				}
			}
		})
	})

	function dragListen(event: MouseEvent) {
		const bounds = canvas.getBoundingClientRect()

		let change: [number, number] = [
			(event.clientX - dragCoords[0]) / (bounds.width / WIDTH),
			(event.clientY - dragCoords[1]) / (bounds.height / HEIGHT),
		]

		change = change.map(Math.ceil) as [number, number]
		// check if change is different than lastChangeCoords
		const changeDif: [number, number] = [
			change[0] - lastChangeCoords[0],
			change[1] - lastChangeCoords[1],
		]
		if (changeDif[0] || changeDif[1]) dragCallback(...changeDif)
		lastChangeCoords = change
	}

	function dragStart(event: MouseEvent) {
		dragging = true
		dragCoords[0] = event.clientX
		dragCoords[1] = event.clientY
		document.addEventListener('mousemove', dragListen)
	}

	function dragEnd(event: MouseEvent) {
		dragging = false
		lastChangeCoords = [0, 0]
		document.removeEventListener('mousemove', dragListen)
	}
	document.addEventListener('mouseup', dragEnd)
</script>

<canvas on:mousedown={dragStart} bind:this={canvas} />

<style lang="scss">
	canvas {
		width: 100%;
		object-fit: cover;
		image-rendering: -moz-crisp-edges;
		image-rendering: -webkit-crisp-edges;
		image-rendering: pixelated;
		image-rendering: crisp-edges;
	}
</style>
