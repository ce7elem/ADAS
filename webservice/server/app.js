const app = require('express')();
const http = require('http').createServer(app);
var io = require('socket.io')(http);

const fs = require('fs');
const wstream = fs.createWriteStream('/tmp/myfifo')

io.on('connection', function (socket) {

	console.log('new connection')

	socket.on('forward', function (data) {
		console.log("forward")

		wstream.write(`forward\n`)
	});

	socket.on('right', function (data) {
		console.log("right")

		wstream.write(`right\n`)
	});

	socket.on('left', function (data) {
		console.log("left")

		wstream.write(`left\n`)
	});

	socket.on('backward', function (data) {
		console.log("backward")

		wstream.write(`backward\n`)
	});

	socket.on('end', function (data) {
		console.log("end")

		wstream.write(`end\n`)
	});
});


app.use(function(req, res, next) {
	res.header("Access-Control-Allow-Origin", "*");
	res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
	next();
});

app.use(require('express').static(__dirname + '/public'));

app.get('/', (req, res) => {
	res.sendFile(__dirname + '/index.html');
	console.log("New client");
});


http.listen(80, function(){
	console.log('listening on *:80');
});
