<script lang="ts">
	import Art from './Art.svelte';
	import Title from '../Title.svelte';
	import Canvas from '../Canvas.svelte';
	import { patch } from '../websockets';
	import { onMount } from 'svelte';

	onMount(() => patch({ streamLayer: 1 }));
</script>

<main>
	<Title size="3.3rem">Satis</Title>
	<Canvas />
</main>
<Art />

<style lang="scss">
	h1 {
		font-family: Plaster;
		font-style: normal;
		font-weight: normal;
		font-size: 3.3rem;
		line-height: 62px;
		background: linear-gradient(
			279.14deg,
			hsl(0, 0%, 50%) 0%,
			hsl(0, 0%, 3%) 100%
		);
		background-clip: text;
		-webkit-background-clip: text;
		-webkit-text-fill-color: transparent;
	}
</style>
