<script lang="ts">
	export let size = '2.7rem'
</script>

<h1 style="font-size:{size}"><slot /></h1>

<style lang="scss">
	h1 {
		font-family: 'Roboto Slab';
		font-style: normal;
		font-weight: 500;
		// background: linear-gradient(
		// 	279.14deg,
		// 	hsl(0, 0%, 60%) 0%,
		// 	hsl(0, 0%, 3%) 100%
		// );
		color: black;
		margin-bottom: 0.3em;
		// background-clip: text;
		// -webkit-background-clip: text;
		// -webkit-text-fill-color: transparent;
	}
</style>
