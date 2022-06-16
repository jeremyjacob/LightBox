if (location.host == 'satislux.com') {
	location.href = 'http://192.168.86.120';
}

import App from './App.svelte';
import './global.scss';

const app = new App({
	target: document.getElementById('app'),
});

export default app;
