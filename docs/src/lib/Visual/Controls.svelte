<script lang="ts">
	import { state } from '../state';
	import { patch } from '../websockets';

	let lastUpdate = Date.now();
	$: {
		if (Date.now() - lastUpdate > 50) {
			lastUpdate = Date.now();
			patch({ speed: $state.speed, brightness: $state.brightness });
		}
	}
</script>

<div>
	<label for="speed">Speed</label>
	<input-group>
		<input
			type="range"
			id="speed"
			min={-4}
			max={4}
			step="0.1"
			bind:value={$state.speed}
		/>
		<input type="number" bind:value={$state.speed} />
	</input-group>
	<label for="brightness">Brightness</label>
	<input-group>
		<input
			type="range"
			id="brightness"
			min={0}
			max={150}
			bind:value={$state.brightness}
		/>
		<input type="number" bind:value={$state.brightness} />
	</input-group>
</div>

<style lang="scss">
	div {
		margin-bottom: 1rem;

		input-group {
			width: 100%;
			display: flex;
			input[type='range'] {
				flex: 1;
			}

			input[type='number'] {
				width: 1.7rem;
				font-size: 1rem;
				text-align: right;
				background-color: transparent;
				border: none;

				&:focus {
					outline: none;
				}
			}
		}

		label {
			text-transform: uppercase;
			font-weight: 600;
			font-size: 0.9rem;

			&[for='brightness'] {
				display: block;
				margin-top: 0.2rem;
			}
		}
	}

	input[type='range'] {
		filter: grayscale(90%) brightness(105%) saturate(200%);
	}

	input::-webkit-outer-spin-button,
	input::-webkit-inner-spin-button {
		-webkit-appearance: none;
		margin: 0;
	}
</style>
