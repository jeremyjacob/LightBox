import Home from './Home/Home.svelte'
import { state } from './state'
import { selectedText } from './Text/text'
import Text from './Text/Text.svelte'
import TextEditor from './Text/TextEditor.svelte'
import Visual from './Visual/Visual.svelte'

function textIndexValid() {
	let index: number
	selectedText.subscribe((v) => (index = v))()
	let total: number
	state.subscribe((v) => (total = v.text.length))()
	if (index < 0) return false
	if (index > total - 1) return false
	return true
}

const routes = [
	{
		name: '/',
		component: Home,
	},
	{
		name: 'text',
		component: Text,
		// nestedRoutes: [{ name: 'edit', component: TextEditor }],
	},
	{
		name: 'text/edit',
		onlyIf: { guard: textIndexValid, redirect: '/text' },
		component: TextEditor,
	},
	{
		name: 'visuals',
		component: Visual,
		// onlyIf: { guard: userIsAdmin, redirect: '/login' },
		// nestedRoutes: [{ name: 'edit', component: TextEditor }],
	},
]

export { routes }
