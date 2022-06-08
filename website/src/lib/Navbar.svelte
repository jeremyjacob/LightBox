<script lang="ts">
	import { navigateTo } from 'svelte-router-spa';
	import PatternsIcon from '../assets/PatternsIcon.svelte';
	import SettingsIcon from '../assets/SettingsIcon.svelte';
	import TextIcon from '../assets/TextIcon.svelte';
</script>

<nav>
	<!-- <span on:mousedown={() => navigateTo('text')}><TextIcon /></span> -->
	<span on:mousedown={() => navigateTo('visuals')}><PatternsIcon /></span>
	<!-- <span on:mousedown={() => navigateTo('settings')}><SettingsIcon /></span> -->
</nav>

<style lang="scss">
	nav {
		position: absolute;
		width: 100%;
		height: 6rem;
		bottom: 0;
		z-index: 20;

		background: var(--dark);
		box-shadow: 0px 3px 11px rgba(0, 0, 0, 0.12);
		$radius: 10px;
		border-top-right-radius: $radius;
		border-top-left-radius: $radius;

		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		display: flex;
		gap: 10vw;
	}

	span {
		transform: scale(1.1);
		transition: 0.2s;
		cursor: pointer;

		&:hover {
			transform: scale(1.17);
		}
	}
</style>
