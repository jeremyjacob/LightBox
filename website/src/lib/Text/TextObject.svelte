<script lang="ts">
	import { navigateTo } from 'svelte-router-spa';
	import FlatTIcon from '../../assets/FlatTIcon.svelte';
	import { selectedText } from './text';
	import { send, receive, fadeInUp } from '../animations';

	export let message = '';
	export let clickable = true;
	export let index: number;

	function select() {
		selectedText.set(index);
		navigateTo('text/edit');
	}
</script>

<div
	class="card"
	class:clickable
	on:click={select}
	in:fadeInUp={{ delay: index * 60 }}
>
	<h2>{message}</h2>
	<span class="icon"><FlatTIcon /></span>
</div>

<style lang="scss">
	.card {
		box-shadow: 0px 6px 10px rgba(0, 0, 0, 0.06);
		border-radius: 12px;
		padding: 1em;
		margin-bottom: 0.7rem;
		background-color: white;
		/* display: flex; */
		/* flex-direction: row; */
		/* align-items: center; */
		/* margin-right: 1em; */
		cursor: default;
		transition: all 0.2s;

		&.clickable {
			cursor: pointer;
		}

		h2 {
			font-family: Work Sans;
			font-style: normal;
			font-weight: bold;
			font-size: 1.45rem;
			display: inline-flex;

			align-items: center;
			letter-spacing: -0.02em;

			color: #2c2c2c;
		}

		.icon {
			display: inline;
			float: right;

			display: flex;
			flex-direction: row;
			align-items: center;
			height: 1.45em;
			margin-right: 0.1em;
		}

		&:hover {
			box-shadow: 0px 6px 10px rgba(0, 0, 0, 0.08);
		}
	}
</style>
