<script lang="ts">
	import Visual from './lib/Visual/Visual.svelte';
	import { Router } from 'svelte-router-spa';
	import Navbar from './lib/Navbar.svelte';
	import { routes } from './lib/router';
	import './lib/websockets';
</script>

<!-- <Router {routes} /> -->
<!-- <Navbar /> -->
<Visual />

<style lang="scss">
</style>
