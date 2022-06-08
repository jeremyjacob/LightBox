<script lang="ts">
	import { fade } from 'svelte/transition';

	import Canvas from '../Canvas.svelte';

	import { patch } from '../websockets';

	export let name: string;
	export let index: number;
	export let selected: boolean;
	const thumbnail = `visual-textures/${name}.png`;
	const setVisual = () => patch({ pattern: index });
</script>

<div class="card" on:click={() => setVisual()} class:selected>
	<h2>{name}</h2>
	<div class="preview">
		{#if selected}
			<div class="canvas">
				<Canvas />
			</div>
			<!-- content here -->
			<!-- <div class="canvas"></div> -->
		{:else}
			<img src={thumbnail} alt="" draggable="false" out:fade />
		{/if}
		<div class="placeholder" />
	</div>
</div>

<style lang="scss">
	.card {
		box-shadow: 0px 6px 10px rgba(0, 0, 0, 0.02);
		border-radius: 12px;
		padding: 0.7em;
		cursor: pointer;
		transition: all 0.2s;
		background: white;
		outline: 2px solid transparent;

		&:hover {
			box-shadow: 0px 6px 10px rgba(0, 0, 0, 0.07);
		}

		&.selected {
			background: var(--dark);

			h2 {
				color: hsl(0, 0%, 100%);
			}
			img {
				aspect-ratio: 1/1;
			}
		}

		h2 {
			font-family: Work Sans;
			font-style: normal;
			font-weight: 600;
			font-size: 1.15rem;
			letter-spacing: -0.02em;
			color: hsl(0, 0%, 25%);
			transition: all 0.2s;
			margin-bottom: 0.5rem;
		}

		.preview {
			position: relative;

			img {
				position: relative;
				z-index: 10;
			}

			img,
			.canvas {
				position: absolute;
				width: 100%;
			}

			img,
			.placeholder,
			:global(canvas) {
				image-rendering: pixelated;
				aspect-ratio: 6 / 5;
				width: 100%;
				border-radius: 9px;
				object-fit: cover;
				object-position: top;
				transition: all 0.4s cubic-bezier(0.22, 1, 0.36, 1);
				box-shadow: rgba(50, 50, 93, 0.2) 0px 10px 20px -5px,
					rgba(0, 0, 0, 0.1) 0px 5px 16px -8px;
			}
		}
	}
</style>
