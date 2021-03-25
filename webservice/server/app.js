const app = require('express')();
const http = require('http').createServer(app);
var io = require('socket.io')(http, {});

const fs = require('fs');
const wstream = fs.createWriteStream('/tmp/rcontroller')

io.on('connection', (socket) => {

	console.log('new connection')

	socket.on('input', function (data) {
		console.log(data)

		wstream.write(`${data}\n`)
	});

});


http.listen(8888)