import { writable } from 'svelte/store';
import { state } from './state';
import { Buffer } from 'buffer';
import ReconnectingWebSocket from 'reconnecting-websocket';

const ip = '192.168.0.120';

let socket = new WebSocket(`ws://${ip}:80`);
let sse = new EventSource(`http://${ip}:80/stream`);

export let imageCanvas = writable<Uint8Array>();

const connect = () =>
	new Promise<void>((resolve, reject) => {
		if (!(socket?.readyState == socket?.OPEN)) {
			setInterval(() => {
				if (socket.readyState == socket.OPEN) resolve();
				else console.log('not yet', socket.readyState);
			}, 100);
		} else resolve();
	});
connect();

sse.addEventListener('message', (event) => {
	const decoded = Buffer.from(event.data, 'base64');
	// console.log(decoded)
	imageCanvas.set(decoded);
});

sse.addEventListener('open', (event) => {
	console.log('SSE Connected');
});

socket.addEventListener('open', (event) => {
	console.log('Connected to device');
	socket.binaryType = 'arraybuffer';
});

socket.addEventListener('close', () => {
	location.reload();
});

socket.addEventListener('message', (event) => {
	if (!event.data.startsWith('{')) return; // not a JSON message
	const json = JSON.parse(event.data);
	console.log(json);
	state.set(json);
});

export async function patch(patch: object) {
	const data = JSON.stringify(patch);
	console.log('Patchin data:', patch);
	await connect();
	socket.send(data);
}

window['msg'] = (data) => {
	socket.send(JSON.stringify(data));
};
