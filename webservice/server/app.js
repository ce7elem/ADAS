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

app.use(require('express').static(__dirname + '/public'));

app.get('/', (req, res) => {
	res.sendFile(__dirname + '/index.html');
	console.log("New client");
});


http.listen(8888)