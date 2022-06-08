<script lang="ts">
	import { navigateTo } from 'svelte-router-spa';
	import TextObject from './TextObject.svelte';
	import Title from '../Title.svelte';
	import { state } from '../state';
	import { editText, selectedText, TextType } from './text';
	import { width, fadeIn, fadeInUp } from '../animations';
	import Canvas from '../Canvas.svelte';

	export let currentRoute, params;

	const text = $state.text[$selectedText];
	let value = text.body;
	let color = '#' + text.color.toString(16);
	$: {
		text.color = parseInt(color.slice(1), 16) || 0;
	}

	const delay = 60;

	enum TextSources {
		Text,
		Time,
		Price,
		Weather,
		API,
	}

	function done() {
		save();
		navigateTo('/text');
	}

	let lastsave = 0;
	function save() {
		if (Date.now() - lastsave < 70) return;
		lastsave = Date.now();
		setTimeout(() => {
			editText($selectedText, text);
		}, 0);
	}

	function move(x: number, y: number) {
		console.log(x, y);
		text.x += x;
		text.y += y;
		save();
	}
</script>

<main>
	<Title>Text</Title>
	<hr in:width />
	<div class="info">
		<span class="bit left" in:fadeIn={{ duration: 140 }}
			>Editing Text #{$selectedText + 1}</span
		>
		<span
			class="bit right done"
			on:click={done}
			in:fadeIn={{ delay: 120, duration: 200 }}>Done</span
		>
	</div>
	<div class="texts">
		<TextObject
			message="“{text.body}”"
			clickable={false}
			index={$selectedText}
		/>
		<div class="parameters">
			{#if text.type === TextSources.Text}
				<div in:fadeInUp={{ delay: 0 }}>
					<label for="text-value"
						>Content
						<input
							type="text"
							id="text-value"
							bind:value={text.body}
							on:input={save}
						/></label
					>
				</div>
				<div in:fadeInUp={{ delay: delay * 1 }}>
					<label for="text-font"
						>Font
						<input
							type="number"
							id="text-font"
							bind:value={text.font}
							on:input={save}
							min="0"
						/></label
					>
				</div>
				<div in:fadeInUp={{ delay: delay * 2 }}>
					<label for="text-color"
						>Color
						<input
							type="color"
							id="text-color"
							bind:value={color}
							on:input={save}
							min="0"
						/></label
					>
				</div>
			{/if}
		</div>
	</div>
	<Canvas dragCallback={move} />
</main>

<style lang="scss">
	.parameters {
		margin-top: 1.2em;
		font-family: 'Work Sans', sans-serif;
		font-weight: 500;
		// display: grid;
		// grid-template-columns: repeat(2, 1fr);
		// row-gap: 0.5em;
		// align-items: center;

		--unfocused: rgb(46, 46, 46);
		input {
			display: block;
			font-size: 1.1em;
			margin-bottom: 1em;
			font-family: 'Roboto Mono';
			width: 100%;
			outline: 0;
			border: 2px solid white;
			padding: 0.21em;
			transition: 0.2s all;

			&:focus {
				border: 2px solid black;
			}
		}

		label {
			transition: 0.2s all;
			color: var(--unfocused);

			&:focus-within {
				color: black;
			}
		}
	}

	hr {
		margin-left: 0;
	}

	.info {
		margin-bottom: 1em;
	}

	.bit {
		font-weight: 600;
		font-size: 0.83em;
		text-transform: uppercase;
		// width: 5px;
		display: inline-block;
		overflow: hidden;
		white-space: nowrap;

		&.done {
			cursor: pointer;
			&:hover {
				text-decoration: underline;
			}
		}
	}

	.right {
		float: right;
	}
</style>
