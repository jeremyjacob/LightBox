import { defineConfig } from 'vite'
import { svelte } from '@sveltejs/vite-plugin-svelte'
import sveltePreprocess from 'svelte-preprocess'
import autoprefixer from 'autoprefixer'

// https://vitejs.dev/config/
const production = process.env.NODE_ENV === 'production'
export default defineConfig({
	plugins: [
		svelte({
			emitCss: production,
			preprocess: sveltePreprocess(),
			compilerOptions: {
				dev: !production,
			},

			hot: !production,
		}),
	],
	css: {
		postcss: {
			plugins: [autoprefixer()],
		},
	},
})
