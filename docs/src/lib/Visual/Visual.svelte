<script lang="ts">
	import Controls from './Controls.svelte';
	import VisualCard from './VisualCard.svelte';
	import { state, patterns } from '../state';

	import Title from '../Title.svelte';
	import { onMount } from 'svelte';
	import { patch } from '../websockets';
	// export let currentRoute, params;

	onMount(() => patch({ streamLayer: 1 }));
</script>

<main>
	<Title>Visual</Title>
	<Controls />
	<div class="visual-list">
		{#each patterns as tuple}
			{@const visual = tuple[1]}
			{@const index = tuple[0]}
			<VisualCard
				name={visual}
				{index}
				selected={index == $state.pattern}
			/>
		{/each}
		<span style="height: 1.5em;" />
	</div>
</main>

<style lang="scss">
	.visual-list {
		display: grid;
		grid-template-columns: repeat(2, 1fr);
		grid-auto-columns: 1fr;
		grid-auto-rows: 1fr;
		gap: 1.3em;
		padding: 1em;
		margin: -1em;

		overflow-y: scroll;
		height: calc(100vh - 10.3rem);
		scrollbar-width: none; /* Firefox */
		&::-webkit-scrollbar {
			display: none;
		}
	}

	@media (min-width: 700px) {
		.visual-list {
			grid-template-columns: repeat(4, 1fr);
		}
	}

	@media (min-width: 1000px) {
		.visual-list {
			grid-template-columns: repeat(5, 1fr);
		}
	}

	@media (min-width: 1330px) {
		.visual-list {
			grid-template-columns: repeat(7, 1fr);
		}
	}

	@media (min-width: 1330px) {
		.visual-list {
			grid-template-columns: repeat(7, 1fr);
		}
	}
</style>
