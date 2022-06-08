<script lang="ts">
	import TextObject from './TextObject.svelte';
	import Title from '../Title.svelte';
	import { defaultTextObject, state } from '../state';
	import { updateText } from './text';
	import { patch } from '../websockets';
	import { onMount } from 'svelte';

	export let currentRoute, params;

	enum TextSources {
		Text,
		Time,
		Stock,
		Crypto,
		Weather,
	}

	function add() {
		if (!$state.text) $state.text = [defaultTextObject];
		else $state.text = [defaultTextObject, ...$state.text];
		console.log('444', $state.text);
		updateText();
	}

	onMount(() => patch({ streamLayer: 2 }));
</script>

<main>
	<Title>Text</Title>
	<div class="texts">
		<div class="add" on:click={add}><span>Add Text</span></div>
		{#if $state.text}
			{#each $state.text as text, index}
				{#if text.type == TextSources.Text}
					<TextObject message="“{text.body}”" {index} />
					<!-- {:else if otherCondition} -->
				{:else}{/if}
			{/each}
		{/if}
	</div>
</main>

<style lang="scss">
	.add {
		cursor: pointer;
		font-size: 1.3rem;

		span:hover {
			text-decoration: underline;
		}
	}
</style>
